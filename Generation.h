//
// Created by Natnail on 4/26/2024.
//

#ifndef P4_GENERATION_H
#define P4_GENERATION_H
#include "token.h"



void funcS(node_t*);
char* funcA(node_t*);
void funcB(node_t*);
void funcC(node_t*);
void funcD(node_t*);
void funcE(node_t*);
char* funcF(node_t*);
void funcG(node_t*);
void funcH(node_t*);
void funcJ(node_t*);
void funcL(node_t*);
char* funcK(node_t*, char*);

char* Gen_temp_var();
void STOP_ASM();
void Generation_code(node_t*);
void open_file_global(char *file_path);
void close_file();

#endif //P4_GENERATION_H
