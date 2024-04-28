//
// Created by Natnail on 4/26/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "TreeNode.h"
#include "Generation.h"
#include "semantics.h"

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

///////////////////////
// create a function for temp varaiables.
#define Max_temp_variables 20
char* Temp_var_table[Max_temp_variables];
int table_index_var = 0;

char* Gen_temp_var(){
    if (table_index_var >= Max_temp_variables) {
        printf("Error: Max number of temp vars reached\n");
        return NULL;
    }
    // let's allocate memory for the temp variable
    char* temp = (char*)malloc(sizeof(char) * 10);
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    // we need to create new temp variable name (T0, T1, T2, ...)
    snprintf(temp, 10, "T%d", table_index_var);

    // atore the new temp var in the Temp_var_table
    Temp_var_table[table_index_var] = temp;
    table_index_var++;

    return temp;
}
/////////////////////////////
//create a function for Generation_code
void Generation_code(node_t* root){

    if (root->Label == 'S'){
        funcS(root);

    }else{
        printf("Root Node not met in generation_Code\n");
    }

//    fprintf(global_file_pointer, "STOP\n");
//
//    // we also need to set the var read from the tree for %3242 or v23 to 0
//    for (int i = 0; i < max_size_table; i++){
//        if(table_array[i] != '\0'){
//            fprintf(global_file_pointer,"%s 0\n", table_array[i]);
//        }
//
//    }
//    // i need to loop and assign 0 to the created variable
//    for(int i = 0; i < Max_temp_variables; i++){
//        if (Temp_var_table[i] != '\0') {
//            fprintf(global_file_pointer,"%s 0\n", Temp_var_table[i]);
//        }
//    }

//    fprintf(global_file_pointer, "STOP\n");
}
/////////////////////////////////////////
//stop function
void STOP_ASM(){
    fprintf(global_file_pointer, "STOP\n");

    // we also need to set the var read from the tree for %3242 or v23 to 0
    for (int i = 0; i < max_size_table; i++){
        if(table_array[i] != '\0'){
            fprintf(global_file_pointer,"%s 0\n", table_array[i]);
        }

    }
    // i need to loop and assign 0 to the created variable
    for(int i = 0; i < Max_temp_variables; i++){
        if (Temp_var_table[i] != '\0') {
            fprintf(global_file_pointer,"%s 0\n", Temp_var_table[i]);
        }
    }
}
/////////////////////////////

// read in int and allocate memory to, any number of additional operations
// (right->C) (center->D)
void funcS(node_t* root) {
    printf("\nfuncS calling %c -- %c \n", root->left->Label, root->center->Label);
    funcC(root->left);
    funcD(root->center);
    STOP_ASM(); //closing out
}
// A->FK (left->F)(center->K)
// sum " int or identiguer (given in class)
char* funcA(node_t* node){
    printf("\nEntering A called from J caaling F\n");
    char* value_1 = funcF(node->left);
    char* value_2 = funcK(node->center,value_1);
    printf(" before returning %s", value_2);

     return value_2; //return num

}
// assigns the value of A to identifier t2 (load and store in to accumulator) need tempstr
void funcB(node_t* node){
    char* tempStr = funcA(node->right);
    fprintf(global_file_pointer,"LOAD %s\n", tempStr);
    fprintf(global_file_pointer,"STORE %s\n", node->center->token_instance); //we need the V20.

}
// read in int, allocate memory (e.g. v10 for %10), assign value = int
//in class example for c is
// t2* (left->t2) (center-> *)
void funcC(node_t* node) {
    if (node == NULL) {
        printf("Error: NULL node encountered in funcC\n");
        return;
    }
    if (node->left != NULL) {
        fprintf(global_file_pointer, "READ %s\n", node->left->token_instance);
    }
    if(node->center != NULL) { // *
        printf("funC--  %c  -- %s\n\n", node->center->token_id, node->center->token_instance);
    }
}
//
//D -> L (first set of L = , ,; . t2 *" ? epsilon
void funcD(node_t* node){
    if (node == NULL) {
        printf("Error: NULL node encountered in funcD\n");
        return;
    }
    if (node->left != NULL) {
        printf("funcD calling L: %c -- %s \n", node->left->Label, node->left->token_instance);
        funcL(node->left);
    }
}
// if first A > second A, do H | do H F times
void funcE(){}
// number | identifier // F-> t1 | t2 (first set of F = t1 | t2)//
char* funcF(node_t* node){

    char* buffer;
    //t1
    if (node->left->token_ID == 1){

        //upper case positive
        if (node->left->token_instance[0] >= 'A' && node->left->token_instance[0] <= 'Z'){
            //copy/duplicate
            printf("\n\nin positive\n");
            return strdup(node->left->token_instance + 1); // - the letter (duplicates the number).

        }else{//lower case negative
            printf("\n\nin negative\n");
            buffer = (char*) malloc(strlen(node->left->token_instance));
            sprintf(buffer, "-%s", node->left->token_instance + 1); //-minus the letter @ 0
            return buffer;

        }
    }

    //t2 identifier
    else if(node->left->token_ID == 2){
        return strdup(node->left->token_instance);
    }
    printf("\ninside of F called from A\n\n");
    return NULL;
}

