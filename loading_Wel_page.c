#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<string.h>

int a=200;
int i=0,state=0;

void typeText(char *string,float x,float y,float z,float w,float h,float sx,float sy,int width){
    int i;
	glColor3f(x, y, z);
	//glLoadIdentity();
	glPushMatrix();
    glTranslatef(w,h,0);
	glScalef(sx,sy,1);
	glLineWidth(width);
    for (i = 0; string[i]; i++)
	{
             glutStrokeCharacter(GLUT_STROKE_ROMAN,string[i]);
	}
	glutSwapBuffers();
	glPopMatrix();
	glFlush();
}

//The following function is to provide a delay
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

/*The following function is use to get the blue bar to show loading in blue color
where 'a' is the value of x which is incremented in steps of 10*/
void setpoly(int a)
{
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex2i(195,244);
    glVertex2i(a,244);
    glVertex2i(a,256);
    glVertex2i(195,256);
    glEnd();
}

/*The following function is use to make the loading bar frame and to call setpoly() function at an interval to show the
the progress bar
variable 'i' is used to keep the trace of number of steps*/
void loading()
{
    /*if(i==0)
    {
            typeText("LOADING...",1,0,0,195,244,0.2,0.2,3);
            delay(500000);
           glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }*/

    float j=1;
    for(i=0;i<10;i++)
    {

        glClearColor(j,1,1,1.0);
        j=j-0.1;
        glColor3f(0,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(195,244);
        glVertex2i(280,244);
        glVertex2i(280,256);
        glVertex2i(195,256);
        glEnd();
        setpoly(a);
        delay(1000000);
        a=a+10;
        glFlush();
        glClear(GL_COLOR_BUFFER_BIT);
    }
    state=2;
    glutPostRedisplay();
}

//The following function is used to show the screen after the loading is complete
void screen2()
{
    glClearColor(0.1,1,1,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    delay(100000);
    typeText("WELCOME",1,1,0,195,244,0.2,0.2,3);
    delay(3000000);
    state=3;
    glFlush();
    glutPostRedisplay();


}
void screen3()
{
   glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if(state==0)
        loading();
    else if(state==2)
        screen2();
    else if(state==3)
        screen3();
    glFlush();
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(1024,800);
    glutCreateWindow("Navigation");
    glutDisplayFunc(display);
    glOrtho(0,500.0,0,500.0,0,500.0);
    glClearColor(1.0,1.0,1.0,1.0);
    //glutReshapeFunc(myReshape);
    //glEnable(GL_DEPTH_TEST);
    glutMainLoop();
}

