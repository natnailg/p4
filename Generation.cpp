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
// function to open the global file so, we can write to it later in the functions.
void open_file_global(char *file_path) {

    global_file_pointer = fopen(file_path, "w"); // Open file in append mode
    if (global_file_pointer == NULL) {
        perror("Error opening file\n");
    }
}
// Responsible for closing the file we have created for the asm
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

// This is for generating a new new temp variables.
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
    snprintf(temp, 10, "V%d", table_index_var);

    // store the new temp var in the Temp_var_table
    Temp_var_table[table_index_var] = temp;
    table_index_var++;

    return temp;
}
/////////////////////////////
//create a function for Generation_code
void Generation_code(node_t* root){
    //checking for the root and calling S.
    if (root->Label == 'S'){
        funcS(root);

    }else{
        printf("Root Node not met in generation_Code\n");
    }
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
// sum " int or identifier (given in class) // we can just return and int in class lecture.
// it is going to look at the value and whatever the value it happens to be. It could be identifier or a direct number.
// it could be two numbers that could be added together.
// (so it has to check to see which one is in the program if it has just one child or three children.)
// the first production will sum the values for the two. the second will return just a value.)
char* funcA(node_t* node){
    printf("\nEntering A\n");
    char* value1 = funcF(node->left);
    char* value2 = funcK(node->center,value1);

     return value2; //return temp t2 var
}
/////////////////////////////////////////////////////////////////////////////////////////
// assigns the value of A to identifier t2 (load and store in to accumulator) need tempstr
// just assigns what ever is returner from A to t2
void funcB(node_t* node){
    printf("\nEntering B \n");
    char* tempStr = funcA(node->right); //A(is the third)
    fprintf(global_file_pointer,"LOAD %s\n", tempStr);
    fprintf(global_file_pointer,"STORE %s\n", node->center->token_instance); //we need the V20 (child two).
}
///////////////////////////////////////////////////////////////////////////////////////
// read in int, allocate memory (e.g. v10 for %10), assign value = int
//in class example for c is (sole responsible for reading and storing)
// t2* (left->t2) (center-> *)
void funcC(node_t* node) {
    printf("func C %c --- %s", node->left->Label, node->center->token_id);
    if (node == NULL) {
        printf("Error: NULL node encountered in funcC\n");
        return;
    }
    if (node->left != NULL) {
        fprintf(global_file_pointer, "READ %s\n", node->left->token_instance);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
//D -> L (first set of L = , ,; . t2 *" ? epsilon
//(responsible for call L )
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
////////////////////////////////////////////////////////////////////////////////////////////
// ,AAH | ,;FH
// , if the firs operand is greater than the second operand. do the third operand
// ,; for the first operand number of times do, do the second operand. (while loop??)
void funcE(node_t* node){
    if(node->left == NULL){
        printf("Error in funcE left node Null\n");
        return;
    }
    // if A > A call H
    if(node->left != NULL) {
        printf("\nEntering E\n");

//        P-> left = E_tk_ptr; //,;
//        tokens = Scanner(); //consume
//        P-> center = A();
//        P-> right = A();
//        P-> far_right = H();
        if(node->left->token_instance[0] == ',' && node->left->token_instance[1] != ';'){
            //AAH
            char* value1 = funcA(node->center);
            char* value2 = funcA(node->right);
//            if A > A do H  (4 - 3) = 1 do H(call H)
//            if A < A break (3 - 4) = -1 break  && (4-4) = 0 break
//            LOAD value1
//            SUB value2
//            BRZNEG out1
//            call H
//            out1 : NOOP
//            stop
//            value2 0
//            value1 0
            fprintf(global_file_pointer, "LOAD %s\n", value1);
            fprintf(global_file_pointer, "SUB %s\n", value2);
            fprintf(global_file_pointer, "BRZNEG out1\n");
            funcH(node->far_right);
            fprintf(global_file_pointer, "out1: NOOP\n");

        }
        else if (node->left->token_instance[0] == ',' && node->left->token_instance[1] == ';') {
//            //we call F that get either an int or identifier.
                // ,; for the first operand number of times, do the second operand
            char* value = funcF(node->center);


            char* tempStr = Gen_temp_var(); //temp var

            fprintf(global_file_pointer, "LOAD %s", value);
            fprintf(global_file_pointer, "STORE %S", tempStr);

            //we then load that with loop like the asm example.
            fprintf(global_file_pointer, "Loop: LOAD %s\n", value); //while F
            fprintf(global_file_pointer,"SUB 1 \n");
            fprintf(global_file_pointer,"BRZNEG: out1 \n");
            funcH(node->right);
            fprintf(global_file_pointer, "STORE %s \n", value);
            fprintf(global_file_pointer, "BR Loop\n");

            //breaking out the loop
            fprintf(global_file_pointer, "out1: NOOP\n");




//            fprintf(global_file_pointer,"LOAD ")
//            fprintf();
//            fprintf(global_file_pointer, "")

//            // since F give me an int or Identifier we need to load that in
//            fprintf(global_file_pointer, "LOAD %s\n", value);
//            //do H F times
//
//
//            printf("E called (F called above!) %s\n", value);
//            funcH(node->right);
//            printf("E called (H called above!)\n");
//
//
        }
    }
}
////////////////////////////////////////////////////////////////////////////////////////
// number | identifier // F-> t1 | t2 (first set of F = t1 | t2)//
// get either int or identifier
char* funcF(node_t* node){
    printf("\nEntering F\n");
    char* buffer; //string
    //t1 int
    if (node->left->token_ID == 1){
        //upper case positive
        if (isupper (node->left->token_instance[0])){
            return strdup(node->left->token_instance + 1); // - the letter (duplicates from index (1)->). duplicates starting from

        }else{//lower case negative
            printf("in negative\n");
            buffer = (char*) malloc(strlen(node->left->token_instance));
            sprintf(buffer, "-%s", node->left->token_instance + 1); //-minus the letter @ 0
            return buffer;

        }
    }
    //t2 identifier
    else if(node->left->token_ID == 2){
        printf("inside of F T2\n");
        return strdup(node->left->token_instance);
    }
    printf("\ninside of F called from A\n\n");
    return NULL;
}

// assignment | read int and allocate memory | print value to screen
// B | C | J (right -> B) (center-> C) (right-> J)
// calling other non-terminals.
void funcG(node_t* node){

    printf("\nEntering G\n");
    if (node->left != NULL) {
        switch(node->left->Label) {
            case 'B':
                printf("inside of G--- calling B\n");
                funcB(node->left);
                break;
            case 'C':
                printf("inside of G--- calling C\n");
                funcC(node->left);
                break;
            case 'J':
                printf("inside of G--- calling J\n");
                funcJ(node->left);
                break;
            default:
                break;
        }
    } else {
        printf("ERROR node G is NULL\n");
    }

}
///////////////////////////////////////////////////////////////////////////////////////////////
// if, for | assignment, read int and allocate memory, print value (E? | G. | empty)
// has delimiters in the center (second child {. | ?})
void funcH(node_t* node){
//    printf("\n in the dame funcH: %c -- %s \n", node->left->Label, node->left->token_instance);
    //if left is empty out!
    printf("\nEntering H\n");

    if (strcmp(node->left->token_instance, "Empty") == 0){
        printf("H This is empty!!\n");
        return;
    }
    //calling node G, if the label is G, { . t2 *" } || {. & t3}
    else if(node->left != NULL) {
        switch (node->left->Label) {
            case 'G':
                printf("calling G from H\n");
                funcG(node->left);
                break;
            case 'E':
                printf("inside H called E BELOW\n");
                funcE(node->left);
                printf("inside H called E above\n");
                break;
            default:
                break;
        }
    }else {
        printf("ERROR node H is NULL\n");
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
// print integer value to screen (sum, int, or identifier)
// *"A. (left -> *" (print value)) (center -> A) (right -> .)
// J is responsible for printing the value to screen as well as calling funcA
void funcJ(node_t* node){
    printf("\nEntering J\n");
    if(node->left != NULL){
        if (node->center->Label == 'A') {
            char *value = funcA(node->center);
            fprintf(global_file_pointer, "WRITE %s\n", value);
        }
    }else{printf("ERROR in J, node J is NULL\n");}

}
///////////////////////////////////////////////////////////////////////////////
// H ? D | Identifier (left -> H | empty) (center-> ?) (right -> L (recursive))
void funcL(node_t* node){
    //if it is empty on the left.
    if (strcmp(node->left->token_instance, "Empty") == 0){
        printf("\nE-L- This is empty!!\n");
        return;
    }
    else{
        printf("Calling H and L -- > in L\n");
        funcH(node->left);
        funcL( node->right);
    }

}
/////////////////////////////////////////////////////////////////////////////////
// K -> F ?$ | . (first set of K = t1 t2 | .
// (left-> F(Call F) | .) (center-> ?$ (add))
// value is nodeptr.child1 from A
// if it is ff it is the sum (those two Fs)return that.
// . if it is an identifier we need to find that identifier.
char* funcK(node_t* node, char* value){

    printf("\ninside of K Called from A\n");
    if(node->left->Label == 'F'){//second F
        //we need to add
        //call F
        char* value_1 = funcF(node->left);
    //
        //need ne var
        char* tempStr = Gen_temp_var();
        fprintf(global_file_pointer,"LOAD %s\n", value);
        fprintf(global_file_pointer,"ADD %s\n", value_1); //from F
        fprintf(global_file_pointer,"STORE %s\n", tempStr);// store in the newly temp-var

        printf("F from K If statement  %s \n", value);
        return tempStr; //return the two F sum
    }
    else if(node->left->token_instance[0] == '.'){// . no sum just return the value.
        char* tempStr = Gen_temp_var();
        printf("\n new temp val creatd %s\n", tempStr);
        printf("F from K ELSE statment %s \n", value);
        //fprintf("LOAD %S \n", nodeptr.child1);
        //(store T0\n)
        fprintf(global_file_pointer,"LOAD %s\n", value);
        fprintf(global_file_pointer, "STORE %s\n", tempStr);

        return tempStr;
    }

    return NULL;
}

//reacource:
//https://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
// https://www.tutorialspoint.com/c_standard_library/c_function_fprintf.htm