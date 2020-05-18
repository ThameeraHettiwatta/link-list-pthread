/*********************************************************************
 * INCLUDES
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

/*********************************************************************
 * GLOBAL VARIABLES
 */

// No of threads being exicuted
int thread_count; 

// Count of member, insert, delete operations being executed by thread
int countM = 0, countI = 0, countD = 0;

// No of member, insert, delete operation carried out to tht list
int opM, opD, opI;

// No of total operation to list
int m; 

// Initializing the head pointer to the list
struct list_node_s *head_p = NULL;

// Construct the read write lock
pthread_rwlock_t rwlock;


/*********************************************************************
 * TYPEDEFS
 */
struct list_node_s { 
 int data; 
 struct list_node_s *next;
};


/*********************************************************************
 * @fn      Member
 *
 * @brief   Check the membership
 *
 * @param   value   - value for node
 * @param   head_p  - pointer to the head on link list
 *
 * @return  1 member or 0 not a member
 */
int Member(int value, struct list_node_s** head_p)
{
    struct list_node_s* curr_p = *head_p;

    while (curr_p != NULL && curr_p->data < value)
        curr_p = curr_p->next;

    if (curr_p == NULL || curr_p->data > value)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/*********************************************************************
 * @fn      Insert
 *
 * @brief   Insert new node to link list
 *
 * @param   value   - value for new node
 * @param   head_p  - pointer to the head on link list
 *
 * @return  1 inserted or 0 not inserted
 */
int Insert(int value, struct list_node_s** head_p)
{
    struct list_node_s* curr_p = *head_p;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value)
    {
        temp_p = malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;

        // New first node
        if (pred_p == NULL)
            *head_p = temp_p;
        else
            pred_p->next = temp_p;
        
        return 1;
    }
    else
    {
        return 0;
    }
}

/*********************************************************************
 * @fn      Delete
 *
 * @brief   Delete node from link list
 *
 * @param   value   - value of node
 * @param   head_p  - pointer to the head on link list
 *
 * @return  1 deleted or 0 node not in list
 */
int Delete(int value, struct list_node_s** head_p)
{
    struct list_node_s* curr_p = *head_p;
    struct list_node_s* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value)
    {
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value)
    {
        // deleting first node
        if (pred_p == NULL)
        {
            *head_p = curr_p->next;
            free(curr_p);
        }
        else
        {
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        
        return 1;
    }
    else
    {
        return 0;
    }
}

/*********************************************************************
 * @fn      print
 *
 * @brief   print each value of node from head 
 *
 * @param   head_p - pointer to the head on link list
 *
 * @return  0
 */
void print(struct list_node_s **head_p) 
{
    struct list_node_s *curr_p = *head_p;

    while(curr_p != NULL) 
    {
    printf("%d, ",curr_p->data);
    curr_p = curr_p->next;
    }
}

/*********************************************************************
 * @fn      destructor
 *
 * @brief   free the memory by releasing the memory allocations 
 *
 * @param   head_p - pointer to the head on link list
 *
 * @return  0
 */
void destructor(struct list_node_s **head_p) 
{
    struct list_node_s *curr_p = *head_p;
    struct list_node_s *prev_p = NULL;

    while(curr_p != NULL) 
    {
        prev_p = curr_p;
        curr_p = curr_p->next;
        free(prev_p);
    }
}


/*********************************************************************
 * @fn      thread_runner
 *
 * @brief   generates and run member, insert and delete operations
 *          the given no of threads in parallel. Uses read write locks 
 *          when accessing the link list. 
 *
 * @return  none
 */
void *thread_runner()
{
    int random;
    int operation;
    int mCount = 0;

    while( mCount < m )
    {        
        if( countD >= opD && countI >= opI )
        {
            operation = 0;
        }
        else
            operation = rand()%3;
        
        random = rand()%65536;

        switch (operation)
        {
            case 0:
            pthread_rwlock_rdlock(&rwlock);
            if( opM > countM)
            {
                Member(random, &head_p);
                countM++;
                // printf("m");
            }
            pthread_rwlock_unlock(&rwlock);
            break;

            case 1:
            pthread_rwlock_wrlock(&rwlock);
            if( opI > countI)
            {
                Insert(random, &head_p);
                countI++;
                // printf("i");
            }
            pthread_rwlock_unlock(&rwlock);
            break;

            case 2:
            pthread_rwlock_wrlock(&rwlock);
            if( opD > countD)
            {
                Delete(random, &head_p);
                countD++;
                // printf("d");
            }
            pthread_rwlock_unlock(&rwlock);
            break;
        }

        mCount = countM + countI + countD;
    }
    return NULL;
}

/*********************************************************************
 * @fn      populate
 *
 * @brief   populates n no of random data nodes in list 
 *
 * @param   head_p - pointer to the head on link list
 * @param   n      - no of data nodes to be populated in list
 *
 * @return  0
 */
void populate(struct list_node_s **head_p, int n)
{
    int i = 0;
    while (i < n) 
    {
        if (Insert(rand()%65536, head_p) == 1)
            i++;
    }
}

/*********************************************************************
 * @fn      run_time
 *
 * @brief   calculates the run time from time begin to time end 
 *
 * @param   time_begin  - begin timer 
 * @param   time_end    - end timer
 *
 * @return  (double) time in seconds
 */
double run_time(struct timeval time_begin, struct timeval time_end) {
    return (double) (time_end.tv_usec - time_begin.tv_usec) / 1000000 + (double) (time_end.tv_sec - time_begin.tv_sec);
}


int  main(int argc, char* argv[])
{
    srand(time(0));
    struct timeval time_begin, time_end;

    // Set the terminal inputs 
    int opt = strtol(argv[1],NULL,10);
    thread_count = strtol(argv[2],NULL,10);

    // Initialize and set n, m values
    int n = 1000;
    m = 10000;

    // Ratio values of member, inerst and delete
    float mM, mI, mD;

    // Construct thread handlers
    pthread_t *thread_handlers;

    // allocate memory for threads
    thread_handlers = malloc(sizeof(pthread_t) * thread_count);

    //populate the list with n values
    populate(&head_p, n);

    // Select the case from cmd prompt input
    switch (opt)
    {
        case 1:
            mM = 0.99;
            mI = 0.005;
            mD = 0.005;
            break;
        case 2:
            mM = 0.9;
            mI = 0.05;
            mD = 0.05;
            break;
        case 3:
            mM = 0.5;
            mI = 0.25;
            mD = 0.25;
            break;
        default:
            // default is case 1
            mM = 0.99;
            mI = 0.005;
            mD = 0.005;
            opt = 1;
            break;
    }

    // Calculate the no of member, insert and delete operations
    opM = m * mM;
    opD = m * mD;
    opI = m * mI;

     // Initializing the rwlock
    pthread_rwlock_init(&rwlock, NULL);

    // Begin timer
    gettimeofday(&time_begin, NULL);

    // Create threads
    int i = 0;
    for(i = 0; i < thread_count; i++) 
    {
        pthread_create(&thread_handlers[i], NULL, (void *) thread_runner, NULL);
    }

    // Join threads 
    for(i = 0; i < thread_count; i++)  
    {
        pthread_join(thread_handlers[i], NULL);
    }

    // End timer 
    gettimeofday(&time_end, NULL);

    // Destroying the rwlock
    pthread_rwlock_destroy(&rwlock);

    printf("Multi threaded linked list with read-write lock time spent for case %d : %.6f secs\n", opt, run_time(time_begin, time_end));

    // Free up the memory 
    destructor(&head_p);

    return 0;
}