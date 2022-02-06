#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "image_load/image_load.h"

#define PI 3.14159265358979323846

using namespace std;
static float day = 0, fov = 60, rot = 0,inclinacao=5;
static float aspect = 0, eixoX = 0,year = 0, eixoZ = 0;

static double dist_sun = 0, dist_mercurio = 2.0, dist_venus = 3.0,
dist_terra = 4.0, dist_marte = 5.0, dist_jupiter = 6.5,
dist_saturno = 9.0, dist_urano = 11.0, dist_netuno = 13.0;

/* raio de cada planeta */
static double size_sun = 1, size_mercurio = 0.1, size_venus = 0.25,
size_terra = 0.3, size_marte = 0.2, size_jupiter = 0.6,
size_saturno = 0.5, size_urano = 0.4, size_netuno = 0.4;

/* velocidade de cada planeta */
static double v_sun = 0, v_mercurio = 4.16, v_venus = 1.61,
v_terra = 1.0, v_marte = 0.53, v_jupiter = 0.28,
v_saturno = 0.11, v_urano = 0.05, v_netuno = 0.02;

GLfloat origin[] = {0.f, 0.f, 0.f, 0.f};

static bool automatico=false;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    LoadGLTextures("textures/sun.bmp");
    LoadGLTextures("textures/mercury.bmp");
    LoadGLTextures("textures/venus_surface.bmp");
    LoadGLTextures("textures/earth.bmp");
    LoadGLTextures("textures/mars.bmp");
    LoadGLTextures("textures/jupiter.bmp");
    LoadGLTextures("textures/saturn.bmp");
    LoadGLTextures("textures/uranus.bmp");
    LoadGLTextures("textures/neptune.bmp");
    LoadGLTextures("textures/saturnring.bmp");

}

void mov()
{
    year+=1;
    day+=5;
    glutPostRedisplay();
}

