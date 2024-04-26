//
// Created by Natnail on 4/6/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Parser.h"
#include "BuildTree.h"
#include "TreeNode.h"
#include "testTree.h"


void print_preorder_tree(node_t* root, int depth) {
    if (root == NULL) {
        // printf("Error root is Null in PrintAST\n");
        return;
    }

    // skip printing nodes with label ' ', i can't find any other way to format it beside creating another empty node.
    if (root->Label != ' ')
    {
        printf("%*c%c\n", depth*3, ' ', root->Label);
    }//
    else{
        // print token instance if it exists

        if(root->token_id != 0){
            //printf("%d", tokens.tokenid);
            printf("%*c %s, %s\n", depth * 3, ' ', root->token_id, root->token_instance);

        }else{
            //printf("inside of else %d", tokens.tokenid);
            printf("%*c %s\n", depth * 3, ' ', root->token_instance); // this is the only way which i can print the empty with out token being 0

        }

    }

    // recursively print the left subtree with increased depth
    if(root->left != NULL){
        print_preorder_tree(root->left, depth + 1);
    }
    // recursively print the center (second child) subtree with increased depth
    if(root->center != NULL) {
        print_preorder_tree(root->center, depth + 1);
    }

    // recursively print the center (third child) subtree with increased depth
    if(root->right != NULL) {
        print_preorder_tree(root->right, depth + 1);
    }

    // recursively print the center (fourth child) subtree with increased depth
    if(root->far_right != NULL) {
        print_preorder_tree(root->far_right, depth + 1);
    }
}


