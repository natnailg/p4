//
// Created by Natnail on 4/26/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TreeNode.h"
#include "Generation.h"

extern FILE *global_file_pointer; // Global variable definition
// function to open the global file
void open_file_global(const char *file_path) {
    global_file_pointer = fopen(file_path, "w"); // Open file in append mode
    if (global_file_pointer == NULL) {
        perror("Error opening file");
        // Handle error
    }
}

void close_file() {
    if (global_file_pointer != NULL) {
        fclose(global_file_pointer);
        global_file_pointer = NULL;
    }
}


// read in int and allocate memory to, any number of additional operations
void funcS() {
    fprintf(global_file_pointer, "Calling C and D in S\n");
    funcC();
//    funcD();
}
// A->FK (we will just call those functions, First set of A = t1 t2)
void funcA(){}
// assigns the value of A to identifier t2
void funcB(){}
// read in int, allocate memory (e.g. v10 for %10), assign value = int
void funcC(){
    fprintf(global_file_pointer, "Calling from C\n");
}
//D -> L (first set of D = , ,; . t2 *" ? epsilon
void funcD(){}
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
void funcL(){}
// K -> F ?$ | . (first set of K = t1 t2 | .
void funcK(){}