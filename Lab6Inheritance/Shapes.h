#pragma once
#include <iostream>
#include <iomanip>
#include <random>
using namespace std;
#define PI 3.14159f

//ABC
class Shape {
	
public:
	virtual void Scale(float scaleFactor) = 0;
	virtual void Display() const = 0;
	virtual ~Shape() = 0;
};
//
class Shape2D : virtual public Shape {

public:
	~Shape2D();
	virtual float Area() const = 0;
	void ShowArea() const;
	virtual string GetName2D() const = 0;
	bool operator>(const Shape2D& rhs) const;
	bool operator<(const Shape2D& rhs) const;
	bool operator==(const Shape2D& rhs) const;
};


class Square : public Shape2D {

	float length;
public:
	Square();
	Square(float length);

	void Scale(float scaleFactor);
	void Display() const;

	float Area() const;
	string GetName2D() const;
};

class Triangle : public Shape2D {

	float base;
	float height;
public:
	Triangle();
	Triangle(float base, float height);
	
	void Scale(float scaleFactor);
	float Area() const;
	string GetName2D() const;
	void Display() const;
};

class Circle : public Shape2D {
	float radius;
public:
	Circle();
	Circle(float radius);
	
	void Scale(float scaleFactor);
	float Area() const;
	string GetName2D() const;
	void Display() const;
};


class Shape3D : virtual public Shape {

public:
	~Shape3D();
	virtual float Volume() const = 0;
	void ShowVolume() const;
	virtual string GetName3D() const = 0;
	bool operator>(const Shape3D& rhs) const;
	bool operator<(const Shape3D& rhs) const;
	bool operator==(const Shape3D& rhs) const;
};

class TriangularPyramid : public Shape3D, private Triangle {
	float heightt;
	float length;
	float height;
	Triangle tri;
public:

	TriangularPyramid();
	TriangularPyramid(float heightt, float length, float height) : Triangle(length, height) {
		this->heightt = heightt;
		this->length = length;
		this->height = height;
	}
	void Scale(float scaleFactor);
	float Volume() const;
	string GetName3D() const;
	void Display() const;
	
	
};

class Cylinder : public Shape3D, private Circle {
	float height;
	float radius;

public:
	Cylinder();
	Cylinder(float height, float radius) : Circle(radius) {
		this->height = height;
		this->radius = radius;
	}

	void Scale(float scaleFactor);
	float Volume() const;
	string GetName3D() const;
	void Display() const;
};
class Sphere : public Shape3D, private Circle {
	float radius;

public:
	Sphere();
	Sphere(float radius) : Circle(radius) {
		this->radius = radius;
	}

	void Scale(float scaleFactor);
	float Volume() const;
	string GetName3D() const;
	void Display() const;
};
