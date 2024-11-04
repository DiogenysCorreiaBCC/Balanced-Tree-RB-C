#ifndef RB_H
#define RB_H

enum color { RED, BLACK, DOUBLE_BLACK };

typedef struct Node {
	int key;
	enum color color;
	struct Node *left, *right, *father;
} Node;


typedef Node *Tree;

extern Tree null_node;

void initialize(Tree *root);
void insert(Tree *root, int value);
enum color color(Tree node);
int isRoot(Tree node);
int isTheLeftSon(Tree node);
int isTheRightSon(Tree node);
Tree brother(Tree node);
Tree uncle(Tree node);
void adjust(Tree *root, Tree element);
void leftRotation(Tree *root, Tree p);
void rightRotation(Tree *root, Tree p);
void doubleRightRotation(Tree *root, Tree p);
void doubleLeftRotation(Tree *root, Tree p);
void inOrder(Tree root);
void posOrder(Tree root);
void preOrder(Tree root);
void remov(Tree *root, int value);
int bigger(Tree root);
void readjust(Tree *root, Tree element);
void removeDoubleBlack(Tree *root, Tree element);
void printElement(Tree root);

#endif









































































