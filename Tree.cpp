int member(int x, Set *pS){
	int i = x / 8;
	int j = x % 8;
	return pS->data[i] & (1 << j);
}

int member(int x, Set *pS){
	return pS->data[x] == 1;
}
int member(int x, Set *pS) {
    if ((*pS) == NULL) return 0;
    if ((*pS)->label == x) return 1;
    if (x < (*pS)->label)
        return member(x, &((*pS)->left));
    return member(x, &((*pS)->right));
}
INSERT
void insert(int x, Set *pS){
    pS->data[x] = 1;
}
void insert(int x, Set *pS){
    if(pS->data[x] == 1){
        printf("Error: element %d has existed.\n", x);
        return;
    }
    pS->data[x] = 1;
}
//ADVANCE
void insert(int x, Set *pS){
	int i = x / 8;
	int j = x % 8;
	pS->data[i] |= (1 << j);
}
void insert(int x, Set *pS){
    int i = x/8;
    int j = x%8;
    if(!(pS->data[i] & (1<<j))){
        pS->data[i] |= (1<<j);
    }else{
        printf("Error: element %d has existed.\n",x);
    }
}
// BST
void insert(int x, Set *pS){
    if((*pS) == NULL){
        (*pS) = (Set)malloc(sizeof(Node));
        (*pS)->label = x;
        (*pS)->left = (*pS)->right = NULL;
        return;
    }
	if((*pS)->label == x){
		// printf("Error: element %d has existed.\n", x);
		return;
	}
	if(x < (*pS)->label)
	    insert(x, &((*pS)->left));
	else
	insert(x, &((*pS)->right));
}

DELETE

void delete(int x, Set *pS){
	pS->data[x] = 0;
}

void delete(int x, Set *pS){
    int i = x/8;
    int j = x%8;
    pS->data[i] &= ~(1<<j);
}

void delete(int x, Set *pS) {
    int i = x / 8;         
    int j = x % 8;         
    if (pS->data[i] & (1 << j)) {
        pS->data[i] &= ~(1 << j); 
    } else {
        printf("Error: element %d does not exist.\n", x);
    }
}

//BST
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
	    // printf("Error: element %d does not exist.\n", x);
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

INTERSECTION

void setIntersection(Set *pA,Set *pB,Set *pC){
    for ( int i = 0 ; i < N ; i++){
        pC->data[i] = pA->data[i] & pB->data[i];
    }
}
//compute the intersection of two sets A and B.
void setIntersection(Set *pA,Set *pB,Set *pC){
    for ( int i = 0 ; i < N ; i++){
        pC->data[i] = pA->data[i] && pB->data[i];
    }
}
// BST
int member(int x, Set *pS){
    if(*pS==NULL) return 0 ;
    if((*pS)->label == x ) return 1;
    if((*pS)->label > x  ){
        return member(x,&((*pS)->left));
    }
    return member(x,&((*pS)->right));
}
void traverseTestAndInsert(Set *pA,Set *pB,Set *pC){
    if((*pA)==NULL){
        return ;
    }
    if(member((*pA)->label,pB)){
        insert((*pA)->label,pC);
    }
    traverseTestAndInsert(&((*pA)->left),pB,pC);
    traverseTestAndInsert(&((*pA)->right),pB,pC);
}
void setIntersection(Set *pA,Set *pB,Set *pC){
    makeNull(pC);
    traverseTestAndInsert(pA,pB,pC);
}

DIFFERENCE

void setDifference(Set *pA, Set *pB, Set *pC){
    for(int i=0; i<N; i++){
        pC->data[i] = pA->data[i] & ~pB->data[i];
    }
}
// BST
int member(int x, Node *node) {
    if (node == NULL)
        return 0;
    if (node->label == x)
        return 1;
    
    if (x < node->label)
        return member(x, node->left);

    return member(x, node->right);
}
void traversal(Node *node, Set *pB, Set *pT) {
    if (node == NULL)
        return;

    if (!member(node->label, *pB))
        insert(node->label, pT);

    traversal(node->left, pB, pT);
    traversal(node->right, pB, pT);
}
void setDifference(Set *pA, Set *pB, Set *pC) {
    (*pC) = NULL;
    traversal(*pA, pB, pC);
}

UNION

void setUnion(Set *pA, Set *pB, Set *pC){
	for(int  i=0; i<N; i++){
		pC->data[i] = pA->data[i] || pB->data[i];
	}
}
//BIT
void setUnion(Set *pA, Set *pB, Set *pC){
	for(int i=0; i<N; i++){
	    pC->data[i] = pA->data[i] | pB->data[i];
	}
}
// BST
void traverseAndInsert(Set *pA, Set *pB){
	if((*pA) == NULL){
		return;
	}
	insert((*pA)->label, pB);
	traverseAndInsert(&(*pA)->left, pB);
	traverseAndInsert(&(*pA)->right, pB);
}
void setUnion(Set *pA, Set *pB, Set *pC){
	makeNull(pC);
	traverseAndInsert(pA, pC);
	traverseAndInsert(pB, pC);
} 

ASSIGN

// BST
/// C1
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
	traverseAndInsert(pB, pA);
}
/// C2
void recursive_assign(Set *pA, Set *pB) {
    if (*pB == NULL)
        return;
    
    insert((*pB)->label, pA);
    recursive_assign(pA, &(*pB)->left);
    recursive_assign(pA, &(*pB)->right);
}

void assign(Set *pA, Set *pB) {
    (*pA) = NULL;
    recursive_assign(pA, pB);
}

EQUAL
//BST
///C1
int isSubset(Set *pA, Set *pB) { //A is a subset of B
    //returns true if *pA is a subset of *pB
    if((*pA) == NULL){
		return 1;
	}
	if(!member((*pA)->label, pB))
		return 0;
	if(!isSubset(&(*pA)->left, pB))
		return 0;
	return isSubset(&(*pA)->right, pB);
}

int equal(Set *pA, Set *pB) {
    return isSubset(pA, pB) && isSubset(pB, pA);
}
///C2
int isSubset(Set *pA, Set *pB) { //A is a subset of B
    if (*pA == NULL)
        return 1;
    
    if (!member((*pA)->label, pB))
        return 0;
        
    if (!isSubset(&(*pA)->left, pB))
        return 0;

    return isSubset(&(*pA)->right, pB);
}

int equal(Set *pA, Set *pB) {
    return isSubset(pA, pB) && isSubset(pB, pA);
}