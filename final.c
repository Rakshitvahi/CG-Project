#include <stdio.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<time.h>
#include<string.h>
#include "SOIL.h"
#include <unistd.h>
#include<GL/freeglut.h>
#define SIZE 19

int flag=0;
int q=0;
int adj[SIZE][SIZE];
float cod[SIZE][2];//stores co-ordinates of the points
int src,dst;//Source node and destination node
int p[SIZE];
float mat[16];
int id;
int view[3]={-3,93,3};
float centre[3]={0,0,0.0};
int up[3]={0.0,1.0,0.0};


void printmat(){
	int i=0;
	for(i=0;i<16;i++)
		printf("%f ",mat[i]);
	printf("\n");

}
void keys(unsigned char key,int x,int y);
void screen3();
//Menu Callback Function
void myMenu(int val)
{
	if(val==1) id=1;
	if(val==2) id=2;
	if(val==3) id=3;
	if(val==4) exit(0);
	screen3();
}
//The following function is used to give a delay
void delay(unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
	while (goal > clock());
}

/*The following function is used to display TEXT on the screen
Arguments are "STRING",R,G,B,X,Y,ScaleX,ScaleY,Width*/
void typeText(char *string,float x,float y,float z,float w,float h,float sx,float sy,float width){
	int i;
	glColor3f(x, y, z);
	glPushMatrix();
	glTranslatef(w,h,0);
	glScalef(sx,sy,1);
	glLineWidth(width);
	for (i = 0; string[i]; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN,string[i]);
	}
	glPopMatrix();
	glFlush();
}

void typeText2(char *string,float x,float y,float z,float w,float h,float sx,float sy,float width){
	int i;
	glColor3f(x, y, z);
	glPushMatrix();
	glTranslatef(w,0,h);
	glScalef(sx,sy,1);
	glLineWidth(width);
	for (i = 0; string[i]; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN,string[i]);
	}
	glPopMatrix();
	glFlush();
}

/*The following function is used to display a point on the screen 3D
Arguments X,Y,SIZE*/
void plotPoint3D(float x,float y,int s){
	glPointSize(s);
	glBegin(GL_POINTS);
	glColor3f(1,0,1);
	glPointSize(s);
	glVertex3f(x,0,y);
	glEnd();
	glPointSize(1);
}
/*The following function is used to display a point on the screen 2D
Arguments X,Y,SIZE*/
void plotPoint(float x,float y,int s){
	glPointSize(s);
	glBegin(GL_POINTS);
	glColor3f(1,0,1);
	glPointSize(s);
	glVertex3f(x,y,0);
	glEnd();
	glPointSize(1);

}

/*Draw a Polygon
used for loading page*/
void rec(int x1,int y,int x2,int y2){
	glColor3f(1,0,0);
	glBegin(GL_LINE_LOOP);
	glVertex3f(x1,y,0);
	glVertex3f(x2,y,0);
	glVertex3f(x2,y2,0);
	glVertex3f(x1,y2,0);
	glEnd();

}

/*The following function stores the co-ordinates of each node in 'cod' 2D matrix
plot the points and mark them on 3D*/
void mark_points3D()
{
	int i;
	cod[0][0]=0.050;
	cod[0][1]=0.050;
	cod[1][0]=0.050;
	cod[1][1]=0.650;
	cod[2][0]=0.650;
	cod[2][1]=0.650;
	cod[3][0]=0.650;
	cod[3][1]=0.050;
	cod[4][0]=0.650;
	cod[4][1]=0.550;
	cod[5][0]=0.350;
	cod[5][1]=0.550;
	cod[6][0]=0.200;
	cod[6][1]=0.650;
	cod[7][0]=0.300;
	cod[7][1]=0.500;
	cod[8][0]=0.300;
	cod[8][1]=0.250;
	cod[9][0]=0.650;
	cod[9][1]=0.250;
	cod[10][0]=0.350;
	cod[10][1]=0.250;
	cod[11][0]=0.350;
	cod[11][1]=0.050;
	cod[12][0]=0.550;
	cod[12][1]=0.150;
	cod[13][0]=0.350;
	cod[13][1]=0.150;
	cod[14][0]=0.100;
	cod[14][1]=0.250;
	cod[15][0]=0.150;
	cod[15][1]=0.500;
	cod[16][0]=0.350;
	cod[16][1]=0.500;
	cod[17][0]=0.375;
	cod[17][1]=0.575;
	cod[18][0]=0.9;
	cod[18][1]=0.9;
	for(i=0;i<SIZE;i++)
	{
		plotPoint3D(cod[i][0],cod[i][1],6);
		char str[12];
		sprintf(str, "%d",i);//convert integer to string
		typeText2(str,1,0,0,cod[i][0],cod[i][1],0.0002,0.0002,0.003);//to show the number along with the point
	}



}

