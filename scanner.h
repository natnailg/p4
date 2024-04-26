//
// Created by Natnail on 4/6/2024.
//

#ifndef P3_SCANNER_H
#define P3_SCANNER_H

#include "token.h"
#include "Parser.h"

const int LETTER = 0;
const int DIGIT = 1;
const int PERCENTAGE = 2;
const int DOT_OR_EXCLAMATION  = 3;
const int COMMA = 4;
const int SEMICOLON = 5;
const int QUESTION_MARK = 6;
const int DOLLAR_SIGN = 7;
const int STAR = 8;
const int QUOTATION = 9;
const int WHITESPACE = 10;
const int END_OF_FILE = 11;

int mapingchar(char ); //mapping switch statement
Token Scanner();
void Scannertest(int);
void printtokens();

#endif //P3_SCANNER_H
