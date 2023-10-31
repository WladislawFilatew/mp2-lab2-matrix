// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <string>
#include <conio.h>
#include <functional>
#include "tmatrix.h"



int vibor(int kol);
int variant(int kol, ...);
TDynamicVector<int> Sozd_vector();
void Random_vector(TDynamicVector<int>& A);
void vivod_vector(TDynamicVector<int> A);
void Scalar_vector(TDynamicVector<int> A);
void Vector_vector(TDynamicVector<int> A);
void panel_vector();
void Random_matrix(TDynamicMatrix<int>& A);

TDynamicMatrix<int> Sozd_Matrix();
void Random_matrix(TDynamicMatrix<int>& A);
void vivod_matrix(TDynamicMatrix<int> A);
void Scalar_matrix(TDynamicMatrix<int> A);
void Vector_matrix(TDynamicMatrix<int> A);
void Matrix_matrix(TDynamicMatrix<int> A);

void Matrix_proisvedenie(TDynamicMatrix<int> A) {
	TDynamicMatrix<int> B(A.size());
	Random_matrix(B);
	Timer time;
	B = A * B;
	time.set();
	system("pause");
}

void panel_matrix() {
	int v;
	TDynamicMatrix<int> A;
	do {
		v = variant(7, "Работа с матрицами", "Создание", "Вывод", "Скалярнае операции", "Векторные операции","Матричные операции","Время умножения", "Выход");
		if (v == 1) A = Sozd_Matrix();
		if (v == 2) vivod_matrix(A);
		if (v == 3) Scalar_matrix(A);
		if (v == 4) Vector_matrix(A);
		if (v == 5) Matrix_matrix(A);
		if (v == 6) Matrix_proisvedenie(A);
	} while (v != 7);
}


int main()
{
	setlocale(LC_ALL, "Rus");
	int v;
	do {
		v = variant(3, "Проверка", "Вектора", "Матрицы", "Выход");
		if (v == 1) panel_vector();
		if (v == 2) panel_matrix();
	} while (v != 3);
}





int variant(int kol, ...) {
	system("cls");
	int* p = (&kol + 1);
	cout << " " << (char*)*(p) << ":" << endl;
	for (int i = 1; i <= kol; i++) {
		cout << i << ")" << (char*)*(p + i) << endl;
	}
	return vibor(kol);
}

int vibor(int kol) {
	char a;
	do {
		a = _getch() - 48;
	} while (!(a >= 1 && a <= kol));
	return (int)a;
}



void panel_vector() {
	int v;
	TDynamicVector<int> A;
	do {
		v = variant(5, "Работа с вектором", "Создание", "Вывод", "Скалярнае операции", "Векторные операции", "Выход");
		if (v == 1) A = Sozd_vector();
		if (v == 2) vivod_vector(A);
		if (v == 3) Scalar_vector(A);
		if (v == 4) Vector_vector(A);

	} while (v != 5);
}

TDynamicVector<int> Sozd_vector() {
	system("cls");
	cout << "Введите размер вектора: ";
	int n; cin >> n;
	TDynamicVector<int> A(n);
	if (n <= 10) {
		int v = variant(2, "Заполнение", "Автоматически","Руками");
		if (v == 1) {
			Random_vector(A);
			cout << "Вектор:" << endl << A << endl;
			system("pause");
		}
		else {
			system("cls");
			cout << "Введите вектор:" << endl;
			for (int i = 0; i < n; i++) {
				cin >> A[i];
			}
		}
	}
	else {
		Random_vector(A);
	}
	return A;
}

void Random_vector(TDynamicVector<int>& A) {
	system("cls");
	int min, max;
	cout << "Введите минимальный размер элемента: "; cin >> min;
	cout << "Введите максимальный размер элемента: "; cin >> max;
	for (int i = 0; i < A.size(); i++) {
		A[i] = (rand() % (max - min + 1)) + min;
	}
}

