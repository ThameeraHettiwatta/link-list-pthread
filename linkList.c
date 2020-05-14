/*********************************************************************
 * INCLUDES
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


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
 * @param   value - 
 * @param   head_p - pointer to the head on link list
 *
 * @return  1 member or 0 not a member
 */
int Member(int value, struct list_node_s* head_p)
{
    struct list_node_s* curr_p = head_p;

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
 * @param   value - value for new node
 * @param   head_p - pointer to the head on link list
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
 * @param   value - value of node
 * @param   head_p - pointer to the head on link list
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
 * @fn      random_generator
 *
 * @brief   random number generator which grenerates numbers not in
 *          the list
 *
 * @param   random - random value
 * @param   head_p - pointer to the head on link list
 *
 * @return  0
 */
// void random_generator(int *random, struct list_node_s *head_p)
// {
//     int member = 1; 
//     while(member)
//     {
//         *random = rand()%65536;
//         member = Member(*random, head_p);
//     }
// }


void main()
{
    srand(time(0));
    struct list_node_s *head = NULL;
    int random;
    int n = 50;
    int m = 20;
    
    for(int i = 0; i<n; i++) 
    {
        // random_generator(random, head);
        random = rand()%65536;
        Insert(random, &head);
    }

    for(int i = 0; i<m; i++)
    {
        random = rand()%65536;
        Insert(random, &head);
        random = rand()%65536;
        Member(random, head);
        random = rand()%65536;
        Delete(random, &head);

    }

    print(&head);
}