#include <stdlib.h>
#include <stdio.h> 
#include <math.h>
#include <GL/glew.h> 
#include <GLFW/glfw3.h> 
#include <gl-matrix.h> 


GLuint vshader, fshader;
GLuint program; 
void loadShaders(void); 
void loadProgram(void); 


void loadShaders(void)
{
	FILE *vs, *fs; 
	char *v_shader_source, *frag_shader_source; 
	
	GLint val; 
	vs = fopen("vs.glsl", "r"); 
	fs = fopen("fs.glsl", "r");
	
	int size; 
	fseek(vs, 0L, SEEK_END); 
	size = ftell(vs); 
	v_shader_source = malloc(size + 1); 
	fseek(vs, 0L, SEEK_SET); 
	fread(v_shader_source, 1, size, vs);

	fseek(fs, 0L, SEEK_END);
	size = ftell(fs);
	frag_shader_source = malloc(size + 1); 
	fseek(fs, 0L, SEEK_SET);
	fread(frag_shader_source, 1, size, fs); 

	fclose(vs);
	fclose(fs); 

	vshader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vshader, 1,  (const char* const*) &v_shader_source, NULL); 
	glCompileShader(vshader); 
	
	glGetShaderiv(vshader, GL_COMPILE_STATUS, &val);
	if(val == GL_FALSE){
		char info[1024]; 
		glGetShaderInfoLog(vshader, 1024, NULL, info);
		puts(info);
	}

	fshader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fshader, 1, (const char* const*) &frag_shader_source, NULL); 
	glCompileShader(fshader); 


	glGetShaderiv(fshader, GL_COMPILE_STATUS, &val);
	if(val == GL_FALSE){
		char info[1024]; 
		glGetShaderInfoLog(fshader, 1024, NULL, info);
		puts(info);
	}

} 


void loadProgram()
{
	program = glCreateProgram(); 
	glAttachShader(program, vshader);
	glAttachShader(program, fshader); 
	glLinkProgram(program);
	
	GLint val; 
	glGetProgramiv(program, GL_LINK_STATUS, &val); 
	if(val == GL_FALSE){
		char info[1024];
		glGetProgramInfoLog(program, 1024, NULL, info);
		puts(info);
	}

	glUseProgram(program);
}
