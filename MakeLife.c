//
// Created by kxia on 22-4-24.
//
#include <stdio.h>
#include <stdlib.h>

#include "MakeLife.h"
int alive(Node *first, int x, int y){
    int i, j, count=0;
    Node *test;
    for(j=-1;j<=1;j++){
        for(i=-1;i<=1;i++){
            test=getPosition(first,x+i,y+j);
            if(j==0&&i==0){
                continue;
            }
            else if(getPosition(first,x+i,y+j)!=NULL && getPosition(first,x+i,y+j)->this==1){
                count++;
            }
        }
    }
    if(getPosition(first,x,y)->this==1){
        if(count==3||count==2){
            return 1;
        }
        else{
            return 0;
        }
    }
    if(getPosition(first,x,y)->this==0){
        if(count==3){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void makeLife(Node *last, Node *present){
    int x, y, xm, ym;
    if(get_y_size(last)!= get_y_size(present)){
        printf("\nIn makelife, last and present's size are not same.\n");
        exit(-1);
    }
    ym = get_y_size(last);
    for(y=0;y<ym;y++){
        xm = get_x_size(last,y);
        if(get_x_size(last,y)!= get_x_size(present,y)){
            printf("\nIn makelife, last and present's size are not same.\n");
            exit(-1);
        }
        for(x=0;x<xm;x++){
            if(getPosition(last,x,y)->this != getPosition(last,x,y)->this){
                printf("\nIn makelife, last and present's size are not same.\n");
                exit(-1);
            }
            getPosition(present,x,y)->this= alive(last,x,y);
        }
    }
}