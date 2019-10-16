#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

/*

MUTEX : This program demonstrates a data race
with two threads competing for a single global variable.

A mutex is used to avoid a data race.

To view a data race, comment out lines labeled
"COMMENT OUT FOR DATA RACE".
*/

pthread_mutex_t my_lock;
int counter;


void *adder(void *arg)
{
	for (int i = 0; i < 50000; i++)
	{
		/* PTHREAD_MUTEX_LOCK is a request to obtain the
		 * lock called MY_LOCK. If another thread is "holding"
		 * the lock at the time of this request, then this thread
		 * will be blocked until that thread gives up the lock. */
		// COMMENT OUT FOR DATA RACE
		pthread_mutex_lock(&my_lock);
		counter++;

		/* PTHREAD_MUTEX_UNLOCK releases the lock for other
		 * threads to use. */
		// COMMENT OUT FOR DATA RACE
		pthread_mutex_unlock(&my_lock);
	}
	return NULL;
}


int main(int argc, char **argv)
{
	/* Initialize the global variable */
	counter = 0;
	pthread_t thread_1, thread_2;

	/* Initialize the lock. */
	int mutex_rc = pthread_mutex_init(&my_lock, NULL);
	if (mutex_rc != 0)
		fprintf(stderr, "The mutex failed to be initialized. Error code: %d.\n", mutex_rc);

	/* Start thread 1 */
	int rc = pthread_create(&thread_1, NULL, adder, NULL);
	if (rc != 0)
		fprintf(stderr, "Error creating thread 1. Error code: %d\n", rc);

	/* Start thread 2 */
	rc = pthread_create(&thread_2, NULL, adder, NULL);
	if (rc != 0)
		fprintf(stderr, "Error creating thread 2. Error code: %d\n", rc);

	void *result;

	/* PTHREAD_JOIN: halt the running of the main thread
	 * until threads 1 and 2 are completed. */
	pthread_join(thread_1, &result);
	pthread_join(thread_2, &result);

	printf("The final value of 'counter' is %d\n", counter);
	return 0;
}