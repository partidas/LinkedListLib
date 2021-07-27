#include <stdio.h>
#include <stdlib.h>


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
    /*
    newNode -> returns address of the memory allocated
    *newNode -> returns the value pointed to on the heap (memory)
    &newNode -> returns the pointer address on the stack (temporary within the function call)
    */
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

//Deletes node but not head tail
void deleteNode(Node* n) {
    if(n->next != NULL) {
        Node* temp = n->next;
    }
    n->data = n->next->data;
    n->next = n->next->next;
    // dealloc temp <-- if allocating to begin with
}

//assign type def struct --> todo
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
    Node * nodeToDelete = findNode(test1, 7)
    printf("testing");
}



int main() {
    Node * linked1 = createNode(5);
    appendToTail(linked1, 4);
    printList(linked1);
    appendToTail(linked1, 6);
    printList(linked1);
    Node * nodeToDelete = findNode(linked1, 4);
    deleteMid(nodeToDelete);
    printList(linked1);
    
    return 0;
}
