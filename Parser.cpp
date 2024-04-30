//
// Created by Natnail on 4/6/2024.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//#include "scanner.h"
//#include "token.h"
#include "Parser.h"
#include "BuildTree.h"
#include "TreeNode.h"
#include "Generation.h"

//Global vars
char nextChar;  // we will use this to look for the next character
FILE *file_pointer_filterd_file;  // our file pointer to the filter file, so we may be able to
struct Token tokens;            // we will be using tokens to get the token_id and token instances.

char empty_String[] = "Empty";  // empty for the nullable functions, so strncpy can copy it. (we will be doing this for the nullables)


//let us get rid of all the comments in, they will start with # and end with one.
void testScanner(char *inputfile, char *outputfile) {
    FILE *input_file = fopen(inputfile, "r");
    if (input_file == NULL) {printf("Error opening input file.\n"); return;}

    FILE *output_file = fopen(outputfile, "w");
    if (output_file == NULL) { printf("Error opening output file.\n");  return;}

    char input_char;
    bool comments = false;

    while ((input_char = fgetc(input_file)) != EOF) {

        if (!comments) {
            if (input_char != '#') {
                if(input_char != '\t' && input_char != '\n' && input_char != ' '){
                    fputc(input_char, output_file); // write character to output file if not in a comment
                }
            }else{ // # is found we set comment to true
                comments = true; //start of comment
            }
        }else{ // we find the second comment
            if(input_char == '#'){
                comments = false; //end of comment when
            }
        }
    }//END OF WHILE LOOp


    fclose(input_file);
    fclose(output_file);

    //parser(outputfile); //passing the char array not the file pointer
}


// Reading from the file and setting the nextchar as the global variable.
node_t* parser(char* filename) {

    node_t* root = NULL; //initialize it to NUll

    file_pointer_filterd_file = fopen(filename, "r"); // Open the file in read mode
    if (file_pointer_filterd_file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }
    //resetting
    memset(tokens.tokeninstance, '\0', MAX_INSTANCE_TOKEN);

    nextChar = fgetc(file_pointer_filterd_file);

    if (nextChar == '\n') {
        tokens.line_num++;
    }


    tokens = Scanner();


    root = S(); // call FUNCTION S




    if(tokens.tokenid == EOFtk){
        printf("All Good OK!!\n");
    }else{
        printf("error in the parser!!! %c------%s.\n", nextChar, tokens.tokeninstance);
    }

    //printf("token found: %s--- %s--line: %d\n", tokenNames[tokens.tokenid], tokens.tokeninstance, line_nums);

    //fclose(file_pointer_filterd_file)

    return root;
}
////////////////////////////////////////////////////////////////////////

