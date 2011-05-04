#include "solver.h"

Solver::Solver(const Grid &_grid, const double &_omega, const double &_eps,
			   const unsigned int &_limit)
				: grid(_grid), omega(_omega), eps(_eps), limit(_limit), blocks(grid.blocks()),
					answer(grid), prev(answer) { }
				
Solver::~Solver() { }

const BlockVector& Solver::operator() (const BlockMatrix &A, const BlockVector &b) {
	//return b;

	for(int i = 0; i < limit && doStep(A, b) > eps; i++);
	
	return answer;
}

const BlockVector& Solver::getLastSolution() {
	return answer;
}

const double Solver::doStep(const BlockMatrix &A, const BlockVector &b) {
	double fault = 0.0;
	BlockVector R(grid);
	R.block(0) = b.block(0)
				 - A.bcen(0) * answer.block(0)
				 - A.bright(0) * answer.block(1);
	fault += (answer.block(0) += A.bcen(0).shuttle(R.block(0))).sqnorm();
	for(int i = 1; i < blocks-1; i++) {
		Vector buf1 = b.block(i);
		Vector buf2 = A.bleft(i) * answer.block(i-1);
		Vector buf3 = A.bcen(i) * answer.block(i);
		Vector buf4 = A.bright(i) * answer.block(i+1);

		R.block(i) = b.block(i)	- A.bleft(i) * answer.block(i-1)
								- A.bcen(i) * answer.block(i)
								- A.bright(i) * answer.block(i+1);
		fault += (answer.block(i) += A.bcen(i).shuttle(R.block(i))).sqnorm();
	}
	R.block(blocks-1) = b.block(blocks-1)
						- A.bleft(blocks-1) * answer.block(blocks-2)
						- A.bcen(blocks-1) * answer.block(blocks-1);
	fault += (answer.block(blocks-1) = A.bcen(blocks-1).shuttle(R.block(blocks-1))).sqnorm();

	return sqrt(fault);
}
