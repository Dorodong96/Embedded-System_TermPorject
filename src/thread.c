#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "utils.h"
int dust_data; // global parameter
//char weather_data[20];

void *dust_thread();
//void *weather_thread();

// use thread for web crawling to get pollution
void use_thread(void)
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	res = pthread_create(&a_thread, NULL, dust_thread, NULL);

	if (res != 0) {
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}
	res = pthread_join(a_thread, &thread_result);

	if (res != 0) {
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);
	}
}


/*
void use_thread(void)
{
	int res1, res2;
	pthread_t a_thread1, a_thread2;
	void *thread_result;

	res1 = pthread_create(&a_thread1, NULL, dust_thread, NULL);
	res2 = pthread_create(&a_thread2, NULL, weather_thread(), NULL);

	if ((res1 != 0)||(res2 != 0)) {
		perror("Thread creation failed\n");
		exit(EXIT_FAILURE);
	}
	res1 = pthread_join(a_thread1, &thread_result);
	res2 = pthread_join(a_thread2, &thread_result);

	if ((res1 != 0)||(res2 != 0)) {
		perror("Thread join failed\n");
		exit(EXIT_FAILURE);
	}
}
*/
void *dust_thread() 
{
	int d;
	if(webcrawling())
		d = webSelecting();
	dust_data = d;
	system("rm index.html");
}

/*
void *weather_thread()
{
	char *w;
	if(webcrawling2())
		w = webSelecting2();
	strcpy(weather_data, w);
	free(w);
	//system("rm index2.html");
}
*/
