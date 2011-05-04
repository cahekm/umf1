#pragma once
#ifndef _SOLVER_H_
#define _SOLVER_H_

#include "blockmatrix.h"
#include "blockvector.h"

class Solver {
	double omega;
	double eps;
	unsigned int limit;
	unsigned int blocks;
	const Grid &grid;

	BlockVector answer;
	BlockVector prev;

	const double doStep(const BlockMatrix &A, const BlockVector &b);

public:
	Solver(const Grid &_grid, const double &_omega, const double &_eps,
			   const unsigned int &_limit);
	~Solver();

	const BlockVector& getLastSolution();

	const BlockVector& operator() (const BlockMatrix &A, const BlockVector &b);
};	


#endif //_SOLVER_H_
