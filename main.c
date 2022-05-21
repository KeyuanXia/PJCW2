#include <stdio.h>

#include "Initial.h"
#include "Array.h"
#include "utility.h"
#include "ViewDraw.h"
#include <SDL2/SDL.h>

int main() {
    int num = -1, i;
    char *string, ch;
    printf("********WELCOME********\n\n");
    while (1) {
        printf("-------GAME TYPE-------\n");
        printf("|  1)INSERT FILE      |\n");
        printf("|  2)PERSONAL DESIGN  |\n");
        printf("|  3)QUIT             |\n");
        printf("==>choice:");
        while (1) {
            num = readInt(1);
            if (num == -1) {
                printf("Please enter a number at least.\n"
                       "==>choice:");
            } else if (num == -2) {
                printf("Please just enter one positive integer.\n"
                       "==>choice:");
            } else if (num == -3) {
                printf("Please don't enter any symbol except number.\n"
                       "==>choice:");
            } else if (num != 1 && num != 2 && num != 3) {
                printf("Please just choose one from the three choice with number 1 or 2\n"
                       "==>choice:");
            } else if (num == 3) {
                exit(0);
            }
            else{
                break;
            }
    }
    //READ FROM FILE DECIDED BY USER
    if (num == 1) {
        while (1) {
            printf("Then, which file would you like to insert?\n");
            printf("==>Filename(<20 chars):");
            string = readChar(100);
            if (!string) {
                printf("The length of filename does not meet the need.\n");
                printf("Please try again>>>\n\n");
            } else {
                FILE *file;
                file = fopen(string, "r");
                Node *head = creat_Node(-1);
                int *delay = (int *) malloc(sizeof(int));
                if (load_Script(file, head, delay) == 0) {
                    printf("\nProgram End.\n");
                    if (file)
                        fclose(file);
                    return 0;
                }
                fclose(file);
                printf("\nThen how many generations would you like to have?\n"
                       "IF NULL is input, then the evolution will just stop when there is no change.\n"
                       "==>number:");
                while (1) {
                    num = readInt(10);
                    if (num == -1) {
                        No_Limit(delay, head);
                        break;
                    } else if (num == -2) {
                        printf("The number is too long, please try again.\n"
                               "==>number:");
                    } else if (num == -3) {
                        printf("This program can just accept positive integers, please try again\n"
                               "==>number:");
                    } else {
                        Limit(delay, head, num);
                        free_all(head);
                        free(delay);
                        break;
                    }
                }
                break;
            }
        }
    }
        //NEED SDL TO LET USER POINT
    else if (num == 2) {
        int xnum, ynum;
        printf("So how many rows would you like to have?\n"
               "==>choice(1~200):");
        while (1) {
            num = readInt(200);
            if (num == -1) {
                printf("Please enter a number at least.\n"
                       "==>choice(1~200):");
            } else if (num == -2) {
                printf("Please don't enter too large number.\n"
                       "==>choice(1~200):");
            } else if (num == -3) {
                printf("Please don't enter any symbol except number.\n"
                       "==>choice(1~200):");
            } else if (num == 0) {
                printf("Please don't use 0 as height.\n"
                       "==>choice(1~200):");
            } else if (num > 200) {
                printf("Please don't enter too large number.\n"
                       "==>choice(1~200):");
            } else {
                break;
            }
        }
        ynum = num;
        printf("So how many columns would you like to have?\n"
               "==>choice(1~200):");
        while (1) {
            num = readInt(200);
            if (num == -1) {
                printf("Please enter a number at least.\n"
                       "==>choice(1~200):");
            } else if (num == -2) {
                printf("Please don't enter too large number.\n"
                       "==>choice(1~200):");
            } else if (num == -3) {
                printf("Please don't enter any symbol except number.\n"
                       "==>choice(1~200):");
            } else if (num == 0) {
                printf("Please don't use 0 as width.\n"
                       "==>choice(1~200):");
            } else if (num > 200) {
                printf("Please don't enter too large number.\n"
                       "==>choice(1~200):");
            } else {
                break;
            }
        }
        xnum = num;
        Node *head;
        head = Customer(xnum, ynum);
        printf("Additionally, how long delay would you like to have?\n"
               "Don't worry, this can be changed during the game.\n"
               "==>choice:");
        while (1) {
            num = readInt(100);
            if (num == -1) {
                printf("Please enter a number at least.\n"
                       "==>choice:");
            } else if (num == -2) {
                printf("Please don't enter too large number.\n"
                       "==>choice:");
            } else if (num == -3) {
                printf("Please don't enter any symbol except number.\n"
                       "==>choice:");
            } else {
                break;
            }
        }
        int *delay;
        delay = (int *) malloc(sizeof(int));
        *delay = num;
        printf("The last, how many times would you like to evolute this grid?\n"
               "You can type in nothing to make evolution until no change.\n"
               "==>choice:");
        while (1) {
            num = readInt(100);
            if (num == -1) {
                No_Limit(delay, head);
                break;
            } else if (num == -2) {
                printf("Please don't enter too large number.\n"
                       "==>choice:");
            } else if (num == -3) {
                printf("Please don't enter any symbol except number.\n"
                       "==>choice:");
            } else {
                Limit(delay, head, num);
                free(delay);
                free_all(head);
                break;
            }
        }

    }
        printf("\n\n");
}
}
