#pragma once
#ifndef _BLOCK3_H_
#define _BLOCK3_H_

#include <vector>
#include <vector.h>

using namespace std;

class Block3 {
	unsigned int n;

	vector <double> lhs;
	vector <double> cen;
	vector <double> rhs;
public:
	Block3(const unsigned int &_n, const double &val=1.0);
	~Block3();

	const unsigned int size() const;

	const double& operator() (const unsigned int &i, const unsigned int &j) const;
	double& operator() (const unsigned int &i, const unsigned int &j);

	const Vector& operator* (const Vector &_rhs) const;

	const Vector& shuttle(const Vector &right) const;
};

#endif //_BLOCK3_H_
