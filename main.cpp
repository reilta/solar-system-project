#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;
static int year = 0, day = 0,fov=60,rot=0;
static float aspect=0,eixoX=0,eixoZ=0;

static double dist_mercurio = 2.0, dist_venus = 3.0,
dist_terra = 4.0, dist_marte = 5.0, dist_jupiter = 6.5,
dist_saturno = 9.0, dist_urano = 11.0, dist_netuno = 13.0;

//raio de cada planeta
static double size_mercurio = 0.1, size_venus = 0.25,
size_terra = 0.3, size_marte = 0.2, size_jupiter = 0.6,
size_saturno = 0.5, size_urano = 0.4, size_netuno = 0.4;

//velocidade de cada planeta
static double v_mercurio = 0.9, v_venus = 0.95,
v_terra = 1.0, v_marte = 1.88, v_jupiter = 2.0,
v_saturno = 2.5, v_urano = 3.0, v_netuno = 2.0;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void planet(float velocity, float dimension, float distance, float r = 1.0, float g = 1.0, float b = 1.0)
{
    glPushMatrix();
    glRotatef ((GLfloat) year*(velocity), 0.0, 1.0, 0.0);
    glTranslatef (distance, 0.0, 0.0);
    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);

    glColor3f (r, g, b);

    glutWireSphere(dimension, 20, 16);   /* draw sun */
    glPopMatrix();
}

void display(void)
{


    glClear (GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glColor3f (1.0, 1.0, 1.0);

    gluPerspective(fov,aspect , 1.0, 100.0);
    gluLookAt (15, 5.0, 15,0,0 , 0, 0.0, 1.0, 0.0);

    glTranslatef (eixoX, 0.0, eixoZ);
    glRotatef(rot, 0.0, 1.0, 0.0);


    //sol

    glPushMatrix();
    glutWireSphere(1.0, 20, 16);   /* draw sun */
    //glPopMatrix();

    planet(v_mercurio,size_mercurio,dist_mercurio); //mercurio
    planet(v_venus,size_venus,dist_venus); //vênus
    planet(v_terra,size_terra,dist_terra,0.0,0.0,1.0); //terra
    planet(v_marte,size_marte,dist_marte); //marte
    planet(v_jupiter,size_jupiter,dist_jupiter); //jupiter
    planet(v_saturno,size_saturno,dist_saturno); //saturno
    planet(v_urano,size_urano,dist_urano); //urano
    planet(v_netuno,size_netuno,dist_netuno,2.5, 0.0, 0.0); //netuno
    glPushMatrix();
    glTranslatef (eixoX, 0.0, 0.0);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();

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
            day = (day + 10) % 360;
            glutPostRedisplay();
            break;
        case 'P':
            day = (day - 10) % 360;
            glutPostRedisplay();
            break;
        case 'y':
            year = (year + 1) % 360;
            glutPostRedisplay();
            break;
        case 'Y':
            year = (year - 5) % 360;
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
