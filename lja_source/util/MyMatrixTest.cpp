//201986 소프트웨어공학과 이장안
//3차원 동차 좌표계상의 행렬 및 벡터 클래스를 테스트한다.
#include <iostream>
#include "MyMatrix.h"

using namespace jangan_lee_my_matrix;
using namespace std;

namespace jangan_lee_my_matrix { 
namespace test {

/***************  test cases  ***************/
void vector4d_init() {
	Vector4d v1 = { 1, 0, 0, 0 };
	Vector4d v2 = { 0, 2, 0, 0 };
	Vector4d v3;
	v3[0] = 1, v3[1] = 5, v3[2] = 8, v3[3] = 0;
	Vector4d v0(true); /* 벡터라는 의미 */

	Vector4d p1 = { 1, 0, 0, 1 };
	Vector4d p2(false);
	p2[0] = 0, p2[1] = 2, p2[2] = 0, p2[3] = 1;
	Vector4d p0(false); /* 점이라는 의미 */

	cout << "v1: " << v1 << ", is_vector(" << v1.is_vector() << ")\n";
	cout << "v2: " << v2 << ", is_vector(" << v2.is_vector() << ")\n";
	cout << "v3: " << v3 << ", is_vector(" << v3.is_vector() << ")\n";
	cout << "v0: " << v0 << ", is_vector(" << v0.is_vector() << ")\n\n";

	cout << "p1: " << p1 << ", is_point(" << p1.is_point() << ")\n";
	cout << "p2: " << p2 << ", is_point(" << p2.is_point() << ")\n";
	cout << "p0: " << p0 << ", is_point(" << p0.is_point() << ")\n";
}
void vector4d_equals() {
	Vector4d v1 = { 1, 2, 3, 0 };
	Vector4d v2 = { 1, 2, 3, 0 };
	Vector4d v3 = { 1, 2, 3, 1 };
	Vector4d p = Vector4d::zero_point;
	Vector4d v = Vector4d::zero_vector;

	cout << "p: " << p.full_format() << endl;
	cout << "v: " << v.full_format() << endl;
	cout << "p == Vecter4d::zero_point: " << (p == Vector4d::zero_point) << endl;
	cout << "p != Vecter4d::zero_point: " << (p != Vector4d::zero_point) << endl;
	cout << "v == Vecter4d::zero_vector: " << (v == Vector4d::zero_vector) << endl;
	cout << "v != Vecter4d::zero_vector: " << (v != Vector4d::zero_vector) << endl;

	cout << "v1: " << v1.full_format() << endl;
	cout << "v2: " << v2.full_format() << endl;
	cout << "v3: " << v3.full_format() << endl;
	cout << "v1 == v2: " << (v1 == v2) << endl;
	cout << "v1 != v2: " << (v1 != v2) << endl;
	cout << "v1 == v3: " << (v1 == v3) << endl;
	cout << "v1 != v3: " << (v1 != v3) << endl;
}
void vector4d_scala_product() {
	Vector4d v = { 1, 2, -4, 0 };
	Vector4d p = { -3, 0, 2, 1 };

	cout << "v: " << v << endl;
	cout << "p: " << p << endl;
	cout << "v * 2: " << (v * 2) << endl;
	cout << "2 * v: " << (2 * v) << endl;
	cout << "p * 2: " << (p * 2) << endl;
	cout << "(p * 2).full_format(): " << (p * 2).full_format() << endl;
	cout << "2 * p: " << (2 * p) << endl;
	cout << "(2 * p).full_format(): " << (2 * p).full_format() << endl;
}
void vector4d_add() {
	Vector4d v = { 1, 2, -4, 0 };
	Vector4d p = { -3, 0, 2, 1 };

	cout << "v: " << v.full_format() << endl;
	cout << "p: " << p.full_format() << endl;
	cout << "v + p: " << (v + p).full_format() << endl;
}
void vector4d_subtract() {
	Vector4d v = { 1, 2, -4, 0 };
	Vector4d p = { -3, 0, 2, 1 };

	cout << "v: " << v.full_format() << endl;
	cout << "p: " << p.full_format() << endl;
	cout << "v - p: " << (v - p).full_format() << endl;
}
void vector4d_cross() {
	Vector4d v1 = { 1, 2, -4, 0 };
	Vector4d v2 = { 3, -4, 2, 0 };
	Vector4d p = { -3, 0, 2, 1 };

	cout << "v1: " << v1.full_format() << endl;
	cout << "v2: " << v2.full_format() << endl;
	cout << "p: " << p.full_format() << endl;
	cout << "v1 * v2: " << (v1 * v2).full_format() << endl;
	cout << "v2 * v1: " << (v2 * v1).full_format() << endl;
	try {
		cout << "v1 * p: ";
		cout << (v1 * p).full_format() << endl;
	}
	catch (exception& e) {
		cout << "v1 * p: " << e.what() << endl;
	}
}
void vector4d_dot() {
	Vector4d v = { 1, 2, -4, 0 };
	Vector4d p = { -3, 0, 2, 1 };

	cout << "v: " << v.full_format() << endl;
	cout << "p: " << p.full_format() << endl;
	cout << "v.dot(p): " << v.dot(p) << endl;
}
void vector4d_full_format() {
	Vector4d v = { 3, 6, 19, 0 };
	Vector4d p = { 3, 6, 19, 1 };
	v = v * (-1.0 / 7.0);
	p = p * (-1.0 / 7.0);

	cout << "v: " << v << endl;
	cout << "p: " << p << endl;
	cout << "v.full_format(): " << v.full_format() << endl;
	cout << "p.full_format(): " << p.full_format() << endl;
}
void vector4d_norm() {
	Vector4d v = { 3, 6, -2, 0 };
	Vector4d p = { 3, 6, -2, 4 };

	cout << "v: " << v.full_format() << endl;
	cout << "p: " << p.full_format() << endl;
	cout << "v.norm(): " << v.norm() << endl;
	cout << "p.norm(): " << p.norm() << endl;
}
void vector4d_normalize() {
	Vector4d v = { 3, 6, -2, 0 };
	Vector4d p = { 3, 6, -2, 4 };

	cout << "v: " << v.full_format() << endl;
	cout << "p: " << p.full_format() << endl;
	cout << "v.normalize(): " << v.normalize().full_format() << endl;
	cout << "p.normalize(): " << p.normalize().full_format() << endl;
}
void vector4d_append() {
	Vector4d v1 = { 3, 6, -2, 0 };
	Vector4d p1 = { 1, 7, 5, 4 };

	cout << "v1: " << v1.full_format() << endl;
	cout << "p1: " << p1.full_format() << endl;
	cout << "v1.append(p1): " << endl << v1.append(p1) << endl;
}

void matrix4d_init() {
	Matrix4d m0, m00(7); //영행렬

	Matrix4d m1 = {
		{ 1, 0, 2, 2 }, //1행
		{ 0, 5 },		//2행: {0, 5, 0, 0}과 동일
		{ 0, 0, 3, 0 }, //3행
		{ 0, 0, 0, 1 }  //4행
	};

	Matrix4d m2(5); //4행 5열 행렬 선언
	m2[0] = { 0, -1, 3, 0 }; //1열
	m2[1] = { 0, 5, 0, 0 };  //2열
	m2[2] = { 2, 1, 1, 0 };  //3열
	m2[4] = { 2, 2, 0, 1 };  //5열

	Matrix4d m3 = {
		{ 0, 0 },
		{ -1, 5 },
		{ 3, 0 },
		{ 0, 0 }
	};

	Matrix4d m4 = {
		{ 0, 0 },
		{ -1, 5, 3, -4, 1, 9 },
		{ 3, 0, -1 },
		{ 0, 0, 0, 0, 0, 1 }
	};

	cout << "m0: " << endl << m0;
	cout << "m00: " << endl << m00;
	cout << "m1: " << endl << m1;
	cout << "m2: " << endl << m2;
	cout << "m3: " << endl << m3;
	cout << "m4: " << endl << m4;
}
void matrix4d_equals() {

	Matrix4d m1 = {
		{ 1, 0, 2, 2 }, //1행
		{ 0, 5 },		//2행: {0, 5, 0, 0}과 동일
		{ 0, 0, 3, 0 }, //3행
		{ 0, 0, 0, 1 }  //4행
	};

	Matrix4d m2(4);
	m2[0] = { 1, 0, 0, 0 }; //1열
	m2[1] = { 0, 5, 0, 0 };  //2열
	m2[2] = { 2, 0, 3, 0 };  //3열
	m2[3] = { 2, 0, 0, 1 };  //5열

	cout << "m1: " << endl << m1;
	cout << "m2: " << endl << m2;
	cout << "m1 == m2: " << (m1 == m2) << endl;
	cout << "m1 != m2: " << (m1 != m2) << endl;
}
void matrix4d_scala_product() {
	Matrix4d m1 = {
		{ 1, 0, 2, 2 },
		{ 0, 5, 0, 0 },
		{ 0, 0, 3, 0 },
		{ 0, 0, 0, 1 }
	};

	cout << "m1: " << endl << m1;
	cout << "m1 * 2: " << endl << (m1 * 2);
	cout << "-2 * m1: " << endl << (-2 * m1);
	cout << "2.5 * m1: " << endl << (2.5 * m1);
}
void matrix4d_negative() {
	Matrix4d m1 = {
		{ 1, 0, 2, 2 },
		{ 0, 5, 0, 0 },
		{ 0, 0, 3, 0 },
		{ 0, 0, 0, 1 }
	};

	cout << "m1: " << endl << m1;
	cout << "-m1: " << endl << (-m1);
}
void matrix4d_add() {
	Matrix4d m1 = {
		{ 1, 0,},
		{ 0, 5 },
		{ 0, 0 },
		{ 0, 0 }
	};

	Matrix4d m2 = {
		{ 2, 2 },
		{ 1, 2 },
		{ -1, 0 },
		{ 1, 1 }
	};

	Matrix4d m3 = {
		{1},
		{0},
		{1},
		{5}
	};

	cout << "m1: " << endl << m1;
	cout << "m2: " << endl << m2;
	cout << "m3: " << endl << m3;
	cout << "동일 차원 행렬의 덧셈 == m1 + m2: " << endl << (m1 + m2);
	try { 
		cout << "다른 차원 행렬의 덧셈 == m1 + m3: " << endl;
		cout << (m1 + m3); 
	} catch (exception& e) {
		cout << "m1 + m3: " << e.what() << endl;
	}
}
void matrix4d_subtract() {
	Matrix4d m1 = {
		{ 1, 0,},
		{ 0, 5 },
		{ 0, 0 },
		{ 0, 0 }
	};

	Matrix4d m2 = {
		{ 2, 2 },
		{ 1, 2 },
		{ -1, 0 },
		{ 1, 1 }
	};

	Matrix4d m3 = {
		{1},
		{0},
		{1},
		{5}
	};

	cout << "m1: " << endl << m1;
	cout << "m2: " << endl << m2;
	cout << "m3: " << endl << m3;
	cout << "동일 차원 행렬의 뺄셈 == m1 - m2: " << endl << (m1 - m2);
	try {
		cout << "다른 차원 행렬의 뺄셈 == m1 - m3: " << endl;
		cout << (m1 - m3);
	}
	catch (exception& e) {
		cout << "m1 + m3: " << e.what() << endl;
	}
}
void matrix4d_append() {
	Matrix4d m1 = {
		{ 1, 0,},
		{ 0, 5 },
		{ 0, 0 },
		{ 0, 0 }
	};

	Matrix4d m2 = {
		{ 2, 2 },
		{ 1, 2 },
		{ -1, 0 },
		{ 1, 1 }
	};

	Matrix4d m3 = {
		{1},
		{0},
		{1},
		{5}
	};

	cout << "m1: " << endl << m1;
	cout << "m2: " << endl << m2;
	cout << "m3: " << endl << m3;
	cout << "m1.append(m2): " << endl << m1.append(m2);
	cout << "m1.append(m3): " << endl << m1.append(m3);
}
void matrix4d_multiply() {
	Matrix4d m1 = {
		{ 1, 0, 2, 2 },
		{ 0, 5, 4, 1 },
		{ 0, 0, 3, 0 },
		{ 0, 0, 0, 1 }
	};
	Matrix4d m2 = {
		{ 1, 8,},
		{ 3, 5 },
		{ -1, 3 },
		{ 1, 0 }
	};

	Matrix4d m3 = {
		{ 0, 0, 1, -1, 5, 2 },
		{ -1, 5, 3, -4, 1, 9 },
		{ 3, 0, -1, 7, 5, 2 },
		{ 0, 0, 0, 0, 0, 1 }
	};

	Matrix4d m4(1);
	m4[0] = { 4, 0, 3, 0 };

	cout << "m1: " << endl << m1;
	cout << "m2: " << endl << m2;
	cout << "m3: " << endl << m3;
	cout << "m4: " << endl << m4;

	cout << "m1 * m2: " << endl << (m1 * m2);
	cout << "m1 * m3: " << endl << (m1 * m3);
	cout << "m1 * m4: " << endl << (m1 * m4);

	try 
	{
		cout << "m2 * m1: " << endl;
		cout << m2 * m1;
	} catch (exception& e) {
		cout << "m2 * m1: " << e.what() << endl;
	}
	try {
		cout << "m3 * m1: " << endl;
		cout << m3 * m1;
	} catch (exception& e) {
		cout << "m3 * m1: " << e.what() << endl;
	}
}

void vector_and_matrix_append() {
	Vector4d v = { 1, -4, 5, 2 };
	Matrix4d m = {
		{ 1, 0, 2, 2 },
		{ 0, 5, 4, 1 },
		{ 0, 0, 3, 0 },
		{ 0, 0, 0, 1 }
	};

	cout << "v: " << v << endl;
	cout << "m: " << endl << m << endl;
	cout << "v.append(m): " << endl << v.append(m) << endl;
	cout << "m.append(v): " << endl << m.append(v) << endl;
}
void vector_and_matrix_multiply() {
	Vector4d v = { 3, -1, 2, 0 };
	Vector4d p = { 1, -4, 5, 2 };
	Matrix4d m = {
		{ 1, 0, 2, 2 },
		{ 0, 5, 4, 1 },
		{ 0, 0, 3, 0 },
		{ 0, 0, 0, 1 }
	};

	cout << "v: " << v.full_format() << endl;
	cout << "p: " << p.full_format() << endl;
	cout << "m: " << endl << m << "\n\n";

	cout << "m * v: " << Vector4d(m * v).full_format() << endl;
	cout << "m * p: " << Vector4d(m * p).full_format() << endl;
	cout << "m * (v + p): " << Vector4d(m * (v + p)).full_format() << endl;
}

void vector4d_move_constructor() {
	Vector4d v0 = { 2, 2, 2, 0 };
	Vector4d v1 = { 1, 1, 1, 0 };
	Vector4d v2 = { -2, -2, -2, 0 };
	
	cout << "v0: " << v0 << endl;
	cout << "v1: " << v1 << endl;
	cout << "v2: " << v2 << endl;

	Vector4d v3 = { 0, 0, 0, 0 };
	v3 = (v1 + v2) * v1;
	cout << "v3: " << v3 << endl;
}
void matrix4d_move_constructor() {

}


/***************  unit test executation  ***************/
void register_tests(vector<pair<void (*)(void), string>>& t) {

	//t.push_back({ vector4d_init/* test func */, "vector4d_init"/* test name */ });
	//t.push_back({ vector4d_equals, "vector4d_equals" });
	//t.push_back({ vector4d_scala_product, "vector4d_scala_product" });
	//t.push_back({ vector4d_add, "vector4d_add" });
	//t.push_back({ vector4d_subtract, "vector4d_subtract" });
	//t.push_back({ vector4d_cross, "vector4d_cross" });
	//t.push_back({ vector4d_dot, "vector4d_dot" });
	//t.push_back({ vector4d_full_format, "vector4d_full_format" });
	//t.push_back({ vector4d_norm, "vector4d_norm" });
	//t.push_back({ vector4d_normalize, "vector4d_normalize" });
	//t.push_back({ vector4d_append, "vector4d_append" });

	//t.push_back({ matrix4d_init, "matrix4d_init" });
	//t.push_back({ matrix4d_equals, "matrix4d_equals" });
	//t.push_back({ matrix4d_scala_product, "matrix4d_scala_product" });
	//t.push_back({ matrix4d_negative, "matrix4d_negative" });
	//t.push_back({ matrix4d_add, "matrix4d_add" });
	//t.push_back({ matrix4d_subtract, "matrix4d_subtract" });
	//t.push_back({ matrix4d_append, "matrix4d_append" });
	//t.push_back({ matrix4d_multiply, "matrix4d_multiply" });

	//t.push_back({ vector_and_matrix_append, "vector_and_matrix_append" });
	//t.push_back({ vector_and_matrix_multiply, "vector_and_matrix_multiply" });
	t.push_back({ vector4d_move_constructor, "vector4d_move_constructor" });
	t.push_back({ matrix4d_move_constructor, "matrix4d_move_constructor" });
}

void unit_test() {
	vector<pair<void (*)(void), string>> unit_test;
	register_tests(unit_test);

	cout << "************************************" << endl;
	cout << "************************************" << endl;
	cout << "****                            ****" << endl;
	cout << "****     MyMatrix Unit Test     ****" << endl;
	cout << "****                            ****" << endl;
	cout << "************************************" << endl;
	cout << "************************************" << "\n\n\n";

	for (size_t i = 0; i < unit_test.size(); i++) {
		cout << "------------------------------------------\n";
		cout << "< Test: " << unit_test[i].second << " >\n";
		unit_test[i].first();
		cout << "\n\n\n";
	}
}

}}

//int main() { jangan_lee_my_matrix::test::unit_test(); }