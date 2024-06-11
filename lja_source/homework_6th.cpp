//소프트웨어공학과 201986 이장안
//Computer Graphics Homework #6
#include <iostream>
#include <memory>
#include "GL/freeglut.h"
#include "util/MyMatrix.h" //벡터 및 행렬 클래스 사용자 정의
#include "util/Raycaster.h" //레이캐스트 수행 클래스
#include "util/CgObject.h" //CG 오브젝트들

//상세한 결과 출력이 필요할 시 주석 해제 바람
#define __DEBUG__

using namespace std;
using namespace jangan_lee_my_matrix;  //벡터 및 행렬 클래스 사용하기 위함

namespace homework_6th {

	shared_ptr<ScreenToWorldRaycaster> raycaster; //레이캐스터
	shared_ptr<ScreenParameter> screen; //스크린 파라미터

	void display(); //디스플레이 콜백함수
	void reshape(int width, int height); //창 크기 변경 콜백함수
	const string GetSettingFilePath(); //설정파일 경로 가져오기

	int main(int argc, char** argv)
	{
		raycaster = make_shared<ScreenToWorldRaycaster>(SettingsReader(GetSettingFilePath().c_str()));
		screen = make_shared<ScreenParameter>(raycaster->GetScreenParameter());

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowPosition(300, 100); //윈도우 위치
		glutInitWindowSize(screen->width, screen->height); //윈도우 크기
		glutCreateWindow("Computer Graphics 6th Homework: 201986 이장안"); //윈도우 타이틀

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glMatrixMode(GL_PROJECTION); //행렬 모드 설정
		glLoadIdentity();
		glViewport(0, 0, screen->width, screen->height);
		glOrtho(screen->left, screen->right, screen->bottom, screen->top, -1.0, 1.0); //좌표를 설정

		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutMainLoop();

		return 0;
	}

	//디스플레이 콜백함수
	//컬러 버퍼를 통해 빠르게 화면 보여줌(응답없음 현상 제거)
	void display()
	{
		glClear(GL_COLOR_BUFFER_BIT);
#ifdef __DEBUG__
		printf("[info] Ray-casting has been started; processed y: { ");
#endif
		for (int y = screen->top; y > screen->bottom; y--)
		{
			glBegin(GL_POINTS);
			for (int x = screen->left; x < screen->right; x++) {
				Color&& c = raycaster->GetColor(x, y);
				glColor3d(c.r, c.g, c.b);
				glVertex2i(x, y);
			}
			glEnd();
			glFlush();
#ifdef __DEBUG__
			printf("%d ", y);
#endif
		}
#ifdef __DEBUG__
		printf("}; done;\n");
#endif
	}


	//창 크기 변경 콜백함수
	void reshape(int width, int height) {
		//레이캐스터 업데이트, 컬러버퍼 초기화
		raycaster->NotifyScreenSizeChanged(width, height);
		screen = make_shared<ScreenParameter>(raycaster->GetScreenParameter());

		//openGL 관련 변경
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0, 0, screen->width, screen->height);
		glOrtho(screen->left, screen->right, screen->bottom, screen->top, -1.0, 1.0);

#ifdef __DEBUG__
		printf("\n\n[info] Screen size changed to %dx%d;\n", screen->width, screen->height);
#endif
	}

	const string GetSettingFilePath() {
		static std::string file_name = "hw_6th_data.json";
		std::string response;
		cout << "렌더링 파일로 기본 지정 파일 '" << file_name << "'을 사용하시겠습니까? [y/n]: ";
		std::cin >> response;
		if (response != "y") {
			cout << "렌더링 파일 경로를 입력하십시오(예: ../data.json 또는 test.json 등): ";
			cin >> file_name;
		}

		return file_name;
	}
}

//int main(int argc, char** argv) { return homework_6th::main(argc, argv); }