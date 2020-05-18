/*********************************************************************
 * INCLUDES
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

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

    if (curr_p == NULL && curr_p->data == value)
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
 * @fn      random_generator
 *
 * @brief   random number generator which grenerates random numbers and
 *          random insert, delete & member operations 
 *
 * @param   head_p - pointer to the head on link list
 * @param   m      - total no of operation to be carried out
 * @param   mM     - no of member operations ratio
 * @param   mI     - no of insert operations ratio
 * @param   mD     - no of delete operations ratio
 *
 * @return  none
 */
void random_generator(struct list_node_s **head_p, int m, float mM, float mI, float mD)
{
    int opM = m * mM;
    int opD = m * mD;
    int opI = m * mI;
    int countM = 0, countI = 0, countD = 0, mCount = 0;
    int random;
    int operation;

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

            if( opM > countM)
            {
                Member(random, head_p);
                countM++;
                // printf("m ");
            }
    
            break;

            case 1:

            if( opI > countI)
            {
                Insert(random, head_p);
                countI++;
                // printf("i");
            }
            
            break;

            case 2:

            if( opD > countD)
            {
                Delete(random, head_p);
                countD++;
                // printf("d");
            }
  
            break;
        }

        mCount = countM + countI + countD;
    }
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


void main(int argc, char* argv[])
{
    srand(time(0));
    struct list_node_s *head = NULL;
    struct timeval time_begin, time_end;

    // Set the terminal inputs
    int opt = strtol(argv[1],NULL,10);

    //n and m values
    int n = 1000;
    int m = 10000;

    //populate the list with n values
    populate(&head, n);

    // Begin timer
    gettimeofday(&time_begin, NULL);

    // Select the case from cmd prompt input
    switch (opt)
    {
        case 1:
            random_generator(&head, m, 0.99, 0.005, 0.005);
            break;
        case 2:
            random_generator(&head, m, 0.9, 0.05, 0.05);
            break;
        case 3:
            random_generator(&head, m, 0.5, 0.25, 0.25);
            break;
        default:
            // default is case 1
            random_generator(&head, m, 0.99, 0.005, 0.005);
            opt = 1;
            break;
    }

    // End timer
    gettimeofday(&time_end, NULL);

    printf("Serial linked list time spent for case %d : %.6f secs\n", opt, run_time(time_begin, time_end));

    //free up the memory 
    destructor(&head);
}