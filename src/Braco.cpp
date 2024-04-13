/*
 * Computacao Grafica
 * Codigo Exemplo: Desenhar um braco robotico 3D
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#include "Config.h"

/*
 * Declaring Constants and Variables
 */
float R, G, B;

static int rotation = 40, shoulder = 0, elbow = 60, hand = 90, thumb = -90, indexfinger = 90, ringfinger = 90;


/*
 * Advance declarations (forward) of functions (signatures)
 */
void init(void);
void keyboard(unsigned char key, int x, int y);
void display(void);
void reshape(int w, int h);
void drawSolidCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks);


/*
 *
 * Main function
 *
 */
int main(int argc, char** argv) {

    // start GLUT
    glutInit(&argc, argv);

    // starts the display using RGB, double-buffering and z-buffering
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Robotic Arm");

    // Function with some commands to initialize OpenGL
    init();

    // defines callback functions
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

    glClearColor(1.0, 1.0, 1.0, 1.0); // Cleans the screen with white color
    glEnable(GL_DEPTH_TEST); // Enables the Z-Buffer algorithm
}


/*
 *
 * Adjusts the projection for window redesign
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
    gluPerspective(60, (float)w / (float)h, 1.0, 15); // (angulo, aspecto, ponto_proximo, ponto distante)
    gluLookAt
    (
        0.0, 0.0, 7.0,  // posicao da camera (olho)
        0.0, 1.0, 0.0,  // direcao da camera (geralmente para centro da cena)
        0.0, 1.0, 0.0
    ); // sentido ou orientacao da camera (de cabeca para cima)
    
    // muda para o modo GL_MODELVIEW para desenhar na tela
    glMatrixMode(GL_MODELVIEW);
}


/*
 *
 * Callback function to control common keys
 *
 */
void keyboard(unsigned char key, int x, int y) {

    switch (key) {
        case 'o': 
            shoulder = (shoulder - 5) % 360; 
            break; // clockwise
        case 'O': 
            shoulder = (shoulder + 5) % 360; 
            break; // clockwise
        case 'c': 
            elbow = (elbow - 5) % 360; 
            break; // clockwise
        case 'C': 
            elbow = (elbow + 5) % 360; 
            break; // clockwise
        case 'm':
            hand = (hand - 5) % 360;
            break;
        case 'M':
            hand = (hand + 5) % 360;
            break;
        case 'p':
            thumb = (thumb - 5) % 360;
            break;
        case 'P':
            thumb = (thumb + 5) % 360;
            break;
        case 'i':
            indexfinger = (indexfinger + 5) % 360;
            break;
        case 'I':
            indexfinger = (indexfinger - 5) % 360;
            break;
        case 'a':
            ringfinger = (ringfinger + 5) % 360;
            break;
        case 'A':
            ringfinger = (ringfinger - 5) % 360;
            break;
        case 'y':
            rotation = (rotation - 5) % 360;
            break;
        case 'Y':
            rotation = (rotation + 5) % 360;
            break;
        case ESC:
            exit(EXIT_SUCCESS);
            break;
    }
    glutPostRedisplay();
}


/*
 *
 * Callback function to draw in the window
 *
 */
void display(void) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the Color Buffer
    glLoadIdentity();

    // Base 0

    glPushMatrix();
        glColor3f(0, 1, 0);
        glTranslatef(0.0, -2.0, 0.0);
        glScalef(7.0, 0.1, 5.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glRotatef((GLfloat)rotation, 0.0, 1.0, 0.0);

    // Base 1

    glPushMatrix();
        glTranslatef(0.0, -2.0, 0.0);
        glRotatef(-90, 1, 0, 0);
        glColor3f(0.8, 0.2, 0.8);
        glutSolidCone(2, 1.0, 30, 30); // base, height, slices, stacks
    glPopMatrix();


    // Base 2

    glPushMatrix();
        glTranslatef(0.0, -1.7, 0.0);
        glRotatef(-90, 1, 0, 0);
        glColor3f(0, 1, 1);
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
        glRotatef((GLfloat)shoulder, 0.0, 0.0, 1.0);

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
            glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
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
                glColor3f(0, 0, 1);
                //glutSolidCube(1.0); // Size
                drawSolidCylinder(1, 1, 30, 30);
            glPopMatrix();

            // Hand
            glTranslatef(0.0, 1, 0.0);
            glRotatef((GLfloat)hand, 0.0, 0.0, 1.0);
            glTranslatef(0.0, -1.0, 0.0);

            glPushMatrix();
                glTranslatef(0.0, 1, 0.0);
                glRotatef(-90, 1, 0, 0);
                glScalef(0.15, 0.15, 1);
                glColor3f(0.5, 0, 0.5);
                //glutSolidCube(1); // Size
                drawSolidCylinder(1, 1, 30, 30);
            glPopMatrix();

            // Elbow
            glPushMatrix();
                glTranslatef(0.0, 2, 0.0);
                glColor3f(0.8, 0.8, 0.8);
                glutSolidSphere(0.3, 30, 30); // radius, slices, stacks
            glPopMatrix();

            // Ring finger
            glPushMatrix();
                glTranslatef(-0.2, 2.06, -0.09);
                glRotatef((GLfloat)ringfinger, 0.0, 0.0, 1.0);
                glTranslatef(0.2, -2.0, -0.09);
                glTranslatef(0.0, 2.0, 0.0);
                glScalef(0.5, 0.15, 0.15);
                glColor3f(0, 0, 0);
                glutSolidCube(1.0); // Size
            glPopMatrix();

            // Thumb
            glPushMatrix();
                glTranslatef(0.2, 2.06, 0.0);
                glRotatef((GLfloat)thumb, 0.0, 0.0, 1.0);
                glTranslatef(-0.2, -2, 0.0);
                glTranslatef(0.0, 2, 0.0);
                glScalef(0.5, 0.15, 0.15);
                glColor3f(0.0, 0.0, 1.0);
                glutSolidCube(1.0); // Size
            glPopMatrix();

            // Index finger
            glPushMatrix();
                glTranslatef(-0.2, 2.06, 0.09);
                glRotatef((GLfloat)indexfinger, 0.0, 0.0, 1.0);
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
 * Function to draw a solid cylinder.
 *
 * Parameters:
 * - radius: radius of the cylinder.
 * - height: height of the cylinder.
 * - slices: number of subdivisions around the axis of the cylinder (surface detail).
 * - stacks: number of subdivisions along the axis of the cylinder (height detail).
 */
void drawSolidCylinder(GLfloat radius, GLfloat height, GLint slices, GLint stacks) {
    GLUquadricObj* obj = gluNewQuadric();
    gluQuadricDrawStyle(obj, GLU_FILL); // Sets the drawing style to filled
    gluCylinder(obj, radius, radius, height, slices, stacks); // Draws the cylinder
    gluDeleteQuadric(obj); // Frees the memory allocated for the GLUquadric object
}