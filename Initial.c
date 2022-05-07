//
// Created by root on 22-5-7.
//
#include <stdio.h>
#include <stdlib.h>
#include <bits/types/FILE.h>
#include "Array.h"
#include "Initial.h"

Node *load_Script(FILE *file, Node *head){
    Node *last, *this;
    int i,j;
    char ch;
    if(!file){
        printf("\nThe source file does not exist.\n");
        return NULL;
    }
    else{
        last=head;
        j=0;
        while((ch=fgetc(file))!=EOF){
            if(ch=='0'||ch=='1'){
                this=creat_Node(atoi(ch));
                last->xnext=this;
            }
            else if(ch==','){}
            else if(ch=='\n'){
                j++;
                last->xnext=NULL;
                last=head;
                for (i=0;i<j;i++){
                    if(last->ynext==NULL){
                        this= creat_Node(-1);
                        last->ynext=this;
                        this->ylast=last;
                        last=this;
                    }
                    else{
                        last=last->ynext;
                    }
                }
            }
            else{
                printf("\nExist wrong format element.\n");
                return NULL;
            }
        }
        if(!head->xnext){
            printf("The file is empty");
            return head;
        }
        else{
            clean_the_edge(head);
        }
    }
}

void clean_the_edge(Node *head){
    Node *this;
    this=head;
    while(this->xnext){
        this->ylast=NULL;
        this=this->xnext;
    }
    this=head;
    while(this->ynext){
        this=this->ynext;
    }
    while(this->xnext){
        this->ynext=NULL;
        this=this->xnext;
    }
}
