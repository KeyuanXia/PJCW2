//
// Created by kxia on 22-4-24.
//
#include <stdio.h>
#include <stdlib.h>

#include "MakeLife.h"
#include "Array.h"
int alive(Node *first, int x, int y){
    int i, j, count=0;
    for(j=-1;j<=1;j++){
        for(i=-1;i<=1;i++){
            if(getPosition(first,x+i,y+j) && getPosition(first,x+i,y+j)->this==1){
                count++;
            }
        }
    }
    if(getPosition(first,x,y)->this==1){
        if(count==3){
            return 1;
        }
        else{
            return 0;
        }
    }
    if(getPosition(first,x,y)->this==0){
        if(count==2||count==3){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void makeLife(Node *last, Node *present){
    int x, y;
    for(y=0;y<get_y_size(last);y++){
        for(x=0;x<get_x_size(last,y);x++){
            if(!getPosition(present, x, y)){
                printf("In MakeLife, present's size is not the same to last.");
                exit(0);
            }
            getPosition(present,x,y)->this= alive(last,x, y);
        }
    }
}