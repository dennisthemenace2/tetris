#include "render.h"


#include <GL/glut.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h> 

 int x=10,y=10;
 int boxsize = 20;
 #define MAPX 10
 #define MAPY 20
 struct Box* map[MAPX][MAPY];
 struct Stone cur;
 struct Stone next;

 int TimerMs = 1000;
 bool gameOver = false;


char string [100];

unsigned int points;
char pointsstring [100];

void Setup(){
    srand (time(NULL));

    memset(map,0,MAPX*MAPY*sizeof(struct Box*) );
  
    memset(next.boxes,0,sizeof(struct Box*) * MAXBOX );
    memset(cur.boxes,0,sizeof(struct Box*) * MAXBOX );

    newStone(&cur);

    newStone(&next);
    
}

void FreeAll(){
    for(int i = 0; i<MAXBOX; ++i){
        if(cur.boxes[i] ){
            free(cur.boxes[i]);
        }
    }
    for(int i = 0; i<MAXBOX; ++i){
        if(next.boxes[i] ){
            free(next.boxes[i]);
        }
    }
}


void newStone( struct Stone *stone){

    memset(stone->boxes,0,sizeof(struct Box*) * MAXBOX );

    float r = (float)rand()/ (float)RAND_MAX, g = (float)rand() / (float)RAND_MAX, b = (float)rand() / (float)RAND_MAX ;

    int c =  rand() % 6;
    printf("new stone %d \n", c);

    for (int i = 0 ;i< 4;++i){ // reset rot box
        for (int n = 0 ; n<4 ; ++n){
            stone->bbox[i][n]= false;
        }
    }
    stone->px = 0; // offset to staert 
    stone->py = 0; // offset to staert 

    int index = 0;
    if (c == 0){ // box
        for(int i = 0; i<2; ++i){
            for (int n = 0 ; n<2 ;++n){
                struct Box * box = malloc( sizeof(struct Box) );
                box->r = r;
                box->g = g;
                box->b = b;
                box->x=i;
                box->y=n;                
                stone->boxes[index++]= box;
                stone->bbox[i][n] = true;

                 
            }
        }
        stone->dimx = 2; 
        stone->dimy = 2;
            
    }else if(c == 1){ // long 4
       for(int i = 0; i<4; ++i){
                struct Box * box = malloc( sizeof(struct Box) );
                box->r = r;
                box->g = g;
                box->b = b;
                box->x=i;
                box->y=0;                
                stone->boxes[index++]= box; 
                stone->bbox[i][0] = true;
       
        }

        stone->dimx = 4; 
        stone->dimy = 4;

    }else if(c == 2){ // pyramid
       for(int i = 0; i<3; ++i){
            for (int n = 0 ; n<2 ;++n){
                if(n == 1 && i %2 == 0 ){
                    break;
                }
                struct Box * box = malloc( sizeof(struct Box) );
                box->r = r;
                box->g = g;
                box->b = b;
                box->x=i;
                box->y=n;                
                stone->boxes[index++]= box;
                stone->bbox[i][n] = true;

                 
            }
        }

        stone->dimx = 3; 
        stone->dimy = 3;
    }else if(c == 3){ // L
       for(int i = 0; i<3; ++i){
            for (int n = 0 ; n<3 ;++n){
                if( (n == 0 && i < 1 )  || ( n== 1 && i > 1 ) ){
                    break;
                }
                struct Box * box = malloc( sizeof(struct Box) );
                box->r = r;
                box->g = g;
                box->b = b;
                box->x=i;
                box->y=n;                
                stone->boxes[index++]= box;
                stone->bbox[i][n] = true;

                 
            }
        }

        stone->dimx = 3; 
        stone->dimy = 3;
    }else if(c == 4){ // T
       for(int i = 0; i<3; ++i){
            for (int n = 0 ; n<3 ;++n){
                if( (n == 0 && i > 1 )  || ( n== 1 && i <  1) ){
                    break;
                }
                struct Box * box = malloc( sizeof(struct Box) );
                box->r = r;
                box->g = g;
                box->b = b;
                box->x=i;
                box->y=n;                
                stone->boxes[index++]= box;
                stone->bbox[i][n] = true;

                 
            }
        }

        stone->dimx = 3; 
        stone->dimy = 3;
    }else if(c == 5){ // Z
       for(int i = 0; i<3; ++i){
            for (int n = 0 ; n<2 ;++n){

                if( i == 2 && n == 1 ){
                    continue;
                }
                if( i == 0 && n == 0 ){
                    continue;
                }
                struct Box * box = malloc( sizeof(struct Box) );
                box->r = r;
                box->g = g;
                box->b = b;
                box->x=i;
                box->y=n;                
                stone->boxes[index++]= box;
                stone->bbox[i][n] = true;

                 
            }
        }

        stone->dimx = 3;
        stone->dimy = 3;

    }

    if(c > 5 ){
        printf("dude a got no such stone...\n");
    }
}

