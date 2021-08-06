#include <stdio.h>
#include <stdlib.h>

/* ***NOTES***
newNode -> returns address of the memory allocated
*newNode -> returns the value pointed to on the heap (memory)
&newNode -> returns the pointer address on the stack (temporary within the function call)
*/

/* Struct declaration: Node
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
typedef struct Node { 
    struct Node* next;
    int data;
}Node;

typedef struct myLinkedList {
    Node * head;
    Node * tail;
    int size;
}


/* Function: createNode
 * --------------------------
 * Helper function that creates a single Node, allocating memory of size Node 
 * and initializing the data to user's input and stating if its the head; can 
 * only be head if its the first element of the linkedlist.
 * 
 * d        : int - data value stored in the Node
 * isHead   : int - 1 is its the head and 0 means its not
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
 * head     : Node* - the head of the linkedlist where a new node is added to
 * d        : int   - the value the new node will have
 * 
 * Returns: 1 if no issues and the node was successfully created and appended
 *          to the end of the linkedlist
 *          -1 if there was an error allocating memory. 
 */
int appendToTail(Node* head, int d) {
    Node* end = createNode(d, 0);
    if(end == NULL) {
        return -1;
    }
    Node* iter = head;
    head->size += 1;
    while (iter->next != NULL) {
        iter = iter->next;
    }
    iter->next = end;
    return 1;
}

/* Function: findNode
 * --------------------------
 * Traverses the linkedlist to find the Node with the value d provided by the
 * user. 
 * 
 * Search Algorithm Used: Linear with an O(n) and Omega(1)
 * 
 * head     : Node* - the head of the linkedlist we need to search in
 * d        : int   - the value the node data we need to find
 * 
 * Returns: Node* if the Node with the value int d is found
 *          NULL if the value d is not found in the linkedlist
 */
Node * findNode(Node * head, int d) {
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
int deleteNode(Node * head, int n) {
    printf("Deleting Node with value %d...\n", n);
    
    Node * iter = head;
    Node * temp;
    //if the head is the node to delete
    if(head->data == n) {
        printf("Node Found, its the Head\n");
        if(head->next == NULL) {
            free(head);
            printf("LinkedList now empty\n");
            return 1;
        } else { //instead of deleting the node, we will update the head node's
                 //data to the next node's and delete the next node.
                 // this is to keep the head node pointer, since we return int.
            iter->data = iter->next->data;
            temp = iter->next;
            iter->next = iter->next->next;
            head->size -= 1;
            free(temp);
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
            head->size -= 1;
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
void printList(Node* head) {
    Node* iter = head;
    printf("%d ", iter->data);
    iter = iter->next;
    while(iter != NULL) {
        printf("->");
        printf(" %d ", iter->data);
        iter= iter->next;    
    }
    printf("\nLinked List Printed!\n");
}

//2.3 - NEED TO ADD COMMENT
void deleteMid(Node* n) {
    Node* temp = n->next;
/*    if(n->next != NULL) {
        struct Node* temp = n->next;
    }*/
    n->data = n->next->data;
    //if a size 3 Linked list, makes sure that if removing mid, end pointing to null.
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
int findKth(Node * head, int k) {
    if(k > head->size) {
        printf("%dth to last element does not exist!!\n", k);
        return -1;
    }

    int index = head->size - k;
    int iter = 0;
    Node * linkedIter= head;
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
    //Create a LinkedList of Size 5;
    int value = 1;
    Node * test1 = createNode(value, 1);
    value++;

    while(value != size) {
        appendToTail(test1, value);
        value++;
    }
    printList(test1);
    Node * nodeToDelete = findNode(test1, 7);
    printf("testing");
}

/*NEED TO CLEAN THIS UP AND CREATE A TEST FILE FOR AUTOMATED TESTING*/
int main() {
    Node * linked1 = createNode(5, 1);
    printf("LinkedList size: %d\n", linked1->size);
    appendToTail(linked1, 4);
    appendToTail(linked1, 6);
    // linked1: 5 -> 4 -> 6
    /*printList(linked1);
    printf("LinkedList size: %d\n", linked1->size);
    Node * nodeToDelete = findNode(linked1, 4);
    deleteNode(linked1, 6);
    printf("LinkedList size: %d\n", linked1->size);
    // linked1: 5 -> 4
    printList(linked1);
    appendToTail(linked1, 7);
    printf("LinkedList size: %d\n", linked1->size);
    // linked1: 5 -> 4 -> 7
    printList(linked1);
    deleteNode(linked1, 5);
    printf("LinkedList size: %d\n", linked1->size);
    // linked1: 4 -> 7
    printList(linked1);
    appendToTail(linked1, 5);
    // linked1: 4 -> 7 -> 5
    printList(linked1);
    deleteNode(linked1, 6);
    printList(linked1);
    deleteNode(linked1, 4);
    printList(linked1);
    deleteNode(linked1, 5);
    printf("LinkedList size: %d\n", linked1->size);
    printList(linked1);
    deleteNode(linked1, 7);
    deleteNode(linked1, 4); */
    appendToTail(linked1, 9);
    appendToTail(linked1, 15);
    appendToTail(linked1, 1);
    printList(linked1);
    printf("LinkedList size: %d\n", linked1->size);

    printf("\n3rd to last element: %d\n", findKth(linked1, 3));
    printf("\n2nd to last element: %d\n", findKth(linked1, 2));
    printf("\n5th to last element: %d\n", findKth(linked1, 5));
    printf("\n6th to last element: %d\n", findKth(linked1, 6));
    printf("\n7th to last element: %d\n", findKth(linked1, 7));
    return 0;
}
