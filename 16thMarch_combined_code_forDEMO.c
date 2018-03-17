#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<string.h>
#define SIZE 10

int cod[SIZE][2];//stores co-ordinates of the points
int src,dst;//Source node and destination node
int p[SIZE];
static int flag=0;

//The following function is used to give a delay
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

//The following function is used to display TEXT on the screen
//Arguments are "STRING",R,G,B,X,Y,ScaleX,ScaleY,Width
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

//The following function is used to display a point on the screen
//Arguments X,Y,SIZE
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

//The following function stores the co-ordinates of each node in 'cod' 2D matrix
void mark_points()
{
    int i;
    cod[0][0]=50;
    cod[0][1]=50;
    cod[1][0]=300;
    cod[1][1]=50;
    cod[2][0]=600;
    cod[2][1]=50;
    cod[3][0]=300;
    cod[3][1]=200;
    cod[4][0]=50;
    cod[4][1]=400;
    cod[5][0]=300;
    cod[5][1]=400;
    cod[6][0]=600;
    cod[6][1]=400;
    cod[7][0]=50;
    cod[7][1]=600;
    cod[8][0]=300;
    cod[8][1]=600;
    cod[9][0]=600;
    cod[9][1]=600;
    for(i=0;i<10;i++)
    {
        plotPoint(cod[i][0],cod[i][1],6);
        char str[12];
        sprintf(str, "%d",i);//convert integer to string
        typeText(str,1,0,0,cod[i][0],cod[i][1],0.2,0.2,3);//to show the number along with the point
    }

}

//The following function is use to draw the initial roads
void drawRoad(int adj[SIZE][SIZE])
{
    int i,j;
    glColor3f(0.96,0.96,0.8);
    glLineWidth(5);
    for(i=0;i<SIZE;i++)
        for(j=0;j<SIZE;j++)
        {
            if((adj[i][j]!=999)&&(adj[i][j]!=0))
            {
                printf("%d %d %d \n ",i,j,adj[i][j]);
                glBegin(GL_LINE_STRIP);
                glVertex2f(cod[i][0],cod[i][1]);
                glVertex2f(cod[j][0],cod[j][1]);
                glFlush();
                glEnd();
            }
        }
    glFlush();
    return;
}

//The following function is used to find the path from source to destination and also draw the path
void path(int k) {
	if(p[k] == -1 ) {
		return;
	}
	path(p[k]);

	printf("%d ",k);
    glVertex2f(cod[k][0],cod[k][1]);
    glEnd();
    glFinish();
    glBegin(GL_LINES);
    delay(1000000);
    glVertex2f(cod[k][0],cod[k][1]);
    glFlush();
}

//Dijkstra implementation
void dijkstra(int adj[SIZE][SIZE],int n,int src) {
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
        delay(1000000);
		printf("path taken is");
		printf("%d ",src);
		glPushMatrix();
        glLineWidth(20);
        glColor3f(0,0,1);
		glBegin(GL_LINES);
		glVertex2f(cod[src][0],cod[src][1]);
		glFlush();
		delay(1000000);
        path(dst);
		glEnd();
		glPopMatrix();
        printf("\n");
}

//The following function makes the adjacency matrix and calls draw road and dijkstra
void callDijkstra(){
    //int i,j;
	int adj[SIZE][SIZE]={
				{0,6,999,4,999,999,999,999,999,999},
				{6,0,3,999,999,999,999,999,999,999},
				{999,3,0,6,999,999,999,999,999,999},
				{4,999,6,0,999,6,7,999,999,999},
                {999,999,999,999,0,8,999,999,999,999,999},
                {999,999,999,6,8,0,10,11,999,999},
                {999,999,999,7,999,10,0,999,999,9},
                {999,999,999,999,999,11,999,0,12,999},
                {999,999,999,999,999,999,999,12,0,999},
                {999,999,999,999,999,999,9,999,999,0},
                };
    drawRoad(adj);
    printf("Enter source\n");
    scanf("%d",&src);
    printf("Enter the destination\n");
    scanf("%d",&dst);

    dijkstra(adj,SIZE,src);
}

//The following function calls mark_points() to make the initial map and then calls Dijkstra
void screen3(){

    glClearColor(0.65,0.93,0.31,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    mark_points();
    glFlush();
    callDijkstra();
    glFlush();
    printf("bye");
}

//The following function is used to display the WELCOME text
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

//The following function displays the loading page
void loading()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    typeText("Loading",1, 0, 0,300,355,0.2,0.2,2);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLineWidth(2);
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
        loading();
    }

}

//The following function shows the initial page
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
