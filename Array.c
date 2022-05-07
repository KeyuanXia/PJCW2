//
// Created by kxia on 22-4-24.
//
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
//the array's head is at the left of the left-top one node
//so the first node is first->xnext
int get_x_size(Node *first){
    Node *q;
    int count = 0;
    q=first->xnext;
    while(q){
        count++;
        q=q->xnext;
    }
    return count;
}

int get_y_size(Node *first){
    Node *q;
    int count = 0;
    q=first->xnext;
    while(q){
        count++;
        q=q->ynext;
    }
    return count;
}

Node *getPosition(Node *first, int x, int y){
    Node *q;
    int i;
    q=first->xnext;
    for(i=0;i<x;i++){
        if(q->xnext){
            q=q->xnext;
        }
        else{
            printf("\nOut of range\n");
            return NULL;
        }
    }
    for(i=0;i<y;i++){
        if(q->ynext){
            q=q->ynext;
        }
        else{
            printf("\nOut of range\n");
            return NULL;
        }
    }
    return q;
}

Node *creat_Node(int type){
    Node *new=(Node*)malloc(sizeof (Node));
    new->this=type;
    return new;
}