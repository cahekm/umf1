#include "application.h"

Application::Application(int &_argc, char **&_argv) :
			argc(_argc), argv(_argv) { }

Application::~Application() { }

int Application::exec() {
	try {
		Grid grid(	3, 3, 3, 2, 
					2, 2, 2, 1,
					2, 2, 2, 2);

		//grid.print();
		/*cout.precision(3);
		cout << "i\tleft\tright\tbot\ttop\n";
		for(int i = 0; i < grid.sizeSLAE(); i++) {
			cout << i << "\t" << grid.left(i) << "\t" << grid.right(i) << "\t" << grid.bottom(i) << "\t" << grid.top(i) << endl;	
		}*/


		BlockMatrix A(grid);
		BlockVector b(grid);
		
		Solver solve(grid, 1.0, 1.0e-7, 1.0e+5);
		BlockVector x = solve(A, b);
		
		cout.precision(1);
		cout << A << endl;
		cout << b << endl;
		cout << endl;
		cout << x << endl;
	}
	catch(...) {
		cerr << "An error occures!\n";
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}