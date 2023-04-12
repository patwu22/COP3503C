#pragma once
#include <string>
#include <iostream>
#define PI 3.14159f
using namespace std;

class Shape
{
public:
    virtual void Scale(float scaleFactor) = 0;
    virtual void Display() const = 0;
    virtual ~Shape(){}
};

class Shape2D : virtual public Shape
{
public:
    virtual float Area() const = 0;
    void ShowArea() const;
    virtual string GetName2D() const = 0;
    bool operator>(const Shape2D &rhs) const;
    bool operator<(const Shape2D &rhs) const;
    bool operator==(const Shape2D &rhs) const;
};

class Shape3D : virtual public Shape
{
public:
    virtual float Volume() const = 0;
    void ShowVolume() const;
    virtual string GetName3D() const = 0;
    bool operator>(const Shape3D &rhs) const;
    bool operator<(const Shape3D &rhs) const;
    bool operator==(const Shape3D &rhs) const;
};

class Square : public Shape2D
{
    float side = 0;

public:
    Square() {}
    Square(float len)
    {
        side = len;
    }
    float Area() const;
    string GetName2D() const;
    void Display() const;
    void Scale(float scaleFactor);
};

class Triangle : public Shape2D
{
    float base = 0;
    float height = 0;

public:
    Triangle() {}
    Triangle(float len1, float len2)
    {
        base = len1;
        height = len2;
    }
    float Area() const;
    string GetName2D() const;
    void Display() const;
    void Scale(float scaleFactor);
};

class Circle : public Shape2D
{
    float radius = 0;

public:
    Circle() {}
    Circle(float len)
    {
        radius = len;
    }
    float Area() const;
    string GetName2D() const;
    void Display() const;
    void Scale(float scaleFactor);
};

class TriangularPyramid : public Shape3D, private Triangle
{
    float height = 0;

public:
    TriangularPyramid() : Triangle() {}
    TriangularPyramid(float len1, float len2, float len3) : Triangle(len2, len3)
    {
        height = len1;
    }
    float Volume() const;
    string GetName3D() const;
    void Display() const;
    void Scale(float scaleFactor);
};

class Cylinder : public Shape3D, private Circle
{
    float height = 0;

public:
    Cylinder() : Circle() {}
    Cylinder(float len1, float len2) : Circle(len2)
    {
        height = len1;
    }
    float Volume() const;
    string GetName3D() const;
    void Display() const;
    void Scale(float scaleFactor);
};

class Sphere : public Shape3D, private Circle
{
    float radius = 0;

public:
    Sphere() : Circle() {}
    Sphere(float len1) : Circle(len1)
    {
        radius = len1;
    }
    float Volume() const;
    string GetName3D() const;
    void Display() const;
    void Scale(float scaleFactor);
};
