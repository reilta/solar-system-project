#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;
static int year = 0, day = 0,eixoX=0,eixoZ=0;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void planet(float velocity, float dimension, float distance)
{
    glPushMatrix();
    glRotatef ((GLfloat) year*(velocity), 0.0, 1.0, 0.0);
    glTranslatef (distance, 0.0, 0.0);
    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);

    glutWireSphere(dimension, 20, 16);   /* draw sun */
    glPopMatrix();
}

void display(void)
{

  //  gluLookAt (0.0, 0.0, 15.0, 5.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f (1.0, 1.0, 1.0);
    gluLookAt (0, 0.0, 15,0,0 , 0, 0.0, 1.0, 0.0);
    glTranslatef (eixoX, 0.0, eixoZ);

    //sol
    //gluLookAt (0, 0, 20, 0, eixoX, 0.0, 0.0, 1.0, 0.0);
    glPushMatrix();
    glutWireSphere(1.0, 20, 16);   /* draw sun */
    glPopMatrix();

    planet(0.9,0.1,2); //mercurio
    planet(0.95,0.25,3); //vênus
    glColor3f (0.0, 0.0, 1.0);
    planet(1.0,0.3,4); //terra
    glColor3f (1.0, 1.0, 1.0);
    planet(1.88,0.2,5); //marte
    planet(2,0.6,6.5); //jupiter
    planet(2.5,0.5,9); //saturno
    planet(3,0.4,11); //urano
    glColor3f (2.5, 0.0, 0.0);
    planet(2,0.4,13); //netuno
    glPushMatrix();
    glTranslatef (eixoX, 0.0, 0.0);
    glPopMatrix();
    glutSwapBuffers();

}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
   // cout<<"entrou"<<endl;
 //   gluLookAt (0.0, 0.0, 15.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
         case 'a':
            eixoX+=1;

            glutPostRedisplay();
            break;
         case 'd':
            eixoX-=1;
            glutPostRedisplay();
            break;
        case 'w':
            eixoZ+=1;

            glutPostRedisplay();
            break;
        case 's':
            eixoZ-=1;
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
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (0, 0);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
