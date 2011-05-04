#pragma once
#ifndef _GRID_H_
#define _GRID_H_

#include <cmath>
#include <iostream>
using namespace std;

namespace zone {
	enum zone {bottom, topleft, topright};
};

class Grid {
	unsigned int _h1, _w1, _h2, _w2;
	double _sh1, _sw1, _sh2, _sw2;	// Длины
	double _kh1, _kw1, _kh2, _kw2;	// Коэффициенты масштабирования
	unsigned int _blocks;
	unsigned int _sizeSLAE;

	void index(const unsigned int &ind, 
				zone::zone &which,
				unsigned int &locali,
				unsigned int &localj) const;
public:
	Grid(const unsigned int &h1, 
		const unsigned int &w1,
		const unsigned int &h2, 
		const unsigned int &w2,
		
		const double &sh1,
		const double &sh2,
		const double &sw1,
		const double &sw2,

		const double &kh1 = 1.0,
		const double &kh2 = 1.0,
		const double &kw1 = 1.0,
		const double &kw2 = 1.0
		);
	~Grid();
	
	const unsigned int& blocks() const;
	const unsigned int& sizeSLAE() const;

	const unsigned int& w1() const;
	const unsigned int& w2() const;
	const unsigned int& h1() const;
	const unsigned int& h2() const;

	const double top(const unsigned int &point) const;
	const double bottom(const unsigned int &point) const;
	const double left(const unsigned int &point) const;
	const double right(const unsigned int &point) const;

	void print() const;
};

#endif //_GRID_H_
