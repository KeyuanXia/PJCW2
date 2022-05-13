//
// Created by root on 22-5-7.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/types/FILE.h>
#include "Array.h"
#include "Initial.h"

//return 0 = initial failed
//return -1 = empty file
int load_Script(FILE *file, Node *head, double delay){
    Node *last, *this;
    int i,j;
    char ch, buf[1024];
    if(!file){
        printf("\nThe source file does not exist.\n");
        return 0;
    }
    else{
        last=head;
        j=0;
        while((ch=fgetc(file))!=';'){
            if(ch==EOF){
                printf("\nIllegal format\n");
                return 0;
            }
            else if(ch=='0'||ch=='1'){
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
                return 0;
            }
        }
        //this is for getting the delay from the initial file
        fgetc(file);
        fgets(buf, sizeof(buf), file);
        if(strspn(buf, "0123456789")==strlen(buf)){
            delay= atoi(buf);
        }
        else{
            printf("\nThe delay format did not meet the standard.\n");
            return 0;
        }
        if(!head->xnext){
            printf("The file is empty");
            return -1;
        }
        else{
            clean_the_edge(head);
            return 1;
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

int free_all(Node* head){
    Node *row, *this, *next;
    this = head;
    row = head;
    while(row->ynext){
        row=row->ynext;
        while(this->xnext){
            next=this->xnext;
            free(this);
            this=next;
        }
        free(this);
        this=row;
    }
}
