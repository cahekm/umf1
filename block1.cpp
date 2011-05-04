#include "block1.h"

Block1::Block1(const unsigned int &_n, const int _offset, const double &val) :
		n(_n), offset(_offset)
{ 
	for(unsigned int i = 0; i < n; i++) 
		cen.push_back(val);
}

Block1::~Block1() { }

const unsigned int Block1::size() const {
	return cen.size();
}

const double& Block1::operator() (const unsigned int &i, const unsigned int &j) const {
	if(i >= cen.size() || j < offset || j >= cen.size()+offset)
		return 0;
	if(i == (j-offset)) 
		return cen[i];
	else {
		return 0;
	}
}

double& Block1::operator() (const unsigned int &i, const unsigned int &j) {
	if(i >= cen.size() || j < offset || j >= cen.size()+offset)
		throw "Wrong index";
	if(i == (j-offset)) 
		return cen[i];
	else {
		throw "Wrong index";
	}
}

const Vector& Block1::operator* (const Vector &_rhs) const {
	Vector ans = _rhs;
	for(int i = 0; i < size(); i++) {
		ans[i] *= cen[i];
	}
	return ans;
}
