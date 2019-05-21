default: solver

variable.o: Variable.cpp Variable.h
	g++ -std=c++11 -c Variable.cpp -o Variable.o

EquationSolver.o: EquationSolver.cpp EquationSolver.h
	g++ -c -std=c++11 EquationSolver.cpp -o EquationSolver.o

main.o: main.cpp EquationSolver.h
	g++ -c -std=c++11 main.cpp -o main.o

solver: main.o EquationSolver.o Variable.o
	g++ main.o EquationSolver.o Variable.o -o solver

clean:
	-rm -f *.o
	-rm -f solver