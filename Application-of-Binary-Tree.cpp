#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef char LabelType;

typedef struct NodeTag {
	LabelType label;
	struct NodeTag *left, *right, *parent;
} Node;

typedef Node *Tree;

void makeNull (Tree *pT) {
	*pT = NULL;
}

Tree create2(LabelType v, Tree T1, Tree T2) {
	Tree T0 = (Node*) malloc (sizeof(Node));
	T0->label = v;
	T0->left = T1;
	T0->right = T2;
	T0->parent = NULL;
	if (T1 != NULL) {
		T1->parent = T0;
	}
	if (T2 != NULL) {
		T2->parent = T0;
	}
	return T0;
}

void deleteTree(Tree *pT) {
	if (*pT == NULL) {
		return;
	}
	deleteTree(&((*pT)->left));
	deleteTree(&((*pT)->right));
	Node* parent = (*pT)->parent;
	Node* temp = *pT;
	(*pT)->parent = NULL;
	if (parent == NULL) {
		makeNull(pT);
		return;
	}
	if (parent->left == *pT) {
		parent->left = NULL;
	} else if (parent->right == *pT) {
		parent->right = NULL;
	}
	free(temp);
}

Tree copyTree (Node* root) {
	Tree newTree;
	makeNull(&newTree);
	if (root == NULL) {
		return newTree;
	}
	newTree = create2(root->label, copyTree(root->left), copyTree(root->right));
	return newTree;
}

void preorder(Node* root) {
	if (root == NULL) {
		return;
	}
	printf("%c ", root->label);
	preorder(root->left);
	preorder(root->right);
}

void inorder(Node* root) {
	if (root == NULL) {
		return;
	}	
	inorder(root->left);
	printf("%c ", root->label);
	inorder(root->right);
}

void postorder(Node* root) {
	if (root == NULL) {
		return;
	}
	postorder(root->left);
	postorder(root->right);
	printf("%c ", root->label);
}

void giaohoan(Node* root) {
	Node* temp = root->left;
	root->left = root->right;
	root->right = temp;
}

int isLetter(char s) {
	if (s >= 'A' && s <= 'Z') {
		return 1;
	}
	return 0;
}

int isOperation (char s) {
	if (s == '+' || s == '-' || s == '*') {
		return 1;
	}
	return 0;
}

int priority(char s) {
	if (s == '*') {
		return 2;
	} else if (s == '+' || s == '-') {
		return 1;
	} else if (isLetter(s)) {
		return 0;
	}
}

void phanphoi(Node* root) {
	if (root->label == '*') {
		if (isLetter(root->left->label) && isOperation(root->right->label)) {
			root->left->left = create2(root->left->label, NULL, NULL);
			root->left->right = create2(root->right->left->label, NULL, NULL);
			root->left->label = root->label;
			root->label = '+';
			root->right->left->label = root->left->left->label;
			root->right->label = root->left->label;
		} else if (isOperation(root->left->label) && isLetter(root->right->label)) {
			root->right->left = create2(root->left->right->label, NULL, NULL);
			root->right->right = create2(root->right->label, NULL, NULL);
			root->right->label = root->label;
			root->label = '+';
			root->left->right->label = root->right->right->label;
			root->left->label = root->right->label;
		}
	}
}

void binaryTreeToInfix(Node* root) {
	if (root == NULL) {
		return;
	}
	if (priority(root->label) == 2) {
		if (priority(root->left->label) == 1) {
			printf("(");
			binaryTreeToInfix(root->left);
			printf(")");
		} 
		else if (priority(root->left->label) == 0) {
			printf("%c", root->left->label);
		} 
		else if (priority(root->left->label) == 2) {
			binaryTreeToInfix(root->left);
		}
		printf("%c", root->label);
		if (priority(root->right->label) == 1) {
			printf("(");
			binaryTreeToInfix(root->right);
			printf(")");
		} 
		else if (priority(root->right->label) == 0) {
			printf("%c", root->right->label);
		} 
		else if (priority(root->right->label) == 2) {
			binaryTreeToInfix(root->right);
		}
	} else if (priority(root->label) == 1) {
		if (priority(root->left->label) >= 1) {
			binaryTreeToInfix(root->left);
		}
		else if (priority(root->left->label) == 0) {
			printf("%c", root->left->label);
		}
		printf("%c", root->label);
		if (priority(root->right->label) >= 1) {
			binaryTreeToInfix(root->right);
		}
		else if (priority(root->right->label) == 0) {
			printf("%c", root->right->label);
		}
	}
}

//Xoa Tree x
//Copy Tree x
//Giao hoan x
//Phan Phoi x
//Binary Tree -> Infix x
//Postfix -> Binary Tree 
//Infix -> Postfix

int main() {
	Tree T1 = create2('A', NULL, NULL);
	Tree T2 = create2('B', NULL, NULL);
	Tree T3 = create2('C', NULL, NULL);
	Tree T4 = create2('D', NULL, NULL);
//	Tree plus = create2('+', T2, T3);
	Tree plus1 = create2('+', T1, T4);	
	Tree plus2 = create2('+', T2, T3);
//	Tree multi = create2('*', T1, plus);
	Tree multi = create2('*', plus1, plus2);
//	deleteTree(&plus);
	preorder(multi);
	printf("\n");
	inorder(multi);
	printf("\n");
	postorder(multi);
	printf("\n");
	
/* Giao hoan
	giaohoan(multi);
	preorder(multi);
	printf("\n");
	inorder(multi);
	printf("\n");
	postorder(multi);
	printf("\n");
*/

// Copy Tree va xoa Tree
//	Tree fix2 = copyTree(multi);
//	deleteTree(&fix2);
//	preorder(fix2);
//	printf("\n");
//	inorder(fix2);
//	printf("\n");
//	postorder(fix2);
//	printf("\n");


//	Tree fix3 = copyTree(multi);
//	giaohoan(fix3);
//	phanphoi(fix2);
//	preorder(fix3);
//	printf("\n");
//	inorder(fix3);
//	printf("\n");
//	postorder(fix3);
//	printf("\n");
	binaryTreeToInfix(multi);
	return 0;
}
