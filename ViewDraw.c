//
// Created by keyuanxia on 22-5-20.
//
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#include "ViewDraw.h"
#include "Array.h"
#include "utility.h"
#include "MakeLife.h"
#include "Initial.h"

//屏幕的宽高常量

int get_Width(Node *first){
    int ym, c, i, j;
    ym=get_y_size(first);
    c=0;
    for(j=0;j<ym;j++){
        i= get_x_size(first,j);
        if(i>c){
            c=i;
        }
    }
    return c;
}

int get_Height(Node *first){
    return get_y_size(first);
}

void rect_Size(SDL_Rect *rect, int w, int h){
    rect->w=w;
    rect->h=h;
}

void draw_White(SDL_Renderer *renderer, SDL_Rect *rect, int x, int y){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    rect->x=x;
    rect->y=y;
    SDL_RenderDrawRect(renderer, rect);
    SDL_RenderFillRect(renderer, rect);
}

void draw_Black(SDL_Renderer *renderer, SDL_Rect *rect, int x, int y){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    rect->x=x;
    rect->y=y;
    SDL_RenderDrawRect(renderer, rect);
    SDL_RenderFillRect(renderer, rect);
}

int get_rect_size(SDL_Rect *rect, Node *first){
    int t;
    if(get_Height(first)<=get_Width(first)){
        rect->w=1000/ get_Width(first)-2;
        rect->h=1000/ get_Width(first)-2;
        return 1;
    }
    else{
        rect->w=1000/ get_Height(first)-2;
        rect->h=1000/ get_Height(first)-2;
        return 2;
    }
}

int print_Grid(Node *present, SDL_Rect *rect, SDL_Renderer *renderer){
    int i,j;
    for(j=0;j< get_y_size(present);j++){
        for (i = 0; i < get_x_size(present, j); ++i) {
            if(getPosition(present,i,j)->this==0){
                draw_Black(renderer,rect, (rect->w+2)*i+1, (rect->h+2)*j+1);
            }
            else if(getPosition(present,i,j)->this==1){
                draw_White(renderer,rect, (rect->w+2)*i+1, (rect->h+2)*j+1);
            }
        }
    }
    //present render
    SDL_RenderPresent(renderer);
}

int No_Limit(int *delay, Node *head)
{
    bool quit=false, end=false;
    //initial of makelife
    FILE *file;
    Node *present, *last, *temp;
    char *foldername,*filename;
    last = head;
    foldername=CreateFolder();

    //Initial SDL part
    int c, i, j;
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        exit(-1);
    }

    //Start of create Window dynamicly
    int which;
    which=get_rect_size(&rect, head);
    if(which ==1 ){
        window = SDL_CreateWindow("GAME OF LIFE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000,
                                  (rect.h+2)* get_y_size(head), SDL_WINDOW_SHOWN);
        if (NULL == window)
        {
            SDL_Quit();
            return -1;
        }
    }
    else{
        window = SDL_CreateWindow("GAME OF LIFE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (rect.w+2)*
                                                                                                    get_x_max_size(head),
                                  1000, SDL_WINDOW_SHOWN);
        if (NULL == window)
        {
            SDL_Quit();
            return -1;
        }
    }
    //End of create Window


    //create background
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 0, 0));
    SDL_UpdateWindowSurface(window);
    //create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    //End of SDL initial

    int state=1;
    bool once=false;
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    i = e.key.keysym.sym;
                    if (i==SDLK_DOWN || i==SDLK_LEFT) {
                        if (*delay > 200) {
                            *delay -= 100;
                        }
                    } else if (i==SDLK_RIGHT || i==SDLK_UP) {
                        *delay += 100;
                    } else if (i==SDLK_p) {
                        if (state == 1) {
                            state = 0;
                        } else {
                            state = 1;
                            once = false;
                            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 0, 0));
                            SDL_UpdateWindowSurface(window);
                            print_Grid(present, &rect, renderer);
                        }
                    }
                    break;
                case SDL_QUIT:
                    quit=true;
                    break;
                default:
                    break;
            }
        }
        if(state==1) {
            present = copy_Grid(last);
            print_Grid(present, &rect, renderer);
            makeLife(last, present);
            temp = last;
            last = present;
            //store life record
            filename = makeFilePath(foldername, c);
            file = fopen(filename, "w");
            storeGrid(file, present);
            fclose(file);
            //end of store
            if (checkSame(temp, present) == 1 && end == false) {
                free_all(temp);
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 255, 0));
                SDL_UpdateWindowSurface(window);
                print_Grid(present, &rect, renderer);
                end = true;
            } else if (checkSame(temp, present) == 0) {
                print_Grid(present, &rect, renderer);
                free_all(temp);
                SDL_Delay(*delay);
            }
        }
        else if(state==0 && once == false){
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 255));
            SDL_UpdateWindowSurface(window);
            print_Grid(present, &rect, renderer);
            once=true;
        }
    }
    return 0;
}


