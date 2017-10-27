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
int counter = 0;
int remain = 0;

struct numbers{ // define the struct
	int printed_num;
	int wait_time;
};

struct numbers buffer[buffer_size]; // create the array of structs statically

pthread_mutex_t mtx; // declare our mutex
pthread_cond_t cons; // declare our condiiton variables (for event handling)
pthread_cond_t prod;

int rng(int min, int max)
{
	int i, boundary;
	srand(time(NULL)); // use srand to create a random seed for Mersenne Twister
	unsigned long seed = rand(); // decalre the seed
	
	init_genrand(seed); // initiallize rng
	int value = 0;
	while(value < min || value > max) // make sure the value produced is between 1 and 10, and our boundaries
	{
		value = genrand_int32(); // assign the value
		if (max < 10) // for our purposes, wait times will always be under 10 seconds. If we are producing the printed_num, we can have any number
		{
			value = value % 10; // keep our values single digit
		}
	}	

	return value; // return only when while loop conditions are met
}


void* producer(void *ptr) // function for producer to execute after call to pthread_create
{    
	struct numbers itemc;
	int prod_wait, i = 0;

	while(1)
	{		
		while (remain != 0)
		{
			remain = sleep(remain);
		}

		itemc.printed_num = rng(1 , 500000); // random value to be printed
		itemc.wait_time = rng(2 , 9); // using Mersenne Twister to produce the random values

		if (counter == 32) // if array is full
		{
			pthread_cond_signal(&cons);
			pthread_cond_wait(&prod, &mtx); // make producer wait when buffer is full.
		}

		pthread_mutex_lock(&mtx); // begin the lock process as soon as we access the buffer


		buffer[counter] = itemc; // add the item to the buffer
		++counter; // increment counter whenever item is added

		printf("Item has been added to the buffer. " , counter); // show it has been added
		printf("Current buffer: \n");

		for (i = 0; i < counter; i++)
		{
			printf("[%d , %d] \n",itemc.printed_num, itemc.wait_time);
		}
		
		pthread_mutex_unlock(&mtx); // Unlock to allow the consumer to do work on item
		pthread_cond_signal(&cons); // signal the consumer to process the item (this func is reason for using condition variables)
		pthread_cond_wait(&prod, &mtx);

		prod_wait = rng(3 , 7); // make producer wait between 3 and 7 seconds.
		remain = sleep(prod_wait);

		
	}
}



void* consumer(void *ptr) // function for consumer to execute after call to pthread_create
{
	
	struct numbers itemp; // decalre new struct to copy into for processing
	int n, wait = 0; 

	while(1)
	{		
		if (counter == 0) // if array is empty
		{
			pthread_cond_wait(&cons, &mtx); // make consumer wait when it is empty
			pthread_mutex_unlock(&mtx);
		}
		
		pthread_mutex_lock(&mtx); // begin the lock process as soon as we access the buffer


		itemp = buffer[0];
		wait = itemp.wait_time;

		for(n = 0; n < counter; n++) // re assign the first element and shift all others left
		{
			buffer[n] = buffer[n + 1];
		}

		--counter; // decrement counter when item is removed
		
		pthread_cond_signal(&prod);
		pthread_mutex_unlock(&mtx); // Unlock to allow the producer to add more elements as needed.
		pthread_cond_signal(&prod);
		
		sleep(wait);
		printf("\nNumber from buffer: %d\n" , itemp.printed_num);

	}
}


int main() // main program flow
{
	pthread_t prod_thread, cons_thread; // create pointers for our two threads (will be args into functions)


	pthread_mutex_init(&mtx, NULL);	// init mutex, we use NULL for default conditions
  	pthread_cond_init(&cons, NULL); // init condition variables
  	pthread_cond_init(&prod, NULL); 

	pthread_create(&prod_thread, NULL, producer, NULL); // create the threads, use NULL for defauly attributes.
  	pthread_create(&cons_thread, NULL, consumer, NULL); // 


	pthread_join(prod_thread, NULL); // wait for threads to finish so main does not complete before the threads have.
	pthread_join(cons_thread, NULL); // we put the producer first because the consumer may need to consume more after producer is done

	return 0; 
}
