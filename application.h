#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include <iostream>
#include <cstdlib>

#include "blockmatrix.h"
#include "blockvector.h"
#include "solver.h"
#include "grid.h"

using namespace std;

class Application {
	int &argc;
	char **&argv;
public:
	Application(int &_argc, char **&_argv);
	~Application();
	int exec();
};

#endif //_APPLICATION_H_
