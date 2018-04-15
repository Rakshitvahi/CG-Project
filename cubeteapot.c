#include<stdio.h>
#include<GL/glut.h>
int view[3]={-3,1,0};
float centre[3]={0,0,0.0};
int up[3]={0.0,1.0,0.0};

GLfloat vert[][3]={{0.5,0.5,0.5},{0.55,0.5,0.5},{0.55,0.55,0.5},{0.5,0.55,0.5},{0.5,0.5,0.55},{0.55,0.5,0.55},{0.55,0.55,0.55},{0.5,0.55,0.55}};
GLfloat vert1[][3]={{0,0,0},{0.05,0,0},{0.05,0.05,0},{0,0.05,0},{0,0,0.05},{0.05,0,0.05},{0.05,0.05,0.05},{0,0.05,0.05}};
GLfloat vert3[][3]={{0.8,0.8,0.8},{0.85,0.8,0.8},{0.85,0.85,0.8},{0.8,0.85,0.8},{0.8,0.8,0.85},{0.85,0.8,0.85},{0.85,0.85,0.85},{0.8,0.85,0.85}};

void square(int a,int b,int c,int d,GLfloat vert1[8][3]){
    glBegin(GL_POLYGON);
    //glColor3f(0,1,0);
    glVertex3fv(vert1[a]);
    //glColor3fv(col[b]);
    glVertex3fv(vert1[b]);
    //glColor3fv(col[c]);
    glVertex3fv(vert1[c]);
    //glColor3fv(col[d]);
    glVertex3fv(vert1[d]);
    glEnd();
    //glFlush();

}

void cube(GLfloat vert1[8][3]){
    glColor3f(0,0,0);
    square(0,3,2,1,vert1);
    //glColor3f(1,0,0);
    square(4,7,3,0,vert1);
    //glColor3f(0,1,0);
    square(0,1,5,4,vert1);
    square(5,6,7,4,vert1);
    square(1,2,6,5,vert1);
    glColor3f(1,0,0);
    square(7,6,2,3,vert1);

}


void displaySolid(void)
{
    /*GLfloat mat_ambient[]={0.7f,0.7f,0.7f,0.9f};
    GLfloat mat_diffuse[]={0.5f,0.5f,0.5f,1.0f};
    GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};
    GLfloat mat_shininess[]={20.0f};


    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    GLfloat lightIntensity[]={0.7f,0.7f,0.7f,0.7f};
    GLfloat light_position[]={2.0f,10.0f,3.0f,0.0f};

    //The glLightfv function returns light source parameter values.
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

    */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double winHt=1.0;
    //glOrtho(-winHt*1.0,winHt*1.0,-winHt,winHt,0.1,100.0);
    glOrtho(0,winHt*1.0,0,winHt,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(view[0],view[1],view[2],centre[0],centre[1],centre[2],up[0],up[1],up[2]);
    printf("%d %d %d %f %f %f %d %d %d\n",view[0],view[1],view[2],centre[0],centre[1],centre[2],up[0],up[1],up[2] );
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    cube(vert1);
    glPopMatrix();
    glPushMatrix();
    cube(vert);
    glPopMatrix();
    glPushMatrix();
    cube(vert3);
    glPopMatrix();
    glFlush();
}
void keys(unsigned char key,int x,int y){
    switch(key){
        case  'x': view[0]-=1;break;
        case  'X': view[0]+=1;break;
        case  'y': view[1]-=1;break;
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
    //display();
    glutPostRedisplay();
}
int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(700,700);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Teapot on table");
    glutKeyboardFunc(keys);
    glutDisplayFunc(displaySolid);
    //glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(1,1,1,0.0);
    glViewport(0,0,700,700);
    glutMainLoop();
}
