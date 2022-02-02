#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int year = 0, day = 0;

void init(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
}

void planet(float velocity, float dimension, float distance)
{
    glPushMatrix();
    glRotatef ((GLfloat) year*(164.80/velocity), 0.0, 1.0, 0.0);
    glTranslatef (distance, 0.0, 0.0);
    glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);

    glutWireSphere(dimension, 20, 16);   /* draw sun */
    glPopMatrix();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (1.0, 1.0, 1.0);

    //sol
    glPushMatrix();
    glutWireSphere(1.0, 20, 16);   /* draw sun */
    glPopMatrix();

    planet(0.24,0.1,2); //mercurio
    planet(0.62,0.25,3); //vênus
    glColor3f (0.0, 0.0, 1.0);
    planet(1.0,0.3,4); //terra
    glColor3f (1.0, 1.0, 1.0);
    planet(1.88,0.2,5); //marte
    planet(11.86,0.6,6.5); //jupiter
    planet(29.46,0.5,9); //saturno
    planet(84.01,0.4,11); //urano
    glColor3f (1.0, 0.0, 0.0);
    planet(164.80,0.4,13); //netuno

    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt (0.0, 0.0, 15.0, 5.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y)
{
    switch (key) {
        case 'd':
            day = (day + 10) % 360;
            glutPostRedisplay();
            break;
        case 'D':
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
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
