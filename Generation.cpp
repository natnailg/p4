//
// Created by Natnail on 4/26/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TreeNode.h"
#include "Generation.h"

FILE *global_file_pointer = NULL; // Global variable definition
// function to open the global files
void open_file_global(const char *file_path) {
    global_file_pointer = fopen(file_path, "w"); // Open file in append mode
    if (global_file_pointer == NULL) {
        perror("Error opening file\n");
    }
}

void close_file() {
    if (global_file_pointer != NULL) {
        fclose(global_file_pointer);
        global_file_pointer = NULL;
    }
}


// read in int and allocate memory to, any number of additional operations
void funcS(node_t* root) {
    fprintf(global_file_pointer, "Calling C and D in S\n");
    printf("\nfuncS %c -- %c \n", root->left->Label, root->center->Label);
    funcC(root->left);
    funcD(root->center);
}
// A->FK (we will just call those functions, First set of A = t1 t2)
void funcA(){}
// assigns the value of A to identifier t2
void funcB(){}
// read in int, allocate memory (e.g. v10 for %10), assign value = int
//in class example for c is
void funcC(node_t* node) {
    if (node == NULL) {
        printf("Error: NULL node encountered in funcC\n");
        return;
    }
    if (node->left != NULL) {
//  fprintf(global_file_pointer, "Read %s\n",nodeptr.child1(left in my case));
        fprintf(global_file_pointer, "READ %s", node->left->token_instance);
        printf("funC--  %c  -- %s\n", node->left->token_id, node->left->token_instance);

    }else {
        printf("Node C is empty!\n");
    }
}
//
//D -> L (first set of D = , ,; . t2 *" ? epsilon
void funcD(node_t* node){
    if (node == NULL) {
        printf("Error: NULL node encountered in funcC\n");
        return;
    }

    printf("\n %c -- %c \n", node->left->Label, node->left->Label);
//    funcL(node);
}
// if first A > second A, do H | do H F times
void funcE(){}
// number | identifier // F-> t1 | t2 (first set of F = t1 | t2)//
void funcF(){}
// assignment | read int and allocate memory | print value to screen
void funcG(){}
// if, for | assignment, read int and allocate memory, print value
void funcH() {}
// print integer value to screen (sum, int, or identifier)
void funcJ(){}
// H ? D | Identifier
void funcL(node_t* node){
//    printf("\n %c -- %c \n", node->left->Label, node->center->Label);
//    funcH();
//    funcD();
}
// K -> F ?$ | . (first set of K = t1 t2 | .
void funcK(){}
