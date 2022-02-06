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
    glShadeModel (GL_FLAT); // usando o modelo flat de calculo de iluminação

    glEnable(GL_DEPTH_TEST); // habilita o algoritimo de visibilidade

    //glClear(GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D); //habilita as texturas
    // carrega todas as texturas
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
    LoadGLTextures("textures/stars_milky_way.bmp");

}

void mov() // função usada para fazer a movimentação automatica dos planetas
{
    year+=1;
    day+=5;
    glutPostRedisplay();
}

void orbitTrail(GLfloat x, GLfloat y, GLfloat radius)
{
	int points = 100;

    glLineWidth(0.5); // define a espessura da linha

	glPushMatrix();  // insere a matriz de transformação atual na pilha
        glRotatef((GLfloat) 90.0, 1.0, 0.0, 0.0); // rotaciona as linhas para ficarem na horizontal

        glBegin(GL_LINE_LOOP); // habilita a exibição de  linhas conectadas por pontos

        //definição dos pontos
        for(int i = 0; i <= points; i++) {
            GLfloat tetha = float(i) * 2.0 * PI / points;
            /* cria os pontos de uma circunferência e os une por uma linha */
            glVertex2f(x + (radius * cos(tetha)), y + (radius * sin(tetha)));
        }
        glEnd();


	glPopMatrix(); // remove a matriz do topo da pilha
}

void backgroundStarsTexture(int id)
{
    glBindTexture(GL_TEXTURE_2D,id); // define a textura pelo id

   // glEnable (GL_TEXTURE_2D); //

    // cria seis quadrados, formando uma cubo, e associa os pontos das faces com a textura
    glBegin(GL_QUADS);
        glTexCoord2f(0,1);
        glVertex3f(-50.f,50.f,-50.f);
        glTexCoord2f(0,0);
        glVertex3f(-50.f,-50.f,-50.f);
        glTexCoord2f(1,0);
        glVertex3f(50.f,-50.f,-50.f);
        glTexCoord2f(1,1);
        glVertex3f(50.f,50.f,-50.f);

        glTexCoord2f(0,1);
        glVertex3f(-50.f,-50.f,50.f);
        glTexCoord2f(0,0);
        glVertex3f(-50.f,50.f,50.f);
        glTexCoord2f(1,0);
        glVertex3f(50.f,50.f,50.f);
        glTexCoord2f(1,1);
        glVertex3f(50.f,-50.f,50.f);

        glTexCoord2f(0,1);
        glVertex3f(-50.f,-50.f,-50.f);
        glTexCoord2f(0,0);
        glVertex3f(-50.f,50.f,-50.f);
        glTexCoord2f(1,0);
        glVertex3f(-50.f,50.f,50.f);
        glTexCoord2f(1,1);
        glVertex3f(-50.f,-50.f,50.f);

        glTexCoord2f(0,1);
        glVertex3f(50.f,-50.f,-50.f);
        glTexCoord2f(0,0);
        glVertex3f(50.f,50.f,-50.f);
        glTexCoord2f(1,0);
        glVertex3f(50.f,50.f,50.f);
        glTexCoord2f(1,1);
        glVertex3f(50.f,-50.f,50.f);

        glTexCoord2f(0,1);
        glVertex3f(-50.f,-50.f,50.f);
        glTexCoord2f(0,0);
        glVertex3f(-50.f,-50.f,-50.f);
        glTexCoord2f(1,0);
        glVertex3f(50.f,-50.f,-50.f);
        glTexCoord2f(1,1);
        glVertex3f(50.f,-50.f,50.f);

        glTexCoord2f(0,1);
        glVertex3f(-50.f,50.f,50.f);
        glTexCoord2f(0,0);
        glVertex3f(-50.f,50.f,-50.f);
        glTexCoord2f(1,0);
        glVertex3f(50.f,50.f,-50.f);
        glTexCoord2f(1,1);
        glVertex3f(50.f,50.f,50.f);

    glEnd();
}

void planet(int id, float velocity, float dimension, float distance, bool ring = false, bool moon =false)
{
    // cria um obejto do tipo quadric
    GLUquadric *qobj = gluNewQuadric();

	//gluQuadricOrientation(qobj, GLU_OUTSIDE);
	//gluQuadricDrawStyle(qobj, GLU_FILL);


    gluQuadricTexture(qobj,GL_TRUE); // habilita a textura do objeto tipo quadric
	//gluQuadricNormals(qobj, GLU_SMOOTH);
    glBindTexture(GL_TEXTURE_2D, id); // seleciona a textura pelo id

    glPushMatrix();

        glRotatef((GLfloat) year*(velocity), 0.0, 1.0, 0.0); //possibilita a rotação dos planetas em torno de um ponto inicial

        glTranslatef(distance, 0.0, 0.0); // desloca os planetas em relação ao ponto inicial
        glRotatef(100, 1.0, 0.0, 0.0);   // rotaciona os planetas para alinhar a  textura da forma correta
        glRotatef((GLfloat) day, 0.0, 0.0, -1.0); // rotaciona os planetas em torno do proprio eixo

        gluSphere(qobj, dimension, 60, 60); // cria uma esfera a partir do quadric

        // cria  a lua para os planetas que habilitarem
        if(moon){
            glRotatef((GLfloat) year*(velocity)*2, 0.0, 0.0, 1.0);
            glTranslatef(0.5, 0.0, 0.0);
            //glRotatef((GLfloat) day*(velocity)*2, 0.0, 0.0, -1.0);
            GLUquadric *qobjmoon = gluNewQuadric();

            gluQuadricOrientation(qobjmoon, GLU_OUTSIDE);
            gluQuadricDrawStyle(qobjmoon, GLU_FILL);

            gluQuadricTexture(qobjmoon,GL_TRUE);
            gluQuadricNormals(qobjmoon, GLU_SMOOTH);
            glBindTexture(GL_TEXTURE_2D, 2);
            gluSphere(qobjmoon, dimension/4, 60, 60);
        }
        // cria aneis em volta dos planetas que habilitarem
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

    glClear (GL_COLOR_BUFFER_BIT);//limpa o buffer das cores
    glClear( GL_DEPTH_BUFFER_BIT );//limpa o buffer da visibilidade

    glLoadIdentity(); // carrega a matriz identidade

    //glColor3f (1.0, 1.0, 1.0);

    //(
    gluPerspective(fov, aspect, 1.0, 150.0); // configura o frustrum

    gluLookAt (15, inclinacao, 15, 0, 0, 0, 0.0, 1.0, 0.0);

    glTranslatef (eixoX, 0.0, eixoZ);
    glRotatef(rot, 0.0, 1.0, 0.0);

    glPushMatrix();

    backgroundStarsTexture(11);

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
    aspect=(float)w/float(h);// Calcula a  razão do aspecto

    glViewport (0, 0, (GLsizei) w, (GLsizei) h); // é a região retangular do near do frustrum
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();



    glMatrixMode(GL_MODELVIEW); //especifica a matriz que vai ser aplicada as  proximas operações matriciais

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
            if(fov>1)
            {
                fov-=1;
            }

            glutPostRedisplay();
            break;
        case 'Z':
            if(fov<100)
            {
                fov+=1;
            }

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
