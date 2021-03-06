//
// Created by kxia on 22-4-24.
//

#ifndef PJCWK2_ARRAY_H
#define PJCWK2_ARRAY_H
typedef struct field {
    int this;
    struct field *xlast;
    struct field  *ylast;
    struct field  *xnext;
    struct field  *ynext;
}Node;

int get_x_size(Node *first, int row);

int get_x_max_size(Node *first);

int get_y_size(Node *first);

Node *getPosition(Node *first, int x, int y);

Node *creat_Node(int type);

Node *copy_Grid(Node *last);

Node *create_Grid(int xnum, int ynum);
#endif //PJCWK2_ARRAY_H
