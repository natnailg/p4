//
// Created by Natnail on 4/26/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TreeNode.h"
#include "Generation.h"
///////////////////////
char

/////////////////////////////
//create a function for Generation_code
void Generation_code(node_t* root){
    if (root->Label == 'S'){
        funcS(root);

    }else{
        printf("Root Node not met in generation_Code\n");
    }

}
/////////////////////////////
// create a function for temp varaiables.



////////////////////////////////
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
void funcA(){

}
// assigns the value of A to identifier t2 (load and store in to accumulator) need tempstr
void funcB(node_t* node){}
// read in int, allocate memory (e.g. v10 for %10), assign value = int
//in class example for c is
void funcC(node_t* node) {
    if (node == NULL) {
        printf("Error: NULL node encountered in funcC\n");
        return;
    }
    if (node->left != NULL) {
        //  fprintf(global_file_pointer, "Read %s\n",nodeptr.child1(left in my case));
        fprintf(global_file_pointer, "READ %s\n", node->left->token_instance);
        printf("funC--  %c  -- %s\n", node->left->token_id, node->left->token_instance);

    }
    if(node->center != NULL) {
        printf("funC--  %c  -- %s\n", node->center->token_id, node->center->token_instance);
    }
}
//
//D -> L (first set of D = , ,; . t2 *" ? epsilon
void funcD(node_t* node){
    if (node == NULL) {
        printf("Error: NULL node encountered in funcD\n");
        return;
    }
    if (node->left != NULL) {
        printf("funcD: %c -- %s \n", node->left->Label, node->left->token_instance);
        funcL(node->left);
    }
    if(node->center != NULL) {
        printf("funD--  %c  -- %s\n", node->center->token_id, node->center->token_instance);

    }else {
        printf("Node D is empty!\n");

    }


}
// if first A > second A, do H | do H F times
void funcE(){}
// number | identifier // F-> t1 | t2 (first set of F = t1 | t2)//
void funcF(){}
// assignment | read int and allocate memory | print value to screen
void funcG(node_t* node){
    printf("inside of G --- %C\n", node->left->Label);

}
// if, for | assignment, read int and allocate memory, print value (E? | G. | empty)
void funcH(node_t* node){
    printf("\n in the dame funcH: %c -- %s \n", node->left->Label, node->left->token_instance);

    if (strcmp(node->left->token_instance, "Empty") == 0){
        printf("E-L- This is empty!!\n");
        return;
    }
    //calling node G, if the label is G
    if(node->left->Label == 'G'){
        funcG(node->left);
    }
//
//    if (node->left != NULL && strcmp(node->left->token_instance, "Empty") != 0) {
//        printf("H This is empty!!\n");
//        return;
//    }
//    if (node->left != NULL) {
//        printf("\nfuncH: %c -- %s \n", node->left->Label, node->left->token_instance);
//    }
//    if (node->center != NULL) {
//        printf("\nfuncH: %c -- %s \n", node->center->Label, node->center->token_instance);
//    }
//    if (node->right != NULL) {
//        printf("\nfuncH: %c -- %s \n", node->right->Label, node->right->token_instance);
//    }
}


// print integer value to screen (sum, int, or identifier)
void funcJ(){}
// H ? D | Identifier
void funcL(node_t* node){
    //if it is empty on the left.
    if (strcmp(node->left->token_instance, "Empty") == 0){
        printf("E-L- This is empty!!\n");
        return;
    }
    else{
        funcH(node->left);
        funcL( node->right);
    }


//    if (node->left != NULL && strcmp(node->left->token_instance, "Empty") != 0) {
//        printf("\nleft funcL: %c -- %s \n", node->left->Label, node->left->token_instance);
//        funcH(node->left);
//    }
//
//    if (node->center != NULL) {
//        printf("\ncenter funcL: %c -- %s \n", node->center->Label, node->center->token_instance);
//    }
//
//    if (node->right != NULL) {
//        printf("\nright funcL: %c -- %s \n", node->right->Label, node->right->token_instance);
//        funcL( node->right);
//    }



    /*
     * if child is empty return
     * else H(left), L(right)
     **/
//    printf("\n %c -- %c \n", node->left->Label, node->center->Label);


}
// K -> F ?$ | . (first set of K = t1 t2 | .
void funcK(){}