/*The following function stores the co-ordinates of each node in 'cod' 2D matrix
plot the points and mark them on 2D*/
void mark_points()
{
	int i;
	cod[0][0]=0.050;
	cod[0][1]=0.050;
	cod[1][0]=0.050;
	cod[1][1]=0.650;
	cod[2][0]=0.650;
	cod[2][1]=0.650;
	cod[3][0]=0.650;
	cod[3][1]=0.050;
	cod[4][0]=0.650;
	cod[4][1]=0.550;
	cod[5][0]=0.350;
	cod[5][1]=0.550;
	cod[6][0]=0.200;
	cod[6][1]=0.650;
	cod[7][0]=0.300;
	cod[7][1]=0.500;
	cod[8][0]=0.300;
	cod[8][1]=0.250;
	cod[9][0]=0.650;
	cod[9][1]=0.250;
	cod[10][0]=0.350;
	cod[10][1]=0.250;
	cod[11][0]=0.350;
	cod[11][1]=0.050;
	cod[12][0]=0.550;
	cod[12][1]=0.150;
	cod[13][0]=0.350;
	cod[13][1]=0.150;
	cod[14][0]=0.100;
	cod[14][1]=0.250;
	cod[15][0]=0.150;
	cod[15][1]=0.500;
	cod[16][0]=0.350;
	cod[16][1]=0.500;
	cod[17][0]=0.375;
	cod[17][1]=0.575;
	cod[18][0]=0.9;
	cod[18][1]=0.9;
	for(i=0;i<SIZE;i++)
	{
		plotPoint(cod[i][0],cod[i][1],6);
		char str[12];
		sprintf(str, "%d",i);//convert integer to string
		typeText(str,1,0,0,cod[i][0],cod[i][1],0.0002,0.0002,0.003);//to show the number along with the point
	}
}

//The following function is use to draw the initial roads on 3D
void drawRoad3D(int adj[SIZE][SIZE])
{
	int i,j;
	glColor3f(0.96,0.96,0.8);
	glLineWidth(5);
	for(i=0;i<SIZE;i++)
		for(j=0;j<SIZE;j++)
		{
			if((adj[i][j]!=999)&&(adj[i][j]!=0))
			{
				//printf("%d %d %d \n ",i,j,adj[i][j]);
				glBegin(GL_LINE_STRIP);
				glVertex3f(cod[i][0],0,cod[i][1]);
				glVertex3f(cod[j][0],0,cod[j][1]);
				glFlush();
				printf("x=%f y=%f x=%f y=%f\n",cod[i][0],cod[i][1],cod[j][0],cod[j][1]);
				glEnd();
			}
		}


	glFlush();
	return;
}

//The following function is use to draw the initial roads on 2D
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
				glVertex3f(cod[i][0],cod[i][1],0);
				glVertex3f(cod[j][0],cod[j][1],0);
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
	//screen3();////////////////
}