void Render(){
	glClear(GL_COLOR_BUFFER_BIT );
	glLoadIdentity();
 
  

//draw a line){){


    glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
		glVertex2i(x,y);
		glVertex2i(x,MAPY*boxsize +y);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(x,MAPY*boxsize +y );
		glVertex2i(MAPX*boxsize+ x, MAPY*boxsize +y );
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(MAPX*boxsize+ x, MAPY*boxsize +y );
    	glVertex2i(x+ MAPX*boxsize, y );
	glEnd();


    
    drawText ("Next:",x+MAPX*boxsize+ 20,y + (MAPY*boxsize /2.) - 5);

	glBegin(GL_LINES);
		glVertex2i(x+MAPX*boxsize+ 10 ,y + (MAPY*boxsize /2.) );
		glVertex2i(x+MAPX*boxsize+ 10,y + (MAPY*boxsize /2.) + 4* boxsize);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(x+MAPX*boxsize+ 10 ,y + (MAPY*boxsize /2.) );
		glVertex2i(x+MAPX*boxsize+ 10 + 4* boxsize , y + (MAPY*boxsize /2.) );
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(x+MAPX*boxsize+ 10,y + (MAPY*boxsize /2.) + 4* boxsize);
		glVertex2i(x+MAPX*boxsize+ 10+ 4* boxsize,y + (MAPY*boxsize /2.) + 4* boxsize);
	glEnd();

	glBegin(GL_LINES);
		glVertex2i(x+MAPX*boxsize+ 10+ 4* boxsize,y + (MAPY*boxsize /2.) );
		glVertex2i(x+MAPX*boxsize+ 10 + 4* boxsize  ,y + (MAPY*boxsize /2.)+ 4* boxsize );
	glEnd();


    DrawNext(&next);

    for(int i = 0 ;i< MAPX;++i){
        for(int n = 0; n < MAPY ; ++n){
            if(map[i][n]){
                DrawRectangle(map[i][n]);
            }
    
        }

    }
    for(int i = 0; i<MAXBOX; ++i){
        if(cur.boxes[i] ){
            DrawRectangle(cur.boxes[i]);
        }
    }

    glColor3f(1.0, 0.0, 0.0);
    drawText (string,50,50);
    glColor3f(0.0, 1.0, 0.0);
    
    sprintf (pointsstring, "Points: %d ", points);
    drawText (pointsstring,10,450);


	//printf("RENDER");
	glutSwapBuffers();
}



void DrawNext(struct Stone *stone) 
{ 
        if (!stone){
            return;
        }

        for(int i = 0 ;i < MAXBOX;++i){
            if(stone->boxes[i]){

                 glColor3f(stone->boxes[i]->r, stone->boxes[i]->g, stone->boxes[i]->b);

                 float left = stone->boxes[i]->x * boxsize +x + MAPX*boxsize +10,
                          top =  stone->boxes[i]->y * boxsize +y + (MAPY*boxsize/2.) + 5,
                          right = left + boxsize,
                          bottom= top + boxsize ; 

                    glBegin(GL_QUADS); 
                    glVertex2f(left,bottom);      //Left - Bottom 
                    glVertex2f(right,bottom); 
                    glVertex2f(right,top); 
                    glVertex2f(left,top); 

                    glEnd(); 
            }
        
        }

}

void DrawRectangle(struct Box *rect) 
{ 
        if (!rect){
            return;
        }

        glColor3f(rect->r, rect->g, rect->b);

        float left = rect->x * boxsize +x,
              top =  rect->y * boxsize +y,
              right = left + boxsize,
              bottom= top + boxsize ; 

        glBegin(GL_QUADS); 
        glVertex2f(left,bottom);      //Left - Bottom 
        glVertex2f(right,bottom); 
        glVertex2f(right,top); 
        glVertex2f(left,top); 

        glEnd(); 
}


void Timer(int v) {
    if(gameOver){
        return;
    } 
    glutTimerFunc(TimerMs,Timer,1); 

    printf("timer move down \n");

    moveDown();

}

