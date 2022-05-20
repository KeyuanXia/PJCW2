#include <stdio.h>

#include "MakeLife.h"
#include "Initial.h"
#include "Array.h"
#include "utility.h"
#include "ViewDraw.h"
#include <SDL2/SDL.h>

int main() {
    int num=-1, i;
    char *string, ch;
    printf("********WELCOME********\n\n");
    printf("-------GAME TYPE-------\n");
    printf("|  1)INSERT FILE      |\n");
    printf("|  2)PERSONAL DESIGN  |\n");
    printf("==>choice:");
    while(1){
        num=readInt(1);
        while((ch = getchar()) != '\n' && ch != EOF);
        if (num==-1){
            printf("Please enter a number at least.\n"
                   "==>choice:");
        }
        else if (num==-2){
            printf("Please just enter one positive number.\n"
                   "==>choice:");
        }
        else if (num==-3){
            printf("Please don't enter any symbol except number.\n"
                   "==>choice:");
        }
        else if (num != 1 && num !=2){
            printf("Please just choose one from the two choice with number 1 or 2\n"
                   "==>choice:");
        }
        else{
            break;
        }
    }
    //READ FROM FILE DECIDED BY USER
    if(num==1){
        while(1){
            printf("Then, which file would you like to insert?\n");
            printf("==>Filename(<20 chars):");
            string=readChar(100);
            if (!string){
                printf("The length of filename does not meet the need.\n");
                printf("Please try again>>>\n\n");
            }
            else{
                FILE *file;
                file = fopen(string, "r");
                Node *head=(Node *)malloc(sizeof (Node));
                int *delay=(int *)malloc(sizeof(int));
                if(load_Script(file, head, delay)==0){
                    printf("\nProgram End.\n");
                    fclose(file);
                    return 0;
                }
                fclose(file);
                printf("\nThen how many generations would you like to have?\n"
                       "IF NULL is input, then the evolution will just stop when there is no change.\n"
                       "==>number:");
                while(1){
                    num=readInt(10);
                    if(num==-1){
                        No_Limit(delay, head);
                        break;
                    }
                    else if(num==-2){
                        printf("The number is too long, please try again.\n"
                               "==>number:");
                    }
                    else if(num==-3){
                        printf("This program can just accept positive integers, please try again\n"
                               "==>number:");
                    }
                    else{
                        Node *present, *last, *temp;
                        char *foldername,*filename;
                        last = head;
                        foldername=CreateFolder();
                        for(i=0;i<num;i++){
                            present=copy_Grid(last);
                            printGrid(present);
                            makeLife(last,present);
                            temp=last;
                            last=present;
                            present=NULL;
                            free_all(temp);
                            filename = makeFilePath(foldername,i+1);
                            file = fopen(filename, "w");
                            storeGrid(file, last);
                            fclose(file);
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
    //NEED SDL TO LET USER POINT
    else if(num == 2){

    }
    exit(0);
}
