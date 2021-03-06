// MatStat.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

using namespace std;

#pragma region Arr init
double* CreateArr(int n)
{
	double* arr = (double*)malloc(n * sizeof(double));;
	return arr;
}

void FreeArr(double* arr)
{
	free(arr);
}

double* X(double* arr, int n)
{
	double a[] = { 3.0,3.2,5.0,3.0,4.0,5.0,4.0,4.0,3.0,4.8 };

	for (int i = 0; i < n; i++)
	{
		arr[i] = a[i];
	}

	return arr;
}

double* Y(double* arr, int n)
{
	double a[] = { 8,7.5,7,8,7,6,7.5,7,7.5,6.5 };

	for (int i = 0; i < n; i++)
	{
		arr[i] = a[i];
	}

	return arr;
}

#pragma endregion
#pragma region Funcs
double ExpectedValue(double* arr, int n)
{
	double expectedValue = 0;
	for (int i = 0; i < n; i++)
	{
		expectedValue += arr[i];
	}
	return expectedValue / n;
}

double Dispersion(double* arr, int n)
{
	double expectedValue = ExpectedValue(arr, n);
	double sigma = 0;
	for (int i = 0; i < n; i++)
	{
		sigma += (arr[i] - expectedValue)*(arr[i] - expectedValue);
	}
	sigma /= n;
	return sigma;
}

double Mu(double* x, double* y, int n)
{
	double mu = 0;
	double expX = ExpectedValue(x, n);
	double expY = ExpectedValue(y, n);

	for (int i = 0; i < n; i++)
	{
		mu += (x[i] - expX) * (y[i] - expY);
	}

	mu /= n;

	return mu;
}

double Sigma(double* arr, int n)
{
	return sqrt(Dispersion(arr, n));
}

double R(double* x, double* y, int n)
{
	double mu = Mu(x, y, n);
	double sigmaX = Sigma(x,n);
	double sigmaY = Sigma(y,n);
	mu /= sigmaX * sigmaY;
	return mu;
}

double aXY(double* x, double* y, int n)
{
	return R(x,y,n) * (Sigma(x,n) / Sigma(y, n));
}
double aYX(double* x, double* y, int n)
{
	return R(x, y, n) * (Sigma(y, n) / Sigma(x, n));
}
double bYX(double* x, double* y, int n)
{
	double byx = ExpectedValue(y, n) - aYX(x, y, n) * ExpectedValue(x, n);
	return byx;
}
double bXY(double* x, double* y, int n)
{
	double bxy = ExpectedValue(x, n) - aXY(x, y, n) * ExpectedValue(y, n);
	return bxy;
}
void yCoeff(double* x, double* y, int n)
{
	cout << aYX(x,y,n) << "x+" << bYX(x,y,n) << endl;
}
void xCoeff(double* x, double* y, int n)
{
	cout << aXY(x, y, n) << "y+" << bXY(x, y, n) << endl;
}
#pragma endregion



int main()
{
	const int n = 10;

	double* x = X(CreateArr(n), n);
	double* y = Y(CreateArr(n), n);
	
	double r = R(x, y, n);

	xCoeff(x, y, n);
	yCoeff(x, y, n);

	cout << r << endl;

	_getch();
}

