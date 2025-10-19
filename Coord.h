#pragma once
#include "Header.h"

template <typename T>
class Coord
{
	private:
		T x;
		T y;

	public:
		Coord(T x = 0, T y = 0);
		~Coord();

		Coord<T> getXY();
		T getX();
		T getY();
		void setXY(T x, T y);

		void operator=(Coord<T> outro);
		void operator+=(Coord<T> outro);
		void operator-=(Coord<T> outro);
		void operator/=(Coord<T> outro);
		void operator*=(Coord<T> outro);
		void operator*=(double multiplicador);
		void operator/=(double divisor);

		Coord<T> operator+(Coord<T> outro);
		Coord<T> operator-(Coord<T> outro);
		Coord<T> operator/(Coord<T> outro);
		Coord<T> operator*(Coord<T> outro);
		Coord<T> operator*(double multiplicador);
		Coord<T> operator/(double divisor);

};

template<typename T>
Coord<T>::Coord(T x, T y) :
	x(x), y(y)
{}

template<typename T>
Coord<T>::~Coord() {
	x = 0;
	y = 0;
}

template<typename T>
void Coord<T>::setXY(T x, T y) {
	this->x = x;
	this->y = y;
}

template<typename T>
Coord<T> Coord<T>::getXY() {
	Coord<T> t;
	t.setXY(x, y);

	return t;
}

template<typename T>
T Coord<T>::getX() {
	return x;
}

template<typename T>
T Coord<T>::getY() {
	return y;
}

template<typename T>
void Coord<T>::operator=(Coord<T> outro) {
	x = outro.getX();
	y = outro.getY();
}

template<typename T>
void Coord<T>::operator+=(Coord<T> outro) {
	x += outro.getX();
	y += outro.getY();
}

template<typename T>
void Coord<T>::operator-=(Coord<T> outro) {
	x -= outro.getX();
	y -= outro.getY();
}

template<typename T>
void Coord<T>::operator/=(Coord<T> outro) {
	x /= outro.getX();
	y /= outro.getY();
}

template<typename T>
void Coord<T>::operator*=(Coord<T> outro) {
	x *= outro.getX();
	y *= outro.getY();
}

template<typename T>
void Coord<T>::operator*=(double multiplicador) {
	x *= multiplicador;
	y *= multiplicador;
}

template<typename T>
void Coord<T>::operator/=(double divisor){
	x /= divisor;
	y /= divisor;
}

template<typename T>
Coord<T> Coord<T>::operator+(Coord<T> outro) {
	Coord<T> t;
	t.setXY(x + outro.getX(), y + outro.getY());

	return t;
}

template<typename T>
Coord<T> Coord<T>::operator-(Coord<T> outro) {
	Coord<T> t;
	t.setXY(x - outro.getX(), y - outro.getY());

	return t;
}

template<typename T>
Coord<T> Coord<T>::operator/(Coord<T> outro) {
	Coord<T> t;
	t.setXY(x / outro.getX(), y / outro.getY());

	return t;
}

template<typename T>
Coord<T> Coord<T>::operator*(Coord<T> outro) {
	Coord<T> t;
	t.setXY(x * outro.getX(), y * outro.getY());

	return t;
}

template<typename T>
Coord<T> Coord<T>::operator*(double multiplicador) {
	Coord<T> t;
	t.setXY(x * multiplicador, y * multiplicador);

	return t;
}

template<typename T>
Coord<T> Coord<T>::operator/(double divisor) {
	Coord<T> t;
	t.setXY(x / divisor, y / divisor);

	return t;
}