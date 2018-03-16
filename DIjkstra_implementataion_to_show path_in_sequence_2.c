#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<string.h>
#define SIZE 10

int t[SIZE];
int cod[SIZE][2];//stores co-ordinates of the points
int src,dst;
int p[SIZE];
//static int flag=0;
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

//The following function is used to draw the point on the screen
void plotPoint(int x,int y,int s){
    glPointSize(s);
    glBegin(GL_POINTS);
    glColor3f(1,0,1);
    glVertex2i(x,y);
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
    glColor3f(1,1,1);

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
    return;
}

//The following function is used to find the path from source to destination
static int y=0;
void path(int k){
	if(p[k] == -1 ) {
        t[y]=k;
        y++;
        return;
	}
	path(p[k]);
    //printf("%d ",k);
    t[y]=k;
    y++;

}

//The following function is used to draw the path found
void drawPath()
{
    glPushMatrix();
	glLineWidth(20);
    int i;
    glColor3f(1,0,0);
    for(i=0;i<y-1;i++)
    {
        glBegin(GL_LINES);
        glVertex2f(cod[t[i]][0],cod[t[i]][1]);
        glVertex2f(cod[t[i+1]][0],cod[t[i+1]][1]);
        delay(1000000);
        glEnd();
        glFlush();
    }
    glPopMatrix();
	glFlush();
    //glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);



}

//Dijkstra
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
		printf("path taken is");
		path(dst);

		int q;

		for(q=0;q<y;q++)
            printf("%d ",t[q]);
		printf("\n");
		drawPath();

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
    dijkstra(adj,SIZE,src);
}

//The following function calls mark_points()
void screen3(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,1,1);
    mark_points();
    glFlush();
    callDijkstra();
    glFlush();
    printf("bye");
}

//Display functions calls screen3()
void display(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(1,1,1,1);
    screen3();
}

int main(int argc, char *argv[])
{
    printf("Enter source\n");
    scanf("%d",&src);
    printf("Enter the destination\n");
    scanf("%d",&dst);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1024,1000);
	glutCreateWindow("Navigation");
//    glutKeyboardFunc(keys);
    glEnable(GL_POINT_SMOOTH);
	glClearColor(0,0.4,0.52,1);
	glOrtho(0,700,0,700,0,700);
	glutDisplayFunc(display);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
