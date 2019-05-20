#include <GL/glut.h>

#include <stdio.h>
#include "render.h"

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (795, 500); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow ("Window");

   Setup();

   glutDisplayFunc(Render); 
   glutIdleFunc(Render);

   glutTimerFunc(1,Timer,1);

   glutReshapeFunc(Reshape);
   
   glutKeyboardFunc(keyboard);

   glutSpecialFunc(inputKey);
  
 //  glutPassiveMotionFunc(MouseMotion);


   glutMainLoop();
   return 0;
}
