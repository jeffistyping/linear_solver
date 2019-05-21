#include "EquationSolver.h"
#include "Variable.h"
#include <stdio.h>      
#include <stdlib.h>     
#include <iostream>
#include <fstream> // File IO 
#include <sstream> // String Streams
#include <string>
#include <map>

using namespace std;

void EquationSolver::ParseFile( const char *filename )
{
	ifstream inFile;
	int strmInt;
	string lhs_var, tmp, line;
	inFile.open(filename);

	while (getline(inFile, line)){
		istringstream strm(line);
		strm >> tmp;
		Variable left_unknown;
		left_unknown.setName(tmp);
		while(strm >> tmp){
			if (isdigit(tmp[0]))
				left_unknown.inc_const(stoi(tmp));
			else if (isalpha(tmp[0]))
				left_unknown.dependents.insert(tmp);
		}
		v[left_unknown.getName()] = left_unknown;
	}
}

void EquationSolver::Solve(){
	map<string, Variable>::iterator eqn_it = v.begin(); 
	while(eqn_it != v.end()){
		eqn_it->second.inc_const(dfs(eqn_it->second));
		eqn_it++;
	}
}

void EquationSolver::Output(){
	for(auto x : v){
		if (x.second.getSolved() && noErrors)
			cout << x.first << " = " << x.second.getConst() << endl;
	}
}

int EquationSolver::dfs(Variable &solve_v){
	set<string>::iterator it = solve_v.dependents.begin();
	visited.push_back(solve_v.getName());
	if (solve_v.dependents.size() == 0){
		solve_v.setSolved(true);
		visited.pop_back();
		return 0;
	}
	int sum = 0;
	// Circular reference errors and non-indexed variables throw exceptions
	while(it != solve_v.dependents.end()){
		try{
			sum += dfs_helper(v.at(*it));
		}
		catch(out_of_range& oor){
			noErrors = false;
			cout << "(Solving for " << solve_v.getName() << ") ";
			cout << "ERROR: " << *it << " can not be resolved" << endl;
			return 0;
		}
		catch(logic_error& oor){
			noErrors = false;
			cout << "ERROR: Circular reference found for " << *it << endl;
			return 0;
		}
		it++;
	} 
	solve_v.setSolved(true);
	return sum;
}

int EquationSolver::dfs_helper(Variable &solve_v){
	visited.push_back(solve_v.getName());
	if (solve_v.dependents.size() == 0){
		solve_v.setSolved(true);
		visited.pop_back();
		return solve_v.getConst();
	}
	set<string>::iterator it = solve_v.dependents.begin();
	int sum = 0;
	while(it != solve_v.dependents.end()){
		vector<string>::iterator circle_it = find(visited.begin(), visited.end(), *it);
		if (circle_it != visited.end()){
			throw logic_error("Circular Reference");
			return 0;
		}
		sum += dfs_helper(v.at(*it));
		it++;
	}
	return sum+solve_v.getConst();
}
