//
// Created by kxia on 22-4-24.
//
#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
//the array's head is at the left of the left-top one node
//so the first node is first->xnext
int get_x_size(Node *first, int row){
    Node *q;
    int i;
    int count = 0;
    q=first;
    for(i=0;i<row;i++){
        if(!q->ynext){
            return 0;
        }
        else{
            q=q->ynext;
        }
    }
    while(q->xnext){
        count++;
        q=q->xnext;
    }
    return count;
}

int get_y_size(Node *first){
    Node *q;
    int count = 1;
    q=first;
    while(q->ynext){
        count++;
        q=q->ynext;
    }
    return count;
}

Node *getPosition(Node *first, int x, int y){
    Node *q;
    int i;
    q=first;
    for(i=0;i<y;i++){
        if(q->ynext){
            q=q->ynext;
        }
        else{
            return NULL;
        }
    }
    for(i=0;i<=x;i++){
        if(q->xnext){
            q=q->xnext;
        }
        else{
            return NULL;
        }
    }
    return q;
}

Node *copy_Grid(Node *last){
    Node *row, *c, *nh, *nrow, *nc;
    if(!last){
        return NULL;
    }
    nh = creat_Node(-1);
    nrow=nh;
    row=last;
    while(1){
        row=row->ynext;
        nc=creat_Node(row->this);
        nrow->ynext=nc;
        nc->ylast=nrow;
        nrow=nrow->ynext;
        if(row->ynext){
            row=row->ynext;
        }
        else{
            nrow->ynext=NULL;
            break;
        }
    }
}

Node *creat_Node(int type){
    Node *new=(Node*)malloc(sizeof (Node));
    new->this=type;
    return new;
}