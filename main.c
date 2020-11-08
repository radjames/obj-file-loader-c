#include <stdlib.h> 
#include <stdio.h> 
#include <math.h> 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl-matrix.h>
#include "modelview.h" 

#include "lists.h" 
#include "loadstuff.h" 

FILE *objfile; 
typedef unsigned int uint; 

extern GLuint vshader, fshader;
extern GLuint program; 
extern float_list orderednorms, orderedverts; 
extern float_list verts, norms; 
extern int_list faces, points_per_draw; 

static GLFWwindow *window; 
static double camera_pos[3] = {-11.815452L, 0L, 275.716L}; 
static double camera_angle = 0.048; 
const double incrementpress = 6; 

int main(void); 
void mainLoop(void); 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); 

void mainLoop(void)
{
	GLint modelview_loc, perspective_loc, camera_loc, vpos_loc, vcol_loc, vnorm_loc; 


	vpos_loc = glGetAttribLocation(program, "vpos");
	vcol_loc = glGetAttribLocation(program, "vcol"); 
	vnorm_loc= glGetAttribLocation(program, "vnorm");

	modelview_loc = 		glGetUniformLocation(program, "modelview");
	perspective_loc = 	glGetUniformLocation(program, "perspective"); 
	camera_loc = 				glGetUniformLocation(program, "camera"); 
	
	GLuint vbuffer, facebuffer, normbuffer; 

	glGenBuffers(1, &vbuffer); 
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * float_list_filled(orderedverts), 
		float_list_points(orderedverts), GL_STATIC_DRAW); 
	
	glEnableVertexAttribArray(vpos_loc);
	glVertexAttribPointer(vpos_loc, 3, GL_FLOAT, GL_FALSE, 
			sizeof(float) * 3, (void*) 0);
	
	glGenBuffers(1, &normbuffer); 
	glBindBuffer(GL_ARRAY_BUFFER, normbuffer); 
	glBufferData(GL_ARRAY_BUFFER, float_list_filled(orderednorms) * sizeof(float), 
			float_list_points(orderednorms), GL_STATIC_DRAW); 
	glEnableVertexAttribArray(vnorm_loc);
	glVertexAttribPointer(vnorm_loc, 3, GL_FLOAT, GL_FALSE, 
			sizeof(float) * 3 , (void *) 0); 

	glfwSwapInterval(1); 
	glfwSetKeyCallback(window, key_callback);		
	vec3_t eye, centre, up; 
	mat4_t modelview, perspective, camera; 

	eye =vec3_create(NULL);
	centre = vec3_create(NULL); 
	up = vec3_create(NULL);
	modelview = mat4_create(NULL); 
	perspective = mat4_create(NULL); 
	camera = mat4_create(NULL); 

	double tick = 0.00; 

	up[0] = 0L;
	up[1] = 1L;
	up[2] = 0L; 
	
	centre[0] = 0L; 
	centre[1] = 0L; 
	centre[2] = 0L; 
	
	glEnable(GL_CULL_FACE); 
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW); 
	// Turn on wireframe mode
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	while(!glfwWindowShouldClose(window))
	{
		eye[0] = camera_pos[0]; 
		eye[1] = camera_pos[1] + 0.01; 
		eye[2] = camera_pos[2]; 

		centre[2] = eye[2] - cos(camera_angle); 
		centre[0] = eye[0] + sin(camera_angle); 
		centre[1] = 0.01; 
		tick += 0.01;

		int width, height; 
		double aspect; 

		glfwGetFramebufferSize(window, &width, &height); 
		aspect = (double) width / (double) height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			
		mat4_perspective(90 * (M_PI / 180), aspect, 0.1, 400.0, perspective); 
		mat4_lookAt(eye, centre, up, camera);
		mat4_identity(modelview);
		mat4_rotateY(modelview, tick, modelview); 

		float fmod[16], fper[16], fcamera[16]; 
		int i; 
		
		for(i = 0; i < 16; i++)
		{
			fmod[i] = (float) modelview[i];
			fper[i] = (float) perspective[i];
			fcamera[i] = (float) camera[i]; 
		}
		
		glUniformMatrix4fv(modelview_loc, 1, GL_FALSE, (const GLfloat*) &fmod);
		glUniformMatrix4fv(perspective_loc, 1, GL_FALSE, (const GLfloat*) &fper);
		glUniformMatrix4fv(camera_loc, 1, GL_FALSE, (const GLfloat*) &fcamera);
		glDrawArrays(	GL_TRIANGLES, 0, (int) float_list_filled(orderedverts)); 
		glfwSwapBuffers(window);
		glfwPollEvents(); 
	}
	glfwTerminate(); 
} 
int main(void)
{ 

	GLuint v_buffer, norm_buffer, color_buffer; 
	objfile = fopen("monkey.obj", "r"); 

	if(objfile == NULL)
	{ 
		puts("Error -> couldn't read the file"); 
		return EXIT_FAILURE; 
	} 

	readObj(objfile); 
	fclose(objfile);
	
	if(!glfwInit())
		exit(EXIT_FAILURE); 

	window = glfwCreateWindow(640, 480,
			".obj File Loader Mini", NULL, NULL); 

	if(!window){ 
		glfwTerminate(); 
		puts("Error -> could not open window"); 
		exit(EXIT_FAILURE); 
	} 

	glfwMakeContextCurrent(window); 
	GLenum err = glewInit();

	if(err != GLEW_OK)
	{ 
		printf("Error -> %s \n", glewGetErrorString(err)); 
		glfwTerminate(); 
		exit(EXIT_FAILURE); 
	} 

	loadShaders(); 
	loadProgram();
	mainLoop(); 

	float_list_free(norms);
	float_list_free(verts);
	float_list_free(orderedverts);
	float_list_free(orderednorms);
	int_list_free(faces);
	int_list_free(points_per_draw);
	return EXIT_SUCCESS;
} 

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){ 
	if(action == GLFW_PRESS || action == GLFW_REPEAT){
		switch(key){
			case GLFW_KEY_W:
				camera_pos[0] += incrementpress * sin(camera_angle); 
				camera_pos[2] -= incrementpress * cos(camera_angle); 
				break; 
			case GLFW_KEY_S: 
				camera_pos[2] += incrementpress * cos(camera_angle);
				camera_pos[0] -= incrementpress * sin(camera_angle); 
				break; 
			case GLFW_KEY_A: 
				camera_angle -= 0.001; 
				break; 
			case GLFW_KEY_D: 
				camera_angle += 0.001; 
				break;
		}
	} 
} 
