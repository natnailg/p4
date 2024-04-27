//
// Created by Natnail on 4/6/2024.
//


#include <stdio.h>
#include <string.h>
#include "scanner.h"
#include <cstdlib>
#include <stdlib.h>
//char nextChar;
//#include "token.h"
#include "scanner.h"

const char* tokenNames[] = {"EOF token",  "T1 token", "T2 token", "T3 token", "unknown"};

int Table [12][12]= {
        {1,-1,3,5,10,-2,8,-3,6,-4,0,1001},
        {-5,2,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5},
        {1002,2,1002,1002,1002,1002,1002,1002,1002,1002,1002,1001},
        {-5,4,-6,-6,-6,-6,-6,-6,-6,-6,-6,-6},
        {1003,4,1003,1003,1003,1003,1003,1003,1003,1003,1003,1001},
        {1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1001},
        {1004,1004,1004,1004,1004,1004,1004,1004,1004,7,1004,1004},
        {1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1001},
        {1004,1004,1004,1004,1004,1004,1004,9,1004,1004,1004,1001},
        {1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1001},
        {1004,1004,1004,1004,1004,11,1004,1004,1004,1004,1004,1001},
        {1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1004,1001}

};

// mapping each character to the column
int mapingchar(char c) {
    switch ((int)c) {
        case 'a': case 'b': case 'c': case 'd': case 'e': case 'f': case 'g':
        case 'h': case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't': case 'u':
        case 'v': case 'w': case 'x': case 'y': case 'z':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F': case 'G':
        case 'H': case 'I': case 'J': case 'K': case 'L': case 'M': case 'N':
        case 'O': case 'P': case 'Q': case 'R': case 'S': case 'T': case 'U':
        case 'V': case 'W': case 'X': case 'Y': case 'Z':
            return LETTER;
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return DIGIT;
        case '%':

            return PERCENTAGE;
        case '.':
        case '!':
            return DOT_OR_EXCLAMATION;
        case ',':
            return COMMA;
        case ';':
            return SEMICOLON;
        case '?':
            return QUESTION_MARK;
        case '$':
            return DOLLAR_SIGN;
        case '*':
            return STAR;
        case '"':
            return QUOTATION;
        case ' ':
        case '\n':
            return WHITESPACE;
        case EOF: // EOF encountered
        case '\0':
            return END_OF_FILE;
        default:
            printf("invalid character detected!! %c \n", c );
            //return -1;// Unknown character
            exit(EXIT_FAILURE);
    }
}

void Scannertest(int line_nums){
    if (nextChar == '\n'){
        nextChar = '\0';
    }
    printf("char : %c----line : %d\n", nextChar,line_nums);

}


// the scanner will find the token for each of the characters using the table
Token Scanner() {

    int state = 0;
    struct Token tokens;
    int nextState;
    char S[256] = ""; // Assumakeming maximum token length of 255 characters
    int index = 0; // Index for tokeninstances
    int S_index = 0; // Index for S array
    int column;

    tokens.tokenid = unknown;
    int line_nums = tokens.line_num;
    //tokens.line_num = line_nums;
    memset(tokens.tokeninstance, '\0', MAX_INSTANCE_TOKEN);

    while(1){
        if(nextChar == '\n'){
            line_nums++;
        }
        //      if(nextChar == '\n'){
        //       nextChar = '\0';
        //      }
        column = mapingchar(nextChar); // Get column index using mappingchar function
        nextState = Table[state][column];

        //printf("entering: nextchar: %c, column: %d, state: %d, nextstate: %d, line_nums: %d, line_num_tk: %d\n", nextChar, column, state, nextState, line_nums,tokens.line_num);

        //printf("2.1 froms readfromFile: %s \n", tokens.tokeninstance);

        if (nextState < 0) {
            tokens.tokeninstance[index++] = nextChar;
            switch (nextState) {
                case -1:
                    //tokens.tokenid = unknown;
                    printf("can't start with a digit! %s %d\n", S, line_nums);
                    exit(EXIT_FAILURE);
                case -2:
                    printf("semicolone Error!! %s %d \n",  S, line_nums);
                    exit(EXIT_FAILURE);
                case -3:
                    printf("can't have dollar sign start %s %d\n",  S, line_nums);
                    exit(EXIT_FAILURE);
                case -4 :
                    printf("CAN'T START WITH STAR!! %s %d\n",  S, line_nums);
                    exit(EXIT_FAILURE);
                case -5 :
                    printf("must be followed by a digit %s %d\n",  S, line_nums);
                    exit(EXIT_FAILURE);
                case -6 :
                    printf("must be followed by a digit %s %d\n",  S, line_nums);
                    exit(EXIT_FAILURE);
                default:
                    printf("unknown Error %s %d\n", S, line_nums);
                    exit(EXIT_FAILURE);
            }
        }//end of error if sttment

        if (nextState > 1000) {
            // printf("2.2 froms readfromFile: %s \n", tokens.tokeninstance);
            //inside the if statment
            if(nextChar == '\n'){
                nextChar = ' ';
            }
            //tokens.tokeninstance[index++] = nextChar;
            //printf("I AM HERE !!\n");
            S[S_index++] = nextChar;
            switch (nextState) {
                case 1001:
                    tokens.tokenid = EOFtk;
                    // printf("token found: %s--- %s--line: %d\n", tokenNames[tokens.tokenid], S, line_nums);
                    //exit(EXIT_FAILURE);
                    return tokens;
                case 1002:
                    tokens.tokenid = T1_tk;
                    //printf("token found: %s--- %s--line: %d \n", tokenNames[tokens.tokenid], S, line_nums);
                    //break;
                    return tokens;
                case 1003:
                    tokens.tokenid = T2_tk;
                    if(tokens.tokenid == T2_tk){
                        tokens.tokeninstance[0] = 'V';
                    }
                    //printf("token found: %s----%s--line: %d \n", tokenNames[tokens.tokenid], S, line_nums);
                    //break;
                    return tokens;
                case 1004:
                    tokens.tokenid = T3_tk;
                    //printf("token found: %s-----%s--line: %d \n", tokenNames[tokens.tokenid],S, line_nums);
                    //break;
                    return tokens;
                default:
                    tokens.tokenid = unknown;
                    //printf("token found: %s--------%s--line: %d\n", tokenNames[tokens.tokenid],S, line_nums);
                    return tokens;
            }
            state = 0;
            S_index = 0;
            nextState=0;
            column=0;
            nextChar = fgetc(file_pointer_filterd_file);

            memset(S, '\0', strlen(S));

        }else{
            //printf("2.3 froms readfromFile: %s \n", tokens.tokeninstance);

            state = nextState;
            nextChar = (nextChar == '\n') ? ' ' : nextChar;
            tokens.tokeninstance[index++] = nextChar;
            S[S_index++] = nextChar; // Append the character to the string
            //nextChar = tokeninstances[index++]; // Read the next character from tokeninstances
            nextChar = fgetc(file_pointer_filterd_file);
            //printf("2.4froms readfromFile: %s \n", tokens.tokeninstance);


        }

        //      printf("bottom: nextchar: %c column: %d, state: %d, nextstate: %d, line_nums: %d, line_num_tk: %d\n", nextChar, column, state, nextState, line_nums,tokens.line_num);

    }// end of loop
}//end of function
