#include "Shapes.h"

void Shape2D::ShowArea() const
{
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
}

bool Shape2D::operator>(const Shape2D &rhs) const
{
    if (this->Area() > rhs.Area())
        return true;
    return false;
}

bool Shape2D::operator<(const Shape2D &rhs) const
{
    if (this->Area() < rhs.Area())
        return true;
    return false;
}

bool Shape2D::operator==(const Shape2D &rhs) const
{
    if (this->Area() == rhs.Area())
        return true;
    return false;
}

void Shape3D::ShowVolume() const
{
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
}

bool Shape3D::operator>(const Shape3D &rhs) const
{
    if (this->Volume() > rhs.Volume())
        return true;
    return false;
}

bool Shape3D::operator<(const Shape3D &rhs) const
{
    if (this->Volume() < rhs.Volume())
        return true;
    return false;
}

bool Shape3D::operator==(const Shape3D &rhs) const
{
    if (this->Volume() == rhs.Volume())
        return true;
    return false;
}

float Square::Area() const
{
    return side * side;
}

string Square::GetName2D() const
{
    return "Square";
}

void Square::Display() const
{
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Length of a side: " << side << endl;
}

void Square::Scale(float scaleFactor)
{
    side *= scaleFactor;
}

float Triangle::Area() const
{
    return 0.5f * base * height;
}

string Triangle::GetName2D() const
{
    return "Triangle";
}

void Triangle::Display() const
{
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Base: " << base << endl;
    cout << "Height: " << height << endl;
}

void Triangle::Scale(float scaleFactor)
{
    base *= scaleFactor;
    height *= scaleFactor;
}

float Circle::Area() const
{
    return PI * radius * radius;
}

string Circle::GetName2D() const
{
    return "Circle";
}

void Circle::Display() const
{
    cout << "The area of the " << GetName2D() << " is : " << Area() << endl;
    cout << "Radius: " << radius << endl;
}

void Circle::Scale(float scaleFactor)
{
    radius *= scaleFactor;
}

float TriangularPyramid::Volume() const
{
    return Triangle::Area() * height / 3;
}

string TriangularPyramid::GetName3D() const
{
    return "TriangularPyramid";
}

void TriangularPyramid::Display() const
{
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    Triangle::Display();
}

void TriangularPyramid::Scale(float scaleFactor)
{
    height *= scaleFactor;
    Triangle::Scale(scaleFactor);
}

float Cylinder::Volume() const
{
    return Circle::Area() * height;
}

string Cylinder::GetName3D() const
{
    return "Cylinder";
}

void Cylinder::Display() const
{
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    cout << "The height is: " << height << endl;
    Circle::Display();
}

void Cylinder::Scale(float scaleFactor)
{
    height *= scaleFactor;
    Circle::Scale(scaleFactor);
}

float Sphere::Volume() const
{
    return Circle::Area() * radius * 4 / 3;
}

string Sphere::GetName3D() const
{
    return "Sphere";
}

void Sphere::Display() const
{
    cout << "The volume of the " << GetName3D() << " is : " << Volume() << endl;
    Circle::Display();
}

void Sphere::Scale(float scaleFactor)
{
    radius *= scaleFactor;
    Circle::Scale(scaleFactor);
}
