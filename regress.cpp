#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
std::string line;
#include <vector>

#include <cmath>

//! ASSIGNMENT: Make Sinusoidal Regression
//! my idea: read a single file which has two lines of space delimited floats
//! perform sinusoidal regression with the first line as x and second as y
// output the sine function
// A*sin(B*x+C)+D

//? the only matrix we need to transpose is the Jacobian
//? since we know there are 4 parameters, the number of columns is 4
//? the number of rows depends on xcoords
void transpose(double **&a, double **&target, int rowdimension, int coldimension)
{
	int i, j;
	// double **temp;
	// temp = new double *[dimension];
	// for (int i = 0; i < 10; i++)
	// 	temp[i] = new double[dimension];

	// memcpy(temp, a, dimension * dimension * sizeof(double));
	for (i = 0; i < rowdimension; i++)
	{
		for (j = 0; j < coldimension; j++)
		{
			target[j][i] = a[i][j];
		}
	}
}

void multiply(double **&a, int rowa, int cola, double **&b, int rowb, int colb, double **&target)
{
	int i, j, k;
	for (i = 0; i < rowa; i++)
	{
		for (j = 0; j < colb; j++)
		{
			for (k = 0; k < cola; k++)
			{
				target[i][j] += a[i][k] * b[k][j];
			}
			// target[i][j] = a[i][0]*b[0][j] + a[i][1]*b[1][j] + a[i][2]*b[2][j] + a[i][3]*b[3][j];
		}
	}
}

//? Recursive calculation
double determinant(double **&a, int dimension)
{
	// std::cout << dimension;
	double returnvalue = 0;
	if (dimension == 1)
	{
		double test = a[0][0];
		return a[0][0];
	}
	else
	{
		int i, j, expansioncolumn, operating_column = 0, operating_row = 0;
		double **array;
		bool negate = false;
		operating_column = 0;
		operating_row = 0;
		array = new double *[dimension - 1];
		for (i = 0; i < dimension - 1; i++)
			array[i] = new double[dimension - 1];
		for (expansioncolumn = 0; expansioncolumn < dimension; expansioncolumn++)
		{
			operating_column = 0;
			//? The new matrix will be missing one column
			for (j = 0; j < dimension; j++)
			{
				if (j == expansioncolumn)
				{
					continue;
				}
				operating_row = 0;
				for (i = 0; i < dimension; i++)
				{
					if (i == 0)
					{
						continue;
					}
					array[operating_row][operating_column] = a[i][j];
					operating_row++;
				}
				operating_column++;
			}
			double test = a[0][expansioncolumn] * ((!negate * 2) - 1) * determinant(array, dimension - 1);
			returnvalue += test;
			negate = !negate;
		}
	}
	return returnvalue;
}

void cofactor(double **&a, int dimension)
{
	double **cofactormatrix;
	cofactormatrix = new double *[dimension];
	int i, j;
	for (i = 0; i < dimension; i++)
		cofactormatrix[i] = new double[dimension];
	// memcpy(&cofactormatrix[0][0], &a[0][0], dimension * dimension * sizeof(double));
	// memcpy(&cofactormatrix[0][0], &a[0][0], dimension * dimension * sizeof(double));
	// // cofactormatrix[0][0] = 420.;
	int expansion_column, expansion_row; //which cell of the cofactormatrix is being set
	for (expansion_column = 0; expansion_column < dimension; expansion_column++)
	{
		for (expansion_row = 0; expansion_row < dimension; expansion_row++)
		{
			double **array;
			bool negate;
			array = new double *[dimension - 1];
			for (i = 0; i < dimension - 1; i++)
				array[i] = new double[dimension - 1];

			int operating_row, operating_column; //the location of the cell in the determinant matrix
			operating_row = 0;
			operating_column = 0;
			for (i = 0; i < dimension; i++)
			{
				if (i == expansion_row)
				{
					continue;
				}
				operating_column = 0;
				for (j = 0; j < dimension; j++)
				{
					if (j == expansion_column)
					{
						continue;
					}
					array[operating_row][operating_column] = a[i][j];
					operating_column++;
				}
				operating_row++;
			}
			negate = (expansion_column + expansion_row) % 2;
			double test;
			test = determinant(array, dimension - 1);
			test = ((!negate * 2) - 1) * test;
			// cout << test;
			cofactormatrix[expansion_row][expansion_column] = test;
			// // cout << "test";
		}
	}
	//! THIS COPIES POINTERS?
	memcpy(a, cofactormatrix, dimension * dimension * sizeof(double));
	// // cout << "test";
}

