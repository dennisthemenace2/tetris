#ifndef RENDER_H
#define RENDER_H



#include <stdbool.h>
#include <time.h> 

struct Box{ 
        int x,y; 
        float r,g,b;
};
#define MAXBOX 6
struct Stone{
    struct Box* boxes[MAXBOX];
    bool bbox[4][4];
    int dimx, dimy;
    int px, py; // pivot

    
};

void Setup();
void FreeAll();

void moveDown();

void drawText(char*string,int x,int y);

void DrawNext(struct Stone *stone) ;
void DrawRectangle(struct Box *rect);
void Render();
void Reshape (int w, int h);
void Timer(int v) ;
void inputKey(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);

void newStone(struct Stone *stone);
void rotateCurrentStone();


#endif
