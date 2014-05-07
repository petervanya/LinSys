/*** Multiplying square NxN matrices ***/
#include<iostream>
#include<fstream>
#include<cmath>
#include"simpleMatrix.h"
using namespace std;

double **matrixMult(double **, double **, int);

int main()
{
	int i,j, N = 3;
	double a;		// dummy variable
	double **A = allocMatrix(N);
	double **B = allocMatrix(N);
	double **C;
	double *v = allocVector(N);
	
	/*** reading in the matrix ***/
	ifstream cucaj("matrix.txt");
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cucaj >> a;
			A[i][j] = a;
			B[i][j] = a;
	}}
	
	/* initialising A and B
	for(i=0; i<N; i++){
		A[i][i] = 2.0;
		B[i][i] = 3.0;
	}//*/
	
	cout << "Product:\n";
	C = matrixMult(A,B,N);
	printMatrix(C,N);
	
	v = matrixCol(A,-1,N);
	cout << "Vector checking:\n";
	printVector(v,N);
	
	freeMatrix(A,N);
	freeMatrix(B,N);
	freeMatrix(C,N);		
}

/***** multiplying two matrices *****
double **MatrixMult(double **m1, double **m2, int n){
	double **prod = (double **)malloc(n*sizeof(double *));
	for(int i=0; i<n; i++)
		prod[i] = (double *)malloc(n*sizeof(double));
	
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			prod[i][j] = 0.0;
			for(int k=0; k<n; k++)
				prod[i][j] += m1[i][k]*m2[k][j];
	}}
	return prod;
}*/

