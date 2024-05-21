#include <GL/freeglut.h>

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

	for (int i = -150; i <= 150; i++)
		for (int j = -150; j <= 150; j++)
		{
			if (j < -50 && j < i && j < -i)			glColor3d(1.0, 0.0, 0.0);	// red
			else if (i<-50 && j>i && j < -i)	glColor3d(0.0, 1.0, 0.0);	// green
			else if (i > 50 && j<i && j>-i)	glColor3d(0.0, 0.0, 1.0);	// blue
			else if (j > 50 && j > i && j > -i)	glColor3d(1.0, 1.0, 0.0);	// yellow
			else								glColor3d(0.0, 1.0, 1.0);	// cyan
			glVertex2i(i, j);
		}
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowPosition(300, 100);
	glutInitWindowSize(301, 301);
	glutCreateWindow("5 coloring");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -1.0, 1.0);

	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}