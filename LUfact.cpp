/*** LU factorisation ***/
#include<iostream>
#include<fstream>
#include<cmath>
#include"simpleMatrix.h"
using namespace std;

int main()
{
	int i,j,k,n, N = 3;
	double **A = allocMatrix(N);	// original matrix
	double **L = allocMatrix(N);
	double **U = allocMatrix(N);
	double **D = allocMatrix(N);
	
	/*** dummy vectors ***/
	double *u = allocVector(N);
	double *l = allocVector(N);
	
	/*** initialising A ***/
	ifstream cucaj("matrix.txt");
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			cucaj >> A[i][j];//*/
	
	cout << "Original matrix:\n";
	printMatrix(A,N);
	
	/*** LU factorisation code ***/
	for(n=0; n<N; n++){
		for(i=0; i<N; i++)
			u[i] = A[n][i];
		for(i=0; i<N; i++)
			l[i] = A[i][n] / u[n];
		
		for(i=0; i<N; i++){		// subtracting the n-th LU bit from A
			for(j=0; j<N; j++){
				A[i][j] -= l[i]*u[j];
		}}
		
		for(i=0; i<N; i++){
			L[i][n] = l[i];
			U[n][i] = u[i];
		}
		//cout << "\nn=" << n+1 << endl;
		//printVector(u,N);
		//printVector(l,N);
		//printMatrix(A,N);
	}
	
	/*** adding Cholesky factorisation ***/
	/*** symmetric matrice A required! ***/
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(i==j)	D[i][j] = 1/U[i][j];
			else		D[i][j] = 0.0;
	}}
	U = matrixMult(D,U,N);
	for(i=0; i<N; i++)
		D[i][i] = 1/D[i][i];
	
	
	cout << "Matrix L:\n";
	printMatrix(L,N);
	cout << "Matrix U:\n";
	printMatrix(U,N);
	cout << "Matrix D:\n";
	printMatrix(D,N);
	
	/*** verification ***/
	//cout << "Verification: L*U = \n";
	//printMatrix(matrixMult(L,U,N),N);//*/
	
	
	return 0;
}	

