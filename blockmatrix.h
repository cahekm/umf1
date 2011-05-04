#pragma once
#ifndef _BLOCKMATRIX_H_
#define _BLOCKMATRIX_H_

#include <iostream>

#include "block1.h"
#include "block3.h"
#include "grid.h"

using namespace std;

class BlockMatrix {
	const Grid &grid;
	unsigned int h1, w1, h2, w2;
	unsigned int n;
	
	vector <Block1> lhs;
	vector <Block3> cen;
	vector <Block1> rhs;

	void fill();

	double& _left(const unsigned int &i);
	double& _right(const unsigned int &i);
	double& _top(const unsigned int &i);
	double& _bottom(const unsigned int &i);
	double& _center(const unsigned int &i);
public:
	BlockMatrix(const Grid &_grid);
	~BlockMatrix();

	const unsigned int size() const;

	const double& operator() (const unsigned int &_i, const unsigned int &_j) const;

	const Block1& bleft(const unsigned int &i) const;
	const Block1& bright(const unsigned int &i) const;
	const Block3& bcen(const unsigned int &i) const;
};

ostream& operator << (ostream &lhs, const BlockMatrix &rhs);

#endif //_BLOCKMATRIX_H_
