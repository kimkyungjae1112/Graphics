#include "GL/freeglut.h"
#include "context.h"

// 화면 크기
const int nx = 400;
const int ny = 400;

Interval FindJ(double small, double big)
{
    auto F = [](double x) -> std::vector<double>
        {
            return { x + 1, (x - 1) * (x - 1), x - 4};
        };

    std::vector<double> smaller = F(small);
    std::vector<double> bigger = F(big);

    std::vector<Interval> intervals;
    for (size_t i = 0; i < smaller.size(); ++i)
    {
        intervals.push_back({ smaller[i], bigger[i] });
    }

    Interval result = intervals[0];
    for (size_t i = 1; i < intervals.size(); ++i)
    {
        result = result * intervals[i];
    }

    return result;
}


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
    std::shared_ptr<Context> a = Context::GetContext();
    printf("(x + 1)(x - 1)(x - 4) 의 근 : %lf", a->IntervalMethod({-0.5,0.5}, FindJ));


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(nx, ny);
    glutCreateWindow("Ray Tracing Image");
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
    return 0;
}