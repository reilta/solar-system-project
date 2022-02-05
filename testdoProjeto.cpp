#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "image_load/image_load.h"

using namespace std;
static int day = 0,fov=60,rot=0;
static float aspect=0,eixoX=0,year = 0,eixoZ=0;

static double dist_mercurio = 2.0, dist_venus = 3.0,
dist_terra = 4.0, dist_marte = 5.0, dist_jupiter = 6.5,
dist_saturno = 9.0, dist_urano = 11.0, dist_netuno = 13.0;

//raio de cada planeta
static double size_mercurio = 0.1, size_venus = 0.25,
size_terra = 0.3, size_marte = 0.2, size_jupiter = 0.6,
size_saturno = 0.5, size_urano = 0.4, size_netuno = 0.4;

//velocidade de cada planeta
static double v_mercurio = 1.5, v_venus = 1.8,
v_terra = 1.9, v_marte = 1.88, v_jupiter = 2.0,
v_saturno = 2.5, v_urano = 3.0, v_netuno = 2.0;

//GLuint texture[1];      // storage for textures
GLfloat origin[] = {0.f, 0.f, 0.f, 0.f};
//GLUquadricObj *sphere = NULL;

static bool automatico=false;
void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);

    glEnable(GL_DEPTH_TEST);
    glClear( GL_DEPTH_BUFFER_BIT );
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




}
void mov()
{
    year+=1;
    glutPostRedisplay();

}
void planet(int id, float velocity, float dimension, float distance, float r = 1.0, float g = 1.0, float b = 1.0)
{
    /*
    glPushMatrix();
        glColor3f(r,g,b);
        glRotatef((GLfloat) year*(velocity), 0.0, 1.0, 0.0);
        glTranslatef (distance, 0.0, 0.0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);   // choose the texture to use.
        gluSphere(sphere,dimension,100,100);
    glPopMatrix();
    */
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
        glRotatef((GLfloat) day, 0.0, 0.0, 1.0);

        gluSphere(qobj, dimension, 60, 60);

    glPopMatrix();

    gluDeleteQuadric(qobj);

   // glDisable(GL_TEXTURE_2D);

}

void display(void){
    glClear (GL_COLOR_BUFFER_BIT);
    glClear( GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glColor3f (1.0, 1.0, 1.0);

    gluPerspective(fov,aspect , 1.0, 100.0);
    gluLookAt (15, 5.0, 15,0,0 , 0, 0.0, 1.0, 0.0);

    glTranslatef (eixoX, 0.0, eixoZ);
    glRotatef(rot, 0.0, 1.0, 0.0);

    glPushMatrix();
     //glutWireSphere(1.0, 20, 16);   /* draw sun */
    planet(1,0,1,0);        //sol
    //planet(1,v_mercurio,10,dist_mercurio);
    planet(2,v_mercurio,size_mercurio,dist_mercurio); //mercurio
    planet(3,v_venus,size_venus,dist_venus); //vênus
    planet(4,v_terra,size_terra,dist_terra); //terra
    planet(5,v_marte,size_marte,dist_marte); //marte
    planet(6, v_jupiter,size_jupiter,dist_jupiter); //jupiter
    planet(7,v_saturno,size_saturno,dist_saturno); //saturno
    planet(8,v_urano,size_urano,dist_urano); //urano
    planet(9,v_netuno,size_netuno,dist_netuno); //netuno
    glPushMatrix();
    glTranslatef (eixoX, 0.0, 0.0);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();

    if( automatico){
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
            year = (year - 5) ;
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

    //configuração da janela
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); //modo
    glutInitWindowSize (1000, 600); //dimensão da janela
    glutInitWindowPosition (0, 0); //posição
    glutCreateWindow ("Solar System - Igor Dias/Matheus Santos/Reilta"); //window's name

    //chama as funções principais
    init();
    glutDisplayFunc(display); //chamada quando um pixel na janela necessita ser atualizado.
    glutReshapeFunc(reshape); //chamado quando a janela é redimensionada
    glutKeyboardFunc(keyboard); //chamada quando uma tecla do teclado é pressionada

    glutMainLoop();
    return 0;
}
