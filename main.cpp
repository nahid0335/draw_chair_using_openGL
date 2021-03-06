#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

double Txval=0,Tyval=0,Tzval=0;
double windowHeight=700, windowWidth=700;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0;
GLboolean bRotate = false, uRotate = false;

static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0},    //0
    {0.0, 0.0, 2.0},    //1
    {2.0, 0.0, 2.0},    //2
    {2.0, 0.0, 0.0},    //3
    {0.0, 2.0, 0.0},    //4
    {0.0, 2.0, 2.0},    //5
    {2.0, 2.0, 2.0},    //6
    {2.0, 2.0, 0.0}     //7
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte quadIndices[1][4] =
{
    {0, 3, 2, 1}
};

static GLubyte planeIndices[6][4] =
{
    {1, 2, 6, 5},
    {2, 3, 7, 6},
    {3, 0, 4, 7},
    {0, 1, 5, 4},
    {4, 5, 6, 7},
    {1, 0, 3, 2}
};

static GLfloat colors[5][3] =
{
    {0.0, 0.0, 1.0},
    {0.5, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0}
};

static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawpyramid()
{
    glColor3f(1,0,0);
    /*glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        glColor3f(colors[i][0],colors[i][1],colors[i][2]);
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();*/

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        glColor3f(colors[4][0],colors[4][1],colors[4][2]);
        getNormal3p(v_cube[planeIndices[i][0]][0], v_cube[planeIndices[i][0]][1], v_cube[planeIndices[i][0]][2],
                    v_cube[planeIndices[i][1]][0], v_cube[planeIndices[i][1]][1], v_cube[planeIndices[i][1]][2],
                    v_cube[planeIndices[i][2]][0], v_cube[planeIndices[i][2]][1], v_cube[planeIndices[i][2]][2]);

        glVertex3fv(&v_cube[planeIndices[i][0]][0]);
        glVertex3fv(&v_cube[planeIndices[i][1]][0]);
        glVertex3fv(&v_cube[planeIndices[i][2]][0]);
        glVertex3fv(&v_cube[planeIndices[i][3]][0]);
    }
    glEnd();


}

void ownTranslatef(GLfloat dx, GLfloat dy, GLfloat dz){

	GLfloat m[16];

	m[0] = 1;	m[4] = 0;  	 m[8] = 0;   	m[12] = dx;
	m[1] = 0; 	m[5] = 1; 	 m[9] = 0;   	m[13] = dy;
	m[2] = 0; 	m[6] = 0;	 m[10] = 1; 	m[14] = dz;
	m[3] = 0; 	m[7] = 0; 	 m[11] = 0; 	m[15] = 1;

	glMatrixMode(GL_MODELVIEW);
	glMultMatrixf(m);
}

void chair(){
    //backLeg left
    glPushMatrix();
    //glTranslated(0,0,4);
    glScalef(0.2,5,0.2);
    drawpyramid();
    glPopMatrix();

    //backLeg Right
    glPushMatrix();
    glTranslated(4,0,0);
    glScalef(0.2,5,0.2);
    drawpyramid();
    glPopMatrix();

    //front leg left
    glPushMatrix();
    glTranslated(0,0,4);
    glScalef(0.2,2,0.2);
    drawpyramid();
    glPopMatrix();

    //front leg right
    glPushMatrix();
    glTranslated(4,0,4);
    glScalef(0.2,2,0.2);
    drawpyramid();
    glPopMatrix();

    //sit placeholder
    glPushMatrix();
    glTranslated(0,4,0);
    glScalef(2.3,0.1,2.3);
    drawpyramid();
    glPopMatrix();

    //back support lower
    glPushMatrix();
    glTranslated(0,6,0);
    glScalef(2,0.2,0.2);
    drawpyramid();
    glPopMatrix();

    //back support 2nd
    glPushMatrix();
    glTranslated(0,7,0);
    glScalef(2,0.2,0.2);
    drawpyramid();
    glPopMatrix();

    //back support 3rd
    glPushMatrix();
    glTranslated(0,8,0);
    glScalef(2,0.2,0.2);
    drawpyramid();
    glPopMatrix();


    //back support upper
    glPushMatrix();
    glTranslated(0,9,0);
    glScalef(2,0.2,0.2);
    drawpyramid();
    glPopMatrix();


    //leg support left
    glPushMatrix();
    glTranslated(0,1,0);
    glScalef(0.2,0.2,2);
    drawpyramid();
    glPopMatrix();

    //leg support right
    glPushMatrix();
    glTranslated(4,1,0);
    glScalef(0.2,0.2,2);
    drawpyramid();
    glPopMatrix();

}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-10,10,-10,10, 4, 50);
    //gluPerspective(60,1,5,100);
    //glOrtho(-5,5,-5,5, 4, 50);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(2,3,12, 2,0,0, 0,1,0);

    glViewport(0, 0, windowHeight, windowWidth);
    /*glPushMatrix();
    //glTranslatef(0,0,Tzval);
    //ownTranslatef(0,0,Tzval);
    //glRotated(60,0,0,1);
    //glTranslated(-8,0,0);
    glScaled(0.2,5,0.2);
    //glRotatef( alpha,axis_x, axis_y, 0.0 );
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawpyramid();

    glPopMatrix();*/




    glPushMatrix();
    //glTranslated(-8,0,-4);
    glTranslatef(0,0,Tzval);
    ownTranslatef(0,0,Tzval);
    glRotatef( alpha,axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );
    chair();
    glPopMatrix();




    /* glPushMatrix();
        glTranslatef(0,0,Tzval);
        glScalef(2,2,2);
        glutSolidCube(1);
    glPopMatrix();*/


    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 's':
    case 'S':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'r':
    case 'R':
        uRotate = !uRotate;
        bRotate = false;
        axis_x=1.0;
        axis_y=0.0;
        break;
    case '+':
        Tzval+=0.2;
        break;

    case '-':
        Tzval-=0.2;
        break;

    case 27:	// Escape key
        exit(1);
    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }
    glutPostRedisplay();

}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Traingle-Demo");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}

