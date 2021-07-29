#include <stdio.h>
#include <stdlib.h>

/* ***NOTES***
newNode -> returns address of the memory allocated
*newNode -> returns the value pointed to on the heap (memory)
&newNode -> returns the pointer address on the stack (temporary within the function call)
*/

typedef struct Node {    /* What the node is:
       Pointer to next node
       Each node has data
    */
    struct Node* next;
    int data;
}Node;

Node * createNode (int d) {
    Node * newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->data = d;
    return newNode;
}
//return status if memory runs out
int appendToTail(Node* head, int d) {
    Node* end = createNode(d);
    if(end == NULL) {
        return -1;
    }
    Node* iter = head;
    while (iter->next != NULL) {
        iter = iter->next;
    }
    iter->next = end;
    return 1;
}
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

//Deletes a node from LinkedList.
//Input - int n - the Node with value n that needs to be removed.
//Input - Node * head - pointer to the linkedList
//Returns 1 or 0 - 1 if found and deleted, 0 if it did not find. -1 if error
//deleteNode calls on findNode and then performs the delete.

/*NOTE for MAX- does not work for removing the tail, need to either
         update the findNode method to return the node before, since
         the next pointer on that node needs to be set to null;
         or run a finde node manually without a call to it.
*/
int deleteNode(Node * head, int n) {
    printf("Deleting Node with value %d...\n", n);
    Node * nNode = findNode(head, n);
    if(nNode == NULL) {
        printf("Does not exist\n");
        return 0;
    }
    printf("Node found! %d\n", nNode->data);
    //if Node to delete is the tail:
    if(nNode->next == NULL) {
        nNode = NULL;
    } else { //if next node is not null - not a real delete, 
             //more of a delete data and remove next node
        nNode->data = nNode->next->data; //copies the data of next node into current
        Node * temp = nNode->next; //temp node so we can free the deleted node
        nNode->next = nNode->next->next; //set next node to next->next node (can be null)
        free(temp); //free node from memory
        return 1; //return 1 for success
    }
    printf("Error deleting node...\n");
    return -1; //if all of the above failed, then report an error
}

//2.3
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

//print out linked list
void printList(Node* n) {
    Node* iter = n;
    printf(" %d ", iter->data);
    iter = iter->next;
    while(iter != NULL) {
        printf("->");
        printf(" %d ", iter->data);
        iter= iter->next;    
    }
    printf("\nFinished!\n");
}



//function to create auto testing
void testing(int size) {
    //Create a LinkedList of Size 5;
    int value = 1;
    Node * test1 = createNode(value);
    value++;

    while(value != size) {
        appendToTail(test1, value);
        value++;
    }
    printList(test1);
    Node * nodeToDelete = findNode(test1, 7);
    printf("testing");
}



int main() {
    Node * linked1 = createNode(5);
    appendToTail(linked1, 4);
    printList(linked1);
    appendToTail(linked1, 6);
    printList(linked1);
    Node * nodeToDelete = findNode(linked1, 4);
    deleteNode(linked1, 4);
    printList(linked1);
    
    return 0;
}
