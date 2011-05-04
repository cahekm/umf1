#pragma once
#ifndef _BLOCK1_H_
#define _BLOCK1_H_

#include <vector>
#include <vector.h>

using namespace std;

class Block1 {
	unsigned int n;
	int offset;

	vector <double> cen;
public:
	Block1(const unsigned int &_n, const int _offset=0, const double &val=1);
	~Block1();

	const unsigned int size() const;

	const double& operator() (const unsigned int &i, const unsigned int &j) const;
	double& operator() (const unsigned int &i, const unsigned int &j);

	const Vector& operator* (const Vector &_rhs) const;
};

#endif //_BLOCK1_H_
