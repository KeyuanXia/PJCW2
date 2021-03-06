//
// Created by keyuanxia on 22-5-18.
//

#ifndef CHAPTER5_01_UTILITY_H
#define CHAPTER5_01_UTILITY_H
#include "Array.h"

char *strdpp(const char *s);

char *readChar(int length);

int readInt(int length);

void printGrid(Node *first);

int checkSame(Node *g1, Node *g2);

void clear_n(char *str);

void clear_s(char *str);

void clear_m(char *str);

char *CreateFolder();

char *makeFilePath(char *time, int round);

void storeGrid(FILE *filename, Node *first, int delay);
#endif //CHAPTER5_01_UTILITY_H