int Limit(int *delay, Node *head)
{
    bool quit=false, end=false;
    //initial of makelife
    FILE *file;
    Node *present, *last, *temp;
    char *foldername,*filename;
    last = head;
    foldername=CreateFolder();

    //Initial SDL part
    int c, i, j;
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Renderer* renderer;
    SDL_Rect rect;
    SDL_Event e;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        exit(-1);
    }

    //Start of create Window dynamicly
    int which;
    which=get_rect_size(&rect, head);
    if(which ==1 ){
        window = SDL_CreateWindow("GAME OF LIFE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1000,
                                  (rect.h+2)* get_y_size(head), SDL_WINDOW_SHOWN);
        if (NULL == window)
        {
            SDL_Quit();
            return -1;
        }
    }
    else{
        window = SDL_CreateWindow("GAME OF LIFE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (rect.w+2)*
                                                                                                    get_x_max_size(head),
                                  1000, SDL_WINDOW_SHOWN);
        if (NULL == window)
        {
            SDL_Quit();
            return -1;
        }
    }
    //End of create Window


    //create background
    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 0, 0));
    SDL_UpdateWindowSurface(window);
    //create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    //End of SDL initial

    int state=1;
    bool once=false;
    while(!quit) {
        while(SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_KEYDOWN:
                    i = e.key.keysym.sym;
                    if (i==SDLK_DOWN || i==SDLK_LEFT) {
                        if (*delay > 200) {
                            *delay -= 100;
                        }
                    } else if (i==SDLK_RIGHT || i==SDLK_UP) {
                        *delay += 100;
                    } else if (i==SDLK_p) {
                        if (state == 1) {
                            state = 0;
                        } else {
                            state = 1;
                            once = false;
                            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 255, 0, 0));
                            SDL_UpdateWindowSurface(window);
                            print_Grid(present, &rect, renderer);
                        }
                    }
                    break;
                case SDL_QUIT:
                    quit=true;
                    break;
                default:
                    break;
            }
        }
        if(state==1) {
            present = copy_Grid(last);
            print_Grid(present, &rect, renderer);
            makeLife(last, present);
            temp = last;
            last = present;
            //store life record
            filename = makeFilePath(foldername, c);
            file = fopen(filename, "w");
            storeGrid(file, present);
            fclose(file);
            //end of store
            if (checkSame(temp, present) == 1 && end == false) {
                free_all(temp);
                SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 255, 0));
                SDL_UpdateWindowSurface(window);
                print_Grid(present, &rect, renderer);
                end = true;
            } else if (checkSame(temp, present) == 0) {
                print_Grid(present, &rect, renderer);
                free_all(temp);
            }
        }
        else if(state==0 && once == false){
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 0, 255));
            SDL_UpdateWindowSurface(window);
            print_Grid(present, &rect, renderer);
            once=true;
        }
        SDL_Delay(*delay);
    }


    return 0;
}