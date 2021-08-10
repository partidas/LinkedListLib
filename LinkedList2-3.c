#include <stdio.h>
#include <stdlib.h>


/* ***NOTES***
newNode -> returns address of the memory allocated
*newNode -> returns the value pointed to on the heap (memory)
&newNode -> returns the pointer address on the stack (temporary within the function call)
*/

/* Struct declaration: Node *********EDIT COMMENTS TO SEPARATE THE STRUCTS*****
 * --------------------------
 * Node is created as a datatype
 * Node has the following elements:  * 
 *      next: struct Node * - the Node pointer to the next Node in the
 *                             linkedlist.
 *      data: int - value the Node holds is this.
 *      size: int - only used for the head Node and holds the size of
 *                        linkedlist
 *      head: int - boolean to declare/determine if the current Node
 *                        is the head of the linkedlist.
 * 
 * Comments: Using typedef to avoid having to state "struct Node" everytime a 
 *           Node is called on. (Thanks for the tip Max!)
 */
typedef struct Node{ 
    struct Node * next;
    int data;
}Node;

typedef struct {
    Node * head;
    Node * tail;
    int size;
}myLinkedList;

/* Function: createNode
 * --------------------------
 * Helper function that creates a single Node, allocating memory of size Node 
 * and initializing the data to user's input and stating if its the head; can 
 * only be head if its the first element of the linkedlist.
 * 
 * d        : int - data value stored in the Node
 * 
 * Returns: the Node * of the newly created Node, the pointer points to the
 *          place in memory where the Node was allocated.
 *          does not handle error if no memory for a new Node 
 *          (handled by appendToTail). 
 */
Node * createNode (int d) {
    Node * newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = d;
    return newNode;
}

/* Function: appendToTail
 * --------------------------
 * Creates a newNode and adds it to the end of the provided linked list with
 * user provided value.
 * 
 * list     : myLinkedList - takes in myLinkedList struct which holds head and
 *                           tail pointers and size of the linkedlist
 * d        : int   - the value the new node will have
 * 
 * Returns: 1 if no issues and the node was successfully created and appended
 *          to the end of the linkedlist
 *          -1 if there was an error allocating memory. 
 */
int appendToTail(myLinkedList * list, int d) {
    Node * newNode = createNode(d);
    if(newNode == NULL) {
        return -1;
    } else if(list->head == NULL) {
        list->head = newNode;
        list->size = 1;
        list->tail = list->head;
        return 1;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
        list->size += 1;
        printf("\nAppending to Tail -- list.tail->data is %d\n",list->tail->data);
        return 1;
    }
}

/* Function: findNode
 * --------------------------
 * Traverses the linkedlist to find the Node with the value d provided by the
 * user. 
 * 
 * Search Algorithm Used: Linear with an O(n) and Omega(1)
 * 
 * list     : myLinkedList - takes in myLinkedList struct which holds head and
 *                           tail pointers and size of the linkedlist
 * d        : int   - the value the node data we need to find
 * 
 * Returns: Node* if the Node with the value int d is found
 *          NULL if the value d is not found in the linkedlist
 */
Node * findNode(myLinkedList list, int d) {
    Node * head = list.head;
    while(head != NULL) {
        if(head->data == d) {
            printf("FOUND %d\n", d);
            return head;
        } else {
            head = head->next;
        }
    }
    return NULL;
}

/* NEED TO FORMAT COMMENT
 * Deletes a node from LinkedList.
 * Input - int n - the Node with value n that needs to be removed.
 * Input - Node * head - pointer to the linkedList
 * Returns 1 or 0 - 1 if found and deleted, 0 if it did not find. -1 if error
 */
int deleteNode(myLinkedList * list, int n) {
    printf("Deleting Node with value %d...\n", n);
    
    Node * iter = list->head;
    Node * temp;
    //if the head is the node to delete
    if(iter->data == n) {
        printf("Node Found, its the Head\n");
        if(iter->next == NULL) {
            list->head = NULL;
            free(iter);
            printf("LinkedList now empty\n");
            return 1;
        } else {
            list->head = iter->next;
            list->size -= 1;
            free(iter);
            return 1; //return the new head
        }
    }

    //Find the node in the linkedList and delete
    //check the next node if its the one we are looking for.
    while(iter->next != NULL) {
        //if the node was found
        if(iter->next->data == n) {
            printf("Node found and deleted! %d\n", iter->next->data);
            temp = iter->next;
            iter->next = iter->next->next;
            list->size -= 1;
            free(temp); 
            return 1; 
        }
        iter = iter->next;
    }
    printf("Error deleting node...%d not in linked list!\n", n);
    return -1; //if all of the above failed, then report an error
}


/* Function: printList
 * --------------------------
 * Traverses the linkedlist and prints out the value in each Node one by 
 * one with an arrow between each value to show the "links" aka pointers
 * between each Node
 * 
 * Runtime: O(n) - because it needs to traverse each Node til the end.
 * 
 * head     : Node* - points to the head of the linkedlist we will be printing
 * 
 * Returns: No returns, it just prints out the value of each Node. 
 */
void printList(myLinkedList list) {
    Node* iter = list.head;
    printf("%d ", iter->data);
    iter = iter->next;
    while(iter != NULL) {
        printf("->");
        printf(" %d ", iter->data);
        iter= iter->next;    
    }
    printf("\nLinked List Printed!\n");
}

//2.3 - NEED TO ADD COMMENT **NEED TO UPDATE TO ACCOUNT FOR myLinkedList struct
void deleteMid(Node * n) {
    Node* temp = n->next;
/*    if(n->next != NULL) {
        struct Node* temp = n->next;
    }*/
    n->data = n->next->data;
    //if a size 3 Linked list, makes sure if removing mid, end pointing to null.
    if(n->next->next != NULL) {
        n->next = n->next->next;
    } else {
        n->next  = NULL;
    }
    if(temp != NULL) {
        free(temp);
    }
}

/* NEED TO FORMAT COMMENT
 * Find and return the kth to last element of singly linked list
 */
int findKth(myLinkedList list, int k) {
    if(k > list.size) {
        printf("%dth to last element does not exist!!\n", k);
        return -1;
    }

    int index = list.size - k;
    Node * linkedIter = list.head;
    int iter = 0;
    while(iter != index) {
        linkedIter = linkedIter->next;
        iter++;
    }
    if(iter == index) {
        return linkedIter->data;
    } else {
        printf("Error finding Kth to last element\n");
        return -1;
    }
}


/* NEED TO FORMAT COMMENT
 * function to create auto testing
 * not finished implementing
 */
void testing(int size) {

}

/*NEED TO CLEAN THIS UP AND CREATE A TEST FILE FOR AUTOMATED TESTING*/
int main() {
    myLinkedList list1;
    appendToTail(&list1, 1);
    appendToTail(&list1, 2);
    appendToTail(&list1, 3);
    appendToTail(&list1, 4);
    appendToTail(&list1, 5);
    printList(list1);
    
    printf("%dnd to last element is: %d\n", 2, findKth(list1,2));
    printf("%dnd to last element is: %d\n", 3, findKth(list1,3));
    printf("%dnd to last element is: %d\n", 4, findKth(list1,4));


    printf("LinkedList Head: %d\n", list1.head->data);
    printf("LinkedList Tail: %d\n", list1.tail->data);
    printf("LinkedList size: %d\n", list1.size);

    deleteNode(&list1, 4);
    deleteNode(&list1, 5);
    deleteNode(&list1, 6);
    printList(list1); //seg fault because its NULL now.

    return 0;
}
