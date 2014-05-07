/*** Finding eigenvalues ***/
#include<iostream>
#include<fstream>
#include<cmath>
#include"simpleMatrix.h"
using namespace std;

int main()
{
	int i,j, N = 3, counter = 0;
	double lambda, eps = 1e-10, s;		// s = shift parameter
	double **A = allocMatrix(N);
	double **I = allocMatrix(N);
	eye(I,N);
	double *x0 = allocVector(N);
	double *x1 = allocVector(N);
	double *e = allocVector(N);
	
	/*** reading in the matrix ***/
	ifstream cucaj("matrix.txt");
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			cucaj >> A[i][j];
	
	for(i=0; i<N; i++)
		x0[i] = 1.0;
	normalise(x0,N);
	
	A = matrixSubtr(A, numTimesMat(s,I,N), N);
	
	/*** power method
	/*******************************************/
	while(true){
		counter++;
		x1 = matVecProd(A, x0, N);
		lambda = dotProd(x0, x1, N) / dotProd(x0, x0, N);
		e = vectorSubtr(x1, numTimesVec(lambda, x0, N), N);
		
		if(norm(e,N) < eps)	break;
		normalise(x1,N);
		x0 = x1;			// redirect pointer to x1 into x0
	}
	
	cout << "Largest e-value: " << lambda << endl;
	cout << "Associated e-vector:\n";
	printVector(x1,N);
	cout << "Number of iterations: " << counter << endl;
	
	/*** inverse iteration
	/*******************************************/
	
		s = 1.0;
}


