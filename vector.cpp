#include "vector.h"

Vector::Vector(const unsigned int &_n, const double &val) {
	for(unsigned int i = 0; i < _n; i++) 
		data.push_back(val);
}

Vector::~Vector() { }

const double& Vector::operator[] (const unsigned int &_i) const {
	if(_i < data.size())
		return data[_i];
	else 
		throw "Wrong index";
}

double& Vector::operator[] (const unsigned int &_i){
	if(_i < data.size())
		return data[_i];
	else 
		throw "Wrong index";
}

const unsigned int& Vector::size() const {
	return data.size();
}

const double& Vector::sqnorm() const {
	double ans = 0.0;
	for(int i = 0; i < size(); i++) {
		ans += data[i]*data[i];
	}
	return ans;
}

const Vector& operator - (const Vector& lhs, const Vector& rhs) {
	Vector ans = lhs;
	for(int i = 0; i < ans.size(); i++) {
		ans[i] -= rhs[i];
	}
	return ans;
}

const Vector& operator += (Vector& lhs, const Vector& rhs) {
	for(int i = 0; i < lhs.size(); i++) {
		lhs[i] += rhs[i];
	}
	return lhs;
}

const Vector& Vector::operator = (const Vector& rhs) {
	for(int i = 0; i < size(); i++) {
		data[i] = rhs[i];
	}
	return *this;
}
