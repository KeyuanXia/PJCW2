//
// Created by keyuanxia on 22-5-7.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bits/types/FILE.h>

#include "Initial.h"
#include "utility.h"

//return 0 = initial failed
//return -1 = empty file
int load_Script(FILE *file, Node *head, int *delay){
    Node *last, *this;
    int i,j;
    char ch, buf[1024], *temp;
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
            else if(ch=='\n'||ch=='\r'){
                j++;
                last->xnext=NULL;
                last=head;
                while(1){
                    if(last->ynext==NULL){
                        this= creat_Node(-1);
                        last->ynext=this;
                        this->ylast=last;
                        last=this;
                        break;
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
        temp= strdpp(buf);
        clear_n(temp);
        if(strspn(temp, "0123456789")==strlen(temp)){
            *delay= atoi(temp);
            free(temp);
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
    while(1){
        if(this->xnext){
            this->ylast=NULL;
            this=this->xnext;
        }
        else{
            this->ylast=NULL;
            break;
        }
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

void free_node(Node *pointer){
    if(pointer->xnext)pointer->xnext=NULL;
    if(pointer->ynext)pointer->ynext=NULL;
    if(pointer->ylast)pointer->ylast=NULL;
    if(pointer->xlast)pointer->xlast=NULL;
}

int free_all(Node* head){
    if(!head->xnext&&!head->ynext){
        free_node(head);
        return 0;
    }
    Node *row, *this, *next;
    row = head;
    while(row){
        this=row;
        row=row->ynext;
        while(1){
            if(this->xnext){
                next=this->xnext;
                free_node(this);
                this=next;
            }
            else{
                free_node(this);
                break;
            }
        }
    }
}
