#include "grid.h"

Grid::Grid(const unsigned int &h1, 
		const unsigned int &w1,
		const unsigned int &h2, 
		const unsigned int &w2,
		
		const double &sh1,
		const double &sh2,
		const double &sw1,
		const double &sw2,
		
		const double &kh1,
		const double &kh2,
		const double &kw1,
		const double &kw2)
		: _h1(h1), _w1(w1), _h2(h2), _w2(w2),
		_blocks(_h1+_h2-1), 
		_sizeSLAE(_h1*_w1 + _h2*_w1 + _h2*_w2 - _w1 - _h2),
		_sh1(sh1), _sh2(sh2), _sw1(sw1), _sw2(sw2), 
		_kh1(kh1), _kh2(kh2), _kw1(kw1), _kw2(kw2) { }

Grid::~Grid() { }

void Grid::index(const unsigned int &ind, 
			zone::zone &which,
			unsigned int &locali,
			unsigned int &localj) const {
	if(ind < (_h1)*_w1) {
		which = zone::bottom;
		locali = ind / _w1;
		localj = ind % _w1;
	} else {
		locali = (ind - (_h1-1)*_w1) / (_w1 + _w2 - 1);
		localj = (ind - (_h1-1)*_w1) % (_w1 + _w2 - 1);
		which = (localj < _w1) ? zone::topleft : zone::topright;
		localj -= (which == zone::topright) ? _w1-1 : 0;
		//locali += (which == zone::topright) ? 0 : 1;
	}
}

void Grid::print() const {
	unsigned int locali, localj;
	zone::zone which;
	cout << "i\ti\tzone\tlocali\tlocalj\n";
	for(int i = 0; i < _sizeSLAE; i++) {
		index(i, which, locali, localj);
		cout << i << "\t" << which << "\t" << locali << "\t" << localj << endl;	
	}
}

const unsigned int& Grid::blocks() const {
	return _blocks;
}

const unsigned int& Grid::sizeSLAE() const {
	return _sizeSLAE;
}

const unsigned int& Grid::w1() const {
	return _w1;
}

const unsigned int& Grid::w2() const {
	return _w2;
}

const unsigned int& Grid::h1() const {
	return _h1;
}

const unsigned int& Grid::h2() const {
	return _h2;
}

const double Grid::top(const unsigned int &point) const {
	unsigned int i, j;
	zone::zone which;
	index(point, which, i, j);

	double h0;
	switch(which) {
	case zone::bottom:
		if(i == _h1 - 1) {
			if(_kh2 == 1)
				return _sh2/(_h2-1);
			return _sh2 * (1 - _kh2) / (1 - pow(_kh2, (int)(_h2-1)));
		}
		if(_kh1 == 1)
			return _sh1/(_h1-1);
		h0 = _sh1 * (1 - _kh1) / (1 - pow(_kh1, (int)(_h1-1)));
		return h0 * pow(_kh1, (int)i);
	default:
		if(i == (_h2-1))
			return 0;
		if(_kh2 == 1)
			return _sh2/(_h2-1);
		h0 = _sh2 * (1 - _kh2) / (1 - pow(_kh2, (int)(_h2-1)));
		return h0 * pow(_kh2, (int)i);
	}
}

const double Grid::bottom(const unsigned int &point) const {
	unsigned int i, j;
	zone::zone which;
	index(point, which, i, j);

	double h0;
	switch(which) {
	case zone::bottom:
		if(i == 0)
			return 0;
		if(_kh1 == 1)
			return _sh1/(_h1-1);
		h0 = _sh1 * (1 - _kh1) / (1 - pow(_kh1, (int)(_h1-1)));
		return h0 * pow(_kh1, (int)(i-1));
	default:
		if(i == 0) 
			return 0;
		if(_kh2 == 1)
			return _sh2/(_h2-1);
		h0 = _sh2 * (1 - _kh2) / (1 - pow(_kh2, (int)(_h2-1)));
		return h0 * pow(_kh2, (int)(i-1));
	}
}

const double Grid::left(const unsigned int &point) const {
	unsigned int i, j;
	zone::zone which;
	index(point, which, i, j);

	double h0;
	switch(which) {
	case zone::topright:
		if(_kw2 == 1)
			return _sw2/(_w2-1);
		h0 = _sw2 * (1 - _kw2) / (1 - pow(_kw2, (int)(_w2-1)));
		return h0 * pow(_kw2, (int)(j-1));
	default:
		if(j == 0)
			return 0;
		if(_kw1 == 1)
			return _sw1/(_w1-1);
		h0 = _sw1 * (1 - _kw1) / (1 - pow(_kw1, (int)(_w1-1)));
		return h0 * pow(_kw1, (int)(j-1));
	}
}

const double Grid::right(const unsigned int &point) const {
	unsigned int i, j;
	zone::zone which;
	index(point, which, i, j);

	double h0;
	switch(which) {
	case zone::topright:
		if(j == _w2-1)
			return 0;
		if(_kw2 == 1)
			return _sw2/(_w2-1);
		h0 = _sw2 * (1 - _kw2) / (1 - pow(_kw2, (int)(_w2-1)));
		return h0 * pow(_kw2, (int)(j));
	case zone::topleft:
		if(j == _w1-1) {
			if(_kw2 == 1)
				return _sw2/(_w2-1);
			return _sw2 * (1 - _kw2) / (1 - pow(_kw2, (int)(_w2-1)));
		}
		if(_kw1 == 1)
			return _sw1/(_w1-1);
		h0 = _sw1 * (1 - _kw1) / (1 - pow(_kw1, (int)(_w1-1)));
		return h0 * pow(_kw1, (int)(j));
	case zone::bottom:
		if(j == _w1-1 && i == _h1-1) {
			if(_kw2 == 1) 
				return _sw2/(_w2-1);
			return _sw2 * (1 - _kw2) / (1 - pow(_kw2, (int)(_w2-1)));
		}
		if(j == _w1-1)
			return 0;
		if(_kw1 == 1)
			return _sw1/(_w1-1);
		h0 = _sw1 * (1 - _kw1) / (1 - pow(_kw1, (int)(_w1-1)));
		return h0 * pow(_kw1, (int)(j));
	}
}