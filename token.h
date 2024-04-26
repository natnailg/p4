//
// Created by Natnail on 4/6/2024.
//

#ifndef P3_TOKEN_H
#define P3_TOKEN_H
//#include "testScanner.h"
//#include "scanner.h"

const int MAX_INSTANCE_TOKEN = 250;
extern char nextChar;

//defining token id's using enumtoto
typedef enum{
    EOFtk,
    T1_tk,
    T2_tk,
    T3_tk,
    unknown
    /*
    EOFtk= 1001,  // end of file
    T1_tk = 1002,  // beings (a-z, A-Z) followed by one or more digits
    T2_tk = 1003,  // beings with % and must have one or more digits
    T3_tk = 1004, // . ! , ,; ? ?$ * 8'
    unknown = -1*/
}tokenID;

extern const char* tokenNames[];

// for each token we are going to need the TokenID, TokenInstance, line#
struct Token{
    tokenID tokenid;   // to say what type of id
    char tokeninstance[MAX_INSTANCE_TOKEN];  // store them in an array
    int line_num; // for the line number
};



#endif //P3_TOKEN_H
