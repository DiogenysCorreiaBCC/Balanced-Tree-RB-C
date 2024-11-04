#include <stdio.h>
#include <stdlib.h>
#include "rb.h"

Tree null_node;

void initialize(Tree *root){
    *root = NULL;
	null_node = (Tree) malloc(sizeof(struct Node));
	null_node->color = DOUBLE_BLACK;
	null_node->key = 0;
    null_node->left = NULL;
    null_node->right = NULL;
}

void insert(Tree *root, int value){
    Tree position = *root, father = NULL, new;
    
    while(position != NULL){
        father = position;
        if(value < position->key){
            position = position->left;
        }else{
            position = position->right;
        }
    }
    
    new = (Tree) malloc(sizeof(Node));
    new->left = NULL;
    new->right = NULL;
    new->father = father;
    new->color = RED;
    new->key = value;
    
    if(isRoot(new)){
        *root = new;
    }else{
        if(value < father->key){
            father->left = new;
        }else{
            father->right = new;
        }
    }
    
    //printf("\nnó %d ligado ao seu pai", value);
    //printf("\n");
    adjust(root, new);
    //printf("\naqui");
    /*if(new->color == BLACK){
        printf("\n%d é preto", value);
    }else{
        printf("\n%d é vermelho", value);
    }*/
}

void adjust(Tree *root, Tree element){
    while(color(element) == RED && color(element->father) == RED){
        //Recoloração
        if(color(uncle(element)) == RED){
            element->father->father->color = RED;
            uncle(element)->color = BLACK;
            element->father->color = BLACK;

            element = element->father->father;
            continue;
        }
        //RSD
        if(isTheLeftSon(element) && isTheLeftSon(element->father)){
            element->father->color = BLACK;
            element->father->father->color = RED;

            rightRotation(root, element->father->father);

            continue;
        }
        //RSE
        if(isTheRightSon(element) && isTheRightSon(element->father)){
            element->father->color = BLACK;
            element->father->father->color = RED;

            leftRotation(root, element->father->father);
            continue;
        }
        //RDD
        if(isTheRightSon(element) && isTheLeftSon(element->father)){
            doubleRightRotation(root, element->father->father);

            element->color = BLACK;
            element->right->color = RED;
            continue;
        }
        //RDE
        if(isTheLeftSon(element) && isTheRightSon(element->father)){
            doubleLeftRotation(root, element->father->father);

            element->color = BLACK;
            element->left->color = RED;
            continue;
        }
    }
    
    (*root)->color = BLACK;
}

void leftRotation(Tree *root, Tree p){
    Tree u = p->right;
    Tree t2 = u->left;

    int isTheLeftS = isTheLeftSon(p);
    int isTheRightS = isTheRightSon(p);

    u->left = p;
    p->right = t2;

    if(t2 != NULL){
        t2->father = p;
    }

    u->father = p->father;
    p->father = u;

    if(isRoot(u)){
        *root = u;
    }else{
        if(isTheLeftS){
            u->father->left = u;
        }
        
        if(isTheRightS){
            u->father->right = u;
        }
    }
}

void rightRotation(Tree *root, Tree p){
    Tree u = p->left;
    Tree t1 = u->right;

    int isTheLeftS = isTheLeftSon(p);
    int isTheRightS = isTheRightSon(p);

    u->right = p;
    p->left = t1;

    if(t1 != NULL){
        t1->father = p;
    }

    u->father = p->father;
    p->father = u;

    if(isRoot(u)){
        *root = u;
    }else{
        if(isTheLeftS){
            u->father->left = u;
        }

        if(isTheRightS){
            u->father->right = u;
        }
    }
}

void doubleRightRotation(Tree *root, Tree p){
    Tree u = p->left;
    Tree v = u->right;
    Tree t2 = v->left;
    Tree t3 = v->right;

    int isTheLeftS = isTheLeftSon(p);
    int isTheRightS = isTheRightSon(p);

    v->left = u;
    v->right = p;
    u->right = t2;
    p->left = t3;

    v->father = p->father;
    p->father = v;
    u->father = v;

    if(t2 != NULL){
        t2->father = u;
    }

    if(t3 != NULL){
        t3->father = p;
    }

    if(isRoot(v)){
        *root = v;
    }else{
        if(isTheLeftS){
            v->father->left = v;
        }

        if(isTheRightS){
            v->father->right = v;
        }
    }
}

void doubleLeftRotation(Tree *root, Tree p){
    Tree u = p->right;
    Tree v = u->left;
    Tree t2 = v->left;
    Tree t3 = v->right;
    
    int isTheLeftS = isTheLeftSon(p);
    int isTheRightS = isTheRightSon(p);

    v->left = p;
    v->right = u;
    p->right = t2;
    u->left = t3;

    if(t2 != NULL){
        t2->father = p;
    }

    if(t3 != NULL){
        t3->father = u;
    }

    v->father = p->father;
    p->father = v;
    u->father = v;
    
    if(isRoot(v)){
        *root = v;
    }else{
        if(isTheLeftS){
            v->father->left = v;
        }

        if(isTheRightS){
            v->father->right = v;
        }
    }
}

enum color color(Tree node){
    enum color c;
    if(node == NULL || node->color == BLACK){
        c = BLACK;
    }else{
        c = RED;
    }

    return c;
}

int isRoot(Tree node){
    return (node->father == NULL);
}

int isTheLeftSon(Tree node){
    return (node->father != NULL && node->father->left == node);
}

int isTheRightSon(Tree node){
    return (node->father != NULL && node->father->right == node);
}

Tree brother(Tree node){
    if(isTheLeftSon(node)){
        return node->father->right;
    }else{
        return node->father->left;
    }
}

