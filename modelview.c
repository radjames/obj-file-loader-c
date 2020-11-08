#include <GLFW/glfw3.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include "modelview.h" 
#include "lists.h"

float_list verts; 
float_list norms; 
float_list orderedverts; 
float_list orderednorms; 
int_list faces; 
int_list points_per_draw; 

int *readObj(FILE *fstream)
{
	verts = malloc(sizeof(float_list));
 	norms = malloc(sizeof(float_list)); 
	faces = malloc(sizeof(int_list));
	orderedverts 		= 	malloc(sizeof(float_list));
	orderednorms 		= 	malloc(sizeof(float_list)); 
	points_per_draw = 	malloc(sizeof(int_list)); 

	float_list_init(verts, 100); 
	float_list_init(norms, 100); 
	int_list_init(faces, 100); 
	int_list_init(points_per_draw, 100); 

	char *line = NULL; 
	size_t size = 0; 

	while(getline(&line, &size, fstream) != -1)
	{
		if(strncmp(line, "v ", 2) == 0)
		{
			char *chunk = strchr(line + 2, (int) ' '); 
			char *counter = line + 2; 
			char number[35]; 

			while(counter < (line + strlen(line)))
			{
				chunk = strchr(counter, (int) ' '); 
				if(chunk == NULL)
					chunk = line + strlen(line); 
				
				size = (size_t) (chunk - counter); 
				memcpy(&number, counter, size); 
				number[size] = '\0'; 
				float no = (float) atof((const char*) &number);
				float_list_add(verts, no);
				counter += size + 1; 					
			}
		}
		else if( strncmp(line, "vn ", 3) == 0)
		{
				
			char *chunk = strchr(line + 3, (int) ' '); 
			char *counter = line + 3; 
			char number[35]; 

			while(counter < (line + strlen(line)))
			{
				chunk = strchr(counter, (int) ' '); 
				if(chunk == NULL)
					chunk = line + strlen(line); 
				
				size = (size_t) (chunk - counter); 
				memcpy(&number, counter, size); 
				number[size] = '\0'; 
				float no = (float) atof((const char*) &number);
				float_list_add(norms, no);
				counter += size + 1; 					
			}
		} 
		else if ( strncmp(line, "f ", 2) == 0) 
		{
			char number[35]; 
			char *counter = line + 2; 
			char *chunk = line; 	

			while(chunk != line + strlen(line))
			{
				chunk = strchr(counter, (int) ' ');
				if(chunk == NULL)
					chunk = line + strlen(line);

				unsigned int i = 1;		
				unsigned int pointcounter = 0; 

				while(counter < chunk)
				{
					char *dig = strchr(counter, (int) '/');
					
					if(dig == NULL)
						dig = line + strlen(line);
					else if( dig > chunk)
						dig = chunk;
					
					size = (int) (dig - counter); 
					memcpy(&number, counter, size);
					number[size] = '\0';
					
					unsigned int no = atoi((const char *) &number); 
					unsigned int start  = (no - 1) * 3; 
					if(i == 1)
					{
						float_list_add(orderedverts, 
								float_list_point(verts,start));
						float_list_add(orderedverts, 
								float_list_point(verts,start + 1));
						float_list_add(orderedverts, 
								float_list_point(verts,start + 2));
					}
					else if (i == 3)
					{
						float_list_add(orderednorms,
								float_list_point(norms, start));
						float_list_add(orderednorms,
								float_list_point(norms, start +1)); 
						float_list_add(orderednorms,
								float_list_point(norms, start +2)); 
					}	
					
					i++; 
					counter += size + 1;  
					pointcounter++; 
				}
				int_list_add(points_per_draw, pointcounter); 
			}
		}
	}

	return 0; 	
} 