void invert(double **&a, int dimension)
{
	double determ = determinant(a, dimension);
	double **targetmatrix;
	targetmatrix = new double *[dimension];
	int i,j;
	for (i = 0; i < dimension; i++)
		targetmatrix[i] = new double[dimension];
	if (determ != 0)
	{
		cofactor(a, dimension);
		transpose(a, targetmatrix, dimension, dimension);
		for (i=0;i<dimension;i++) {
			for (j=0;j<dimension;j++) {
				a[i][j] = targetmatrix[i][j]/determ;
			}
		}
	}
	else {
		cout << "\nError: Unable to Invert";
	}
}

void jacobian(vector<double> x, double *parameters, double **&target)
{
	int i;
	for (i = 0; i < x.size(); i++)
	{
		target[i][0] = sin(parameters[1] * x[i] + parameters[2]);
		target[i][1] = parameters[0] * x[i] * cos(parameters[1] * x[i] + parameters[2]);
		target[i][2] = parameters[0] * cos(parameters[1] * x[i] + parameters[2]);
		target[i][3] = 1;
	}
}

void error(vector<double> x, double *parameters, vector<double> y, double **&target)
{
	int i;
	for (i = 0; i < y.size(); i++)
	{
		target[i][0] = y[i] - (parameters[0] * sin(parameters[1] * x[i] + parameters[2]) + parameters[3]);
	}
}

void adjustparameter(double **&change, double damping, double *parameter) {
	int i;
	for (i=0;i<4;i++) {
		parameter[i] += damping*change[i][0];
	}
}

//? void passFunc(int **&a)
//? {
//? 	std::cout << a[0][0];
//? 	a[0][0] = 2;
//? }

