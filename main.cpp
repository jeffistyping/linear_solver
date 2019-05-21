#include "EquationSolver.h"

int main(int argc, char* argv[])
{
	if( argc <= 0 )
	{
		std::perror( "Error: No file provided." );
		return 1;
	}

	const char *filename = argv[1];

	EquationSolver solver;
	
	solver.ParseFile( filename );
	solver.Solve();
	solver.Output();
	
	return 0;
}