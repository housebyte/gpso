
#include <stdlib.h>
#include <stdio.h>
#ifndef WIN32
#include <unistd.h>
#else
#define random rand
#define srandom srand
#endif
#include <math.h>
#include <time.h>
#include <iostream>
#include <GL/glut.h>
#include "particle.h"

/* Some <math.h> files do not define M_PI... */
#ifndef M_PI
#define M_PI 3.14159265
#endif
#ifndef M_PI_2
#define M_PI_2 1.57079632
#endif

using namespace std;


GLfloat funcpoints[200][200][3];

GLboolean moving = GL_FALSE;

swarm myswarm(14,3);

double gsize=1;	    //Problem size
double hgt=1,scl=1,pscl=1;   //Position
int res=10.0;		//Resolution
int lowres=1;
double scrn = 50;		//Screen size
#define MAX_PLANES 14

struct {
  float speed;          /* zero speed means not flying */
  GLfloat red, green, blue;
  float theta;
  float x, y, z, angle;
} planes[MAX_PLANES];

#define v3f glVertex3f  /* v3f was the short IRIS GL name for
                           glVertex3f */
#define v3d glVertex3d

void loadpoints(void){

double t0,t1,t2,x_,y_;

for(int i=0;i<200;i++){

for(int j=0;j<200;j++){

x_ = ((double)i-100)/res;
y_ = ((double)j-100)/res;

if(lowres==1){
x_ = (int)x_;
y_ = (int)y_;
}

double pos[2];

pos[0] = x_;
pos[1] = y_;

funcpoints[i][j][0]=x_;
funcpoints[i][j][1]=y_;
funcpoints[i][j][2]=myswarm.evalfunc(pos,3);
				}
				}

}

void drawlines2buffer(void){
glNewList(1,GL_COMPILE);
glPushMatrix ();

for(int i=0;i<200;i++){
for(int j=0;j<200;j++){
glBegin(GL_LINES);
glColor3f(0.0,1.0,1.0);
if(i<199){	
v3d( funcpoints[i][j][0],funcpoints[i][j][1],funcpoints[i][j][2]); 
      v3d( funcpoints[i+1][j][0],funcpoints[i+1][j][1],funcpoints[i+1][j][2]);
 }
glEnd();

glBegin(GL_LINES);
glColor3f(0.0,1.0,1.0);
if(j<199){	
v3d( funcpoints[i][j][0],funcpoints[i][j][1],funcpoints[i][j][2]); 
      v3d( funcpoints[i][j+1][0]+0.1,funcpoints[i][j+1][1]+0.1,funcpoints[i][j+1][2]+0.1);
 }
glEnd();

}
}
glPopMatrix ();


glEndList();
}

void
print_bitmap_string(void* font, char* s)
{
   if (s && strlen(s)) {
      while (*s) {
         glutBitmapCharacter(font, *s);
         s++;
      }
   }
}

