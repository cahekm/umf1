#pragma once
#ifndef _BLOCKVECTOR_H_
#define _BLOCKVECTOR_H_

#include <vector>
#include <iostream>

#include "vector.h"
#include "grid.h"

using namespace std;

class BlockVector {
	const Grid &grid;
	unsigned int h1, w1, h2, w2;
	unsigned int n, m;

	vector <Vector> data;

	void fill();
public:
	BlockVector(const Grid &grid);
	~BlockVector();

	const double& operator[] (const unsigned int &_i) const;
	double& operator[] (const unsigned int &_i);

	const Vector& block(const unsigned int &i) const;
	Vector& block(const unsigned int &i);

	const unsigned int size() const;
};

ostream& operator << (ostream &lhs, const BlockVector &rhs);

const BlockVector& operator - (const BlockVector& lhs, const BlockVector& rhs);

#endif //_BLOCKVECTOR_H_
