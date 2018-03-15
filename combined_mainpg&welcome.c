#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<string.h>
#define SIZE 4

int p[SIZE];
static int flag=0;
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

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
	//glutSwapBuffers();
	glPopMatrix();
	glFlush();
	//glLoadIdentity();//
}
void plotPoint(int x,int y,int s){
    //glPushMatrix();
    glPointSize(s);
    glBegin(GL_POINTS);
    glColor3f(1,0,1);
    glPointSize(s);
    glVertex2i(x,y);
    glEnd();
    glPointSize(1);

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
void path(int k,int map[SIZE][2]) {
	if(p[k] == -1 ) {
		return;
	}
	path(p[k],map);

	printf("%d ",k);
    glVertex2f(map[k][0],map[k][1]);

    delay(1000000);
    glFlush();
}
void dijkstra(int adj[SIZE][SIZE],int n,int src,int map[SIZE][2]) {
	int visit[SIZE];
	int d[SIZE];
	int i,j,k;
	int min=0,w=0;
	for(i=0;i<n;i++) {
		visit[i]=0;
		d[i]= 999;
		p[i]= -1;
	}
	visit[src]=1;
	d[src]=0;
	p[src]=-1;
	for(i=0;i<n;i++) {
		if(adj[src][i] != 999 && adj[src][i] != 0) {
			d[i]=adj[src][i];
			p[i]=src;
		}

	}
	for(i=1;i<n;i++) {
		min = 999;
		for(j=0;j<n;j++) {
			if(visit[j]==0 && d[j] < min) {
				min =d[j];
				w=j;
			}
		}
		visit[w]=1;
		for(k=0;k<n;k++) {
			if(visit[k]==0 && adj[w][k] != 999 && adj[w][k] != 0) {
				if(d[k] > (d[w] + adj[w][k])) {
					d[k]= d[w] + adj[w][k];
					p[k]=w;
				}
			}
		}
	}
	//for(i=0;i<n;i++) {
		//printf("Distence of node %d from source is %d parent is %d\n",i,d[i],p[i]);
		printf("path taken is");
		printf("%d ",src);
		glBegin(GL_LINE_STRIP);
		glVertex2f(map[0][0],map[0][1]);
		glFlush();
		delay(1000000);

		path(3,map);
		glEnd();
		printf("\n");
	//}
}

void callDijkstra(int map[SIZE][2]){
    //int i,j;
	int adj[SIZE][SIZE]={
				{0,4,1,999},
				{2,0,999,999},
				{999,10,0,6},
				{1,999,999,0}
				};
    dijkstra(adj,SIZE,0,map);
}

void screen3(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,1,1);
    int map[SIZE][2]={{100,100},{100,200},{200,200},{200,100}};
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //printf("bye");
    plotPoint(map[0][0],map[0][1],5);
    plotPoint(map[1][0],map[1][1],5);
    plotPoint(map[2][0],map[2][1],5);
    plotPoint(map[3][0],map[3][1],5);
    //glutSwapBuffers();
    glFlush();
    callDijkstra(map);
    glFlush();
    printf("bye");
    //glutSwapBuffers();
    //glFlush();
}

void welcomepg()
{
    glClearColor(0.1,1,1,1.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    delay(100000);
    typeText("WELCOME",1,1,0,200,345,0.5,0.5,3);
    delay(3000000);
    glFlush();
    screen3();
}

void setpoly(int a)
{
    glColor3f(0,0,1);
    glBegin(GL_POLYGON);
    glVertex2i(300,345);
    glVertex2i(a,345);
    glVertex2i(a,355);
    glVertex2i(300,355);
    glEnd();
}

void loading()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    int i;
    float j=1;
    int a=310;
    for(i=0;i<10;i++)
    {

        glClearColor(j,1,1,1.0);
        j=j-0.1;
        glColor3f(0,0,0);
        glBegin(GL_LINE_LOOP);
        glVertex2i(300,345);
        glVertex2i(390,345);
        glVertex2i(390,355);
        glVertex2i(300,355);
        glEnd();
        setpoly(a);
        delay(1000000);
        a=a+10;
        glFlush();
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    }
    welcomepg();
}

void keys(unsigned char key,int x,int y){
    if(key ==(char)13){
        //printf("Hi");
        //flag=1;
        //display();
        //glutPostRedisplay();
        loading();
    }

}



void screen1()
{
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
        //glutSwapBuffers();
        glPopMatrix();
        glFlush();

        //glLoadIdentity();
        len=(int) strlen(string);
        typeText(string,0.99, 0.75, 0.06,175,600,0.5,0.5,5);
        typeText("ENTER TO START",0.97, 0.22, 0.22,175,400,0.3,0.3,3);
        typeText("RAHUL.J 1PE15CS115",0.75, 0.93, 0.96,10,130,0.2,0.2,3);
        typeText("RAKSHIT 1PE15CS119",0.75, 0.93, 0.96,10,80,0.2,0.2,3);
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    screen1();

}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1024,1000);
	glutCreateWindow("Navigation");
    glutKeyboardFunc(keys);
    glEnable(GL_POINT_SMOOTH);
	glClearColor(0,0.4,0.52,1);
	glOrtho(0,700,0,700,0,700);
	glutDisplayFunc(display);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
