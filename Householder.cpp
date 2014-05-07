/*** Algorithm for Householder reflections ***/
#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include"simpleMatrix.h"
using namespace std;

int main()
{
	int i,j,k, N = 3;
	double temp;
	double **A = allocMatrix(N);
	double **H = allocMatrix(N);
	double *u = allocVector(N);
	double *a = allocVector(N);
	
	/*** reading in the matrix ***/
	ifstream cucaj("matrix.txt");
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cucaj >> A[i][j];
	}}
	
	/*** printing the matrix ***/
	cout << "Matrix A:\n";
	printMatrix(A,N);
	
	
	/*** Creating Householder reflection *******/
	for(k=0; k<N-1; k++){
		/*** choose u ***/
		a = matrixCol(A,k,N);	// pick the k-th column of A
		for(i=0; i<N; i++){
			if(i<k)	
				u[i] = 0.0;
			else if(i==k){
				u[i] = a[i];
				temp = 0.0;
				for(j=k; j<N; j++)
					temp += a[j]*a[j];
				u[i] += sqrt(temp);
				
			}else
				u[i] = a[i];
		}
		
		//cout << "Vector u, norm squared: " << normSq(u,N) << endl;
		//printVector(u,N);
		
		normalise(u,N);
		
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				H[i][j] = -2*u[i]*u[j];
				if(i==j)	H[i][j] += 1.0;		// adding identity
		}}
	
		cout << "Householder reflection matrix:\n";
		printMatrix(H,N);
		
		/*** reflecting A ***/
		A = matrixMult(H,A,N);	
		
		/*** rounding ***/
		for(i=0; i<N; i++)
			for(j=0; j<N; j++)
				if(abs(A[i][j]) < 1e-15) 	A[i][j] = 0.0; //*/
	
		cout << "Matrix A reflected:\n";
		printMatrix(A,N);
		cout << "------------------------------\n";
	}
	/*******************************************/
	
	freeMatrix(A,N);
	freeMatrix(H,N);
	freeVector(a,N);
	freeVector(u,N);
}
	

