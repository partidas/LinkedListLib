#include <stdio.h>
#include <stdlib.h>


typedef struct Node {.    /* What the node is:
       Pointer to next node
       Each node has data
    */
    struct Node* next;
    int data;
}Node;

struct Node * createNode (int d) {
    struct Node * newNode = malloc(sizeof(struct Node));
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
int appendToTail(struct Node* head, int d) {
    struct Node* end = createNode(d);
    if(end == NULL) {
        return -1;
    }
    struct Node* iter = head;
    while (iter->next != NULL) {
        iter = iter->next;
    }
    iter->next = end;
    return 1;
}
struct Node * findNode(struct Node * head, int d) {
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
void deleteNode(struct Node* n) {
    if(n->next != NULL) {
        struct Node* temp = n->next;
    }
    n->data = n->next->data;
    n->next = n->next->next;
    // dealloc temp <-- if allocating to begin with
}

//assign type def struct --> todo
void deleteMid(struct Node* n) {
    struct Node* temp = n->next;
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
void printList(struct Node* n) {
    struct Node* iter = n;
    printf(" %d ", iter->data);
    iter = iter->next;
    while(iter != NULL) {
        printf("->");
        printf(" %d ", iter->data);
        iter= iter->next;    
    }
    printf("\nFinished!\n");
}

int main() {
    struct Node * linked1 = createNode(5);
    appendToTail(linked1, 4);
    printList(linked1);
    appendToTail(linked1, 6);
    printList(linked1);
    struct Node * nodeToDelete = findNode(linked1, 4);
    deleteMid(nodeToDelete);
    printList(linked1);
    
    return 0;
}
