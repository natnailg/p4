//
// Created by Natnail on 4/6/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "BuildTree.h"
#include "TreeNode.h"

//function to create a new node for the binary tree
node_t* createNode(char label){
    //allocate memo for new node
    node_t* new_Node = (struct node_t*)malloc(sizeof(struct node_t));
    //check to see if mem allocation was successful
    if(new_Node == NULL){
        printf("Error, memory allocation!\n");
        return NULL;
    }
    if (new_Node != NULL) {

        //initalize node data
        new_Node->Label = label;        // the functions
        new_Node->left = NULL;          //left child
        new_Node->center =NULL;         //some have three children
        new_Node->right = NULL;         //right child
        new_Node->far_right = NULL;     // far right child (fourth child)
        new_Node->token_instance[0] = '\0';        //token instances
    }
    //return the created node
    return new_Node;
}


//free the memory
void freeNode(node_t* node) {
    if (node == NULL) {
        return;
    }
    freeNode(node->left);
    freeNode(node->right);
    freeNode(node->center);
    freeNode(node->far_right);
    free(node);
}