void
draw(void)
{
  GLfloat red, green, blue;
  int i,j;


glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/*Text output*/
   double x = 15.0;
   double y = -5.0;
   double ystep  = 100.0;
   double yild   = 20.0;
      glColor3f(1.0, 1.0, 1.0);
char string[50]; 
sprintf(string,"Global Best Solution = %f,%f,%f",myswarm.evalfunc(myswarm.globalg,3),myswarm.globalg[0],myswarm.globalg[1]);
int len = strlen(string);
glRasterPos2f(x, y);
print_bitmap_string(GLUT_BITMAP_TIMES_ROMAN_10, string);
         



 /* draw function in 3d */

glCallList(1);


  /* paint planes */
  

  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
  for (i = 0; i < MAX_PLANES; i++)
    if (planes[i].speed != 0.0) {
      glPushMatrix();
      glTranslatef(planes[i].x, planes[i].y, planes[i].z);
//glScalef(1.0 / 5, 1.0 / 5, 1.0 / 5);      
//glRotatef(290.0, 1.0, 0.0, 0.0);
      glRotatef(planes[i].angle, 0.0, 0.0, 1.0);
      glScalef(1.0 / 12.0, 1.0 / 16.0, 1.0 / 16.0);
      glTranslatef(0.0, -4.0, -1.5);
      
if(1){
glBegin(GL_TRIANGLE_STRIP);
      /* left wing */
      v3f(-7.0, 0.0, 2.0);
      v3f(-1.0, 0.0, 3.0);
      glColor3f(red = planes[i].red, green = planes[i].green,
        blue = planes[i].blue);
      v3f(-1.0, 7.0, 3.0);
      /* left side */
      glColor3f(0.6 * red, 0.6 * green, 0.6 * blue);
      v3f(0.0, 0.0, 0.0);
      v3f(0.0, 8.0, 0.0);
      /* right side */
      v3f(1.0, 0.0, 3.0);
      v3f(1.0, 7.0, 3.0);
      /* final tip of right wing */
      glColor3f(red, green, blue);
      v3f(7.0, 0.0, 2.0);      
glEnd();
	}
//glColor3f(0, 1, 0);
//glutSolidSphere(7.0,50,50);

      glPopMatrix();
    }
  glutSwapBuffers();


}


void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho(-scrn, scrn, -scrn*(GLfloat)h/(GLfloat)w, 
              scrn*(GLfloat)h/(GLfloat)w, -scrn, scrn);
   else
      glOrtho(-scrn*(GLfloat)w/(GLfloat)h, 
              scrn*(GLfloat)w/(GLfloat)h, -scrn, scrn, -scrn, scrn);

/* Rescale and resize Globally */

glScalef(scl*6.0 / 3.7, scl*6.0 / 3.7, scl*6.0 / 3.7);
glTranslatef(0.0,hgt,0.0);
glRotatef(310,1.0,0.0,0.0);
glRotatef(65,0.0,0.0,1.0);
glRotatef(5,0.0,1.0,0.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

}

void
tick_per_plane(int i)
{

  myswarm.mainloop(1);

  float theta = planes[i].theta += planes[i].speed;
  planes[i].z =  myswarm.evalfunc(myswarm.p[i].position,3)/gsize;
  planes[i].x =  myswarm.p[i].position[0]/gsize;
  planes[i].y =  myswarm.p[i].position[1]/gsize;
  planes[i].angle = ((atan(2.0) + M_PI_2) * sin(theta) - M_PI_2) * 180 / M_PI;
  if (planes[i].speed < 0.0)
    planes[i].angle += 180;
}

void
add_plane(void)
{
  int i;

  for (i = 0; i < MAX_PLANES; i++)
    if (planes[i].speed == 0) {

#define SET_COLOR(r,g,b) \
	planes[i].red=r; planes[i].green=g; planes[i].blue=b;

      switch (random() % 6) {
      case 0:
        SET_COLOR(1.0, 0.0, 0.0);  /* red */
        break;
      case 1:
        SET_COLOR(1.0, 1.0, 1.0);  /* white */
        break;
      case 2:
        SET_COLOR(0.0, 1.0, 0.0);  /* green */
        break;
      case 3:
        SET_COLOR(1.0, 0.0, 1.0);  /* magenta */
        break;
      case 4:
        SET_COLOR(1.0, 1.0, 0.0);  /* yellow */
        break;
      case 5:
        SET_COLOR(0.0, 1.0, 1.0);  /* cyan */
        break;
      }
      planes[i].speed = ((float) (random() % 20)) * 0.001 + 0.02;
      if (random() & 0x1)
        planes[i].speed *= -1;
      planes[i].theta = ((float) (random() % 257)) * 0.1111;
      tick_per_plane(i);
      if (!moving)
        glutPostRedisplay();
      return;
    }
}

void
remove_plane(void)
{
  int i;

  for (i = MAX_PLANES - 1; i >= 0; i--)
    if (planes[i].speed != 0) {
      planes[i].speed = 0;
      if (!moving)
        glutPostRedisplay();
      return;
    }
}

