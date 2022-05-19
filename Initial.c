//
// Created by keyuanxia on 22-5-7.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/types/FILE.h>

#include "Initial.h"

//return 0 = initial failed
//return -1 = empty file
int load_Script(FILE *file, Node *head, int *delay){
    rewind(file);
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
        while(1){
            ch= fgetc(file);
            if(ch==';'){
                break;
            }
            if(ch==EOF){
                printf("\nIllegal format\n");
                return 0;
            }
            else if(ch=='0'){
                this=creat_Node(0);
                last->xnext=this;
                this->xlast=last;
                last=this;
            }
            else if(ch=='1'){
                this=creat_Node(1);
                last->xnext=this;
                this->xlast=last;
                last=this;
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
        int m= strlen(buf);
        int n=strspn(buf, "0123456789");
        if(strspn(buf, "0123456789")==strlen(buf)-1){
            *delay= atoi(buf);
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
    while(1){
        this->xlast=NULL;
        if(this->ynext){this=this->ynext;}
        else{break;}
    }
    while(1){
        this->ynext=NULL;
        if(this->xnext){this=this->xnext;}
        else{break;}
    }
}

int free_all(Node* head){
    Node *row, *this, *next;
    row = head;
    while(row){
        this=row;
        row=row->ynext;
        while(1){
            if(this->xnext){
                next=this->xnext;
                free(this);
                this=next;
            }
            else{
                free(this);
                break;
            }
        }
    }
}