void orbitTrail(GLfloat x, GLfloat y, GLfloat radius)
{
	int points = 100;
	glLineWidth(0.5);
	glPushMatrix();
	glRotatef((GLfloat) 90.0, 1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
    for(int i = 0; i <= points; i++) {
        GLfloat tetha = float(i) * 2.0 * PI / points;
        /* cria os pontos de uma circunferência e os une por uma linha */
        glVertex2f(x + (radius * cos(tetha)), y + (radius * sin(tetha)));
    }
	glEnd();
	glPopMatrix();
}

void planet(int id, float velocity, float dimension, float distance, bool ring = false, bool moon =false)
{
    GLUquadric *qobj = gluNewQuadric();


	gluQuadricOrientation(qobj, GLU_OUTSIDE);
	gluQuadricDrawStyle(qobj, GLU_FILL);

    gluQuadricTexture(qobj,GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
    glBindTexture(GL_TEXTURE_2D, id);

    glPushMatrix();

        glRotatef((GLfloat) year*(velocity), 0.0, 1.0, 0.0);

        glTranslatef(distance, 0.0, 0.0);
        glRotatef(100, 1.0, 0.0, 0.0);
        glRotatef((GLfloat) day, 0.0, 0.0, -1.0);

        gluSphere(qobj, dimension, 60, 60);
        if(moon){
            glRotatef((GLfloat) year*(velocity), 0.0, 0.0, -1.0);
            glTranslatef(0.5, 0.0, 0.0);
            GLUquadric *qobjmoon = gluNewQuadric();


            gluQuadricOrientation(qobjmoon, GLU_OUTSIDE);
            gluQuadricDrawStyle(qobjmoon, GLU_FILL);

            gluQuadricTexture(qobjmoon,GL_TRUE);
            gluQuadricNormals(qobjmoon, GLU_SMOOTH);
            glBindTexture(GL_TEXTURE_2D, 2);
            gluSphere(qobjmoon, dimension/4, 60, 60);
        }


        if(ring){
            glBindTexture(GL_TEXTURE_2D, 10);
            glRotatef(100, 1.0, 0.0, 0.0);
            orbitTrail(0, 0, 0.64);
            orbitTrail(0, 0, 0.67);
            orbitTrail(0, 0, 0.69);
            orbitTrail(0, 0, 0.7);
            orbitTrail(0, 0, 0.74);
            orbitTrail(0, 0, 0.78);
            orbitTrail(0, 0, 0.8);
            orbitTrail(0, 0, 0.85);
            orbitTrail(0, 0, 0.88);
        }

    glPopMatrix();

    gluDeleteQuadric(qobj);
}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT);
    glClear( GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glColor3f (1.0, 1.0, 1.0);

    gluPerspective(fov, aspect, 1.0, 100.0);
    gluLookAt (15, inclinacao, 15, 0, 0, 0, 0.0, 1.0, 0.0);

    glTranslatef (eixoX, 0.0, eixoZ);
    glRotatef(rot, 0.0, 1.0, 0.0);

    glPushMatrix();
    /* sol */
    planet(1,v_sun,size_sun,dist_sun);

    /* mercurio */
    orbitTrail(0, 0, dist_mercurio);
    planet(2,v_mercurio,size_mercurio,dist_mercurio);

    /* vênus */
    orbitTrail(0, 0, dist_venus);
    planet(3,v_venus,size_venus,dist_venus);

    /* terra */
    orbitTrail(0, 0, dist_terra);
    planet(4,v_terra,size_terra,dist_terra,false,true);

    /* marte */
    orbitTrail(0, 0, dist_marte);
    planet(5,v_marte,size_marte,dist_marte);

    /* jupiter */
    orbitTrail(0, 0, dist_jupiter);
    planet(6, v_jupiter,size_jupiter,dist_jupiter);

    /* saturno */
    orbitTrail(0, 0, dist_saturno);
    planet(7,v_saturno,size_saturno,dist_saturno,true);

    /* urano */
    orbitTrail(0, 0, dist_urano);
    planet(8,v_urano,size_urano,dist_urano);

    /* netuno */
    orbitTrail(0, 0, dist_netuno);
    planet(9,v_netuno,size_netuno,dist_netuno);

    glPushMatrix();
    glTranslatef (eixoX, 0.0, 0.0);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();

    if(automatico){
        mov();
        _sleep(35);
    }
}

void reshape (int w, int h)
{
    aspect=(float)w/float(h);
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    //gluPerspective(fov, aspect, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
   // cout<<"entrou"<<endl;
 //   gluLookAt (0.0, 0.0, 15.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
         case 'a':
            eixoX += 1;
            glutPostRedisplay();
            break;
         case 'd':
            eixoX -= 1;
            glutPostRedisplay();
            break;
        case 'w':
            eixoZ += 1;
            glutPostRedisplay();
            break;
        case 's':
            eixoZ -= 1;
            glutPostRedisplay();
            break;

        case 'i':
            if (inclinacao<29){
                inclinacao+=1;
                if(inclinacao<29){
                    fov-=1;
                }else{
                    fov-=2;
                }

            }

            glutPostRedisplay();
            break;
        case 'I':
            if(inclinacao>0)
            {
                inclinacao-=1;
                fov+=1;
            }


            glutPostRedisplay();
            break;

        case 'z':
            fov-=1;
            glutPostRedisplay();
            break;
        case 'Z':
            fov+=1;
            glutPostRedisplay();
            break;


        case 'r':
            rot-=1;
            glutPostRedisplay();
            break;
        case 'R':
            rot+=1;
            glutPostRedisplay();
            break;


        case 'p':
            day = (day + 10) ;
            glutPostRedisplay();
            break;
        case 'P':
            day = (day - 10) ;
            glutPostRedisplay();
            break;


        case 'y':
            year = (year + 1) ;
            glutPostRedisplay();
            break;
        case 'Y':
            year = (year - 1) ;
            glutPostRedisplay();
            break;


        case 'g':
            automatico =!automatico;
            glutPostRedisplay();
            break;

        default:
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    /* configuração da janela */
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); /* modo */
    glutInitWindowSize (1000, 600); /* dimensão da janela */
    glutInitWindowPosition (0, 0); /* posição */
    glutCreateWindow ("Solar System - Igor Dias/Matheus Santos/Reilta"); /* window's name */

    /* chama as funções principais */
    init();
    glutDisplayFunc(display); /* chamada quando um pixel na janela necessita ser atualizado. */
    glutReshapeFunc(reshape); /* chamado quando a janela é redimensionada */
    glutKeyboardFunc(keyboard); /* chamada quando uma tecla do teclado é pressionada */

    glutMainLoop();
    return 0;
}
