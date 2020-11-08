#ifndef LISTS_H
#define LISTS_H 

#include <GLFW/glfw3.h>

typedef struct float_list_struct * float_list; 
typedef struct int_list_struct * int_list;
typedef struct double_list_struct * double_list; 

void float_list_init (float_list  list, unsigned int initsize);
void float_list_free (float_list  list);
void float_list_add (float_list  list, float point);
unsigned int float_list_filled(float_list list); 
unsigned int float_list_size(float_list list); 
float float_list_point(float_list list, unsigned int i); 
float* float_list_points(float_list list);

void int_list_init (int_list  list, unsigned int initsize);
void int_list_free (int_list  list);
void int_list_add (int_list  list, unsigned int point);
unsigned int int_list_point(int_list list, unsigned int i); 
unsigned int int_list_filled(int_list list);
unsigned int* int_list_points(int_list list);

void double_list_init (double_list  list, unsigned int initsize);
void double_list_free (double_list  list);
void double_list_add (double_list  list, double point);
unsigned int double_list_filled(double_list list); 
unsigned int double_list_size(double_list list); 
double* double_list_points(double_list list); 
double double_list_point(double_list list, unsigned int i); 
#endif 
