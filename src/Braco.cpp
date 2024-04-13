/*
 * Computacao Grafica
 * Codigo Exemplo: Desenhar um braco robotico 3D
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#include "Config.h""

// Global variables for defining colors
float R, G, B;

// Function prototypes for OpenGL callbacks
void init(void);
void keyboard(unsigned char key, int x, int y);
void display(void);
void reshape(int w, int h);
void drawSolidCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks);


/*
 * Declaring Constants and Variables
 */
static int ombro = 0, cotovelo = 0, rotacionar = 0, mao = 0, polegar = 0, indicador = 0, anelar = 0;
static int rotation = 0, shoulder = 0, elbow = 0, hand = 0, thumb = 0, index = 0, ring = 0;

/*
 * Declaracoes antecipadas (forward) das funcoes (assinaturas)
 */
void init(void);
void keyboard(unsigned char key, int x, int y);
void display(void);
void reshape(int w, int h);

//Fucao principal
int main(int argc, char** argv) {

    // inicia o GLUT
    glutInit(&argc, argv);

    // inicia o display usando RGB, double-buffering e z-buffering
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robotic Arm");

    // Funcao com alguns comandos para a inicializacao do OpenGL
    init();

    // define as funcoes de callback
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return EXIT_SUCCESS;
}


/*
 *
 * Initialize OpenGL parameters
 *
 */
void init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
    glEnable(GL_DEPTH_TEST); // Habilita o algoritmo Z-Buffer
}


/*
 *
 * Ajusta a projecao para o redesenho da janela
 *
 */
void reshape(int w, int h) {

    // muda para o modo GL_PROJECTION e reinicia a matriz de projecao
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // define o tamanho da area de desenho da janela
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // Define a forma do volume de visualizacao para termos
    // uma projecao perspectiva (3D).
    gluPerspective(60, (float)w / (float)h, 1.0, 9.0); //(angulo, aspecto, ponto_proximo, ponto distante)
    gluLookAt(0.0, 0.0, 7.0,  // posicao da camera (olho)
        0.0, 1.0, 0.0,  // direcao da camera (geralmente para centro da cena)
        0.0, 1.0, 0.0); // sentido ou orientacao da camera (de cabeca para cima)
    // muda para o modo GL_MODELVIEW para desenhar na tela

    glMatrixMode(GL_MODELVIEW);
}


/*
 *
 * Funcao callback para controle das teclas comuns
 *
 */
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'o': ombro = (ombro - 5) % 360; break; // sentido horario
    case 'O': ombro = (ombro + 5) % 360; break; // sentido anti-horario
    case 'c': cotovelo = (cotovelo - 5) % 360; break; // sentido horario
    case 'C': cotovelo = (cotovelo + 5) % 360; break; // sentido anti-horario
    case 'm':
        mao = (mao - 5) % 360;
        break;
    case 'M':
        mao = (mao + 5) % 360;
        break;
    case 'p':
        polegar = (polegar - 5) % 360;
        break;
    case 'P':
        polegar = (polegar + 5) % 360;
        break;
    case 'i':
        indicador = (indicador + 5) % 360;
        break;
    case 'I':
        indicador = (indicador - 5) % 360;
        break;
    case 'a':
        anelar = (anelar + 5) % 360;
        break;
    case 'A':
        anelar = (anelar - 5) % 360;
        break;
    case 'y':
        rotacionar = (rotacionar - 5) % 360;
        break;
    case 'Y':
        rotacionar = (rotacionar + 5) % 360;
        break;
    case ESC:
        exit(EXIT_SUCCESS);
        break; // sai do programa
    }
    glutPostRedisplay();
}


