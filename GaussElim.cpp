/*** Gaussian elimination **********************/
#include<iostream>
#include<fstream>
#include<cmath>
#include"simpleMatrix.h"
using namespace std;

void backSubst(double **A, double *x, double *b, int N){
	int i,j;
	double sum;		// dummy variable
	for(i=N-1; i>=0; i--){
		sum = 0.0;
		// getting the sum
		for(j=i+1; j<N; j++)
			sum += A[i][j]*x[j];
			
		x[i] = (b[i] - sum)/A[i][i];
	}
}

int main()
{
	int i,j,k, N = 3;
	double **B = allocMatrix(N);	// matrix
	double *b = allocVector(N);		// RHS vector
	double *x = allocVector(N);		// the sought vector
	double a;			// dummy var
	ifstream RHScucaj("RHSvector.txt");
	ifstream cucaj("matrix.txt");

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			cucaj >> B[i][j];
		
	/*** RHS vector allocation ***/
	for(i=0; i<N; i++)
		RHScucaj >> b[i];
			
	cout << "Original matrix:" << endl;
	printMatrix(B,N);
	cout << "Original RHS vector: " << endl;
	printVector(b,N);
	
	/*** Below-diagonal elimination *************
	/*** pseudocode *****************************
	denote columns by k, start by 1st column
	for every k
		for every row i (start with 2nd row), where i<k
			multiply every element of (i-1)th row by -B[i][k] / B[i-1][k]
			add for every column j, B[i][j] += B[i-1][j]
		end
	end	
	*/
	
	/*** eliminating below-diagonal space ******/
	for(k=0; k<N; k++){
		for(i=k+1; i<N; i++){			
			a = B[i][k] / B[k][k];	
			for(j=0; j<N; j++)			// multiply every element of (i-1)th row by a number, -B[i][k] / B[k][k]
				B[k][j] *= -a;
			b[k] *= -a;
			
			for(j=0; j<N; j++)			// add to (i-1)th row to the k-th row
				B[i][j] += B[k][j];
			b[i] += b[k];
		}
	}
	
	/*** eliminating above-diagonal part ***
	/*** USELESS NOW ***
	for(k=N-1; k>0; k--){
		for(i=k-1; i>=0; i--){		// above diagonal, going from the bottom
			// multiply every element of (i-1)th row by a number, -B[i][k] / B[k][k]
			a = B[i][k] / B[k][k];
			for(j=0; j<N; j++)
				B[k][j] *= -a;
			b[k] *= -a;
			// add to (i-1)th row to the k-th row
			for(j=0; j<N; j++)
				B[i][j] += B[k][j];
			b[i] += b[k];
		}
	}	//*/
	
	/*** cleaning the diagonal ***
	/*** USELESS NOW ***
	for(k=0; k<N; k++){
		b[k] /= B[k][k];
		B[k][k] /= B[k][k];
	}//*/
	
	/*** backward substitution *****************/
	backSubst(B,x,b,N);
		
	cout << "Upper-diagonal matrix:" << endl;
	printMatrix(B,N);
	cout << "The solution:" << endl;
	printVector(x,N);
	
	freeMatrix(B,N);
	freeVector(x,N);
	freeVector(b,N);
}
	
	