void addImage2(float x1,float x4,float y1,float y4,float h) {

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	GLuint tex_2d1 = SOIL_load_OGL_texture
		(
		 "wall5.jpeg",
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_COMPRESS_TO_DXT
		);
	//change vertex co-ordinates accordingly
	glBindTexture(GL_TEXTURE_2D, tex_2d1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(x4,0,y4);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(x1,0,y1);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(x1,h,y1);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(x4,h,y4);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glFlush();
}


float colors[6][3] ={{0.96,0.63,0.59},{0.01,0.47,0.78},{0.96,0.73,0.59},{1,0.85,0.55},{0.15, 0.49, 0.42},{1,0.95,0.55}};
//Draw building in 3D
void drawbuild3D(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4,float h,int c)
{
	//glColor3f(1,1,1);
	glColor3f(0.88,0.93,0.93);
	glBegin(GL_POLYGON);
	glVertex3f(x1,0,y1);
	glVertex3f(x2,0,y2);
	glVertex3f(x3,0,y3);
	glVertex3f(x4,0,y4);
	glEnd();

	glColor3fv(colors[c]);
	glBegin(GL_POLYGON);
	glVertex3f(x2,0,y2);
	glVertex3f(x3,0,y3);
	glVertex3f(x2,h,y2);
	glVertex3f(x3,h,y3);
	glEnd();

	glColor3fv(colors[c+1]);
	glBegin(GL_POLYGON);
	glVertex3f(x3,0,y3);
	glVertex3f(x4,0,y4);
	glVertex3f(x4,h,y4);
	glVertex3f(x3,h,y3);
	glEnd();

	addImage2(x1,x4,y1,y4,h);

	glColor3fv(colors[c]);
	glBegin(GL_POLYGON);
	glVertex3f(x1,0,y1);
	glVertex3f(x2,0,y2);
	glVertex3f(x2,h,y2);
	glVertex3f(x1,h,y1);
	glEnd();

	glColor3f(0.88,0.93,0.93);
	glBegin(GL_POLYGON);
	glVertex3f(x1,h,y1);
	glVertex3f(x2,h,y2);
	glVertex3f(x3,h,y3);
	glVertex3f(x4,h,y4);
	glEnd();
}

//Draw Building in 2D
void drawbuild(float x1,float y1,float x2,float y2,float x3,float y3,float x4,float y4)
{
	//glColor3f(1,1,1);
	glColor3f(0.88,0.93,0.93);
	glBegin(GL_POLYGON);
	glVertex3f(x1,y1,0);
	glVertex3f(x2,y2,0);
	glVertex3f(x3,y3,0);
	glVertex3f(x4,y4,0);
	glEnd();
}

//The following function makes the adjacency matrix
void callDijkstra(){
	int i,j;
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if(i==j)
				adj[i][j]=0;
			else
				adj[i][j]=999;
		}
	}
	adj[0][1]=adj[1][0]=20;
	adj[0][11]=adj[11][0]=10;
	adj[1][2]=adj[2][1]=20;
	adj[1][6]=adj[6][1]=6;
	adj[2][3]=adj[3][2]=20;
	adj[2][4]=adj[4][2]=3;
	adj[2][6]=adj[6][2]=14;
	adj[3][4]=adj[4][3]=17;
	adj[3][9]=adj[9][3]=8;
	adj[3][11]=adj[11][3]=10;
	adj[4][5]=adj[5][4]=10;
	adj[4][9]=adj[9][4]=9;
	adj[5][6]=adj[6][5]=5;
	adj[5][7]=adj[7][5]=2;
	adj[7][8]=adj[8][7]=8;
	adj[8][9]=adj[9][8]=12;
	adj[8][10]=adj[10][8]=1;
	adj[9][10]=adj[10][9]=11;
	adj[10][11]=adj[11][10]=8;
	adj[10][13]=adj[13][10]=4;
	adj[11][13]=adj[13][11]=4;
	adj[12][13]=adj[13][12]=7;
	adj[8][14]=adj[14][8]=8;
	adj[7][15]=adj[15][7]=6;
	adj[5][16]=adj[16][5]=1;
	adj[5][17]=adj[17][5]=1;
	adj[2][18]=adj[18][2]=5;
	drawRoad(adj);

	drawbuild(0.350,0.300,0.600,0.300,0.600,0.500,0.350,0.500);
	drawbuild(0.100,0.300,0.250,0.300,0.250,0.450,0.100,0.450);
	drawbuild(0.100,0.350,0.150,0.350,0.150,0.550,0.100,0.550);
	drawbuild(0.100,0.550,0.250,0.550,0.250,0.600,0.100,0.600);
	drawbuild(0.060,0.100,0.300,0.100,0.300,0.200,0.060,0.200);
	drawbuild(0.060,0.200,0.100,0.200,0.100,0.250,0.060,0.250);
	drawbuild(0.375,0.575,0.550,0.575,0.550,0.625,0.275,0.625);
	drawbuild(0.100,0.550,0.250,0.550,0.250,0.600,0.100,0.600);
	drawbuild(0.575,0.575,0.600,0.575,0.600,0.625,0.575,0.625);
	drawbuild(0.600,0.600,0.625,0.600,0.625,0.625,0.600,0.625);
	drawbuild(0.550,0.100,0.600,0.100,0.600,0.200,0.550,0.200);
	drawbuild(0.925,0.8,0.990,0.8,0.990,0.990,0.925,0.990);
	drawbuild(0.925,0.910,0.925,0.990,0.810,0.990,0.810,0.910);
	//draw sea and island

	glColor3f(0.6, 0.6, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.050,0.660);
	glVertex2f(0.645,0.660);
	glVertex2f(0.8,0.820);
	glVertex2f(0.8,1);
	glVertex2f(0.050,1);
	glEnd();
	glColor3f(0.6, 0.6, 1.0);
	glBegin(GL_POLYGON);
	glVertex2f(0.660,0.050);
	glVertex2f(1,0.050);
	glVertex2f(1,0.790);
	glVertex2f(0.8,0.790);
	glVertex2f(0.660,0.640);
	glEnd();

	glFlush();
}


