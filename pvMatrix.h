/***** file containing all the necessary functions ********/
double **allocMatrix(int N){
	int i;
	double **A = new double *[N];
	for(i=0; i<N; i++)
		A[i] = new double[N];
	return A;
}

void freeMatrix(double **A, int N){
	int i;
	for(i=0; i<N; i++)
		delete[] A[i];
	delete[] A;
}

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
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			A[i][j] = 1.0;
	}}
}


void printMatrix(double **A, int N){
	int i,j;	
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			cout << A[i][j] << "\t";
		}cout << endl;
	}
}

double **matrixProd(double **A, double **B, int N){
	int i,j,k;
	double **C = allocMatrix(N);
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			C[i][j] = 0.0;
		
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			for(k=0; k<N; k++){
				C[i][j] += A[i][k] * B[k][j];
		}}}
	return C;
}