//S-CD (we just call those functions, First set of S = t2)
node_t* S(){
    //printf("Entering S()\n");

    node_t* P = createNode('S');

    P->left = C();
    P->center = D();


    // printf("1. End of S non-terminal\n");
    //printf("EXITING S()\n");

    return P;

}
//
// A->FK (we will just call those functions, First set of A = t1 t2)
node_t* A(){
    node_t* P = createNode('A');
    P-> left  = F();
    P-> center = K();
//    printf("1. End of A non-terminal\n");
    return  P;
}
//
// B-> . t2 A ! (first set of B = . )
node_t* B(){
    if (tokens.tokeninstance[0] == '.'){
        node_t* P = createNode('B'); //create the node

        node_t* B_token_ptr = createNode(' '); //create an empty node
        //B_token_ptr -> token_id = tokens.tokenid;   //getting token id
        strncpy(B_token_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
//        P->center = B_token_ptr;
        P->left = B_token_ptr;

        tokens = Scanner(); //consume .

        if(tokens.tokenid == T2_tk){

            node_t*  B_tk_ptr_2 = createNode(' '); //create an empty node
            B_tk_ptr_2 -> token_id = strdup(tokenNames[tokens.tokenid]);  //getting token id
            B_tk_ptr_2 -> token_ID = tokens.tokenid; // for the semantics
            strncpy(B_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = B_tk_ptr_2;

            tokens = Scanner(); //consume

            P->right = A(); //call A

            if (tokens.tokeninstance[0] == '!'){

                node_t*  B_tk_ptr_3 = createNode(' '); //create an empty node
                B_tk_ptr_3 -> token_id = strdup(tokenNames[tokens.tokenid]);  //getting token id
                B_tk_ptr_3 -> token_ID = tokens.tokenid; // for hte semantics
                strncpy(B_tk_ptr_3->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
                P->far_right = B_tk_ptr_3;

                //printf("5.B token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
                tokens = Scanner();
                // printf("6.B token instance { %s } token Id %s consumed ( ! )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

                return P;

            }else{ printf("B1. ERROR\n"); return NULL; }
        }else{ printf("B2. ERROR\n");return NULL; }
    }else{ printf("B3. ERROR\n"); return NULL;}
}
//
// C -> t2 * (first set of C = T2)
node_t* C(){
    //printf("Entering C()\n");

    node_t* P = createNode('C'); //create node C
//
    if(tokens.tokenid == T2_tk){
        // printf("1.C token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        //printf("Token Instance: %s \n", tokens.tokeninstance);

        node_t* c_token_ptr = createNode(' ');
        c_token_ptr->token_id = strdup(tokenNames[tokens.tokenid]);
        strncpy(c_token_ptr->token_instance, tokens.tokeninstance, MAX_INSTANCE_TOKEN);
        c_token_ptr->token_ID= tokens.tokenid; // for the semantics evaluation
        P->left = c_token_ptr;


        //printf("!!!Token Instance: %s --%s \n", tokens.tokeninstance, c_token_ptr->token_instance );
        //printf("tokens.tokenid: %d---%s\n", tokens.tokenid, tokenNames[tokens.tokenid]);


        tokens = Scanner();
        // printf("2.C token instance { %s } token Id %s consumed ( t2 )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        if(tokens.tokeninstance[0] == '*'){
            // printf("3.C token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            node_t* c_tokenptr_2 = createNode(' ');
            // c_tokenptr_2->token_id = strdup(tokenNames[tokens.tokenid]);
            // c_tokenptr_2 -> token_id = tokens.tokenid;   //getting token id
            strncpy(c_tokenptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = c_tokenptr_2;

            tokens = Scanner();
            // printf("4.C token instance { %s } token Id %s consumed ( * )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

            //printf("EXITING C()\n");
            return P;

        }else{ printf("C1. ERROR\n");return NULL;}
    }else{ printf("C2. ERROR\n");return NULL;}
}
//
//D -> L (first set of D = , ,; . t2 *" ? epsilon
node_t* D(){
    //printf("Entering C()\n");

    node_t* P = createNode('D'); //create node

    P-> left = L(); //left child

    //printf("1.5 Value of P: %p, Left: %p, Right: %p\n", (void*)P, (void*)(P->left), (void*)(P->right)); // Print P, left, and right
    //printf("EXITING C()\n");

    return P;
}
//
//E -> , A A H | ,; F H (first set of E = , | ,;
node_t* E(){
    node_t* P = createNode('E'); //create node E

    if (tokens.tokeninstance[0] == ',' and tokens.tokeninstance[1] != ';'){

        node_t* E_tk_ptr = createNode(' ');
        E_tk_ptr -> token_id = strdup(tokenNames[tokens.tokenid]);   //getting token id
        E_tk_ptr->token_ID = tokens.tokenid; // this is for the semantics check
        strncpy(E_tk_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
        P-> left = E_tk_ptr; //,;

        tokens = Scanner(); //consume
        P-> center = A();
        P-> right = A();
        P-> far_right = H();

        return P;
    }
    else if (tokens.tokeninstance[0] == ',' and tokens.tokeninstance[1] == ';'){

        node_t* E_tk_ptr_2 = createNode(' ');
        E_tk_ptr_2 -> token_id = strdup(tokenNames[tokens.tokenid]);   //getting token id
        E_tk_ptr_2-> token_ID = tokens.tokenid; // thi is for the semantics check
        strncpy(E_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
        P-> left = E_tk_ptr_2;

        tokens = Scanner(); //consume
//
//        P->left = F();
//        P->center = H();
        P->center = F();
        P->right = H();

        return P;

    }else{ printf("E1. ERROR\n");return NULL;}
}
//
// F-> t1 | t2 (first set of F = t1 | t2)//
node_t* F(){

    node_t* P = createNode('F'); //create node E
    if (tokens.tokenid == T1_tk){

        node_t* F_tk_ptr = createNode(' ');
        F_tk_ptr -> token_id = strdup(tokenNames[tokens.tokenid]);   //getting token id
        F_tk_ptr->token_ID = tokens.tokenid; // this is for the semantics check;
        strncpy(F_tk_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
        P-> left = F_tk_ptr;

        tokens = Scanner(); //consume

        return P;

    }
    else if( tokens.tokenid == T2_tk){

        node_t* F_tk_ptr_2 = createNode(' ');
        F_tk_ptr_2 -> token_id = strdup(tokenNames[tokens.tokenid]);  //getting token id
        F_tk_ptr_2->token_ID = tokens.tokenid; //this is for the semantics check
        strncpy(F_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
        P-> left = F_tk_ptr_2;

        tokens = Scanner(); //consume
        return P;

    }else{ printf("E1. ERROR\n"); return NULL;}
}
//
//
node_t* G(){

    node_t* P = createNode('G'); //create node

    if (tokens.tokeninstance[0] == '.'){
        // printf("1.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        P->left = B();

        return P;
    }
    else if (tokens.tokenid == T2_tk){
        //printf("2.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);
        P->left = C();
        return P;
    }
    else if(tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"'){
        // printf("3.G token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        P->left = J();
        return P;

    }else{ printf("G1. ERROR\n");return NULL;}
}
//
//
node_t* H(){
    //printf("Entering H()\n");

    node_t* P = createNode('H'); //create node

//    if(tokens.tokenid == T3_tk && tokens.tokeninstance[0] == ','){
    if(tokens.tokeninstance[0] == ','){

        P -> left = E();

        if(tokens.tokeninstance[0] == '?'){

            node_t* H_tk_ptr = createNode(' ');
            strncpy(H_tk_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = H_tk_ptr;

            tokens = Scanner(); //consume

            //printf("EXITING H()\n");

            return P;
        }else{printf("1.H ERROR\n");return NULL;}

    }else if(tokens.tokeninstance[0] == '.' || tokens.tokenid == T2_tk ||
             (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"')){
        //printf("5.H token instance { %s } token Id %s \n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        P->left =G();


        if (tokens.tokeninstance[0] == '.' && tokens.tokenid == T3_tk){

            node_t* H_tk_ptr_2 = createNode(' ');
            strncpy(H_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = H_tk_ptr_2;

            tokens = Scanner(); //consume


            //printf("EXITING H()\n");
            return P;
        }else{printf("2.H ERROR\n");return NULL;}

    }else{
        //printf("H.7 EMPTY\n");
        node_t* H_tk_ptr_3 = createNode(' ');
        //H_tk_ptr_3 -> token_id = tokens.tokenid;   //getting token id
        strncpy(H_tk_ptr_3->token_instance, empty_String,MAX_INSTANCE_TOKEN );
        P->left = H_tk_ptr_3;
        // printf("!!!EXITING empty H()\n");
        return P;
    }
}
//
// J-> *" A . (first set of J = *"
node_t* J(){

    node_t* P = createNode('J'); //create node

    if (tokens.tokeninstance[0]=='*' && tokens.tokeninstance[1]=='"' && tokens.tokenid == T3_tk){

        node_t* J_tk_ptr= createNode(' '); //create node
        //J_tk_ptr -> token_id = tokens.tokenid;   //getting token id
        strncpy(J_tk_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
        P->left = J_tk_ptr;

        tokens = Scanner(); //consume

        P->center = A();

        if (tokens.tokenid == T3_tk && tokens.tokeninstance[0] == '.'){
            node_t* J_tk_ptr_2 = createNode(' '); //create node
            //J_tk_ptr -> token_id = tokens.tokenid;   //getting token id
            strncpy(J_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->right = J_tk_ptr_2;

            tokens = Scanner(); //consume

            return P;

        }else{printf("1.J ERROR\n");return NULL;}
    }else{printf("2.J ERROR\n"); return NULL;}

}
//
//we don't consume???????? (ask prof)
// K -> F ?$ | . (first set of K = t1 t2 | .
node_t* K(){
    node_t* P = createNode('K'); //create node

    if (tokens.tokenid == T1_tk || tokens.tokenid == T2_tk ){

        P->left = F();

        if (tokens.tokeninstance[0] == '?' && tokens.tokeninstance[1] == '$' && tokens.tokenid == T3_tk){

            node_t* K_tk_ptr= createNode(' '); //create node in
            //J_tk_ptr -> token_id = tokens.tokenid;   //getting token id
            strncpy(K_tk_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = K_tk_ptr;

            tokens = Scanner();

            return P;
        }else{printf("1.J ERROR\n");return NULL; }
    }
    else if(tokens.tokeninstance[0] == '.'){

        node_t* K_tk_ptr_2 = createNode(' '); //create node
        //K_tk_ptr_2 -> token_id = tokens.tokenid;   //getting token id
        strncpy(K_tk_ptr_2->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
        P->left = K_tk_ptr_2;

        tokens = Scanner();

        return P;
    }
    else{printf("2.J ERROR\n"); return NULL;}
}

node_t* L(){
    //printf("Entering L()\n");

    node_t* P = createNode('L'); //create the node
    //printf("1.hit here %s--- \n", tokens.tokeninstance);
    //printf("1.L token instance { %s } token Id %s ()\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

    if(tokens.tokenid == T2_tk || tokens.tokeninstance[0] == '?' || (tokens.tokenid == T3_tk && (tokens.tokeninstance[0] == ',' || (tokens.tokeninstance[0] == ',' && tokens.tokeninstance[1] == ';') ||
                                                                                                 tokens.tokeninstance[0] == '.' || (tokens.tokeninstance[0] == '*' && tokens.tokeninstance[1] == '"')))){
        node_t* P = createNode('L'); //create the node

        //  printf("2.L token instance { %s } token Id %s (  )\n", tokens.tokeninstance, tokenNames[tokens.tokenid]);

        //printf("2.hit here %s--- \n", tokens.tokeninstance);
        P->left = H();
        //printf("3. hit here\n");

        if (tokens.tokeninstance[0] == '?'){

            node_t* L_token_ptr = createNode(' ');
            // L_token_ptr -> token_id = strdup(tokenNames[tokens.tokenid]); //getting token id
            strncpy(L_token_ptr->token_instance, tokens.tokeninstance,MAX_INSTANCE_TOKEN );
            P->center = L_token_ptr;

            tokens = Scanner();

            P->right = L();

            //printf("EXITING L()\n");

            return P;

        }else{printf("1.L ERROR\n");return NULL; }

    }else{
        //nullable
        //printf("3.L EMPTY\n");
        node_t* L_token_ptr_2 = createNode(' ');
        //L_token_ptr_2 -> token_id = tokens.tokenid;   //getting token id
        strncpy(L_token_ptr_2->token_instance, empty_String,MAX_INSTANCE_TOKEN );
        P->left = L_token_ptr_2;

        //printf("EXITING/empty L()\n");
        return P;
    }
}



//I haven't removed any of my debugging prints because i wanted to use them just in case in the future.