void callDijkstra3D(){
	int i,j;
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if(i==j)
				adj[i][j]=0;
			else
				adj[i][j]=999;
		}
	}
	adj[0][1]=adj[1][0]=20;
	adj[0][11]=adj[11][0]=10;
	adj[1][2]=adj[2][1]=20;
	adj[1][6]=adj[6][1]=6;
	adj[2][3]=adj[3][2]=20;
	adj[2][4]=adj[4][2]=3;
	adj[2][6]=adj[6][2]=14;
	adj[3][4]=adj[4][3]=17;
	adj[3][9]=adj[9][3]=8;
	adj[3][11]=adj[11][3]=10;
	adj[4][5]=adj[5][4]=10;
	adj[4][9]=adj[9][4]=9;
	adj[5][6]=adj[6][5]=5;
	adj[5][7]=adj[7][5]=2;
	adj[7][8]=adj[8][7]=8;
	adj[8][9]=adj[9][8]=12;
	adj[8][10]=adj[10][8]=1;
	adj[9][10]=adj[10][9]=11;
	adj[10][11]=adj[11][10]=8;
	adj[10][13]=adj[13][10]=4;
	adj[11][13]=adj[13][11]=4;
	adj[12][13]=adj[13][12]=7;
	adj[8][14]=adj[14][8]=8;
	adj[7][15]=adj[15][7]=6;
	adj[5][16]=adj[16][5]=1;
	adj[5][17]=adj[17][5]=1;
	adj[2][18]=adj[18][2]=5;
	drawRoad3D(adj);

	drawbuild3D(0.350,0.300,0.600,0.300,0.600,0.500,0.350,0.500,0.1,0);
	drawbuild3D(0.100,0.300,0.250,0.300,0.250,0.450,0.100,0.450,0.2,0);
	drawbuild3D(0.100,0.350,0.150,0.350,0.150,0.550,0.100,0.550,0.125,0);
	drawbuild3D(0.100,0.550,0.250,0.550,0.250,0.600,0.100,0.600,0.2,3);
	drawbuild3D(0.060,0.100,0.300,0.100,0.300,0.200,0.060,0.200,0.1,0);
	drawbuild3D(0.060,0.200,0.100,0.200,0.100,0.250,0.060,0.250,0.2,0);
	drawbuild3D(0.375,0.575,0.550,0.575,0.550,0.625,0.275,0.625,0.1,0);
	drawbuild3D(0.100,0.550,0.250,0.550,0.250,0.600,0.100,0.600,0.2,0);
	drawbuild3D(0.575,0.575,0.600,0.575,0.600,0.625,0.575,0.625,0.1,0);
	drawbuild3D(0.600,0.600,0.625,0.600,0.625,0.625,0.600,0.625,0.2,0);
	drawbuild3D(0.550,0.100,0.600,0.100,0.600,0.200,0.550,0.200,0.1,0);
	drawbuild3D(0.925,0.8,0.990,0.8,0.990,0.990,0.925,0.990,0.1,0);
	drawbuild3D(0.925,0.910,0.925,0.990,0.810,0.990,0.810,0.910,0.1,0);

	glFlush();
}

