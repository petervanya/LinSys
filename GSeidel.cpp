/*** Gauss-Seidel method ***********************/
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
	double **U = allocMatrix(N);
	double **LD = allocMatrix(N);
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
	
	/*** create L+D and U matrix ***/
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(i>=j)	LD[i][j] = A[i][j];
			if(i<j)		U[i][j] = A[i][j];
	}}
	
	while(norm(vectorSubtr(x0,x1,N), N) > eps){
		copyVec(x1, x0, N);				// update x0
		double *temp = allocVector(N);
		for(i=0; i<N; i++)
			for(j=0; j<N; j++)
				temp[i] -= U[i][j]*x0[j];
		temp = vectorAdd(temp, b, N);
		forwSubst(LD, x1, temp, N);
		counter++;
	}
	if(counter > 30)
		cout << "The system did not converge.\n";
	else{
		cout << "The system converged after " << counter << " steps.\n The resulting vector:\n";
		printVector(x1,N);
	}
	
	/*freeMatrix(A,N);
	freeMatrix(U,N);
	freeMatrix(LD,N);
	freeVector(b);
	freeVector(x0);
	freeVector(x1);*/
}