void vivod_vector(TDynamicVector<int> A) {
	system("cls");
	if (A.size() <= 10)
		cout << "Вектор:\n" << A << endl;
	else
		cout << "Размер вектора слишком большой" << endl;
	system("pause");
}

void Scalar_vector(TDynamicVector<int> A) {
	int k;
	system("cls");
	cout << "Введите элемент: "; cin >> k;
	int v = variant(4, "Скалярные операции", "Сложение", "Разность", "Умножение", "Выход");
	system("cls");
	if (v == 1) cout << "A + " << k << " = " << A + k << endl;
	if (v == 2) cout << "A - " << k << " = " << A - k << endl;
	if (v == 3) cout << "A * " << k << " = " << A * k << endl;
	system("pause");
}

void Vector_vector(TDynamicVector<int> A) {
	TDynamicVector<int> B(A.size());
	system("cls");
	cout << "Введите вектор:" << endl;
	for (int i = 0; i < A.size(); i++) {
		cin >> B[i];
	}
	int v = variant(4, "Векторные операции", "Сложение", "Разность", "Умножение", "Выход");
	system("cls");
	if (v == 1) cout << "A + B = " << A + B << endl;
	if (v == 2) cout << "A - B = " << A - B << endl;
	if (v == 3) cout << "A * B = " << A * B << endl;
	system("pause");
}

TDynamicMatrix<int> Sozd_Matrix() {
	system("cls");
	cout << "Введите размер матрицы: ";
	int n; cin >> n;
	TDynamicMatrix<int> A(n);
	if (n <= 5) {
		int v = variant(2, "Заполнение", "Автоматически", "Руками");
		if (v == 1) {
			Random_matrix(A);
			cout << "Матрица:" << endl << A << endl;
			system("pause");
		}
		else {
			system("cls");
			cout << "Введите матрицу:" << endl;
			for (int i = 0; i < n; i++) {
				cin >> A[i];
			}
		}
	}
	else {
		Random_matrix(A);
	}
	return A;
}
void Random_matrix(TDynamicMatrix<int>& A) {
	system("cls");
	int min, max;
	cout << "Введите минимальный размер элемента: "; cin >> min;
	cout << "Введите максимальный размер элемента: "; cin >> max;
	for (int i = 0; i < A.size(); i++) {
		for (int j = 0; j < A.size(); j++)
			A[i][j] = (rand() % (max - min + 1)) + min;
	}
}
void vivod_matrix(TDynamicMatrix<int> A) {
	system("cls");
	if (A.size() <= 5)
		cout << "Матрица:\n" << A << endl;
	else
		cout << "Размер Матрицы слишком большой" << endl;
	system("pause");
}

void Scalar_matrix(TDynamicMatrix<int> A) {
	int k;
	system("cls");
	cout << "Введите элемент: "; cin >> k;
	int v = variant(2, "Скалярные операции", "Умножение", "Выход");
	system("cls");
	if (v == 1) cout << "A * " << k << " = \n" << A * k << endl;
	system("pause");
}

void Vector_matrix(TDynamicMatrix<int> A) {
	TDynamicVector<int> B(A.size());
	system("cls");
	cout << "Введите вектор:" << endl;
	for (int i = 0; i < A.size(); i++) {
		cin >> B[i];
	}
	int v = variant(2, "Векторные операции", "Умножение", "Выход");
	system("cls");
	if (v == 1) cout << "A * B = " << A * B << endl;
	system("pause");
}

void Matrix_matrix(TDynamicMatrix<int> A) {
	TDynamicMatrix<int> B(A.size());
	system("cls");
	cout << "Введите матрицу:" << endl;
	for (int i = 0; i < A.size(); i++) {
		cin >> B[i];
	}
	int v = variant(4, "Матричные операции", "Сложение", "Разность", "Умножение", "Выход");
	system("cls");
	if (v == 1) cout << "A + B = " << endl << A + B << endl;
	if (v == 2) cout << "A - B = " << endl << A - B << endl;
	if (v == 3) cout << "A * B = " << endl << A * B << endl;
	system("pause");
}