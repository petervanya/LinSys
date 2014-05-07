/*** Algorithm for QR factorisation  ***********/
/* in the form of Givens rotations
/***********************************************/
#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include"simpleMatrix.h"
using namespace std;

double DotProdM(double **, int, double **, int, int);
double **Transpose(double **, int);

int main()
{
	int N = 3, i,j,k;
	double mag = 0.0;					// dummy variable
	double *DP = allocVector(N-1);		// array of dot products 
	double *NormSq = allocVector(N-1);	// array of squared norms of matrix columns
	
	double **A = allocMatrix(N);
	double **R = allocMatrix(N);
	double **Q = allocMatrix(N);
	double **QT = allocMatrix(N);
	double **temp = allocMatrix(N);
	
	/*** reading in the matrix ***/
	ifstream cucaj("matrix.txt");
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cucaj >> A[i][j];
			R[i][j] = A[i][j];		// first iteration of R is A
	}}
	
	cout << "Original matrix: \n";
	printMatrix(A,N);
		
	// initialise Q
	for(i=0; i<N; i++)
		Q[i][i] = 1.0;
	
	/*** QR algorithm ***************************
	1. create rotation matrix temp, that will create 0 at A[i,k] (starting at k = 0)
	2. set R = Q*R; R first is A;
	2. set Q = temp*Q, first time Q[:,:] set to 0
	3. create temp creating 0 at another position
	/*******************************************/
	for(k=0; k<N; k++){		// each vector
		for(j=k+1; j<N; j++){
			// set temp 
			for(i=0; i<N; i++){
				for(int ii=0; ii<N; ii++){
					if(i == ii)	temp[i][ii] = 1.0;
					else		temp[i][ii] = 0.0;
			}}
			mag = sqrt( R[k][k]*R[k][k] + R[j][k]*R[j][k] );
			temp[j][j] = R[k][k]/mag;
			temp[j][k] = -R[j][k]/mag;
			temp[k][k] = R[k][k]/mag;
			temp[k][j] = R[j][k]/mag;
			
			R = matrixMult(temp,R,N);	// overall upper triangular matrix
			Q = matrixMult(temp,Q,N);	// overall rotation matrix
	}}	//*/
	
	/*** rounding of R ***/
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			if(abs(R[i][j]) < 1e-15) R[i][j] = 0.0;
	
	cout << "Final matrix R:\n";
	printMatrix(R,N);
	cout << "Matrix Q:\n";
	printMatrix(Q,N);
	
	cout << "Sanity check 1: are colums of Q orthogonal?:\n";
	cout << DotProdM(Q,1,Q,2,N) << "\t" <<  DotProdM(Q,1,Q,3,N) << "\t" << DotProdM(Q,2,Q,3,N) << endl;
	
	// sanity check: create Q^T
	cout << "Sanity check 2: is QT*R the original matrix?\n";
	QT = Transpose(Q,N);
	printMatrix(matrixMult(QT,R,N),N);
	
	freeMatrix(A,N);
	freeMatrix(R,N);
	freeMatrix(Q,N);
	freeMatrix(QT,N);
	freeMatrix(temp,N);
	freeVector(DP,N);
	freeVector(NormSq,N);
}


double DotProdM(double **A, int i, double **B, int j, int N){	// dot product for i-th and j-th column of a matrix
	double D = 0.0;
	for(int k=0; k<N; k++)
		D += A[k][i]*B[k][j];
	return D;
}

double **Transpose(double **A, int N){
	int i,j;
	double **C = allocMatrix(N);	
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			C[i][j] = A[j][i];
	return C;
}

