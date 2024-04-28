//
// Created by Natnail on 4/6/2024.
//

#ifndef P3_TREENODE_H
#define P3_TREENODE_H

#include "BuildTree.h"
#define MAX_INSTANCE_TOKENS 256

typedef struct node_t{

    char Label; // the value of the node (label of the functions)
    struct node_t* left; // pointer to the left node
    struct node_t* right; // pointer to the right
    struct node_t* center;
    struct node_t* far_right;
    char token_instance[MAX_INSTANCE_TOKENS];  //printing token instance value
    char* token_id;
    int token_ID; // for the tree to be able to evaluate it in semantics.
}node_t;


#endif //P3_TREENODE_H
