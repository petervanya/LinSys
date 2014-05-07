#include<iostream>
#include<fstream>
using namespace std;

class pvMatrix
{
private:
	int i,j,k;
	int N;
	double **A;

public:
	pvMatrix (int n){
		A = new double *[n];
		for(i=0; i<n; i++)
			A[i] = new double [n];
		
		for(i=0; i<n; i++){
			for(j=0; j<n; j++){
				A[i][j] = 0.0;
		}}
		N = n;
	}
	
	pvMatrix eye(){
		A = new double *[N];
		for(i=0; i<N; i++)
			A[i] = new double [N];
			
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				if(i==j) 	A[i][j] = 1.0;
				else		A[i][j] = 0.0;
		}}
	}		

	/*** methods ***/
	int getSize(){
		return N;
	}
	
	double getij(int i, int j){
		return A[i][j];
	}
	
	void setij(int i, int j, double c){
		A[i][j] = c;
	}
	
	void print(){
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				std::cout << A[i][j] << "\t";
			}
		std::cout << endl;}
	}
		
	void print(ofstream &tlac){
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				tlac << A[i][j] << "\t";
			}
		tlac << endl;}
	}
	
	void free(){
		for(i=0; i<N; i++)
			delete[] A[i];
		delete[] A;
	}
	
	/******** operators **********/
	/*** accessing matrix element ***/
	double operator()(int i, int j){
		return A[i][j];
	}
	
	/*** matrix addition ***/
	pvMatrix operator+(const pvMatrix B){
		pvMatrix C(N);
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				C.setij(i,j, A[i][j] + B(i,j) );
		}}
		return C;
	}
	
	/*** matrix * number ***/
	pvMatrix operator*(const double c){		// defining A*c... How to define c*A?
		pvMatrix B(N);
		for(i=0; i<N; i++){
			for(j=0; j<N; j++){
				B.setij(i,j, c*A[i][j] );
		}}
		return B;
	}
	
	/*** matrix multiplication ***/
	pvMatrix operator*(const pvMatrix B){		// defining A*c... How to define c*A?
		if(B.getsize() == N){
			pvMatrix C(N);
			for(i=0; i<N; i++){
				for(j=0; j<N; j++){
					for(k=0; k<N; k++){
						C.setij(i,j, C(i,j) + A[i][k]*B(k,j) );
					}
			}}
			return C;
		}
		else cout << "The matrix sizes are not the same.\n";
	}
	
	

};

/**************************************************/
int main()
{
	int N = 3, c = 2;
	pvMatrix A(N), B(N), C(N);
	A.eye();
	//ofstream tlac("pokus.txt");
	
	cout << A.getSize() << endl;
	A.setij(1,2,3);;
	cout << "A:\n";
	A.print();
	
	B = A*c;
	cout << "B:\n";
	B.print();
	
	C = A*B;					// C = A+B tested, all right
	cout << "C:\n";
	C.print();
	
	A.free();
	B.free();
	C.free();
	
	
}
