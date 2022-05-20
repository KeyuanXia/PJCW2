//
// Created by keyuanxia on 22-5-20.
//

#ifndef CHAPTER5_01_VIEWDRAW_H
#define CHAPTER5_01_VIEWDRAW_H
#include "Array.h"
#include <SDL2/SDL.h>

int create_Window(SDL_Window *window, SDL_Rect *rect, Node *first);

int No_Limit(int *delay, Node *head);

int Limit(int *delay, Node *head, int times);

Node *Customer(int xnum, int ynum);

#endif //CHAPTER5_01_VIEWDRAW_H
