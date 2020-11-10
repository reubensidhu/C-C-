#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include "bst.h"

// Your source code here

Node* insertNode(Node *root, int value) {
    
    //Node* current = root;
    if (root == NULL) {
        Node *new = (Node*)malloc(sizeof(struct Node));
        new->data = value;
        new->left = NULL;
        new->right = NULL;
        return new;
        //return new;
    }
    else{ 
        if (value > root->data) {
            //root = root->right;
            root->right = insertNode (root->right, value);
        }
        else {
            //root = root->left;
            root->left = insertNode (root->left, value);
        }
    }
    return root;
   }

Node* deleteNode(Node* root, int value) {
    //Node* current = root;

    if (root == NULL) {
        return NULL;
    }

    else if (value > root->data){
        root->right = deleteNode (root->right, value);
    }

    else if (value < root->data){
        root->left = deleteNode (root->left, value);
    }

    else {
        if ((root->left == NULL) && (root->right == NULL)) {
        free (root);
        return NULL;
        }
        else if ((root->left != NULL) && (root->right == NULL)) {
            Node* new = root->left;
            free(root);
            return new;
        }
        else if ((root->left == NULL) && (root->right != NULL)) {
            Node* new = root->right;
            free(root);
            return new;
        }
        else {
            if ((root->right)->left != NULL) {
            Node* new = (root->right)->left;
            root->data = new->data;
            root->right = deleteNode (root->right, new->data);
            }
            else {
                Node* new = root->right;
                root->data = new->data;
                root->right = deleteNode (root->right, new->data);
            }
        }
        return root;
    }
    
    /*while (current->data != value) {
        if ((current->data) < value) {
            current = current->right;
         }
        else if ((current->data) > value) {
            current = current->left;
         }
    }

    if ((current->left == NULL) && (current->right == NULL)) {
        current = NULL;
    }

    else if ((current->left != NULL) && (current->right == NULL)) {
        current->data = current->left->data;
        current->left = NULL;
        current->right = NULL;
    }

    else if ((current->right != NULL) && (current->left == NULL)) {
        current->data = current->right->data;
        current->left = NULL;
        current->right = NULL;
    }

    else
    {
        current->data = current->right->left->data;
        current->right->left = NULL;
    } */
     
}

void printSubtree(Node *N) { 
     if (N == NULL) //{
          return;
     //} 
     printSubtree(N->left); 
     printf("%d\n", N->data);   
     printSubtree(N->right); 
}

int countNodes(Node *N) { 
     if (N == NULL) {
          return 0;
     } 
     int num = 1 + countNodes(N->left) + countNodes(N->right);
     return num; 
}

/*int countNodes(Node *N){
    if (N == NULL) 
       return 0; 
   
    int num = 0; 
    if  ((N->left != NULL) && (N->right !=NULL)) {
        num = num + 1;
    }
    num = num + (countNodes(N->left) +  
            countNodes(N->right)); 
    return num;
} */

Node* freeSubtree(Node *N) {
    if (N == NULL) {
        return N;
    }
    else {
        N->right = freeSubtree(N->right);
        N->left = freeSubtree(N->left);
        free(N);
    }
    return NULL;
}

int sumSubtree(Node *N) {
     if (N == NULL) 
        return 0; 
    int sum = N->data + sumSubtree(N->left) + sumSubtree(N->right);
    return sum; 
}


int main()
{
	Node *root=NULL;
	
	root=insertNode(root, 14);
	root=insertNode(root, 12);
    root=insertNode(root, 2);
	root=insertNode(root, 6);
	root=insertNode(root, 17);
	root=insertNode(root, 8);
	printSubtree(root);
	printf("\n");
	printf("%d\n", sumSubtree(root));
	root=deleteNode(root,14);
	root=deleteNode(root,8);
    printf("\n");
	printSubtree(root);
    printf("Number of nodes=%d\n", countNodes(root));
	root=freeSubtree(root);
	printf("Number of nodes=%d\n", countNodes(root));

	return 0;
}  