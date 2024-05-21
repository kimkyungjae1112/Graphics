#include "GL/freeglut.h"
#include "vector.h"
#include "matrix.h"
#include "triangle.h"
#include "ball.h"
#include "ray.h" 
#include <vector>

#define M_PI 3.141592653589793238462643383279

// 화면 크기 및 프레임버퍼
const int nx = 400;
const int ny = 400;
std::vector<Color> FrameBuffer(nx* ny);

// 광선 추적을 수행하고 프레임버퍼에 결과 저장
void RenderScene()
{
    double fov = 90;
    Vector E = { 600, 0, 0, 1 }; // 카메라 위치
    Vector D = { 0, 0, 0 }; // 카메라가 바라보는 지점
    Vector AT = D - E;
    Vector UP = { 0, 0, 1 }; // 업 벡터
    Vector LightPos = { 300, 300, 300 };

    std::vector<Ball> Balls = {
        {{0, 0, 0}, 50, {1, 0, 0}}, // 빨간색 구
        {{0, 100, 0}, 50, {0, 1, 0}} // 초록색 구
    };

	Plane floor = { {1, 0, 0}, {0, 0, 0}, {0.2, 0.5, 0.8} }; // 흰색 바닥

    Vector U = AT * UP;
    Vector V = U * AT;
    Vector W = -AT;

    Matrix mat4;
    mat4.InitM({ U, V, W, E });
    double Distance = ny / (2 * tan(fov * M_PI / 360.0));


    for (int j = 0; j < ny; ++j)
    {
        for (int i = 0; i < nx; ++i)
        {
            Vector Pixel = { -(nx / 2.0) + (0.5 + (i * 1)), (ny / 2.0) - (0.5 + (j * 1)) ,  -Distance, 1};
            Vector CameraToScreen = (mat4 * Pixel - E);
            Ray ray = { E, CameraToScreen };
            FrameBuffer[j * nx + i] = ray.TraceRay(Balls, floor, LightPos);
        }
    }
 
}

// OpenGL 초기화 및 렌더링 함수
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (int j = 0; j < ny; ++j)
    {
        printf("%d ", j);

        for (int i = 0; i < nx; ++i)
        {
            Color color = FrameBuffer[j * nx + i];
            glColor3d(color.r, color.g, color.b);
            glVertex2f((i / (float)nx) * 2 - 1, (j / (float)ny) * 2 - 1);
        }
    }
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    RenderScene();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(nx, ny);
    glutCreateWindow("Ray Tracing Image");
    glutDisplayFunc(display);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glutMainLoop();
    return 0;
}