/*** Gramm-Schmidt orthogonalisation, QR factorisation ***/
#include<iostream>
#include<fstream>
#include<cmath>
#include"simpleMatrix.h"
using namespace std;

int main()
{
	int N = 3, i,j,k;
	double **A = allocMatrix(N);		// original set of vectors
	double *DP = allocVector(N);		// array of dot products
	double *NormSq = allocVector(N);	// array of squared norms of matrix columns
	
	/*** reading in the matrix ***/
	ifstream cucaj("matrix.txt");
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			cucaj >> A[i][j];
	
	cout << "Original matrix: \n";
	printMatrix(A,N);
			
	/*** Gram-Schmidt algorithm *****************
	1. select k-th vector a_k = A[:,k], starting with 2nd column, k=1
	2. produce dot product for i-th column, i<k, with k-th column: DP[i] = A[:,k], A[:,i],
	3. produce new vector A[:,k] = A[:,k] - sum_{i,i<k} DP[i]*A[:,i]
	/*******************************************/
	
	for(k=1; k<N; k++){		// each vector
		// producing dot products 
		for(j=0; j<k; j++){			
			DP[j] = dotProd(matrixCol(A,k,N), matrixCol(A,j,N), N);
			NormSq[j] = dotProd(matrixCol(A,j,N), matrixCol(A,j,N), N);
		}		
		// new, orthogonalised column A[:,k]
		for(i=0; i<N; i++){
			for(j=0; j<k; j++){	// summing the dot products
				A[i][k] -= DP[j]*A[i][j] / NormSq[j];
		}}		
	}//*/
	
	cout << "New matrix:\n";
	printMatrix(A,N);
	
	cout << "Verification: q1*q2 = ";
	cout << dotProd(matrixCol(A,0,N), matrixCol(A,1,N), N) << endl;
	
	return 0;
}


