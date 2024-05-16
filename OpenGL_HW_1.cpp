#include "GL/freeglut.h"

double degree1;
double degree2;
double degree3;
double degree4;

void quad()
{
    glBegin(GL_QUADS);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(1.0, 0.0, 0.0);
        glVertex3d(1.0, 1.0, 0.0);
        glVertex3d(0.0, 1.0, 0.0);
    glEnd();
}

void triangle()
{
    glBegin(GL_TRIANGLES);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(0.5, 0.866, 0.0); // ���̰� 1�� ���ﰢ���� �� ���� ���̰� 1�̹Ƿ�, ���̴� sqrt(3)/2
    glEnd();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // �ո� (����)
    glPushMatrix();
    glColor3d(1.0, 0.0, 0.0);
    glRotatef(degree1 += 0.05, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 2.0, 0.0);
    quad();
    glPopMatrix();

    // ���ʸ� (�Ķ�)
    glPushMatrix();
    glColor3d(0.0, 0.0, 1.0);
    glRotatef(degree1 += 0.05, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 2.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    quad();
    glPopMatrix();

    // ������ (���)
    glPushMatrix();
    glColor3d(0.0, 1.0, 0.0);
    glRotatef(degree1 += 0.05, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 2.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, 1.0);
    quad();
    glPopMatrix();

    // �Ʒ��� (���)
    glPushMatrix();
    glColor3d(1.0, 1.0, 0.0);
    glRotatef(degree1 += 0.05, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 2.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    quad();
    glPopMatrix();

    // ���� (��ȫ)
    glPushMatrix();
    glColor3d(1.0, 0.0, 1.0);
    glRotatef(degree1 += 0.05, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 2.0, 0.0);
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(90.0, 0.0, 1.0, 0.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    quad();
    glPopMatrix();

    // ���� (�ϴ�)
    glPushMatrix();
    glRotatef(degree1 += 0.05, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 2.0, 0.0);
    glColor3d(0.0, 1.0, 1.0);
    glTranslatef(0.0, 0.0, -1.0);
    quad();
    glPopMatrix();

    glPushMatrix();
    glColor3d(1.0, 0.0, 0.0);
	glRotatef(degree2 += 0.1, 1.0, 0.0, 0.0);
	glTranslatef(-3.0, -1.0, 0.0);
	glutSolidTeapot(1.0);
	glPopMatrix();

    glPushMatrix();
    glColor3d(1.0, 0.0, 1.0);
    glRotatef(degree3 += 0.1, 0.0, 1.0, 0.0);
    glTranslatef(3.0, 0.0, 0.0);
    glutSolidSphere(1.0, 12, 12);
    glPopMatrix();

    glPushMatrix();
    glColor3d(0.0, 0.0, 1.0);
    glRotatef(degree4 += 0.05, 1.0, 0.0, 0.0);
    glTranslatef(0.0, 5.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();


	glutSwapBuffers();
}

void init()
{
	glClearColor(0.7, 0.5, 0.3, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(10.0, 1.0, 1.0, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0, 70.0, 30.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1360, 960);
	glutCreateWindow("Moving Object");

	init();

	glutDisplayFunc(display);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}