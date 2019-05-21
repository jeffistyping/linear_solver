#pragma once
#include <set>
#include <string>

// An internal representation of a singular equation within
// a system for use by the EquationSolver class
// Representation:
// name (string) -  The alpha name of the variable
// solved (bool) -  True flag when numerical answer is found
// constant (int) - Intemediate (and final) numberical value
using namespace std;

class Variable
{
private:
	string name;
	int constant;
	bool solved;
public:
	Variable(int i = 0, bool s = false):constant(i), solved(s) {}  
	set<string> dependents;
	int getConst() { return constant; }
	string getName() { return name; }
	bool getSolved() { return solved; }
	void setSolved( bool state );
	void setName(string n);
	void inc_const(int num);
};