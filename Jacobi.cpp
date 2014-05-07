/*** Jacobi method *****************************/
#include<iostream>
#include<fstream>
#include<cmath>
#include"simpleMatrix.h"
using namespace std;

int main()
{
	int N = 3, i,j, counter = 0;
	double eps = 1e-5;
	double **A = allocMatrix(N);
	double **LU = allocMatrix(N);
	double **D = allocMatrix(N);
	double *b = allocVector(N);
	double *x0 = allocVector(N);
	double *x1 = allocVector(N);
	ifstream cucaj("matrix.txt");
	ifstream RHScucaj("RHSvector.txt");
	
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			cucaj >> A[i][j];
	
	for(i=0; i<N; i++)
		RHScucaj >> b[i];
	
	for(i=0; i<N; i++)
		x0[i] = 1.0;
	
	/*** create L, D, U matrices ***/
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(i!=j)	LU[i][j] = A[i][j];
			if(i==j)	D[i][j] = A[i][j];
	}}
	
	/*** D x^(k+1) = -(L+U) x^(k) + b ***/
	while(norm(vectorSubtr(x0,x1,N), N) > eps){
		copyVec(x1, x0, N);				// update x0
		double *temp = allocVector(N);
		for(i=0; i<N; i++)
			for(j=0; j<N; j++)
				temp[i] -= LU[i][j]*x0[j];
		x1 = vectorAdd(temp, b, N);
		for(i=0; i<N; i++)
			x1[i] /= D[i][i];
		counter++;
	}
	if(counter > 50)
		cout << "The system did not converge.\n";
	else{
		cout << "The system converged after " << counter << " steps.\n The resulting vector:\n";
		printVector(x1,N);
	}
	
	freeVector(b);
	freeVector(x0);
	freeVector(x1);
}

