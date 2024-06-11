#include "GL/freeglut.h"
#include "context.h"
#include "interval.h"
#include <iostream>

// 화면 크기
const int nx = 500;
const int ny = 500;

// OpenGL 초기화 및 렌더링 함수
void display()
{
    std::shared_ptr<Context> c = Context::GetContext();
    c->Init(nx, ny);

    glClear(GL_COLOR_BUFFER_BIT);
    const std::vector<Color> framebuffer(c->GetFrameBuffer());
    for (int j = 0; j < ny; ++j)
    {

        glBegin(GL_POINTS);
        for (int i = 0; i < nx; ++i)
        {
            Color color = framebuffer[j * nx + i];
            glColor3d(color.r, color.g, color.b);
            glVertex2f((i / (float)nx) * 2 - 1, (j / (float)ny) * 2 - 1);
        }
        glEnd();
    }
    glutSwapBuffers();

}

int main(int argc, char** argv)
{ 
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(nx, ny);
    glutCreateWindow("Implicit Surface Image");
    
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop(); 

    return 0;
}