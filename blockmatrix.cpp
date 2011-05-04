#include "blockmatrix.h"

BlockMatrix::BlockMatrix(const Grid &_grid)
		: h1(_grid.h1()), h2(_grid.h2()), w1(_grid.w1()), w2(_grid.w2()),
			n(_grid.sizeSLAE()), grid(_grid)
		//h1(_h1), h2(_h2), w1(_w1), w2(_w2),
		//n(h1*w1 + h2*w1 + h2*w2 - w1 - h2)
{
	fill();
}

BlockMatrix::~BlockMatrix() { }

void BlockMatrix::fill() {
	lhs.push_back(Block1(0, 0, 1));
	cen.push_back(Block3(w1, 1));
	rhs.push_back(Block1(w1, 0, 1));

	for(unsigned int i = 0; i < h1-2; i++) {
		lhs.push_back(Block1(w1, 0, i+2));
		cen.push_back(Block3(w1, i+2));
		rhs.push_back(Block1(w1, 0, i+2));
	}

	lhs.push_back(Block1(w1, w2-1, h1));
	cen.push_back(Block3(w1+w2-1, h1));
	rhs.push_back(Block1(w1+w2-1, 0, h1));

	for(unsigned int i = 0; i < h2-2; i++) {
		lhs.push_back(Block1(w1+w2-1, 0, h1+i+1));
		cen.push_back(Block3(w1+w2-1, h1+i+1));
		rhs.push_back(Block1(w1+w2-1, 0, h1+i+1));
	}

	lhs.push_back(Block1(w1+w2-1, 0, h1+h2-1));
	cen.push_back(Block3(w1+w2-1, h1+h2-1));
	rhs.push_back(Block1(0));

	for(unsigned int i = 0; i < grid.sizeSLAE(); i++) {
		double left = grid.left(i);
		double right = grid.right(i);
		double top = grid.top(i);
		double bottom = grid.bottom(i);
		
		if(left != 0.0 && right != 0.0 && top != 0.0 && bottom != 0.0) {
			_left(i) = 2.0 / (left * (left + right));
			_right(i) = 2.0 / (right * (left + right));
			_top(i) = 2.0 / (top * (bottom + top));
			_bottom(i) = 2.0 / (bottom * (bottom + top));
			_center(i) = -2.0 / (left * right) - 2.0 / (top * bottom);
		}
		else {
			if(left != 0.0)
				_left(i) = 0.0;
			if(right != 0.0)
				_right(i) = 0.0;
			if(top != 0.0)
				_top(i) = 0.0;
			if(bottom != 0.0)
				_bottom(i) = 0.0;
			_center(i) = 1.0;
		}
	}
}

double& BlockMatrix::_left(const unsigned int &i) {
	unsigned int j, k;
	for(j = i, k = 0; j >= cen[k].size(); j -= cen[k].size(), k++);
	return cen[k](j,j-1);
}

double& BlockMatrix::_right(const unsigned int &i) {
	unsigned int j, k;
	for(j = i, k = 0; j >= cen[k].size(); j -= cen[k].size(), k++);
	return cen[k](j,j+1);
}

double& BlockMatrix::_top(const unsigned int &i) {
	unsigned int j, k;
	for(j = i, k = 0; j >= cen[k].size(); j -= cen[k].size(), k++);
	return rhs[k](j,j);
}

double& BlockMatrix::_bottom(const unsigned int &i) { 
	unsigned int j, k;
	for(j = i, k = 0; j >= cen[k].size(); j -= cen[k].size(), k++);
	if(i >= (h1-1)*w1 && i < h1*w1)
		return lhs[k](j,j+w2-1);
	return lhs[k](j,j);
}

double& BlockMatrix::_center(const unsigned int &i) {
	unsigned int j, k;
	for(j = i, k = 0; j >= cen[k].size(); j -= cen[k].size(), k++);
	return cen[k](j,j);
}

const unsigned int BlockMatrix::size() const {
	return n;
}

const double& BlockMatrix::operator() (const unsigned int &_i, const unsigned int &_j) const {
	int i = _i, j = _j, k, s;

	if(i < w1*(h1-1)) {
		s = w1;
		k = i / w1;
		j -= k * w1;
		i -= k * w1;
	}
	else if(i < n) {
		s = (w1+w2-1);
		k = h1-1;
		i -= w1*(h1-1);
		j -= w1*(h1-1);
		int d = i/s;
		k += d;
		i -= d*s;
		j -= d*s;
	}
	else
		return 0;

	if(j < -s || j >= 2*s)
		return 0;
	else if (j < 0)
		return lhs[k](i,j+s);
	else if(j < s)
		return cen[k](i,j);
	else return rhs[k](i,j-s);
}

const Block1& BlockMatrix::bleft(const unsigned int &i) const {
	return lhs[i];
}

const Block1& BlockMatrix::bright(const unsigned int &i) const {
	return rhs[i];
}

const Block3& BlockMatrix::bcen(const unsigned int &i) const {
	return cen[i];
}

ostream& operator << (ostream &lhs, const BlockMatrix &rhs) {
	for(unsigned int i = 0; i < rhs.size(); i++) {
		for(unsigned int j = 0; j < rhs.size(); j++) {
			cout.width(3);
			cout << rhs(i,j) << " ";
		}
		cout << endl;
	}
	return lhs;
}