void moveDown(){
    bool end = false;

    bool possible = true;
    for(int i = 0; i<MAXBOX; ++i){
        if(cur.boxes[i] ){
            if( cur.boxes[i]->y+1 == MAPY || map[ cur.boxes[i]->x ][cur.boxes[i]->y+1] != NULL  ){
                possible = false;
                end = true;
                printf("not possible but  \n");

            }
        }
    }

    if(possible){
        for(int i = 0; i<MAXBOX; ++i){
            if(cur.boxes[i] ){
                cur.boxes[i]->y++;
                if( cur.boxes[i]->y == MAPY || map[ cur.boxes[i]->x ][cur.boxes[i]->y +1] != NULL  ){
                    end = true;
                    printf("moved and end now  \n");

                }
            }
        }
        cur.py++;

    }
    
    if(end){
      for(int i = 0; i<MAXBOX; ++i){
            if(cur.boxes[i] ){
               if(map[ cur.boxes[i]->x ][cur.boxes[i]->y ] != NULL){
                 printf("map field is not empty game over. take care of this case.!");
                

                 free( map[ cur.boxes[i]->x ][cur.boxes[i]->y ] );
                 strcpy(string,"Game Over, Man !");
                 gameOver = true;
    

               }
              
               map[ cur.boxes[i]->x ][cur.boxes[i]->y ] =cur.boxes[i] ;
               printf("moved the box to the map  \n");

                    
            }
        }

        // check for remove...
       
        printf("check for remove  \n");

        int removeAnz = 0;
        for(int i = MAPY-1 ;i>= 0;--i){
           int filled = 0;   
           for(int n = MAPX -1 ; n >= 0 ; --n){
                if(map[n][i]){
                   map[n][i]->y+=removeAnz;
                    ++filled;
                }
            }
            if(filled == MAPX){ // all are filled ! remove
                printf("remove one ..\n");
                for(int r=0;r<MAPX; ++r){
                    if(! map[r][i ] ){
                        printf("that an error !!!!");
                    }
                    free(map[r][i ]);
                    map[r][i ] = NULL;
                }
                for(int mx = 0; mx < MAPX; ++mx ){
                    for(int my = i-1 ; my >= 0 ; -- my)  {
                        map[mx][my+1] = map[mx][my]; // move all one lower 
                    }          
                }
                for(int mx = 0; mx < MAPX; ++mx ){
                    map[mx][0] = NULL; 
                }
                
                ++i;
                removeAnz++;
                printf("removed one  \n");

            }
            points += removeAnz * 10+ (removeAnz*removeAnz);

        }

        memcpy(&cur, &next, sizeof(struct Stone) );
        newStone(&next);

    }
}

void Reshape (int w, int h){
//	WINDOW_WIDTH =w ;
//	WINDOW_HEIGHT =h ;

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0, w, h, 0);


   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();

}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}


//Key Board Message 
void inputKey(int key, int x, int y) {

    if(gameOver){
        return;
    }
    bool possible = true;

	switch (key) {
		case GLUT_KEY_LEFT :
            for(int i = 0; i<MAXBOX; ++i){
                if(cur.boxes[i] ){
                    if( cur.boxes[i]->x-1 < 0 || map[ cur.boxes[i]->x-1 ][cur.boxes[i]->y] != NULL  ){
                        possible = false;
                    }
                }
            }
            if(possible){
                for(int i = 0; i<MAXBOX; ++i){
                    if(cur.boxes[i] ){
                        cur.boxes[i]->x--;
                    }   
                }
                cur.px--; 

            }
            
			break;

		case GLUT_KEY_RIGHT : 
            for(int i = 0; i<MAXBOX; ++i){
                if(cur.boxes[i] ){
                    if( cur.boxes[i]->x+1 > MAPX-1 || map[ cur.boxes[i]->x+1 ][cur.boxes[i]->y] != NULL  ){
                        possible = false;
                    }
                }
            }
            if(possible){
                for(int i = 0; i<MAXBOX; ++i){
                    if(cur.boxes[i] ){
                        cur.boxes[i]->x++;
                    }   
                }
                cur.px++;
            }

			break;


		case GLUT_KEY_UP : 
            rotateCurrentStone();
			break ;


		case GLUT_KEY_DOWN : 
            moveDown();
			break;

	}
}

void rotateCurrentStone(){
    printf("rotate stone...\n");

    bool result[4][4];
    if(! cur.boxes[0]){
        printf("no current stone.. so i cant rotate...\n");
        return;
    }


    int stonecnt = 0;
    bool collision = false;

    // check rotate stone first..
    for(int x=0; x<cur.dimx; ++x){
        for(int y=0; y<cur.dimy; ++y){
            if(cur.bbox[y][cur.dimy - 1 -x] ){// move stone
                int newx =  cur.px  + y;
                int newy =  cur.py + cur.dimy -1 -x;
                if(map[newx][newy] || newy>= MAPY || newx < 0 || newx >= MAPX ){
                    printf("will collide will not rotate...\n");
                    return;
                }
            }
        }
    }


    for(int x=0; x<cur.dimx; ++x){
        for(int y=0; y<cur.dimy; ++y){
            result[x][y]= cur.bbox[y][cur.dimy - 1 -x];
            if(result[x][y] ){// move stone
                printf(" cur.boxes[stonecnt]->x %d", cur.boxes[stonecnt]->x);
                printf(" cur.px  + y %d \n", cur.px  + y);

                cur.boxes[stonecnt]->x =  cur.px  + y;
                cur.boxes[stonecnt++]->y =  cur.py + cur.dimy -1 -x;
            }
            printf ("%d", result[x][y] );
        }
        printf ("\n");

    }
    printf ("\n");
    
    memcpy(cur.bbox,result,4*4*sizeof(bool)); // cpy

}

void drawText(char*string,int x,int y)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y,0);
	  glScalef(0.1,-0.1,1);
  
	  for (c=string; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();

}



