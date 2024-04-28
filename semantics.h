//
// Created by natnail on 4/6/2024.
//

#ifndef P3_SEMANTICS_H
#define P3_SEMANTICS_H
#include "TreeNode.h"

extern const int max_size_table = 20;
extern char* table_array[max_size_table];
extern int table_index = 0;
extern bool t2_found = false;
extern bool  string_check = false;


void pre_order_traversal(node_t* root, int );
void input_into_memory(node_t* root);
//void Symbol_Table_print(); //printing the table.
void Static_semantic_print(); // printing the table if not we are going to print the error.
bool Table_check(node_t* identifier); // boolean check if it is already in memory
#endif //P3_SEMANTICS_H
