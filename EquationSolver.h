#pragma once
#include "Variable.h"
#include <vector>
#include <string>
#include <map>

// Parses a system of equations from a specified file and returns
// a solved system or errors detailing why no solution can be reached
// Representation:
// noErrors (bool) - true when system is solvable
// v (map) -  maps an quick access key for all eqns in system
// visited (vector) - stack to hold nodes during traversals

class EquationSolver
{
private:
	bool noErrors = true;
	map<string, Variable> v;
	vector<string> visited;
public: 
	int dfs(Variable &solve_v);
	int dfs_helper(Variable &solve_v);
	void ParseFile( const char *filename ); 
	void Solve();
	void Output();
};