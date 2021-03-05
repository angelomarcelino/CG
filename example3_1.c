#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

static GLfloat spin = 0.0;
static GLfloat pos = -5.0;

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_FLAT);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glPushMatrix();
   glRotatef(spin, 0.0, 0.0, 1.0);
   glColor3f (1.0, 1.0, 1.0);
   //glLoadIdentity ();             /* clear the matrix */
            /* viewing transformation  */
   //gluLookAt (0.0, 0.0, 2.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glTranslatef (0.0, 0.0, pos);
   //glScalef (1.0, 2.0, 1.0);      /* modeling transformation */
   glutWireCube(1.0);
   glPopMatrix();
   //glutWireSphere(0.5, 20, 20);
   // glFlush ();
   glutSwapBuffers();
}

void spinDisplay(void) {

   static GLfloat movm = 0.0;
   spin = spin + 0.1;
   if (spin > 360.0){
     spin = spin - 360.0;
   }
   /* pos = pos + movm;
   if (pos <= -5.0) {
     movm = 0.001;
   }
   else if (pos >= -2.0) {
     movm = -0.001;
   } */
   glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   // glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   gluPerspective(60, 2, 1.5, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void mouse(int button, int state, int x, int y) 
{
   switch (button) {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
           glutIdleFunc(spinDisplay);
         break;
      case GLUT_MIDDLE_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
   
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize(720, 480); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutMouseFunc(mouse);
   glutMainLoop();
   return 0;
}