void entersrc()
{
	flag=1;
}


void screen33D(){
	//glGetFloatv(GL_MODELVIEW_MATRIX, mat);
	glPushMatrix();
	glLoadIdentity();
	glClearColor(0.65,0.93,0.31,1);
	glOrtho(0,1,0,1,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.01,1.0,-0.01,1,0.1,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(view[0],view[1],view[2],centre[0],centre[1],centre[2],up[0],up[1],up[2]);
	printf("%d %d %d %f %f %f %d %d %d\n",view[0],view[1],view[2],centre[0],centre[1],centre[2],up[0],up[1],up[2] );
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_COLOR_MATERIAL);
	float mat_amb[] = {.1,.1,.1,1.0};
	float mat_diff[] = {0.1,0.1,0.1,1.0};
	float mat_spec[] = {.10,.10,.10,1.0};
	float mat_shine[] = {70.0};

	glMaterialfv(GL_FRONT,GL_AMBIENT,mat_amb);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diff);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_spec);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shine);
	float lightIntensity[] = {0.7,0.7,0.7,1.0};
	float light_pos[] = {2.0,6.0,3.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
	glPushMatrix();
	mark_points3D();
	glPopMatrix();
	glPushMatrix();
	callDijkstra3D();
	glPopMatrix();
	glFlush();
	glPopMatrix();
}

//The following function calls mark_points() to make the initial map and then calls Dijkstra
void screen3(){
	//glGetFloatv(GL_PROJECTION_MATRIX, mat);
	printf("screen3\n");
	printmat();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(mat); 
	glMatrixMode(GL_MODELVIEW);
	/*glLoadIdentity();
	  glClearColor(0.65,0.93,0.31,1);
	  glOrtho(0,1,0,1,0,1);
	  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);*/
	//glClearColor(0.94,1,1,1);
	//glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glClearColor(0.94,1,1,1);
	glLoadIdentity();
	glOrtho(0,1,0,1,0,1);
	if(id==1){
		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//glOrtho(0,1,0,1,0,1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		gluLookAt(0,0,0,0,0,-1,0,1,0);
		mark_points();
		glFlush();
		callDijkstra();
		glFlush();
	}
	else if(id==2)
	{
		// glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(0,1,0,1,0,1);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		gluLookAt(0,0,0,0,0,-1,0,1,0);
		mark_points();
		glFlush();
		callDijkstra();
		glFlush();
		entersrc();
		glFlush();
	}
	else if(id==3)
	{
		glPushMatrix();
		//glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_CONTINUE_EXECUTION);
		//int a = glutCreateWindow("3D");

		//glutSetWindow(a);
		//glutKeyboardFunc(keys);
		screen33D();
		glPopMatrix();

	}

	printf("bye");
}

