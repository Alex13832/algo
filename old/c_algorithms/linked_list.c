// Linked data structure
// Supports Stack and Queue operations also

#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int item;
    struct list *next;
} list;


void print_list(list *l);


// search a list
list *search_list(list *l, int x)
{
    if (l == NULL) return NULL;
    
    if (l->item == x) return l;
    else return (search_list(l->next, x));
}

// Insertion first into a list
void insert_list(list **l, int x)
{
    list *temp = malloc(sizeof(list));
    temp->item = x;
    temp->next = *l;
    *l = temp;
}

// Deletion from a list
list* predecessors(list *l, int x)
{
    if ((l == NULL)||(l->next == NULL)) {
        printf("Error null in list\n");
        return NULL;
    }
    
    if ((l->next)->item == x)
        return l;
    else
        return predecessors(l->next, x);
}

// Removes an item
void remove_item(list **l, int x)
{
    list *p, *pred;
    list *search_list(), *predecessors();
    
    p = search_list(*l, x);
    if (p != NULL) {
        pred = predecessors(*l, x);
        if (pred == NULL)
            *l = p->next;
        else
            pred->next = p->next;
        
        free(p);
    }
}


// Removes duplicates, if there are any
void remove_duplicates(list **l)
{
    list *head, *prev;
    list *front = *l;
    
    while ((*l) != NULL) {
        int itm = (*l)->item;
        
        head = (*l)->next;
        prev = (*l);
        
        while (head != NULL) {
            if (head->item == itm) {
                list *temp = head;
                head = head->next;
                prev->next = head;
                free(temp);
            } else {
                prev = prev->next;
                head = head->next;
            }
        }
        *l = (*l)->next;
    }
    *l = front;
}

// Reverses the list *l. Time O(n), Space O(1)
void reverse_list(list **l)
{
    list *prev = NULL, *curr = (*l), *front = (*l)->next;
    
    while (front != NULL) {
        front = front->next;    // Move forward in *l
        curr->next = prev;      // Point current to list beheind (reverese the pointer)
        prev = curr;            // Update last pointer to current
        curr = front;           // assign current to most rescent (front)
    }
    
    // front is now the last pointer (prev)
    // which points in thre reverse order of *l
    *l = prev;
}

// Prints the k last elements of the list l
int k_last_elements(list *head, int k)
{
    if (head == NULL)
        return 0;
    
    int i = k_last_elements(head->next, k) + 1;
    
    if (i <= k) printf("%d\n", head->item);
    
    return i;
}

// Removes the middle node if there is a middle node
void remove_middle(list **l)
{
    list *mega = *l, *mini = *l;
    mega = mega->next->next;
    int count = 0;
    
    while (mega != NULL) {
        // protection
        if (mega->next == NULL) break;
        if (mega->next->next == NULL) break;
        
        mini = mini->next;
        mega = mega->next->next; // Will reach the end twice as fast as mini
        
        count++;
    }
    
    if (count % 2 == 0) {
        list *temp = mini->next;
        mini->next = mini->next->next;
        free(temp);
    }
}

void partition_list(list **l, int value)
{
    list *lessLink = NULL, *greatLink = NULL, *forward = *l, *pre = *l;
    list *front = lessLink;
    while (forward != NULL) {
        
        list *temp = forward;
        
        if (forward->item < value) {
            lessLink->next = temp;
            pre->next = forward;
            forward = forward->next;
            
        } else if (forward->item >= value) {
            greatLink->next = temp;
            pre->next = forward;
            forward = forward->next;
        }
        
    }
    
    
    lessLink->next = greatLink;
    lessLink = front;
    *l = lessLink;
}


// Prints the entire list
void print_list(list *l)
{
    printf("%d ", l->item);
    
    if (l->next != NULL) print_list(l->next);
    
    else printf("end\n");
}

/* Stack operations here --------------------------------------------------- */

// Inserts an item x at the top of the stack
void push(list **stack, int x)
{
    insert_list(stack, x);
}

// Returns and removes the top item of stack
int pop(list **stack)
{
    int temp = (*stack)->item;
    
    if ((*stack)->next != NULL) {
        list* head = (*stack)->next;
        list* r = *stack;
        *stack = head;
        free(r);
    }
    
    return temp;
}

/* Queue operations here --------------------------------------------------- */

typedef struct queue {
    list *first, last; //(?)
} queue;


// Inserts an item at the back of the queue
void enqueue(list **queue, int x);

// Returns and removes the first (front) item of the queue
void dequeue(list **queue);
