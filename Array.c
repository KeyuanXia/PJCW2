//
// Created by kxia on 22-4-24.
//
#include <stdio.h>
#include <stdlib.h>

#include "Array.h"
#include "Initial.h"
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

int get_x_max_size(Node *first){
    int count, temp, i;
    count = 0;
    for(i=0;i< get_y_size(first);i++){
        temp= get_x_size(first, i);
        if(temp>count){
            count=temp;
        }
    }
    return count;
}

int get_y_size(Node *first){
    Node *q;
    int count = 0;
    q=first;
    while(1){
        count++;
        if(q->ynext)
            q=q->ynext;
        else
            break;
    }
    return count;
}

Node *getPosition(Node *first, int x, int y){
    Node *q;
    int i;
    q=first;
    if(x<0||y<0){
        return NULL;
    }
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
    Node *nh, *nrow, *lrow, *nc, *this, *n;
    if(!last){
        return NULL;
    }
    nh = creat_Node(-1);
    nrow=nh;
    lrow=last;
    while(1){
        if(lrow->ynext){
            nrow->this=-1;
            nc = creat_Node(-1);
            nrow->ynext=nc;
            nc->ylast=nrow;
            nrow=nc;
            lrow=lrow->ynext;
        }
        else{
            nrow->ynext=NULL;
            break;
        }
    }
    nrow=nh;
    lrow=last;
    this=lrow;
    n=nrow;
    while(1){
        if(this->xnext){
            nc = creat_Node(this->xnext->this);
            n->xnext = nc;
            nc->xlast = n;
            n = nc;
            this = this->xnext;
        }
        else{
            n->xnext=NULL;
            if(lrow->ynext){
                lrow=lrow->ynext;
                nrow=nrow->ynext;
                n=nrow;
                this=lrow;
            }
            else{
                break;
            }
        }
    }
    clean_the_edge(nh);
    return nh;
}

Node *creat_Node(int type){
    Node *new=(Node*)malloc(sizeof (Node));
    new->this=type;
    return new;
}

Node *create_Grid(int xnum, int ynum){
    Node *head, *n, *row, *c;
    head= creat_Node(-1);
    row=head;
    int i, j;
    for (j=1;j<ynum;j++){
        n = creat_Node(0);
        row->ynext=n;
        n->ylast=row;
        row=n;
    }
    row->ynext=NULL;
    row=head;
    c=row;
    for(j=0;j<ynum;j++){
        for(i=0;i<xnum;i++){
            n= creat_Node(0);
            c->xnext=n;
            n->xlast=c;
            c=n;
        }
        c->xnext=NULL;
        row=row->ynext;
        c=row;
    }
    clean_the_edge(head);
    return head;
}