//
// 2021 Fall - Cloud Computing (01)
// Homework #2: Pthread Programming
//
// Copyright (c) Prof. Jaehyeong Sim
// Department of Computer Science and Engineering, Ewha Womans University
//

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#define STR_SIZE 128

char original_string[STR_SIZE] = "Computer, Ewha";
char result_string[STR_SIZE] = "";
int global_index = 0;

typedef struct {
	char string_buffer[STR_SIZE];
	char target[STR_SIZE];
	int index;
	pthread_mutex_t lock;
}arg_struct;

arg_struct* arg_init() {
	arg_struct* arg;
	arg = (arg_struct*)malloc(sizeof(arg_struct));
	arg->index = 0;
	pthread_mutex_init(&arg->lock, NULL);

	return arg;
}

void* get_str(void* args)
{
	arg_struct* arg_data = (arg_struct*)args;
	for (int i = 0; i < strlen(arg_data->target); i++) {
		//for(int j=0; j<10000000; j++);
		find_char(arg_data);
	}
	if (strcmp(arg_data->string_buffer, arg_data->target) != 0)
	{
		printf("*** Error : Thread %d cannot find the string [ %s ] from the orginal string", pthread_self(), arg_data->target);
		exit(NULL);
	}
	printf("*** Thread %d made a string : %s\n", pthread_self(), arg_data->string_buffer);
	pthread_exit(NULL);
}

void find_char(arg_struct* arg_data) {
	pthread_mutex_lock(&arg_data->lock);
	for (int i = 0; i < strlen(original_string); i++)
	{
		if (arg_data->target[arg_data->index] == original_string[i])
		{
			arg_data->string_buffer[arg_data->index] = original_string[i];
			printf("Iteration %d :  thread %d       got %c  from    %s\n", global_index, pthread_self(), original_string[i], original_string);
			original_string[i] = '_';
			arg_data->index++;
			global_index++;
			break;
		}
	}
	pthread_mutex_unlock(&arg_data->lock);
}



int main() {

	char target_string1[STR_SIZE] = "Ewha";
	char target_string2[STR_SIZE] = "Computer";

	pthread_t threads[2];

	arg_struct* arg1;
	arg_struct* arg2;

	arg1 = arg_init();
	arg2 = arg_init();

	strcpy(arg1->target, target_string1);
	strcpy(arg2->target, target_string2);


	printf("*** The initial original string:\t\t%s\n", original_string);

	pthread_create(&threads[0], NULL, get_str, (void*)arg1);
	pthread_create(&threads[1], NULL, get_str, (void*)arg2);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	printf("*** Final original string:\t\t\t%s\n", original_string);
	return 0;

}