Tree uncle(Tree node){
    return brother(node->father);
}

void inOrder(Tree root){
    if(root){
        inOrder(root->left);
        printElement(root);
        inOrder(root->right);
    }
}

void preOrder(Tree root){
    if(root){
        printElement(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void posOrder(Tree root){
    if(root){
        posOrder(root->left);
        posOrder(root->left);
        printElement(root);
    }
}

void printElement(Tree root){
    switch(root->color){
        case BLACK:
            printf("[%d B]", root->key);
            break;
        case RED:
            printf("[%d R]", root->key);
            break;
        case DOUBLE_BLACK:
			printf("[%d DB]", root->key);
			break;
    }
}

void remov(Tree *root, int value){
    Tree position = *root;
    printf("\n");
    while(position != NULL){
        if(value == position->key){            
            //Sem filhos
            if(position->left == NULL && position->right == NULL){
                printf("\n");
                if(position->color == RED){
                    if(isTheLeftSon(position)){
                        position->father->left = NULL;
                    }else{
                        position->father->right = NULL;
                    }
                    free(position);
                    break;
                }
                if(isRoot(position)){
                    *root = NULL;
                    break;
                }
                
                
                null_node->color = DOUBLE_BLACK;
                null_node->father = position->father;

                if(isTheLeftSon(position)){
                    position->father->left = null_node;
                }else{
                    position->father->right = null_node;
                }
                free(position);
                readjust(root, null_node);
                break;
            }

            //Dois filhos
            if(position->left != NULL && position->right != NULL){
                position->key = bigger(position->left);
                remov(&(position->left), position->key);

                break;
            }

            //Um filho (Direito)
            if(position->left == NULL && position->right != NULL){
                position->right->color = BLACK;
                position->right->father = position->father;

                if(isRoot(position)){
                    *root = position->right;
                }else{
                    if(isTheRightSon(position)){
                        position->father->right = position->right;
                    }else{
                        position->father->left = position->right;
                    }
                }

                break;
            }

            //Um filho (Esquerdo)
            if(position->left != NULL && position->right == NULL){
                position->left->color = BLACK;
                position->left->father = position->father;

                if(isRoot(position)){
                    *root = position->left;
                }else{
                    if(isTheLeftSon(position)){
                        position->father->left = position->left;
                    }else{
                        position->father->right = position->left;
                    }
                }

                break;
            }
        }else{
            if(value < position->key){
                position = position->left;
            }else{
                position = position->right;
            }
        }
    }

    /*if(*root){
        (*root)->color = BLACK;
    }*/
    /*printf("\ncabô o while");
    printf("\n");*/
}

void readjust(Tree *root, Tree element){
    //Caso 1
    if(isRoot(element)){
        element->color = BLACK;

        return;
    }

    //Caso 2
    if(color(element->father) == BLACK && color(brother(element)) == RED && color((brother(element)->right)) == BLACK && color((brother(element)->left)) == BLACK){
        if(isTheLeftSon(element)){
            leftRotation(root, element->father);
        }else{
            rightRotation(root, element->father);
        }

        element->father->father->color = BLACK;
        element->father->color = RED;

        readjust(root, element);
        return;
    }

    //Caso 3
    if(color(element->father) == BLACK && color(brother(element)) == BLACK && color(brother(element)->left)== BLACK && color(brother(element)->right) == BLACK){
        element->father->color = DOUBLE_BLACK;
        brother(element)->color = RED;
    
        removeDoubleBlack(root, element);
        readjust(root, element->father);

        return;
    }

    //Caso 4
    if(color(element->father) == RED && color(brother(element)) == BLACK && color(brother(element)->left) == BLACK && color(brother(element)->right) == BLACK){
        element->father->color = BLACK;
        brother(element)->color = RED;
        
        removeDoubleBlack(root, element);

        return;
    }

    //Caso 5a
    if(isTheLeftSon(element) && color(brother(element)) == BLACK && color((brother(element))->left) == RED && color((brother(element))->right) == BLACK){rightRotation(root, brother(element));

        brother(element)->color = BLACK;
        brother(element)->right->color = RED;

        readjust(root, element);

        return;
    }

    //Caso 5b
    if(isTheRightSon(element) && color(brother(element)) == BLACK && color(brother(element)->right) == RED && color(brother(element)->left) == BLACK){
        leftRotation(root, brother(element));

        brother(element)->color = BLACK;
        brother(element)->left->color = RED;


        readjust(root, element);

        return;
    }

    //Caso 6a
    if(isTheLeftSon(element) && color(brother(element)) == BLACK && color(brother(element)->right) == RED){
        leftRotation(root, element->father);    

        element->father->father->color = element->father->color;
        element->father->color = BLACK;
        uncle(element)->color = BLACK;

        removeDoubleBlack(root, element);

        return;
    }
    
    //Caso 6b
    if(isTheRightSon(element) && color(brother(element)) == BLACK && color(brother(element)->left) == RED){
        rightRotation(root, element->father);

        element->father->father->color = element->father->color;
        element->father->color = BLACK;
        uncle(element)->color = BLACK;

        removeDoubleBlack(root, element);
        
        return;
    }
}

void removeDoubleBlack(Tree *root, Tree element){
    if(element == null_node){
        if(isTheLeftSon(element)){
            element->father->left = NULL;
        }else{
            element->father->right = NULL;
        }
    }else{
        element->color = BLACK;
    }
}

int bigger(Tree root){
    Tree aux = root;    
    while(aux->right != NULL){
        aux = aux->right;
    }
    
    return aux->key;
}



























