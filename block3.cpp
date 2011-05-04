#include "block3.h"

Block3::Block3(const unsigned int &_n, const double &val) :
		n(_n)
{ 
	for(unsigned int i = 0; i < n; i++) {
		lhs.push_back(i == 0 ? 0.0 : val);
		cen.push_back(val);
		rhs.push_back(i == (n-1) ? 0.0 : val);
	}
}

Block3::~Block3() { }

const unsigned int Block3::size() const {
	return cen.size();
}

const double& Block3::operator() (const unsigned int &i, const unsigned int &j) const {
	if(i < 0 || j < 0 || i >= cen.size() || j >= cen.size())
		return 0;
	switch(i - j) {
		case -1:
			return rhs[i];
		case 0:
			return cen[i];
		case 1:
			return lhs[i];
		default:
			return 0;
	}
}

double& Block3::operator() (const unsigned int &i, const unsigned int &j) {
	if(i < 0 || j < 0 || i >= cen.size() || j >= cen.size())
		throw "Wrong index";
	switch(i - j) {
		case -1:
			return rhs[i];
		case 0:
			return cen[i];
		case 1:
			return lhs[i];
		default:
			throw "Wrong index";
	}
}

const Vector& Block3::operator* (const Vector &_rhs) const {
	if(size() != _rhs.size())
		throw "Wrong size";
	Vector ans = _rhs;
	for(int i = 0; i < size(); i++) {
		ans[i] = cen[i] * _rhs[i];
	}
	for(int i = 0; i < size(); i++) {
		ans[i] += (i == 0 ? 0.0 : lhs[i] * _rhs[i-1]);
		ans[i] += (i == (n-1) ? 0.0 : rhs[i] * _rhs[i+1]);
	}
	return ans;
}

const Vector& Block3::shuttle(const Vector &right) const {
	Vector x = right;
	vector <double> a(lhs);
	vector <double> b(rhs);
	vector <double> c(cen);
	vector <double> f(size());
	for(int i = 0; i < size(); i++) {
		f[i] = right[i];
	}

	int n = size();

	for (int i = 1; i < n; i++)
	{
			double m = a[i-1]/c[i-1];
			c[i] = c[i] - m*b[i-1];
			f[i] = f[i] - m*f[i-1];
	}
	x[n-1] = f[n-1]/c[n-1];

	for (int i = n - 2; i >= 0; i--)
			x[i]=(f[i]-b[i]*x[i+1])/c[i];

	return x;
}
