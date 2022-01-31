#include "vector.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <initializer_list>



using namespace std;

// Constructors

//!constructor for a zero vector of size size
Vector::Vector(size_t size)
    : v(vector<double>(size, 0))
{}

//!constructor for an initializer_list
Vector::Vector(std::initializer_list<double> const& list)
{
    for(auto const& element : list){
            v.push_back(element);
    }
}

//!constructor for a 3D vector
Vector::Vector(double x, double y, double z)
    : v(vector<double> {x, y, z})
{}

// Methods

//!appends a value to the vector
void Vector::append(double value)
{
    v.push_back(value);
}

//!compares two vectors, element by element, true if same
bool Vector::compare(Vector const& v2) const
{
    if(v.size() != v2.v.size()) return false;

    for(size_t i(0); i < v.size(); ++i){
        if(v[i] != v2.v[i]){
            return false;
        }
    }
    return true;
}

//!returns addition of two vectors
Vector Vector::add(Vector const& v2) const
{
    if(v.size()==v2.v.size())
    {
        Vector result(*this);

        for(size_t i(0);i<v.size();i++)
        {
            result.v[i]+=v2.v[i];
        }
        return result;
    }
    else
    {
        throw string("Error, addition between Vectors of different sizes");
    }
}

//!returns substraction with other vector
Vector Vector::substract(Vector const& v2) const
{
    if(v.size()==v2.v.size())
    {
        Vector result(*this);

        for(size_t i(0);i<v.size();i++)
        {
            result.v[i]-=v2.v[i];
        }
        return result;
    }
    else
    {
        throw string("Error, addition between Vectors of different sizes");
    }
}

//!returns multiplication of vector by constant
Vector Vector::multiply(double const a) const
{
    Vector result(*this);

    for(size_t i(0);i<v.size();i++)
    {
        result.v[i]*=a;
    }
    return result;
}

//!returns scalar product with other vector
double Vector::scalarProduct(Vector const& v2) const
{
    if(v.size()==v2.v.size())
    {
        double result(0.0);

        for(size_t i(0);i<v.size();i++)
        {
            result+=v[i]*v2.v[i];
        }

        return result;
    }
    else
    {
        throw string("Error, scalar product between Vectors of different sizes");
    }
}

Vector Vector::crossProduct(Vector const& v2) const
{
    if((v.size()!=3)||(v2.v.size()!=3))
        {
            throw string("Error, cross product with vectors of dim != 3");
        }
        else
        {
            Vector result(3);

            result.v[0]=(v[1]*v2.v[2])-(v[2]*v2.v[1]);
            result.v[1]=(v[2]*v2.v[0])-(v[0]*v2.v[2]);
            result.v[2]=(v[0]*v2.v[1])-(v[1]*v2.v[0]);

            return result;
        }
}

//!returns opposite
Vector Vector::opposite() const
{
    Vector result(*this);
    for(size_t i=0; i < v.size(); ++i)
    {
        result.v[i] *= -1;
    }
    return result;
}

//!returns norm
double Vector::norm() const
{
    return sqrt(squareNorm());
}

//!returns squared norm
double Vector::squareNorm() const
{
    double result(0.0);

    for(size_t i(0);i<v.size();i++)
    {
        result+=v[i]*v[i];
    }

    return result;
}

//!returns the unit vector
Vector Vector::unit() const
{
    return ((*this) / (this->norm()));
}

//!returns size of vector
std::size_t Vector::size() const
{
    return v.size();
}

//!returns output stream containing elements of vector
std::ostream& Vector::display(std::ostream& output) const
{
    output<<"( ";
    for(size_t i(0);i<v.size()-1;i++)
    {
        output<<v[i]<<" ; ";
    }
    output<<v[v.size()-1]<<" )";
    return output;
}

//!displays vector in command line
void Vector::display() const
{
    display(cout);
}

// Member overloading methods

//!returns reference to index th element of vector
double& Vector::operator[](std::size_t index)
{
    return v[index-1];
}

//!returns reference to index th element of vector
double Vector::operator[](std::size_t index) const
{
    return v[index-1];
}

//!compares two vectors, element by element
bool Vector::operator==(Vector const& v2) const
{
    return compare(v2);
}

bool Vector::operator!=(Vector const& v2) const
{
    return !compare(v2);
}

//!increments with other vector
Vector& Vector::operator+=(Vector const& v2)
{
    if(v.size()==v2.v.size())
    {
        for(size_t i(0);i<v.size();i++)
        {
            v[i]+=v2.v[i];
        }

        return *this;
    }
    else
    {
        throw string("Error, addition between Vectors of different sizes");
    }
}

//!decrements with other vector
Vector& Vector::operator-=(Vector const& v2)
{
    if(v.size()==v2.v.size())
    {
        for(size_t i(0);i<v.size();i++)
        {
            v[i]-=v2.v[i];
        }

        return *this;
    }
    else
    {
        throw string("Error, substraction between Vectors of different sizes");
    }
}

//!multiplies vector by constant
Vector& Vector::operator*=(double d)
{
    for (size_t i(0); i < v.size(); ++i)
    {
        v[i] *= d;
    }
    return *this;
}

//!divides vector by constant
Vector& Vector::operator/=(double d)
{
    return ((*this)*=(1.0/d));
}

//!returns scalar product with other vector
double Vector::operator*(Vector const& v2) const
{
    return scalarProduct(v2);
}

// Non-member overloading functions

//!returns stream containing vector elements
std::ostream& operator<<(std::ostream& output, Vector const& v)
{
    return v.display(output);
}

//!adds two vectors
Vector operator+(Vector v, Vector const& v2)
{
    return v += v2;
}

//!substracts two vectors
Vector operator-(Vector v, Vector const& v2)
{
    return v-=v2;
}

Vector operator^(Vector v, Vector const& v2)
{
    return v.crossProduct(v2);
}

//!multiplies vector by constant
Vector operator*(double d, Vector v)
{
    return v*=d;
}

Vector operator*(Vector v, double d)
{
    return v*=d;
}

//!divides vector by constant
Vector operator/(Vector v, double d)
{
    return v/=d;
}

//!returns opposite of vector
Vector operator-(Vector v)
{
    return v.opposite();
}