int main()
{
	//? int tester;
	//? int **array;
	//? array = new int *[tester];
	//? for (int i = 0; i < 10; i++)
	//? 	array[i] = new int[10];
	//? array[0][0] = 1;
	//? passFunc(array);
	//? std::cout << array[0][0];

	vector<double> xcoords, ycoords;
	//? Read the file for the data
	{
		ifstream inFile;
		inFile.open("points.txt");
		double value;
		if (std::getline(inFile, line))
		{
			std::istringstream iss(line);
			while (iss >> value)
			{
				xcoords.push_back(value);
			}
		}
		if (std::getline(inFile, line))
		{
			std::istringstream iss(line);
			while (iss >> value)
			{
				ycoords.push_back(value);
			}
		}
		if (xcoords.size() != ycoords.size())
		{
			std::cout << "ERR: number of x's does not equal number of y's in points.txt.\n";
			return 1;
		}
		if (!inFile)
		{
			std::cout << "ERR: points.txt does not exist in the current directory.\n";
			return 1;
		}
	}

	double parameters[4]; //A, B, C, D
	double damping;
	int iterations;
	parameters[0] = 0.1; parameters[1] = 9; parameters[2] = 8; parameters[3] = .1;
	damping = 0.1; iterations = 999;
	//? Initialize a guess
	{
		//TODO uncomment: */ std::cout << "Equation: A*sin(B*x+C)+D\nEnter your floating-point guesses for \nA: ";
		//TODO uncomment: */ std::cin >> parameters[0];
		//TODO uncomment: */ std::cout << "B: ";
		//TODO uncomment: */ std::cin >> parameters[1];
		//TODO uncomment: */ std::cout << "C: ";
		//TODO uncomment: */ std::cin >> parameters[2];
		//TODO uncomment: */ std::cout << "D: ";
		//TODO uncomment: */ std::cin >> parameters[3];
		//TODO uncomment: */ std::cout << "Damping Factor: ";
		//TODO uncomment: */ std::cin >> damping;
		//TODO uncomment: */ std::cout << "Number of Iterations: ";
		//TODO uncomment: */ std::cin >> iterations;
	}

	int iter;
	int i, j;
	double **change;
	{
		change = new double *[4];
		for (i = 0; i < 4; i++)
			change[i] = new double[1];
	}
	double **jacobmatrix;
	{
		jacobmatrix = new double *[xcoords.size()];
		for (i = 0; i < xcoords.size(); i++)
			jacobmatrix[i] = new double[4];
	}
	double **residual;
	{
		residual = new double *[xcoords.size()];
		for (i = 0; i < xcoords.size(); i++)
			residual[i] = new double[1];
	}
	double **transposedjacob;
	{
		transposedjacob = new double *[4];
		for (i = 0; i < 4; i++)
			transposedjacob[i] = new double[xcoords.size()];
	}
	double **invertiblematrix;
	{
		invertiblematrix = new double *[4];
		for (i = 0; i < 4; i++)
			invertiblematrix[i] = new double[4];
	}
	double **tempmatrix;
	{
		tempmatrix = new double *[4];
		for (i = 0; i < 4; i++)
			tempmatrix[i] = new double[xcoords.size()];
	}

	//? Loop over number of iterations
	for (iter = 0; iter < iterations; iter++)
	{
		//? Calculate Newton's method gradient
		//* DOES THIS WORK? not needed, but good to know
		//* for (i=0;i<xcoords.size();i++) {
		//* 	memcpy(transposedjacob[i],jacobmatrix[i],4 * sizeof(double));
		//* }

		/*TODO uncomment! */jacobian(xcoords,parameters,jacobmatrix);
		/*TODO uncomment! */transpose(jacobmatrix,transposedjacob,xcoords.size(),4);
		/*TODO uncomment! */multiply(transposedjacob,4,xcoords.size(),jacobmatrix,xcoords.size(),4,invertiblematrix);
		/*TODO uncomment! */invert(invertiblematrix,4);
		/*TODO uncomment! */multiply(invertiblematrix,4,4,transposedjacob,4,xcoords.size(),tempmatrix);
		/*TODO uncomment! */error(xcoords,parameters,ycoords,residual);
		// tempmatrix[3][0];
		/*TODO uncomment! */multiply(tempmatrix,4,xcoords.size(),residual,xcoords.size(),1,change);
		/*TODO uncomment! */adjustparameter(change,damping,parameters);
		//debug int arraysize = 4;
		//debug double **array;
		//debug array = new double *[arraysize];
		//debug for (i = 0; i < arraysize; i++)
		//debug 	array[i] = new double[arraysize];
		//debug double **target;
		//debug target = new double *[arraysize];
		//debug for (i = 0; i < arraysize; i++)
		//debug 	target[i] = new double[arraysize];
		//debug int counter = 0;
		//debug for (i = 0; i < arraysize; i++)
		//debug {
		//debug 	for (j = 0; j < arraysize; j++)
		//debug 	{
		//debug 		array[i][j] = counter ; //counter + 1;
		//debug 		if (i == j)
		//debug 		{
		//debug 			array[i][j] = 2.;
		//debug 		}
		//debug 		// else {
		//debug 		// 	array[i][j] = 0.;
		//debug 		// }
		//debug 		counter++;
		//debug 	}
		//debug }
		//debug for (i = 0; i < arraysize; i++)
		//debug {
		//debug 	for (j = 0; j < arraysize; j++)
		//debug 	{
		//debug 		std::cout << array[i][j] << " ";
		//debug 	}
		//debug 	std::cout << endl;
		//debug }
		//debug double targetdouble;
		//debug targetdouble = determinant(array,arraysize);
		//debug cout << "Determinant: " << targetdouble;
		//debug // array[0][0] = 0;
		//debug // calculate_change(change,parameters,xcoords,ycoords);
		//debug //debug printf("%.2f\n", determinant(array, arraysize));
		//debug // transpose(array,target,arraysize,arraysize);
		//debug // cofactor(array, arraysize);
		//debug invert(array, arraysize);
		//debug std::cout << "Changed: \n";
//debug 
		//debug for (i = 0; i < arraysize; i++)
		//debug {
		//debug 	for (j = 0; j < arraysize; j++)
		//debug 	{
		//debug 		std::cout << array[i][j] << " ";
		//debug 	}
		//debug 	std::cout << endl;
		//debug }
		//? Adjust parameters according to gradient and damping factor
	cout << parameters[0] << "*" 
		<< "sin(" << parameters[1]
		<< "*x+" << parameters[2]
		<< ")+" << parameters[3]
		<< endl
		;
	}
	// cout << parameters[0] << "*" 
	// 	<< "sin(" << parameters[1]
	// 	<< "*x+" << parameters[2]
	// 	<< ")+" << parameters[3]
	// 	<< endl
	// 	;
	cout << "Iterations: " << iterations;
	cout << "Damping: "<<damping;
	return 0;
}