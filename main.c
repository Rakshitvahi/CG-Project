#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>>

static int flag=0;
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
void rec(int x1,int y,int x2,int y2){
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1,y);
    glVertex2i(x2,y);
    glVertex2i(x2,y2);
    glVertex2i(x1,y2);
    glEnd();

}
void keys(unsigned char key,int x,int y){
    if(key ==(char)13){
        printf("Hi");
        flag=1;
        display();
        glutPostRedisplay();

    }

}
void screen2(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //printf("bye");

    glutSwapBuffers();
    glFlush();
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(flag == 0){
        int len;
        char string[]="NAVIGATION";
    //    rec(1,1,100,100);
        glPushMatrix();
        //glLoadIdentity();
        glTranslatef(270,300,0);
        glScalef(2,2,1);

        glColor3f(0.93, 0.27, 0.21);
        glBegin(GL_POLYGON);
        glVertex2f(30,23);
        glVertex2f(40,25);
        glVertex2f(45,35);
        glEnd();
        glColor3f(0.75, 0.22, 0.17);
        glBegin(GL_POLYGON);
        glVertex2f(45,17);
        glVertex2f(40,25);
        glVertex2f(45,35);
        glEnd();
        glutSwapBuffers();
        glPopMatrix();
        glFlush();
        len=(int) strlen(string);
        typeText(string,0.99, 0.75, 0.06,175,600,0.5,0.5,5);
        typeText("ENTER TO START",0.97, 0.22, 0.22,175,400,0.3,0.3,3);
        typeText("RAHUL.J 1PE15CS115",0.75, 0.93, 0.96,10,130,0.2,0.2,3);
        typeText("RAKSHIT 1PE15CS119",0.75, 0.93, 0.96,10,80,0.2,0.2,3);
    }else if(flag == 1){
        screen2();
    }
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(700,700);
	glutCreateWindow("Navigation");
    glutKeyboardFunc(keys);
	glClearColor(0,0.4,0.52,1);
	glOrtho(0,700,0,700,0,700);
	glutDisplayFunc(display);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}

