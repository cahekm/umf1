#include "blockvector.h"

BlockVector::BlockVector(const Grid &_grid) 
			: h1(_grid.h1()), h2(_grid.h2()), w1(_grid.w1()), w2(_grid.w2()),
			n(_grid.sizeSLAE()), grid(_grid)
{
	fill();
}

void BlockVector::fill() {
	for(unsigned int i = 0; i < h1-1; i++)
		data.push_back(Vector(w1, i + 1));
	for(unsigned int i = h1-1; i < h1+h2-1; i++)
		data.push_back(Vector(w1+w2-1, i + 1));
}

BlockVector::~BlockVector() { }

const unsigned int BlockVector::size() const {
	return n;
}

const double& BlockVector::operator[] (const unsigned int &_i) const {
	int i = _i;
	if(i < 0 || i > (int)n) 
		return 0;
	else if(i < (h1-1)*w1)
		return data[i/w1][i%w1];
	else {
		int s = w1+w2-1;
		i -= (h1-1)*w1;
		return data[h1-1 + i/s][i%s];
	}
	return data[_i/m][_i%m];
}

double& BlockVector::operator[] (const unsigned int &_i) {
	int i = _i;
	if(i < 0 || i > (int)n) 
		throw "Wrong index";
	else if(i < (h1-1)*w1)
		return data[i/w1][i%w1];
	else {
		int s = w1+w2-1;
		i -= (h1-1)*w1;
		return data[h1-1 + i/s][i%s];
	}
	return data[_i/m][_i%m];
}

const Vector& BlockVector::block(const unsigned int &i) const {
	return data[i];
}

Vector& BlockVector::block(const unsigned int &i) {
	return data[i];
}

ostream& operator << (ostream &lhs, const BlockVector &rhs) {
	for(unsigned int i = 0; i < rhs.size(); i++) {
		cout << rhs[i] << " ";
	}
	return lhs;
}

const BlockVector& operator - (const BlockVector& lhs, const BlockVector& rhs) {
	BlockVector ans(lhs);
	int n = ans.size();
	for(int i = 0; i < n; i++) {
		ans[i] -= rhs[i];
	}
	return ans;
}
