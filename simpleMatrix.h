/*** a header with matrix functions ************/
/***********************************************/
/* for manipulating with square NxN            */
/* matrices and vectors                        */
/***********************************************/
#include<stdlib.h>

/*** prototypes ********************************/
double **allocMatrix(int);
void freeMatrix(double **, int);
double *allocVector(int);
void freeVector(double *, int);
/***********************************************/

double **allocMatrix(int N){
	double *mainBlock = new double [N*N];
	double **ptrsToRows = new double *[N];
	for(int i=0; i<N; i++)
		ptrsToRows[i] = mainBlock + i*N;
	// initialise to 0
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			ptrsToRows[i][j] = 0.0;
	return ptrsToRows;
}

void freeMatrix(double **A, int N){
	int i;
	for(i=0; i<N; i++)
		delete[] A[i];
	delete[] A;
}

/*** identity matrix ***/
void eye(double **A, int N){
	int i,j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			if(i==j)	A[i][j] = 1.0;
			else		A[i][j] = 0.0;
	}}
}

void ones(double **A, int N){
	int i,j;
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			A[i][j] = 1.0;
}

void printMatrix(double **A, int N){
	int i,j;
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			std::cout << A[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

/*** multiplication of two NxN matrices ***/
double **matrixMult(double **A, double **B, int N){
	int i,j,k;
	double **C = allocMatrix(N);
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			C[i][j] = 0.0;
			for(k=0; k<N; k++)
				C[i][j] += A[i][k] * B[k][j];
	}}
	return C;
	freeMatrix(C,N);
}

/*** matrix addition ***/
double **matrixAdd(double **A, double **B, int N){
	double **C = allocMatrix(N);
			
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			C[i][j] = A[i][j] + B[i][j];
	}}
	return C;
	freeMatrix(C,N);
}

/*** matrix subtraction ***/
double **matrixSubtr(double **A, double **B, int N){
	double **C = allocMatrix(N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			C[i][j] = A[i][j] - B[i][j];
	}}
	return C;
}

/*** matrix times number ***/
double **numTimesMat(double c, double **A, int N){
	double **C = allocMatrix(N);
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			C[i][j] = c*A[i][j];
	return C;
	freeMatrix(C,N);
}

/*** matrix divided by number ***/
double **numDivMat(double c, double **A, int N){
	double **C = allocMatrix(N);
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			C[i][j] = A[i][j]/c;
	return C;
	freeMatrix(C,N);
}

/*** multiply matrix by vector *****************/
double *matVecProd(double **A, double *b, int N){
	int i,k;
	double *a = allocVector(N);
	for(i=0; i<N; i++)
		a[i] = 0.0;
	for(i=0; i<N; i++){
		for(k=0; k<N; k++){
			a[i] += A[i][k]*b[k];
	}}
	return a;
}

/***********************************************/
/*** vectors
/***********************************************/
double *allocVector(int N){
	double *a = new double[N];
	for(int i=0; i<N; i++)
		a[i] = 0.0;
	return a;
}

void freeVector(double *a){
	delete[] a;
}
	
void printVector(double *v, int n){
	for(int i=0; i<n; i++)
		std::cout << v[i] << "\t";
	std::cout << std::endl;
}

double dotProd(double *u, double *v, int N){
	double sum = 0.0;
	for(int i=0; i<N; i++)
		sum += u[i]*v[i];
	return sum;
}

/*** get i-th row from matrix A ***/
double *matrixRow(double **A, int i, int N){
	if(i>=N)
		std::cerr << "Error: choosing a row outside the range {0,N}.\n";
	double *v_i = allocVector(N);	// i-th row
	for(int j=0; j<N; j++)
		v_i[j] = A[i][j];
	return v_i;
}

/*** get j-th column from matrix A ***/
double *matrixCol(double **A, int j, int N){
	if(j>=N || j<0)
		std::cerr << "Error: choosing a column outside the range {0,N}.\n";
	else{
		double *v_j = allocVector(N);
		for(int i=0; i<N; i++)
			v_j[i] = A[i][j];
		return v_j;
	}
}

double norm(const double *a, unsigned int N){
	int i;
	double sum = 0.0;
	for(i=0; i<N; i++)
		sum += a[i]*a[i];
	return sqrt(sum);
}

double normSq(const double *a, unsigned int N){
	int i;
	double sum = 0.0;
	for(i=0; i<N; i++)
		sum += a[i]*a[i];
	return sum;
}

/*** normalise vector ***/
void normalise(double *a, unsigned int N){
	double s = norm(a,N);
	for(int i=0; i<N; i++)
		a[i] = a[i]/s;
}

/*** outer product of two vectors ***/
double **outerProd(const double *u, const double *v, unsigned int N){
	double **A = allocMatrix(N);
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			A[i][j] = u[i]*v[j];
	return A;
}

/*** add two vectors ***************************/
double *vectorAdd(double *u, double *v, int N){
	int i;
	double *w = allocVector(N);	
	for(i=0; i<N; i++)
		w[i] = u[i] + v[i];
	return w;
}

/*** subtract two vectors **********************/
double *vectorSubtr(double *u, double *v, int N){
	int i;
	double *w = allocVector(N);	
	for(i=0; i<N; i++)
		w[i] = u[i] - v[i];
	return w;
}

/*** multiply vector by number *****************/
double *numTimesVec(double c, double *u, int N){
	int i;
	double *w = allocVector(N);	
	for(i=0; i<N; i++)
		w[i] = c*u[i];
	return w;
}

/*** divide vector by number *******************/
double *numDivVec(double c, double *u, int N){
	int i;
	double *w = allocVector(N);	
	for(i=0; i<N; i++)
		w[i] = u[i]/c;
	return w;
}

/*** copy 1st vector onto 2nd ******************/
void copyVec(double *x1, double *x2, int N){
	for(int i=0; i<N; i++)
		x2[i] = x1[i];
}

/***********************************************/
/*** Algorithms                                */
/***********************************************/

/*** backward substitution *********************/
void backSubst(double **A, double *x, double *b, int N){
	double sum;		// dummy variable
	for(int i=N-1; i>=0; i--){
		sum = 0.0;
		// getting the sum
		for(int j=i+1; j<N; j++)
			sum += A[i][j]*x[j];
			
		x[i] = (b[i] - sum)/A[i][i];
	}
}

/*** forward substitution **********************/
void forwSubst(double **A, double *x, double *b, int N){
	/*** assume A is in lower-diagonal form ***/
	double sum;		// dummy variable
	for(int i=0; i<N; i++){
		sum = 0.0;
		// getting the sum
		for(int j=0; j<i; j++)
			sum += A[i][j]*x[j];
			
		x[i] = (b[i] - sum)/A[i][i];
	}
}