void prescreen3()
{
	glLoadIdentity();
	//glClearColor(0.65,0.93,0.31,1);
	glClearColor(0.94,1,1,1);
	glOrtho(0,1,0,1,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	int submenu1= glutCreateMenu(myMenu);
	glutAddMenuEntry("Draw Map",1);
	glutAddMenuEntry("src and dst",2);

	int submenu2= glutCreateMenu(myMenu);
	glutAddMenuEntry("Draw Map",3);

	glutCreateMenu(myMenu);
	glutAddSubMenu("Options 2D",submenu1);
	glutAddSubMenu("Options 3D",submenu2);
	glutAddMenuEntry("Exit",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glGetFloatv(GL_PROJECTION_MATRIX, mat);
}

void instruction()
{
	glClearColor(0.1,1,1,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	typeText("INSTRUCTION",0,0,0,165,600,0.5,0.5,4);
	typeText("1. Right click on the next screen to view the menu",0.33,0.33,0.33,20,500,0.15,0.15,2);
	typeText("2. Click on src and dst to find path from source to destination",0.33,0.33,0.33,20,450,0.15,0.15,2);
	typeText("3. Click on the points to select source and destination",0.33,0.33,0.33,20,400,0.15,0.15,2);	
	typeText("4. Click on draw map to only view the map",0.33,0.33,0.33,20,350,0.15,0.15,2);
	typeText("5. Click on 3D to enter 3D viewing mode to see the map in 3D",0.33,0.33,0.33,20,300,0.15,0.15,2);
	typeText("6. Use X,x,Y,y,Z,z to change the view",0.33,0.33,0.33,20,250,0.15,0.15,2);
	typeText("7. Press Enter to continue...",0.33,0.33,0.33,20,200,0.15,0.15,2);

	glFlush();

}
//The following function is used to display the WELCOME text
void welcomepg()
{
	glClearColor(0.1,1,1,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	delay(100000);
	typeText("WELCOME",0.99,0.75,0.06,200,345,0.5,0.5,3);
	delay(3000000);
	glFlush();
	instruction();
}

void setpoly(int a)
{
	glColor3f(0,0,1);
	glBegin(GL_POLYGON);
	glVertex3f(300,345,0);
	glVertex3f(a,345,0);
	glVertex3f(a,355,0);
	glVertex3f(300,355,0);
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
		glVertex3f(300,345,0);
		glVertex3f(390,345,0);
		glVertex3f(390,355,0);
		glVertex3f(300,355,0);
		glEnd();
		setpoly(a);
		delay(100000);
		a=a+10;
		glFlush();
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	}
	welcomepg();
}

void keys(unsigned char key,int x,int y){
	if(key ==(char)13){
		if(q==0)
		{
			loading();
			q=1;
		}
		else
			prescreen3();
	}
	else if(key=='e'){
		prescreen3();
	}

	else{
		switch(key){
			case  'x': view[0]-=1;break;
			case  'X': view[0]+=1;break;
			case  'y': view[1]-=7;break;
			case  'Y': view[1]+=1;break;
			case  'z': view[2]-=1;break;
			case  'Z': view[2]+=1;break;
			case  'l': centre[0]-=.1;break;
			case  'L': centre[0]+=.1;break;
			case  'i': centre[1]-=.1;break;
			case  'I': centre[1]+=.1;break;
			case  'j': centre[2]-=.1;break;
			case  'J': centre[2]+=.1;break;
		}
		screen33D();
	}
}

void addImage() {

	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	GLuint tex_2d1 = SOIL_load_OGL_texture
		(
		 "pesitsouth.png",
		 SOIL_LOAD_AUTO,
		 SOIL_CREATE_NEW_ID,
		 SOIL_FLAG_COMPRESS_TO_DXT
		);
	//change vertex co-ordinates accordingly
	glBindTexture(GL_TEXTURE_2D, tex_2d1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0);
	glVertex2f(500, 80);
	glTexCoord2f(0.0, 1.0);
	glVertex2f(650, 80);
	glTexCoord2f(1.0, 1.0);
	glVertex2f(650, 120);
	glTexCoord2f(1.0, 0.0);
	glVertex2f(500, 120);

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glFlush();
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
	glVertex3f(30,23,0);
	glVertex3f(40,25,0);
	glVertex3f(45,35,0);
	glEnd();
	glColor3f(0.75, 0.22, 0.17);
	glBegin(GL_POLYGON);
	glVertex3f(45,17,0);
	glVertex3f(40,25,0);
	glVertex3f(45,35,0);
	glEnd();
	//glutSwapBuffers();
	glPopMatrix();
	glFlush();

	//glLoadIdentity();
	len=(int) strlen(string);
	typeText(string,0.99, 0.75, 0.06,175,600,0.5,0.5,5);
	typeText("ENTER TO START",0.97, 0.22, 0.22,175,400,0.3,0.3,3);
	typeText("RAHUL J    1PE15CS115",0.75, 0.93, 0.96,10,130,0.2,0.2,3);
	typeText("RAKSHIT VAHI 1PE15CS119",0.75, 0.93, 0.96,10,80,0.2,0.2,3);
	addImage();
}

void display(){
	//gluLookAt(0,0,0,0,0,-1,0,0,1);
	gluLookAt(0,0,0,0,0,-1,0,1,0);
	//gluLookAt(2.3,1.3,2.0,350,350,350,0.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	screen1();
}
void mouse(int btn,int state,int x,int y){
	if(btn==GLUT_LEFT_BUTTON&&state==GLUT_DOWN){
		float w,h,nx,ny;
		int s=-1;
		w =glutGet(GLUT_WINDOW_WIDTH);
		h =glutGet(GLUT_WINDOW_HEIGHT); 
		printf("mouse:x%d y:%d %f %f %f %f\n",x,y,w,h,(x/w),(1-y/h));
		nx=x/w;
		ny=1-y/h;
		if(flag==1||flag==2){
			if((nx<0.06)&&(nx>0.04)&&(ny<0.06)&&(ny>0.04)){
				s=0;
				printf("selected 0");
			}else if((nx<0.36)&&(nx>0.34)&&(ny<0.06)&&(ny>0.04)){
				s=11;				
				printf("selected 11");
			}else if((nx<0.06)&&(nx>0.04)&&(ny<0.66)&&(ny>0.64)){
				s=1;				
				printf("selected 1");
			}else if((nx<0.66)&&(nx>0.64)&&(ny<0.66)&&(ny>0.64)){
				s=2;
				printf("selected 2");
			}else if((nx<0.66)&&(nx>0.64)&&(ny<0.06)&&(ny>0.04)){
				s=3;
				printf("selected 3");
			}else if((nx<0.66)&&(nx>0.64)&&(ny<0.56)&&(ny>0.54)){
				s=4;
				printf("selected 4");
			}else if((nx<0.36)&&(nx>0.34)&&(ny<0.56)&&(ny>0.54)){
				s=5;
				printf("selected 5");
			}else if((nx<0.21)&&(nx>0.19)&&(ny<0.66)&&(ny>0.64)){
				s=6;
				printf("selected 6");
			}else if((nx<0.31)&&(nx>0.29)&&(ny<0.51)&&(ny>0.49)){
				s=7;
				printf("selected 7");
			}else if((nx<0.31)&&(nx>0.29)&&(ny<0.26)&&(ny>0.24)){
				s=8;
				printf("selected 8");
			}else if((nx<0.66)&&(nx>0.64)&&(ny<0.26)&&(ny>0.24)){
				s=9;
				printf("selected 9");
			}else if((nx<0.36)&&(nx>0.34)&&(ny<0.26)&&(ny>0.24)){
				s=10;
				printf("selected 10");
			}else if((nx<0.56)&&(nx>0.54)&&(ny<0.16)&&(ny>0.14)){
				s=12;
				printf("selected 12");
			}else if((nx<0.36)&&(nx>0.34)&&(ny<0.16)&&(ny>0.14)){
				s=13;
				printf("selected 13");
			}else if((nx<0.11)&&(nx>0.09)&&(ny<0.26)&&(ny>0.24)){
				s=14;
				printf("selected 14");
			}else if((nx<0.16)&&(nx>0.14)&&(ny<0.51)&&(ny>0.49)){
				s=15;
				printf("selected 15");
			}else if((nx<0.36)&&(nx>0.34)&&(ny<0.51)&&(ny>0.49)){
				s=16;
				printf("selected 16");
			}else if((nx<0.385)&&(nx>0.365)&&(ny<0.585)&&(ny>0.565)){
				s=17;
				printf("selected 17");
			}else if((nx<0.91)&&(nx>0.89)&&(ny<0.91)&&(ny>0.89)){
				s=18;
				printf("selected 18");
			}
			if(s!=-1)
			{
			if(flag==1){
				src=s;
				flag++;
			}else{ 
				if(flag==2){
				dst=s;
				flag=0;
				dijkstra(adj,SIZE,src);
				}
			}
			}
		}
	}

}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(1024,1000);
	glutCreateWindow("Navigation");
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glEnable(GL_POINT_SMOOTH);
	glClearColor(0,0.4,0.52,1);
	glOrtho(0,700,0,700,0,700);
	glutDisplayFunc(display);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;
}
