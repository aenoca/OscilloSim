#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
#include <cmath>
#include <initializer_list>


class Vector
{
private:
    std::vector<double> v;
public:
    // Constructors

    //!constructor for a zero vector of size size
    Vector(std::size_t size=0);

    //!constructor for an initializer_list
    Vector(std::initializer_list<double> const& list);

    //!constructor for a 3D vector
    Vector(double x, double y, double z);

    // Methods

    //!appends a value to the vector
    void append(double value);

    //!compares two vectors, element by element, true if same
    bool compare(Vector const& v2) const;

    //!returns addition of two vectors
    Vector add(Vector const& v2) const;

    //!returns substraction with other vector
    Vector substract(Vector const& v2) const;

    //!returns multiplication of vector by constant
    Vector multiply(double const a) const;

    //!returns scalar product with other vector
    double scalarProduct(Vector const& v2) const;

    Vector crossProduct(Vector const& v2) const;

    //!returns opposite
    Vector opposite() const;

    //!returns norm
    double norm() const;

    //!returns squared norm
    double squareNorm() const;

    //!returns the unit vector
    Vector unit() const;

    //!returns size of vector
    std::size_t size() const;

    //!returns output stream containing elements of vector
    std::ostream& display(std::ostream& output) const;

    //!displays vector in command line
    void display() const;

    // Member overloading methods

    //!returns reference to index th element of vector
    double& operator[](std::size_t index);

    //!returns reference to index th element of vector
    double operator[](std::size_t index) const;

    //!compares two vectors, element by element
    bool operator==(Vector const& v2) const;

    bool operator!=(Vector const& v2) const;

    //!increments with other vector
    Vector& operator+=(Vector const& v2);

    //!decrements with other vector
    Vector& operator-=(Vector const& v2);

    //!multiplies vector by constant
    Vector& operator*=(double d);

    //!divides vector by constant
    Vector& operator/=(double d);

    //!returns scalar product with other vector
    double operator*(Vector const& v2) const;
};

// Non-member overloading functions

//!returns stream containing vector elements
std::ostream& operator<<(std::ostream& output, Vector const& v);

//!adds two vectors
Vector operator+(Vector v, Vector const& v2);

//!substracts two vectors
Vector operator-(Vector v, Vector const& v2);

//!cross product
Vector operator^(Vector v, Vector const& v2);

//!multiplies vector by constant
Vector operator*(double d, Vector v);

Vector operator*(Vector v, double d);

//!divides vector by constant
Vector operator/(Vector v, double d);

//!returns opposite of vector
Vector operator-(Vector v);


#endif // VECTOR_H
