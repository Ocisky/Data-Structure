#include <stdio.h>
#include <stdlib.h>
typedef int LabelType;

typedef struct NodeTag {
    LabelType label;
    struct NodeTag *left, *right;
} Node;

typedef Node *Set; //Set is a pointer to root of the tree

void makeNull(Set *pS) {
    //makes the set *pS empty
}

void printSet(Set *pS) {
    //print the set in format {a1, a2, ..., an}
}

void insert(int x, Set *pS){
    if((*pS) == NULL){
        (*pS) = (Set)malloc(sizeof(Node));
        (*pS)->label = x;
        (*pS)->left = NULL;
        (*pS)->right = NULL;
        return;
    }
	if((*pS)->label == x){
		return;
	}
	if(x < (*pS)->label)
	    insert(x, &((*pS)->left));
	else
	insert(x, &((*pS)->right));
}

void insert(int x, Set *pS){
    if((*pS) == NULL){
        (*pS) = (Set)malloc(sizeof(Node));
        (*pS)->label = x;
        (*pS)->left = NULL;
        (*pS)->right = NULL;
        return;
    }
	if((*pS)->label == x){
		printf("Error: element %d has existed.\n", x);
		return;
	}
	if(x < (*pS)->label)
	    insert(x, &((*pS)->left));
	else
	insert(x, &((*pS)->right));
}
printf("Error: element %d does not exist.\n", x);

int deleteMin(Set *pS) {
    if ((*pS)->left == NULL) {
        int min = (*pS)->label;
        (*pS) = (*pS)->right;
        return min;
    }
        
    return deleteMin(&(*pS)->left);
}

void delete(int x, Set *pS){
	if((*pS) == NULL){
	    printf("Error: element %d does not exist.\n", x);
        return;
    }
    if (x < (*pS)->label)
        delete(x, &(*pS)->left);
    else if (x > (*pS)->label)
        delete(x, &(*pS)->right);
    else {
        if ((*pS)->left == NULL && (*pS)->right == NULL) {
            (*pS) = NULL;
            return;
        }
        if ((*pS)->left != NULL && (*pS)->right != NULL) {
            (*pS)->label = deleteMin(&(*pS)->right);
            return;
        }
        if ((*pS)->left != NULL)
            (*pS) = (*pS)->left;
        else
            (*pS) = (*pS)->right;
    }
	
}

void setUnion(Set *pA, Set *pB, Set *pC){
	makeNull(pC);
	traverseAndInsert(pA, pC);
	traverseAndInsert(pB, pC);
} 

void traverseAndInsert(Set *pA, Set *pB){
	if((*pA) == NULL){
		return;
	}
	insert((*pA)->label, pB);
	traverseAndInsert(&(*pA)->left, pB);
	traverseAndInsert(&(*pA)->right, pB);
}

void assign(Set *pA, Set *pB){
	makeNull(pA);
	traverseAndInsert(pA, pB);
}
int member(int x, Node *node) {
    if (node == NULL)
        return 0;
    if (node->label == x)
        return 1;
    
    if (x < node->label)
        return member(x, node->left);

    return member(x, node->right);
}
int isSubset(Set *pA, Set *pB){
	if((*pA) == NULL){
		return 1;
	}
	if(!member((*pA)->label, pB))
		return 0;
	if(!isSubset(&(*pA)->left, pB))
		return 0;
	return isSubset(&(*pA)->right, pB);
}

void equal(Set *pA, Set *pB){
	return isSubset(pA, pB) && isSubset(pB, pA); 
}














































