/* 
CS 444 Producer-Consumer Problem
Authors: Akash Sharma, Rohit Chaudhary
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define buffer_size 32
int counter;

struct numbers{ // define the struct
	int printed_num;
	int wait_time;
};

struct numbers buffer[buffer_size]; // create the array of structs statically
struct numbers copier[buffer_size]; // create another array of same size for removing elements

pthread_mutex_t mtx; // declare our mutex
pthread_cond_t cons; // declare our condiiton variables (for event handling)
pthread_cond_t prod;

int rngMT(int min, int max)
{
	int i, boundary = 0;
	srand(time(NULL));
	unsigned long seed = rand();
	init_genrand(seed);
	int value = 0;

	while(value < min || value > max)
	{
		value = genrand_int32();
		value = value % 9;
	}
	return value;
}

/*
void* producer(void *ptr) // function for producer to execute after call to pthread_create
{    
	struct numbers itemc;
	int x, y = 0;

	while(x < 32)
		{		
			x += 1;  // increment x for each iteration
			itemc.printed_num = x + 2; // arbitrary values into struct (testing)
			itemc.wait_time = 3; // still need to figure out how to produce these randomly

			if (counter == 32) // if array is full
			{
				printf("Buffer is full, producer thread now waiting.\n");
				// make it wait here
			}
			
			pthread_mutex_lock(&mtx); // begin the lock process as soon as we access the buffer
			
			buffer[x - 1] = itemc; // add the item to the buffer
			counter++; // increment counter whenever item is added

			printf("\n Item %d has been added to the buffer" , x); // show it has been added
			pthread_cond_signal(&cons); // signal the consumer to process the item (this func is reason for using condition variables)

			pthread_mutex_unlock(&mtx); // Unlock to allow the consumer to do work on item

			// To-do: Implement wait time from random number. Wait must not be interrupted by signals
			// so we cannot simply use sleep(). 
		}
}
*/

/*
void* consumer(void *ptr) // function for consumer to execute after call to pthread_create
{
	/*
	struct numbers itemp; // decalre new struct to copy into for processing
	int n, y = 0; 

	pthread_mutex_lock(&mtx); // begin the lock process as soon as we access the buffer
	
	if (counter == 0) // if array is empty
	{
		printf("Buffer is empty, consumer thread now waiting\n");
		// make it wait
	}
	for (y = 0; y < buffer_size; y++) // loop to iterate through buffer and find items to process
	{
		itemp = buffer[y];
		printf("Number from struct: %d\n" , itemp.printed_num);

		for(n = 0; n < counter - 1; n++) // re assign the first element and shift all others left
		{
			buffer[n] = buffer[n + 1];
		}

		counter--; // decrement counter when item is removed
		// To-do: Imlement wait time of consumer before next item is printed.
	}

	pthread_mutex_unlock(&mtx); // Unlock to allow the producer to add more elements as needed. 
}
*/

int main() // main program flow
{
	// pthread_t prod_thread, cons_thread; // create pointers for our two threads (will be args into functions)

/*
	pthread_mutex_init(&mtx, NULL);	// init mutex, we use NULL for default conditions
  	pthread_cond_init(&cons, NULL); // init condition variables
  	pthread_cond_init(&prod, NULL); 

	pthread_create(&prod_thread, NULL, producer, NULL); // create the threads, use NULL for defauly attributes.
  	pthread_create(&cons_thread, NULL, consumer, NULL); // 


	pthread_join(prod_thread, NULL); // wait for threads to finish so main does not complete before the threads have.
   	pthread_join(cons_thread, NULL); // we put the producer first because the consumer may need to consume more after producer is done
*/
	int test = rngMT(2,9);
	printf("Random value:%d\n" , test);
	return 0; 
}