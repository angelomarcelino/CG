#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int year = 0, day = 0;
static GLdouble planet[8], moon[8];

GLdouble double_rand( GLdouble min, GLdouble max )
{
    GLdouble scale = rand() / (GLdouble) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 0.0);

   glPushMatrix(); // Sun Matrix
   /* draw sun */
   glutSolidSphere(1.0, 20, 16);
   glRotatef((GLfloat)year, 1.0, 1.0, 1.0);
   
   glColor3f (1.0, 1.0, 1.0);
   for (int i = 0; i < 3; i++) {
     // Add planet
      glTranslatef (2.5, 0.0, 0.0);
      glPushMatrix(); // Planet Matrix
      glRotatef((GLfloat)day, 1.0, 0.0, 0.0); // Rotates
      
      glutWireSphere(planet[i], 10, 8);
	  glPopMatrix();

	  glPushMatrix();
	  glRotatef((GLfloat)day, 1.0, 1.0, 0.0);  // Rotates
	  for (int j = 0; j < 2; j++) {
         glTranslatef (0.0, 0.0, 0.3);
         glPushMatrix(); // Moon Matrix
         glutWireSphere(moon[j], 10, 8);
         glPopMatrix();
      }
      glPopMatrix();
   }

   glPopMatrix();
   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         day = (day + 10) % 360;
         glutPostRedisplay();
         break;
      case 'D':
         day = (day - 10) % 360;
         glutPostRedisplay();
         break;
      case 'y':
         year = (year + 5) % 360;
         glutPostRedisplay();
         break;
      case 'Y':
         year = (year - 5) % 360;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

int main(int argc, char **argv) {

   srand((unsigned int)time(NULL));
   for (int i = 0; i < 8; i++) {
      // Add planet
      planet[i] = double_rand(0.1, 0.5);
      moon[i] = double_rand(0.01, 0.1);
      printf("%f --- %f\n",moon[i], planet[i]);
   }
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
