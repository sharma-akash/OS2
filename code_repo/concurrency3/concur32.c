#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct Node {
    int value;
    struct Node *next;
}*head; // define global list as shared resource

pthread_mutex_t inserter;
pthread_mutex_t searcher;
pthread_mutex_t deleter;


void ins()
{
    struct Node * temp;
    while(1)
    {
        if (!pthread_mutex_lock(&inserter)) // check for other inserters
        {
            int input = (rand() % 10) + 1; // create random input
            temp = (struct Node *)malloc(sizeof(struct Node));
            printf("Inserting: [%d] \n" , input);
            append_node(input); // put node onto end of list

            pthread_mutex_unlock(&inserter); // allow other inserters
            sleep(4); // sleep for 4 rather than 3 to avoid list getting too big
        }
    }

}

void ser()
{
    struct Node * temp;
    while(1)
    {
        if (!pthread_mutex_trylock(&searcher))
        {
            temp = head;
            
            if (temp == NULL)
            {
                printf("List is empty\n");
                continue;
            } 
           
            else 
            {
                printf ("Current List (searching): ");
                while (temp != NULL)
                {
                    printf("[%d] ", temp->value);
                    temp = temp->next;
                }
                printf("\n");
            }
            pthread_mutex_unlock(&searcher);
        }
        sleep(3); // need these commands or else the list gets big too quickly
    }
}

void del()
{
    struct Node * temp, * prev;
    while(1)
    {
        int delete = rand() % 10; // set random value for deletion
        if (!pthread_mutex_trylock(&inserter))
        {
            if(!pthread_mutex_trylock(&searcher))
            {
                temp = head; // map onto the current list
                while(temp != NULL) // traverse the list for the value
                {
                    if (temp->value == delete) // delete if we see the value
                    {
                        printf("Deleting [%d] from the list. \n" , delete);
                        if (temp == head) // if the value was the head node, we need to re assign
                        {
                            head = temp->next; // make the new head after the old one
                            free(temp);
                            break;
                        }

                        else
                        {
                            prev->next = temp->next;
                            free(temp);
                            break;
                        }
                    }
                    else
                    {
                        prev = temp;
                        temp = temp->next;
                    }
                }
            pthread_mutex_unlock(&searcher);
            }
        pthread_mutex_unlock(&inserter);
        }
    sleep(2);    
    }
}

void append_node(int newvalue)
{
    struct Node *new = (struct Node*) malloc(sizeof(struct Node)); // allocate and create new node for insertion
    struct Node *temp = head; // temp node to traverse and get to the end
  
    new->value = newvalue;
    new->next = NULL; // assign the argument and make the next NULL to make this node the final one
 
    if (head == NULL)
    {
       head = new;
       return;
    }  
      
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
  
    temp->next = new;
    return;    
}

int main()
{
    srand(time(NULL));  // seed for random numbers that will be the values in our linked list

    struct Node * list;
    list = (struct Node *)malloc(sizeof(struct Node)); // declare and assign memory for the shared resource (singly linked list)

    list->value = (rand() % 10) + 1; // keep values between 1 and 10
    head = list; // define the node we just made as the beginning of the list
    head->next = NULL; 
    printf("Starting value in the list: [%d]\n" , list->value);

    pthread_t search[4];
    pthread_t insert[4]; // create 4 of each thread arbitrarily
    pthread_t delete[4];
    int i; // iterator

    for(i = 0; i < 4; ++i)
    {
        int ithread = pthread_create(&insert[i], NULL, (void *)ins, (void *)NULL); // create the inserter thread
        if (ithread)
        {
            fprintf(stderr, "Error with insertion thread.\n");
            return 1;
        }

        int sthread = pthread_create(&search[i], NULL, (void *)ser, (void *)NULL); // create the searcher thread
        if (sthread)
        {
            fprintf(stderr, "Error with search thread.\n");
            return 1;
        }

        int dthread = pthread_create(&delete[i], NULL, (void *)del, (void *)NULL); // create the deleter thread
        if (dthread)
        {
            fprintf(stderr, "Error with deleter thread.\n");
            return 1;
        }
    }
    
    for(i = 0; i < 4; ++i)
    {
        pthread_join(insert[i], NULL);
        pthread_join(search[i], NULL);
        pthread_join(delete[i], NULL);
    }

    return 0;
}