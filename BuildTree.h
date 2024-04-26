//
// Created by Natnail on 4/6/2024.
//

#ifndef P3_BUILDTREE_H
#define P3_BUILDTREE_H


struct node_t* createNode(char); // for creating a new node for tree, takes a value

void print_preorder_tree(node_t* root, int depth); //printing the tree pre-order

void freeNode(node_t* node); //free memory


#endif //P3_BUILDTREE_H
