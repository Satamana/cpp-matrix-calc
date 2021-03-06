#pragma once
#include "stdafx.h"
template <typename t>
class matrix
{
	t **arr = nullptr;
	size_t r = 0;
	size_t c = 0;
public:
	matrix() = default;
	matrix(const size_t &row, const size_t &col) : r(row), c(col)
	{
		this->arr = (t**)malloc(this->r * sizeof(t*));
		for (size_t row = 0; row < this->r; row++)
		{
			this->arr[row] = (t*)malloc(this->c * sizeof(t));
			for (size_t col = 0; col < this->c; col++) this->arr[row][col] = 0;
		}
	}
	matrix(const matrix &ob) : r(ob.r), c(ob.c)
	{
		this->arr = (t**)malloc(this->r * sizeof(t*));
		for (size_t row = 0; row < this->r; row++)
		{
			this->arr[row] = (t*)malloc(this->c * sizeof(t));
			for (size_t col = 0; col < this->c; col++) this->arr[row][col] = ob.arr[row][col];
		}
	}
	matrix& operator=(const matrix &ob)
	{
		if (this->arr) 
		{
			for (size_t row = 0; row < this->r; row++) free(this->arr[row]);
			free(this->arr);
		}
		this->r = ob.r;
		this->c = ob.r;
		this->arr = (t**)malloc(this->r * sizeof(t*));
		for (size_t row = 0; row < this->r; row++)
		{
			this->arr[row] = (t*)malloc(this->c * sizeof(t));
			for (size_t col = 0; col < this->c; col++) this->arr[row][col] = ob.arr[row][col];
		}
		return *this;
	}
	matrix operator+(const matrix &ob)
	{
		if (this->r == ob.r && this->c == ob.c)
		{
			matrix tmp(this->r, this->c);
			for (size_t row = 0; row < this->r; row++)
			{
				for (size_t col = 0; col < this->c; col++) tmp.arr[row][col] = this->arr[row][col] + ob.arr[row][col];
			}
			return tmp;
		}
		else return matrix();
	}
	matrix operator-(const matrix &ob)
	{
		if (this->r == ob.r && this->c == ob.c)
		{
			matrix tmp(this->r, this->c);
			for (size_t row = 0; row < this->r; row++)
			{
				for (size_t col = 0; col < this->c; col++) tmp.arr[row][col] = this->arr[row][col] - ob.arr[row][col];
			}
			return tmp;
		}
		else return matrix();
	}
	matrix operator*(const matrix &ob)
	{
		if (this->c == ob.r)
		{
			matrix tmp(this->r, ob.c);
			for (size_t row = 0; row < this->r; row++)
			{
				for (size_t col = 0; col < ob.c; col++)
				{
					for (size_t k = 0; k < ob.r; k++) tmp.arr[row][col] += arr[row][k] * ob.arr[k][col];
				}
			}
			return tmp;
		}
		else matrix();
	}
	matrix& operator*=(t num)
	{
		for (size_t row = 0; row < this->r; row++)
		{
			for (size_t col = 0; col < this->c; col++) this->arr[row][col] *= num;
		}
		return *this;
	}
	matrix operator/(t o)
	{
		if (this->r == this->c)
		{
			double n1 = 0, ninf = 0;
			matrix A0 = *this;
			for (size_t row = 0; row < this->r; row++)
			{
				double colsum = 0, rowsum = 0;
				for (size_t col = 0; col < this->c; col++)
				{
					rowsum += fabs(A0.arr[row][col]);
					colsum += fabs(A0.arr[col][row]);
				}
				n1 = (colsum > n1) ? colsum : n1;
				ninf = (rowsum > ninf) ? rowsum : ninf;
			}
			A0 = A0.transpose();
			A0 *= (1. / (n1 * ninf));
			matrix E2(this->r, this->c);
			for (size_t row = 0; row < this->r; row++)
			{
				for (size_t col = 0; col < this->c; col++)
				{
					if (row == col) E2.arr[row][col] = 2;
				}
			}
			matrix inv = A0;
			double EPS = 0.001;
			if (det(*this))
			{
				while (fabs(det(this->operator*(inv)) - 1) >= EPS)
				{
					matrix prev = inv;
					inv = *this * prev;
					inv *= -1;
					inv = inv + E2;
					inv = prev * inv;
				}
				return inv;
			}
			else std::cout << "Матрица вырождена. Обратной матрицы нет." << std::endl;
		}
		else std::cout << "Матрица не квадратная." << std::endl;
		return matrix();
	}
	matrix transpose()
	{
		matrix tmp = *this;
		for (size_t row = 0; row < this->r; row++)
		{
			for (size_t col = 0; col < this->c; col++) tmp.arr[row][col] = this->arr[col][row];
		}
		return tmp;
	}
	double det(const matrix &ob)
	{
		double det = 0;
		if (this->r == this->c)
		{
			matrix tmp = ob;
			for (size_t step = 0; step < this->r - 1; step++)
			{
				for (size_t row = step + 1; row < this->r; row++)
				{
					double coef = -tmp.arr[row][step] / tmp.arr[step][step];
					for (size_t col = step; col < this->c; col++) tmp.arr[row][col] += tmp.arr[step][col] * coef;
				}
			}
			det = 1;
			for (size_t i = 0; i < this->r; i++) det *= tmp.arr[i][i];
		}
		else std::cout << "Матрица не квадратная." << std::endl;
		return det;
	}
	void init()
	{
		for (size_t row = 0; row < this->r; row++)
		{
			for (size_t col = 0; col < this->c; col++) this->arr[row][col] = rand() % 10;
		}
	}
	t max()
	{
		t max = this->arr[0][0];
		for (size_t row = 0; row < this->r; row++)
		{
			for (size_t col = 0; col < this->c; col++)
			{
				if (this->arr[row][col] > max) max = this->arr[row][col];
			}
		}
		return max;
	}
	t min()
	{
		t min = this->arr[0][0];
		for (size_t row = 0; row < this->r; row++)
		{
			for (size_t col = 0; col < this->c; col++)
			{
				if (this->arr[row][col] < min) min = this->arr[row][col];
			}
		}
		return min;
	}
	friend std::ostream & operator<<(std::ostream &os, matrix &ob)
	{
		for (size_t row = 0; row < ob.r; row++)
		{
			for (size_t col = 0; col < ob.c; col++) os << std::left << std::setw(7) << std::setprecision(3) << ob.arr[row][col];
			os << std::endl;
		}
		os << std::endl;
		return os;
	}
	friend std::istream & operator>>(std::istream &os, matrix &ob)
	{
		std::cout << "Введите матрицу:" << std::endl << std::endl;
		for (size_t row = 0; row < ob.r; row++)
		{
			for (size_t col = 0; col < ob.c; col++)
			{
				std::cout << "a" << row + 1 << col + 1 << ": ";
				std::cin >> ob.arr[row][col];
			}
			std::cout << std::endl;
		}
		return os;
	}
	~matrix()
	{
		for (size_t row = 0; row < this->r; row++) free(this->arr[row]);
		free(this->arr);
	}
};