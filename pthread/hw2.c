#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#define STR_SIZE 128

char original_string[STR_SIZE] = "apple, banana";
//int index = 0;
char result_string[STR_SIZE] = "";
int global_index = 0;


//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

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

void* get_str(void *args)
{
	////////////////////////
	// You need to fill here
	////////////////////////
	
	arg_struct* arg_data = (arg_struct*)args;
	for (int i = 0; i < strlen(arg_data->target); i++) {
		//for(int j=0; j<10000000; j++);
		//char found_char = find_char(arg_struct);
		if(arg_data->target[i]=='\0' )
		{
			printf("Cannot find\n");
			exit(NULL);
		
		}
//		else 
//		{
//		printf("Iteration %d :  thread %d       got %c  from    %s\n",global_index, pthread_self(), found_char, original_string);
	
//	}
	}
	if (strcmp(arg_data->string_buffer, arg_data->target)!=0)	
	{
	//	printf("result : %d\n", strncmp(arg_data->string_buffer, arg_data->target, strlen(arg_data->target)));
	//	printf("%d\n	%d\n", strlen(arg_data->string_buffer), strlen(arg_data->target));
	//	printf("%s\n", arg_data->string_buffer);
	//	printf("%s\n", arg_data->target);
		printf("*** Error : Thread %d cannot find the string [ %s ] from the orginal string", pthread_self(), arg_data->target);
			//printf("thread %d: c[%] at %d\n", tid, c[i], i);
		exit(NULL);
	}
	printf("*** Thread %d made a string : %s\n", pthread_self(), arg_data->string_buffer);
	pthread_exit(NULL);
}

void find_char(arg_struct* arg_data) {
	pthread_mutex_lock(&arg_data->lock);
	//char* data_string = (char*)data;
	//int is_found = 0;
	char found_char = '\0';
	for (int i = 0; i < strlen(original_string); i++)
	{
		if (arg_data->target[arg_data->index] == original_string[i])
		{
		arg_data->string_buffer[arg_data->index] = original_string[i];
		printf("Iteration %d :	thread %d	got %c	from	%s\n",global_index, pthread_self(), original_string[i], original_string);
		found_char = original_string[i];
		original_string[i] = '_';
		arg_data->index++;
		global_index++;
		//is_found = 1;
		break;
		}
		//if(i==strlen(original_string)){
                //	printf("Cannot find a string\n");
		//	exit(NULL);
	 	// }
		

		}


	pthread_mutex_unlock(&arg_data->lock);
     	return found_char;	
}

int main() {

	char target_string1[STR_SIZE] = "banana";
	char target_string2[STR_SIZE] = "apple";
	pthread_t threads[2];
	arg_struct* arg1;
	arg_struct* arg2;
	arg1 = arg_init();
	arg2 = arg_init();
	strcpy(arg1->target, target_string1);
	strcpy(arg2->target, target_string2);
	

	printf("*** The initial original string:\t\t%s\n", original_string);

	////////////////////////
	// You need to fill here
	////////////////////////
	pthread_create(&threads[0], NULL, get_str, (void*)arg1);
	pthread_create(&threads[1], NULL, get_str, (void*)arg2);

	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	printf("*** Final original string:\t\t\t%s\n", original_string);
	return 0;

}
