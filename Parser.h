//
// Created by Natnail on 4/6/2024.
//

#ifndef P3_PARSER_H
#define P3_PARSER_H

//#include "token.h"
#include "scanner.h"
#include "TreeNode.h"

node_t* parser(char* file); // read from file and map
void testScanner(char *, char  *); //remove comments and write to new file.

extern FILE *file_pointer_filterd_file;
extern int line_nums;
extern struct Token tokens;


node_t* S(); // CD  -> first set of S = t2
node_t* A(); // FK -> first set of A = t1 t2
node_t* B(); // .t2A! -> first set of B = .
node_t* C(); // t2* -> first set of C = t2
node_t* D(); // L -> first set of D = , ,; . t2 *" ? empty
node_t* E();
node_t* F();
node_t* G();
node_t* H();
node_t* J();
node_t* K();
node_t* L();

#endif //P3_PARSER_H
