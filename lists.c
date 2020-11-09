#include <stdlib.h>
#include "lists.h" 

struct float_list_struct 
{ 
	float *points; 
	unsigned int size; 
	unsigned int filled;
};

struct int_list_struct
{
	unsigned int *points; 
	unsigned int size; 
	unsigned int filled; 
}; 

struct double_list_struct 
{
	double *points; 
	unsigned int size; 
	unsigned int filled; 
};

unsigned int* int_list_points(int_list list)
{
	return list->points; 
}

float* float_list_points(float_list list)
{
	return list->points; 
}

double* double_list_points(double_list list)
{
	return list->points; 
}

void float_list_init (float_list list, unsigned int initsize) 
{
	list->size = initsize; 
	list->filled = 0; 
	list->points = malloc(initsize * sizeof(float)); 
} 

void double_list_init (double_list list, unsigned int initsize) 
{
	list->size = initsize; 
	list->filled = 0; 
	list->points = malloc(initsize * sizeof(double)); 
}


inline void float_list_add (float_list list, float point)
{
	if(list->filled == list->size){
		list->points = realloc(list->points, 
				sizeof(float) * (list->size + 100));
		list->size += 100; 
	}

	list->points[list->filled] = point;
	list->filled++;
}

inline void double_list_add (double_list list, double point)
{ 
	
	if(list->filled == list->size){
		list->points = realloc(list->points, 
				sizeof(double) * (list->size + 100));
		list->size += 100; 
	}

	list->points[list->filled] = point;
	list->filled++;
} 

unsigned int double_list_filled(double_list list) 
{
	return list->filled; 
} 

unsigned int double_list_size(double_list list) {
	return list->size; 
} 

double double_list_point(double_list list, unsigned int i)
{
	return list->points[i]; 
}

void double_list_free(double_list list)
{
	free(list->points);
	free(list);
}
unsigned int float_list_filled(float_list list)
{
	return list->filled; 
}

unsigned int float_list_size(float_list list) 
{
	return list->size; 
}

float float_list_point(float_list list, unsigned int i)
{
	return list->points[i];
}

void float_list_free (float_list list)
{
	free(list->points); 
	free(list);
}

void int_list_init (int_list list, unsigned int initsize)
{
	list->size = initsize; 
	list->filled = 0; 
	list->points = malloc(initsize * sizeof(int)); 
} 

inline void int_list_add (int_list list, unsigned int point)
{
	if(list->filled == list->size){
		list->points = realloc(list->points, sizeof(int) * (list->size + 100));
		list->size += 100; 
	}
	list->points[list->filled] = point;
	list->filled++;
}

void int_list_free (int_list list)
{
	free(list->points); 
	free(list);
}

unsigned int int_list_point(int_list list, unsigned int i)
{
	return list->points[i];
}

unsigned int int_list_filled(int_list list)
{
	return list->filled; 
}


unsigned int int_list_size(int_list list)
{
	return list->size; 
}