void
tick(void)
{
  int i;

  for (i = 0; i < MAX_PLANES; i++)
    if (planes[i].speed != 0.0)
      tick_per_plane(i);
}

void
animate(void)
{
  tick();
  glutPostRedisplay();
}

void timer(int value){


/* Set the next timed callback */
    glutTimerFunc ( 30, timer, 0 ) ;

drawlines2buffer();
glutPostRedisplay () ;
}

void
visible(int state)
{
  if (state == GLUT_VISIBLE) {
    if (moving)
      glutIdleFunc(animate);
  } else {
    if (moving)
      glutIdleFunc(NULL);
  }
}

float horiz=0,vert=0,zoom=4.0;


/* ARGSUSED1 */
void
keyboard(unsigned char ch, int x, int y)
{
  switch (ch) {
  case 'l':
	zoom+=1;
      glScalef(1.0/zoom,1.0/zoom,1.0/zoom);
      glutPostRedisplay();
	break;
  case 'k':
	zoom-=1;
      glScalef(1.0/zoom,1.0/zoom,1.0/zoom);
      glutPostRedisplay();
	break;
  case ',':
      vert++;
      glRotatef(vert,0.0,1.0,0.0);
      glutPostRedisplay();
	break;
  case '.':
	vert++;
      glRotatef(vert,1.0,0.0,0.0);
      glutPostRedisplay();
	break;
  case '#':
	horiz++;
      glRotatef(horiz,0.0,1.0,0.0);
      glutPostRedisplay();
	break;
  case '/':
      horiz++;
      glRotatef(horiz,1.0,0.0,0.0);
      glutPostRedisplay();
	break;
  case ' ':
    if (!moving) {
      tick();
      glutPostRedisplay();
    }
    break;
  case 27:             /* ESC */
    exit(0);
    break;
  }
}

#define ADD_PLANE	1
#define REMOVE_PLANE	2
#define MOTION_ON	3
#define MOTION_OFF	4
#define QUIT		5
#define INCREASE_LRT    6

void
menu(int item)
{
  switch (item) {
  case ADD_PLANE:
    add_plane();
    break;
  case REMOVE_PLANE:
    remove_plane();
    break;
  case MOTION_ON:
    moving = GL_TRUE;
    glutChangeToMenuEntry(3, "Motion off", MOTION_OFF);
    glutIdleFunc(animate);
    break;
  case MOTION_OFF:
    moving = GL_FALSE;
    glutChangeToMenuEntry(3, "Motion", MOTION_ON);
    glutIdleFunc(NULL);
    break;
  case INCREASE_LRT:
    myswarm.lrt+=0.1;  
    break;
  case QUIT:
    exit(0);
    break;
  }
}

int
main(int argc, char *argv[])
{
hgt = 7.5;scl =2;pscl=1;gsize = 1;
res = 10;lowres=1;scrn=75;

myswarm.initialise(0.64,0.6,0.55,0.75,10,-10,func4);

  glutInit(&argc, argv);
  /* use multisampling if available */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
  glutCreateWindow("glutplane");
loadpoints();
drawlines2buffer();
 glutDisplayFunc(draw);
 glutReshapeFunc(reshape);
 //glutTimerFunc(30, timer, 0 );  
glutKeyboardFunc(keyboard);
  //glutVisibilityFunc(visible);
  glutCreateMenu(menu);
  glutAddMenuEntry("Add plane", ADD_PLANE);
  glutAddMenuEntry("Remove plane", REMOVE_PLANE);
  glutAddMenuEntry("Motion", MOTION_ON);
  glutAddMenuEntry("Inc Lrt", INCREASE_LRT);
  glutAddMenuEntry("Quit", QUIT);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  /* setup OpenGL state */
  glClearDepth(1.0);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 20);
  glMatrixMode(GL_MODELVIEW);
  /* add three initial random planes */
  srandom(time(NULL));
for(int i=0;i<14;i++){ 
add_plane();	   }
  
  /* start event processing */
  glutMainLoop();
  return 0;             /* ANSI C requires main to return int. */
}