/*
 *
 * Funcao callback para desenhar na janela
 *
 */
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Limpa o Buffer de Cores
    glLoadIdentity();

    // Base 0

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(0.0, -2.0, 0.0);
    glScalef(7.0, 0.1, 5.0);
    glutSolidCube(1.0);
    glPopMatrix();

    glRotatef((GLfloat)rotacionar, 0.0, 1.0, 0.0);

    // Base 1

    glPushMatrix();
        glTranslatef(0.0, -2.0, 0.0);
        glRotatef(-90, 1, 0, 0);
        glColor3f(0.8, 0.8, 0.8);
        glutSolidCone(2, 1.0, 30, 30); // base, height, slices, stacks
    glPopMatrix();


    // Base 2

    glPushMatrix();
        glTranslatef(0.0, -1.7, 0.0);
        glRotatef(-90, 1, 0, 0);
        glColor3f(1, 1, 0.5);
        glutSolidCone(1.0, 1.2, 30, 30); // base, height, slices, stacks
    glPopMatrix();

    // Elbow 1

    glPushMatrix();
        glTranslatef(0.0, -1.0, 0.0);
        glColor3f(0.8, 0.8, 0.8);
        glutSolidSphere(0.5, 30, 30); // radius, slices, stacks
    glPopMatrix();

    // Arm movement
    glPushMatrix();

        // Origin positioned at the shoulder
        glTranslatef(0.0, -1.0, 0.0);
        glRotatef((GLfloat)ombro, 0.0, 0.0, 1.0);

        // Origin positioned at the center of the arm
        glTranslatef(0.0, 1.0, 0.0);

        // Arm
        glPushMatrix();
            glTranslatef(0.0, -1, 0.0);
            glRotatef(-90, 1, 0, 0);
            glScalef(0.3, 0.3, 2);
            glColor3f(1, 1, 0);
            //glutSolidCube(1.0); // Size
            drawSolidCylinder(1, 1, 30, 30);
        glPopMatrix();

        // Elbow
        glPushMatrix();
            glTranslatef(0.0, 1.0, 0.0);
            glColor3f(0.8, 0.8, 0.8);
            glutSolidSphere(0.45, 30, 30); // radius, slices, stacks
        glPopMatrix();

        // Forearm movement
        glPushMatrix();

            // Origin positioned at the elbow
            glTranslatef(0.0, 1.0, 0.0);
            glRotatef((GLfloat)cotovelo, 0.0, 0.0, 1.0);
            glTranslatef(0.0, 1.0, 0.0);

            glPushMatrix();
                // Wrist
                glPushMatrix();
                    glTranslatef(0.0, 1.0, 0.0);
                    glColor3f(0.8, 0.8, 0.8);
                    glutSolidSphere(0.3, 30, 30); // radius, slices, stacks
                glPopMatrix();

                // Forearm
                glTranslatef(0.0, -0.7, 0.0);
                glRotatef(-90, 1, 0, 0);
                glScalef(0.2, 0.2, 1.8);
                glColor3f(1, 1, 0);
                //glutSolidCube(1.0); // Size
                drawSolidCylinder(1, 1, 30, 30);
            glPopMatrix();

            // Hand
            glTranslatef(0.0, 1.0, 0.0);
            glRotatef((GLfloat)mao, 0.0, 0.0, 1.0);
            glTranslatef(0.0, -1.0, 0.0);

            glPushMatrix();
                glTranslatef(0.0, 1.5, 0.0);
                glScalef(0.4, 1, 0.7);
                glColor3f(0, 1, 0.0);
                glutSolidCube(1); // Size
            glPopMatrix();

            // Ring finger
            glPushMatrix();
                glTranslatef(-0.2, 2.06, -0.09);
                glRotatef((GLfloat)anelar, 0.0, 0.0, 1.0);
                glTranslatef(0.2, -2.0, -0.09);
                glTranslatef(0.0, 2.0, 0.0);
                glScalef(0.5, 0.15, 0.15);
                glColor3f(0, 0, 0);
                glutSolidCube(1.0); // Size
            glPopMatrix();

            // Thumb
            glPushMatrix();
                glTranslatef(0.2, 2.06, 0.0);
                glRotatef((GLfloat)polegar, 0.0, 0.0, 1.0);
                glTranslatef(-0.2, -2, 0.0);
                glTranslatef(0.0, 2, 0.0);
                glScalef(0.5, 0.15, 0.15);
                glColor3f(0.0, 0.0, 1.0);
                glutSolidCube(1.0); // Size
            glPopMatrix();

            // Index finger
            glPushMatrix();
                glTranslatef(-0.2, 2.06, 0.09);
                glRotatef((GLfloat)indicador, 0.0, 0.0, 1.0);
                glTranslatef(0.2, -2.0, 0.09);
                glTranslatef(0.0, 2.0, 0.0);
                glScalef(0.5, 0.15, 0.15);
                glColor3f(1.0, 0.0, 0.0);
                glutSolidCube(1.0); // Size
            glPopMatrix();

        glPopMatrix();

    // Origin returns to the original coordinate system
    glPopMatrix();


    // Troca os buffers, mostrando o que acabou de ser desenhado
    glutSwapBuffers();
}


/*
 *
 * Funcao callback para desenhar na janela
 *
 */
void drawSolidCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
    GLUquadricObj* obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_FILL);
    gluCylinder(obj, radius, radius, height, slices, stacks);
    gluDeleteQuadric(obj);
}