// assignment | read int and allocate memory | print value to screen
// B | C | J (right -> B) (center-> C) (right-> J)
void funcG(node_t* node){
//    printf("inside of G --- %C\n", node->right->Label);
    if(node->left->Label == 'B') {
        //call B (haven't go to b YET
        printf("inside of G--- %c\n", node->left->Label);
        funcB(node->left);

    }
    else if(node->right->Label == 'J'){
        printf("\ninside G called j BELOW\n");
        funcJ(node->right);
    }
    else if(node->center->Label == 'C'){
        funcC(node->center);
    }

}
//
// if, for | assignment, read int and allocate memory, print value (E? | G. | empty)
void funcH(node_t* node){
    printf("\n in the dame funcH: %c -- %s \n", node->left->Label, node->left->token_instance);
    //if left is empty out!
    if (strcmp(node->left->token_instance, "Empty") == 0){
        printf("E-L- This is empty!!\n");
        return;
    }
    //calling node G, if the label is G, { . t2 *" } || {. & t3}
    if(node->left->Label == 'G'){
        funcG(node->left);
    }
    if(node->left->Label == 'E'){
        printf("inside H called E BELOW\n");
//        funcE(node->left);
        printf("inside H called E above\n");
    }

}


// print integer value to screen (sum, int, or identifier)
// *"A. (left -> *" (print value)) (center -> A) (right -> .)
void funcJ(node_t* node){
//    printf("\n in func J: %c -- %s \n", node->left->Label, node->left->token_instance);
    // *"A.
    // left -> *"
    if (node->left->Label == ' ') {
        printf("funcJ-  L: %c -- %s \n", node->left->Label, node->left->token_instance);
//        funcL(node->left);
    }
    // center -> A//
    if (node->center->Label == 'A') {
        printf("funcJ- C: %c -- %s \n", node->center->Label, node->center->token_instance);
        char* value = funcA(node->center);
        fprintf(global_file_pointer, "WRITE %s\n", value);

    }
    // right -> .
    if (node->right->Label == ' ') {//.
        printf("funcJ - R: %c -- %s \n", node->right->Label, node->right->token_instance);
//        funcL(node->right);
    }

}
// H ? D | Identifier (left -> H | empty) (center-> ?) (right -> L (recursive))
void funcL(node_t* node){
    //if it is empty on the left.
    if (strcmp(node->left->token_instance, "Empty") == 0){
        printf("\nE-L- This is empty!!\n");
        return;
    }
    else{
        funcH(node->left);
        funcL( node->right);
    }

}

// K -> F ?$ | . (first set of K = t1 t2 | .
// (left-> F(Call F) | .) (center-> ?$ (add))
// value is nodeptr.child1 from A
char* funcK(node_t* node, char* value){

    printf("\ninside of K Called from A\n");
    if(node->left->Label == 'F'){


        printf("F from K If statment  %s \n", value);
        return NULL;
    }
    else{// .
        char* temp_val = Gen_temp_var();
        printf("\n new temp val creatd %s\n", temp_val);
        printf("F from K ELSE statment %s \n", value);
        //fprintf("LOAD %S \n", nodeptr.child1);
        //(store T0\n)
        fprintf(global_file_pointer,"LOAD %s\n", value);
        fprintf(global_file_pointer, "STORE %s\n", temp_val);

        return temp_val;
    }

    return NULL;
}

//reacource:
//https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_fprintf.htm