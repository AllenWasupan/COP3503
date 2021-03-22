
#include <iostream>
#include <iomanip>
#include "Shapes.h"
#include <random>
using namespace std;

Shape::~Shape() {

}
Shape2D::~Shape2D() {

}
void Shape2D::ShowArea() const {
	cout << GetName2D() << endl;
	cout << Area() << endl;
}

//Overloads for 2d
bool Shape2D::operator>(const Shape2D& rhs) const {
	if (Area() > rhs.Area()) {
		return true;
	}
	else {
		return false;
	}
}
bool Shape2D::operator<(const Shape2D& rhs) const {
	if (Area() < rhs.Area()) {
		return true;
	}
	else {
		return false;
	}
}
bool Shape2D::operator==(const Shape2D& rhs) const {
	if (Area() == rhs.Area()) {
		return true;
	}
	else {
		return false;
	}
}


Square::Square() {
	length = 0;
}
Square::Square(float length) {
	this->length = length;
}
void Square::Scale(float scaleFactor) {
	length *= scaleFactor;
}
void Square::Display() const {
	cout << GetName2D() << Area() << endl;
	cout << "Length of a side: " << length << endl << endl;
}
float Square::Area() const {
	float area = length * length;
	return area;
}
string Square::GetName2D() const {
	return "The area of the Square is : ";
}


Triangle::Triangle() {
	base = 0;
	height = 0;
}
Triangle::Triangle(float base, float height) {
	this->base = base;
	this->height = height;
	
}
float Triangle::Area() const {
	float area = .5 * base * height;
	return area;
}
void Triangle::Scale(float scaleFactor) {
	base *= scaleFactor;
	height *= scaleFactor;
}
string Triangle::GetName2D() const {
	return "The area of the Triangle is : ";
}
void Triangle::Display() const {
	cout << GetName2D() << Area() << endl;
	cout << "Base: " << base << endl;
	cout << "Height: " << height << endl;
}

Circle::Circle() {
	radius = 0;
}
Circle::Circle(float radius) {
	this->radius = radius;
}
float Circle::Area() const {
	float area = PI * radius * radius;
	return area;
}
void Circle::Scale(float scaleFactor) {
	radius *= scaleFactor;
}
string Circle::GetName2D() const {
	return "The area of the Circle is : ";
}
void Circle::Display() const {
	cout << GetName2D() << Area() << endl;
	cout << "Radius: " << radius << endl;
}


Shape3D::~Shape3D() {

}
void Shape3D::ShowVolume() const {
	cout << GetName3D() << endl;
	cout << Volume() << endl;
}
bool Shape3D::operator>(const Shape3D& rhs) const {
	if (Volume() > rhs.Volume()) {
		return true;
	}
	else {
		return false;
	}
}
bool Shape3D::operator<(const Shape3D& rhs) const {
	if (Volume() < rhs.Volume()) {
		return true;
	}
	else {
		return false;
	}
}
bool Shape3D::operator==(const Shape3D& rhs) const {
	if (Volume() == rhs.Volume()) {
		return true;
	}
	else {
		return false;
	}
}

TriangularPyramid::TriangularPyramid() {
	heightt = 0;
	length = 0;
	height = 0;
}


void TriangularPyramid::Scale(float scaleFactor) {
	heightt *= scaleFactor;
	length *= scaleFactor;
	height *= scaleFactor;
	Triangle::Scale(scaleFactor);
}
float TriangularPyramid::Volume() const {
	
	float volume = .333333333333333333333333333333333 * Triangle::Area() * heightt;
	return volume;
}
string TriangularPyramid::GetName3D() const {
	return "The volume of the TriangularPyramid is : ";
}
void TriangularPyramid::Display() const {
	cout << GetName3D() << Volume() << endl;
	cout << "The height is: " << heightt << endl;
	Triangle::Display();

}


Cylinder::Cylinder() {
	height = 0;
	radius = 0;
}


void Cylinder::Scale(float scaleFactor) {
	height *= scaleFactor;
	radius *= scaleFactor;
	Circle::Scale(scaleFactor);
}
float Cylinder::Volume() const {
	float volume = Circle::Area() * height;
	return volume;
}
string Cylinder::GetName3D() const {
	return "The volume of the Cylinder is : ";
}
void Cylinder::Display() const {
	cout << GetName3D() << Volume() << endl;
	cout << "The height is: " << height << endl;
	Circle::Display();
}

Sphere::Sphere() {
	radius = 0;
}

void Sphere::Scale(float scaleFactor) {
	radius *= scaleFactor;
	Circle::Scale(scaleFactor);
}
float Sphere::Volume() const {
	float volume = 1.33333333333 * radius * Circle::Area();
	return volume;
}
string Sphere::GetName3D() const {
	return "The volume of the Sphere is : ";
}
void Sphere::Display() const {
	cout << GetName3D() << Volume() << endl;
	Circle::Display();
}