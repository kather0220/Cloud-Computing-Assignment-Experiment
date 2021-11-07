#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

int balance = 500;
pthread_mutex_t mutexbalance = PTHREAD_MUTEX_INITIALIZER;

void* deposit(void* sum){
	pthread_mutex_lock(&mutexbalance);
	int currbalance = balance;
	currbalance+=(long)sum;
	balance=currbalance;
	pthread_mutex_unlock(&mutexbalance);
}

void* withdraw(void* sum){
	pthread_mutex_lock(&mutexbalance);
	int currbalance = balance;
	for(int i=0; i<1000000; i++);
	if(currbalance>0)
		currbalance-=(long)sum;
	for(int i=0; i<1000000; i++);
	balance=currbalance;
	pthread_mutex_unlock(&mutexbalance);

}

int main() {
	pthread_t threads[2];
	int rc;
	long t;
	int a = 2;
	pthread_create(&threads[1], NULL, withdraw, (void*)50);
	pthread_create(&threads[0], NULL, deposit, (void*)100);
	
	
	//for(int i=0; i<10000000; i++) a = a*a;
//	pthread_join(threads[0], NULL);
//	pthread_join(threads[1], NULL);

	printf("balance = %d\n", balance);
//	for(t=0; t<NUM_THREADS;t++)
//		pthread_join(threads[t], NULL);
//	printf("main finished\n");
	return 0;
}
