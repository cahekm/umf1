#pragma once
#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <vector>

using namespace std;

class Vector {
	vector <double> data;
public:
	Vector(const unsigned int &_n, const double &val);
	~Vector();

	const double& operator[] (const unsigned int &_i) const;
	double& operator[] (const unsigned int &_i);
	const Vector& operator = (const Vector& rhs);

	const unsigned int& size() const;

	const double& sqnorm() const;
};

const Vector& operator - (const Vector& lhs, const Vector& rhs);
const Vector& operator += (Vector& lhs, const Vector& rhs);

#endif //_VECTOR_H_
