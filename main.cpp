#include "GL/freeglut.h"
#include "context.h"
#include "interval.h"

// 화면 크기
const int nx = 400;
const int ny = 400;

// OpenGL 초기화 및 렌더링 함수
void display()
{
    std::shared_ptr<Context> c = Context::GetContext();
    c->Init(nx, ny);

    const std::vector<Color> framebuffer(c->GetFrameBuffer());
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            Color color = framebuffer[j * nx + i];
            glColor3d(color.r, color.g, color.b);
            glVertex2f((i / (float)nx) * 2 - 1, (j / (float)ny) * 2 - 1);
        }
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    Interval interval(-2, 5);
    std::vector<double> Roots = interval.FindAllRoot([](double x) -> std::vector<double>
        {
            return { x + 1, (x - 1) * (x - 1), x - 4};
        });

    for (int i = 0; i < Roots.size(); ++i)
    {
        printf("%d 번째 Root : %lf\n", i + 1, Roots[i]);
    }
   

    /*glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(nx, ny);
    glutCreateWindow("Ray Tracing Image");
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();*/
    return 0;
}