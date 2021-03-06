#include "stdafx.h"
#include "matrix.h"
void main()
{
	setlocale(0, "rus");
	matrix<double> a(3, 3), b(3,3);
	a.init();
	b.init();
	std::cout << "Первая матрица:" << std::endl << a;
	std::cout << "Вторая матрица:" << std::endl << b;
	std::cout << "Сложение:" << std::endl << a + b;
	std::cout << "Вычитание:" << std::endl << a - b;
	std::cout << "Произведение:" << std::endl << a * b;
	std::cout << "Обратная матрица:" << std::endl << a / 0;
	std::cout << "Максимальный элемент: " <<  a.max() << std::endl;
	std::cout << "Минимальный элемент: " << a.min() << std::endl << std::endl;
	std::cin >> a;
	std::cout << "Вывод заполненной матрицы:" << std::endl << a;
}