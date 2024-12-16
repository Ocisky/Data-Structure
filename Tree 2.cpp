Node* rotate(Node *r){
	Node* newRoot = r->right;
	Node* newright = newRoot->left;
	newRoot->left = r;
	r->right = newright;
	return newRoot;
}
 
// right rotate
Node* rotate(Node *r){
    Node* nroot = r->left;
    Node* nleft = nroot->right;
    nroot->right = r;
    r->left = nleft;
    return nroot;
}

int numberOfInteriorNodes(Tree n){
	if(n == NULL){
		return 0;
	}
	if(n->left != NULL || n->right != NULL){
		return numberOfInteriorNodes(n->left) + numberOfInteriorNodes(n->right) +1 ;
    }
	return 0;
}

int retrieveMark(char n[], StudentBST T){
	if(T == NULL){
		return -968;
	}
	if(strcmp(n, T->label.name) == 0){
		return T->label.mark;
	}
	if(strcmp(n, T->label.name) < 0)  return retrieveMark(n, T->left);
	return retrieveMark(n, T->right);
}
int retrieveMark(char n[], StudentBST* pT){
	if(*pT == NULL) return -680;
	if(strcmp(n, (*pT)->label.name) == 0) return (*pT)->label.mark;
	if(strcmp(n, (*pT)->label.name) < 0) return retrieveMark(n, &(*pT)->left);
	return retrieveMark(n, &(*pT)->right);
}

int first;
void inorder(Node *n) {
    if(n == NULL) return;
    inorder(n->left);
    if(first == 1){
        printf("%s: %d", n->label.name, n->label.mark);
        first++;
    }else
    printf(",\n%s: %d", n->label.name, n->label.mark);
    inorder(n->right);
}
void printStudents(StudentBST T) {
    first = 1;
    inorder(T);
    printf("\n==END==\n");
}

void insert (char n[], int m, StudentBST *pT) {
    if (*pT == NULL) {
        *pT = (StudentBST) malloc (sizeof(Node));
        strcpy((*pT)->label.name, n);
        (*pT)->label.mark = m;
        (*pT)->left = (*pT)->right = NULL;
        return;
    }
    if(strcmp(n, (*pT)->label.name) == 0) {
        printf("The name has existed.\n");
        return;
    }
    if(strcmp(n, (*pT)->label.name) < 0) {
        insert(n, m, &(*pT)->left);
    }else{
        insert(n, m, &(*pT)->right);
    }
}

void transformWithPseudoAssociativity(Node* r){
	if(r == NULL) return;
	if(r->label == '-' && r->left->label == '-'){
		Node *newLeft = r->left->left;
		Node *newRight = r->left;
		newRight->label = '+';
		Node *newRightLeft = r->left->right;
		Node *newRightRight = r->right;
		r->right = newRight;
		r->left = newLeft;
		r->right->left = newRightLeft;
		r->right->right = newRightRight;
		return;
	}
	transformWithPseudoAssociativity(r->left);
	transformWithPseudoAssociativity(r->right);
}

int max(int a, int b){
	return (a > b) ? a : b;
}
int height(Tree n){
	if(n == NULL) return -1;
	return max(height(n->left), height(n->right)) + 1;
}

int countByMark(int v, StudentBST *pT){
	if((*pT) == NULL) return 0;
	if(v <= (*pT)->label.mark) return countByMark(v, &(*pT)->left) + countByMark(v, &(*pT)->right) + 1;
	return countByMark(v, &(*pT)->left) + countByMark(v, &(*pT)->right);
}
int countByMark(int v, StudentBST T){
	if(T == NULL) return 0;
	if(v <= T->label.mark) return countByMark(v, T->left) + countByMark(v, T->right) + 1;
	return countByMark(v, T->left) + countByMark(v, T->right);
}
/////
void preorder(int v, StudentBST n, StudentBST *pResult) {
    if(n == NULL) return;
    if(n->label.mark >= v) insert(n->label.name,n->label.mark, pResult);
    preorder(v, n->left, pResult);
	preorder(v, n->right, pResult);
}
StudentBST filterByMark(int v, StudentBST *pT) {
    StudentBST result = NULL;
    preorder(v, *pT, &result);    
    return result;
}


int max(int a, int b){
	if (a >= b) {
		return a;
	}
	return b;
}

int height(Node* n) {
    if (n == NULL) {
        return -1;
    }
    return max(height(n->left), height(n->right)) + 1;
}
void insert (char n[], int m, StudentBST *pT) {
    if (*pT == NULL) {
        *pT = (StudentBST) malloc (sizeof(Node));
        strcpy((*pT)->label.name, n);
        (*pT)->label.mark = m;
        (*pT)->left = (*pT)->right = NULL;
        return;
    }
    if (strcmp(n, (*pT)->label.name) == 0) {
        printf("The name has existed.\n");
        return;
    }
    if (strcmp(n, (*pT)->label.name) < 0) {
        insert(n, m, &(*pT)->left);
    } else {
        insert(n, m, &(*pT)->right);
    }
}

void copyTree(Tree *pT1, Tree *pT2) {
    if (*pT2 == NULL) {
        return;
    }
    *pT1 = (Tree) malloc (sizeof(Node));
    (*pT1)->label = (*pT2)->label;
    copyTree(&(*pT1)->left, &(*pT2)->left);
    copyTree(&(*pT1)->right, &(*pT2)->right);
}
void update(char* n, int m, StudentBST T) {
	if (T == NULL) {
		printf("The student does not exist.\n");
		return;
	}
	if (strcmp(n, T->label.name) == 0) {
		T->label.mark = m;
		return;
	}
	if (strcmp(n, T->label.name) < 0) {
		update(n, m, T->left);
	} else {
		update(n, m, T->right);
	}
}
Tree copyTree(Node* T) {
    if (T == NULL) {
        return NULL;
    }
    Node* newTree = (Node*) malloc (sizeof(Node));
    newTree->label = T->label;
    newTree->parent = NULL;
    newTree->left = copyTree(T->left);
    newTree->right = copyTree(T->right);
    if (newTree->left != NULL) {
        newTree->left->parent = newTree;
    }
    if (newTree->right != NULL) {
        newTree->right->parent = newTree;
    }
    return newTree;
}
=====

void preorder(int v, Node *n, StudentBST *pResult){
	if(n == NULL){
		return;
	}
	if(v <= n->label.mark){
		insert(n->label.name, n->label.mark, pResult);
	}
	preorder(v, n->left, pResult);
	preorder(v, n->right, pResult);
}

Node* filterByMark(int v, StudentBST T){
	Tree p = NULL;
	preorder(v, T, &p);
	return p;
}

void transformWithPseudoAssociativity(Node *r){
	Node* left = r->left->left;
	Node* right = r->left;
	Node* rl = r->left->right; 
	Node* rr = r->right;
	if(right->label == ':' ){
		right->label = '*';
	}
	r->left = left;
	r->right =right;
	r->right->left = rl;	
	r->right->right = rr;
}

void transformWithAssociativity(Node *r){
	Node *l = r->left->left;
	Node *ri = r->left;
	Node *rl = r->left->right;
	Node *rr = r->right;
	if(ri->label == '+'){
		ri->label = '+';
	}
	r->left = l;
	r->right = ri;
	r->right->left = rl;
	r->right->right = rr;
}






