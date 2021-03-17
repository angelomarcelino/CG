#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string>


#define screen_width 750
#define screen_height 750
#define true 1
#define false 0
#define perpendicular 0

int gridXsize = 20;
int gridZsize = 20;
float plane[] = {0.0, 1.0, 0.0, -50.0,};
float sphere[] = {250.0, 270.0, -100.0, 100.0};
float eye[] = {0.0, 400.0, 550.0};
float light[] = {250.0, 550.0, -200.0};

float dot(float *u, float *v)
{
   return u[0]*v[0] + u[1]*v[1] + u[2]*v[2];
}

void norm(float *u)
{
   float norm = sqrt(abs(dot(u,u)));

   for (int i =0; i <3; i++)
   {
      u[i] = u[i]/norm;
   }

}

float plane_intersect(float *u, float *pO)
{
   float normt[3] = {plane[0], plane[1], plane[2]};

   float s;

   if (dot(u,normt) == 0)
   {
      s = -10;
   }

   else
   {//#include "stdafx.h"
      s = (plane[3]-(dot(pO,normt)))/(dot(u,normt));
   }

   return s;
}

float sphere_intersect(float *u, float *pO)
{

   float deltaP[3] = {sphere[0]-pO[0],sphere[1]-pO[1],sphere[2]-pO[2]};
   float deltLen = sqrt(abs(dot(deltaP,deltaP)));
   float t=0;
   float answer;
   float det;

   if ((det =(abs(dot(u,deltaP)*dot(u,deltaP))- (deltLen*deltLen)+sphere[3]*sphere[3])) < 0)
   {
      answer = -10;
   }

   else
   {
      t =-1*dot(u,deltaP)- sqrt(det) ;

      if (t>0)
      {
         answer = t;
      }

      else
      {
         answer = -10;
      }
   }

   return answer;
}

void find_reflect(float *u, float s, float *pO)
{
   float n[3] = {pO[0]+s *u[0]-sphere[0],pO[1]+s *u[1]-sphere[1],pO[2]+s *u[2]- sphere[2]};
   float l[3] = {s *u[0],s *u[1],s *u[2]};
   u[0] =(2*dot(l,n)*n[0])-l[0];
   u[1] = (2*dot(l,n)*n[1])-l[1];
   u[2] = (2*dot(l,n)*n[2])-l[2];
}

float find_shade(float *u,float s, float *pO)
{
   float answer;
   float lightVec[3] = {light[0]-(pO[0]+s *u[0]), light[1]-(pO[1]+s *u[1]), light[2]-(pO[2]+s *u[2])};
   float n[3] = {pO[0]+s *u[0]-sphere[0],pO[1]+s *u[1]-sphere[1],pO[2]+s *u[2]-sphere[2]};
   answer = -1*dot(lightVec,n)/(sqrt(abs(dot(lightVec,lightVec)))*sqrt(abs(dot(n,n))));
   return answer;
}

void init()
{
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0,screen_width,0,screen_height);
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   for (int i=0; i < screen_width; i++)
   {
      for (int j=0; j < screen_height; j++)
      {
         float ray[3] = {1*(eye[0]-i),-1*(eye[1]-j),1*eye[2]};
         float point[3] = {(float)i,(float)j,0};
         norm(ray);
         int plotted = false;

         while (!plotted)
         {
            float s_plane = plane_intersect(ray, point);
            float s_sphere = sphere_intersect(ray, point);

            if (s_plane <= 0 && s_sphere <=0)
            {
               glColor3f(0,0,0);
               glBegin(GL_POINTS);
               glVertex3f(i,j,0);
               glEnd();
               plotted = true;
            }

            else if (s_sphere >= 0  && (s_plane <=0 || s_sphere <= s_plane))
            {
               find_reflect(ray, s_sphere, point);
            }

            else if (s_plane >=0 && (s_sphere <=0 ||s_plane <= s_sphere))
            {
               float shade = find_shade(ray, s_plane, point);
               float xx = s_plane*ray[0] + eye[0];
               float z = s_plane*ray[2] + eye[2];

               if (abs((int)xx/gridXsize)%2 == abs((int)z/gridZsize)%2)
               {
                  glColor3f(shade,0,0);
               }

               else
               {
                  glColor3f(shade,shade,shade);
               }

               glBegin(GL_POINTS);
               glVertex3f(i,j,0);
               glEnd();
               plotted = true;
            }
         }
      }
   }

   glFlush();
}

int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutCreateWindow("Ray Trace with Sphere.");
   glutInitWindowSize(screen_width,screen_height);
   glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
   glutDisplayFunc(display);
   init();
   glutMainLoop();
   return 0;
}