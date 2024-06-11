//����Ʈ������а� 201986 �����
//Computer Graphics Homework #6
#include <iostream>
#include <memory>
#include "GL/freeglut.h"
#include "util/MyMatrix.h" //���� �� ��� Ŭ���� ����� ����
#include "util/Raycaster.h" //����ĳ��Ʈ ���� Ŭ����
#include "util/CgObject.h" //CG ������Ʈ��

//���� ��� ����� �ʿ��� �� �ּ� ���� �ٶ�
#define __DEBUG__

using namespace std;
using namespace jangan_lee_my_matrix;  //���� �� ��� Ŭ���� ����ϱ� ����

namespace homework_6th {

	shared_ptr<ScreenToWorldRaycaster> raycaster; //����ĳ����
	shared_ptr<ScreenParameter> screen; //��ũ�� �Ķ����

	void display(); //���÷��� �ݹ��Լ�
	void reshape(int width, int height); //â ũ�� ���� �ݹ��Լ�
	const string GetSettingFilePath(); //�������� ��� ��������

	int main(int argc, char** argv)
	{
		raycaster = make_shared<ScreenToWorldRaycaster>(SettingsReader(GetSettingFilePath().c_str()));
		screen = make_shared<ScreenParameter>(raycaster->GetScreenParameter());

		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
		glutInitWindowPosition(300, 100); //������ ��ġ
		glutInitWindowSize(screen->width, screen->height); //������ ũ��
		glutCreateWindow("Computer Graphics 6th Homework: 201986 �����"); //������ Ÿ��Ʋ

		glClearColor(0.0, 0.0, 0.0, 0.0);
		glMatrixMode(GL_PROJECTION); //��� ��� ����
		glLoadIdentity();
		glViewport(0, 0, screen->width, screen->height);
		glOrtho(screen->left, screen->right, screen->bottom, screen->top, -1.0, 1.0); //��ǥ�� ����

		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glutMainLoop();

		return 0;
	}

	//���÷��� �ݹ��Լ�
	//�÷� ���۸� ���� ������ ȭ�� ������(������� ���� ����)
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


	//â ũ�� ���� �ݹ��Լ�
	void reshape(int width, int height) {
		//����ĳ���� ������Ʈ, �÷����� �ʱ�ȭ
		raycaster->NotifyScreenSizeChanged(width, height);
		screen = make_shared<ScreenParameter>(raycaster->GetScreenParameter());

		//openGL ���� ����
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
		cout << "������ ���Ϸ� �⺻ ���� ���� '" << file_name << "'�� ����Ͻðڽ��ϱ�? [y/n]: ";
		std::cin >> response;
		if (response != "y") {
			cout << "������ ���� ��θ� �Է��Ͻʽÿ�(��: ../data.json �Ǵ� test.json ��): ";
			cin >> file_name;
		}

		return file_name;
	}
}

//int main(int argc, char** argv) { return homework_6th::main(argc, argv); }