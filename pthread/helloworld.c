#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5


void* printhello(void* t){
	long tid;
	tid = (long)t;
	//if(tid ==1 ){
	//	for(int i=0; i<800000; i++);
	//}
	printf("Hello World! This is %ld\n", t);
	pthread_exit(NULL);
}

int main() {
	pthread_t threads[NUM_THREADS];
	int rc;
	long t;

	for(t=0; t<NUM_THREADS;t++){
		rc = pthread_create(&threads[t], NULL, printhello, (void *)t);
		if(rc){
			printf("Error\n");
			pthread_exit(NULL);
		}
	
	}
	for(t=0; t<NUM_THREADS;t++)
		pthread_join(threads[t], NULL);
	printf("main finished\n");
	return 0;
}
