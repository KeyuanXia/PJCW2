//
// Created by keyuanxia on 22-5-18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "utility.h"
#include "Array.h"

char *strdpp(const char *s){
    size_t size = strlen(s) + 1;
    char *p = (char *)malloc(size*sizeof(char));
    if (p) {
        memcpy(p, s, size);
    }
    return p;
}

void clear_n(char *str){
    char *tmp = NULL;
    if ((tmp = strstr(str, "\n")))
    {
        *tmp = '\0';
    }
}

char *readChar(int length){
    char *input, *output;
    int tl;
    fgets(input,length+1,stdin);
    clear_n(input);
    fflush(stdin);
    tl=strlen(input);
    if (tl > 0 && tl <= length) {
        output = strdpp(input);
        return output;
    }
    return NULL;
}

//this function just accept positive integer
int readInt(int length){
    char *input;
    int output, tl;
    fgets(input,20,stdin);
    clear_n(input);
    fflush(stdin);
    tl=strlen(input);
    if(tl<=0){
        return -1;
    }
    else if(tl>length){
        return -2;
    }
    else{
        if(strspn(input, "0123456789")==strlen(input)){
            return atoi(input);
        }
        else{
            return -3;
        }
    }
}

char *CreateFolder(){
    time_t t;
    time(&t);
    char *str=ctime(&t);
    if (access(str, 0) == -1)
    {
        mkdir(str,0777);
    }
    return str;
}

void makeFilePath(char *time, int round){
    char *str,*r, *temp="";
    str=(char *)malloc(100*sizeof(char));
    sprintf(r,"%d",round);
    r=strdpp(str);
    free(str);
    strcat(temp,"./");
    strcat(temp,time);
    strcat(temp,"/");
    strcat(temp,r);
    time=strdpp(temp);
    free(temp);
}

void storeGrid(FILE *filename, Node *first){
    Node *row, *c;
    if(first==NULL){
        printf("In storeGrid, first is NULL");
        exit(-1);
    }
    row=first;
    c=first->xnext;
    while(1){
        while(1){
            fprintf(filename, "%i", c->this);
            if(!c->xnext){
                fprintf(filename,"\n");
                break;
            }
            else{
                fprintf(filename, ",");
                c=c->xnext;
            }
        }
        if(!row->ynext){
            fprintf(filename,";");
            break;
        }
        else{
            row=row->ynext;
            if(row->xnext){
                c=row->xnext;
            }
        }
    }
}

void printGrid(Node *first){
    Node *row, *c;
    if(first==NULL){
        printf("In storeGrid, first is NULL");
        exit(-1);
    }
    row=first;
    c=first->xnext;
    while(1){
        while(1){
            printf("%d",c->this);
            if(!c->xnext){
                printf("\n");
                break;
            }
            else{
                printf(",");
                c=c->xnext;
            }
        }
        if(!row->ynext){
            printf(";");
            break;
        }
        else{
            row=row->ynext;
            if(row->xnext){
                c=row->xnext;
            }
        }
    }
    exit(0);
}