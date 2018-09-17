#include <iostream>
#include <fstream>
#include <iomanip> 
#include <cmath>
#include <cfloat>


using namespace std;
const int w = 8;
const double eps = FLT_EPSILON;

void inline freematr(double **&a, int n) {
	int i;
	for(i = 0; i < n; ++i) {
		delete[] a[i];
	}
	delete[] a;
}


void freemem(double **&a, double *&b, int n){
	int i;
	for(i = 0; i < n; ++i) {
		delete[] a[i];
	}
	delete[] a;
	delete[] b;
}

void printmatr(double **a, int n) {
	int i,j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cout << setw(w) << a[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

template <typename T>
void printmatr(T b, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		cout << setw(w) << b[i] << endl;
	}
}

double func(int i,int j) {
	return 	(i + 1) * (i + 1) * (j + 1)- i;
}

void multmatr(double **&a, double **&b, int n) {
	double **c = new double*[n];
	int i,j,k;
	for (i =0; i < n; ++i) {
		c[i] = new double[n];
		for (k = 0 ; k < n; ++k) {
			c[i][k] = 0;
			for (j = 0 ;  j < n; ++j){
				c[i][k] += a[i][j] * b[j][k];
			}
		}

	}
	printmatr(c,n);
	freematr(c,n);
}


void gauss(int n, double **&a, double *&b, double *&x, int *&ind) {
	double *y = new double[n];
	int i,j;
	for(i = 0 ; i < n; ++i) {
		y[i] = b[ind[i]];
		for(j = 0 ; j < i; ++j) {
			y[i] -= a[ind[i]][j] * y[j];
		}
		y[i] /= a[ind[i]][i];
	}
	printmatr(y,n);
	for ( i = n - 1; i >= 0; --i) {
		x[i] = y[i];
		for (j = n - 1; j > i; --j) {
			x[i] -= a[ind[i]][j] * x[j];
		}
	}
	printmatr(x,n);
}

void answer(int n, double **&a, double *&b, double *&x) {
	/*double **l = new double *[n];
	double **u = new double *[n];
	for(i = 0; i < n; ++i) {
		l[i] = new double[n];
		u[i] = new double[n];
	}*/
	int i,j,k;
	int *ind = new int [n];
	for (i = 0 ; i < n; ++i) {
		ind[i] = i;
	}
	double max = 0;
	for (k = 0 ; k < n; ++k) {
		for( i = k; i < n; ++i) {
			for (j = 0; j <= k - 1; ++j) {
				a[ind[i]][k] -= a[ind[i]][j] * a[ind[j]][k];
			}
		}
		max = 0;
		int maxind = k;
		for (i = k ; i < n; ++i) {
			if (abs(a[ind[i]][k]) > max) {
				max = a[ind[i]][k];
				maxind = i;
			}
		}
		int t = ind[k];
		ind[k] = ind[maxind];
		ind[maxind] = t;
		if (abs(max) <= eps) {
			cout << "singular";
			return ;
		}
		for ( i = k + 1; i < n; ++i) {
			for (j = 0; j<= k - 1; ++j) {
				a[ind[k]][i] -= a[ind[k]][j] * a[ind[j]][i];
			}
			a[ind[k]][i] /= a[ind[k]][k];
		}
	}

	gauss(n, a, b, x, ind);
	/*
	for(i = 0 ; i < n; ++i) {
		l[i][0] = a[i][0];
		u[0][i] = a[0][i]/l[0][0];
		u[i][i] = 1;
	}
	for(k = 1 ; k < n; ++k) {
		for(i = k; i < n; ++i) {
			sum = 0;
			for (j = 0 ; j <= k - 1; ++j) {
				sum += l[i][j] * u[j][k ];
			}
			l[i][k] = a[i][k] - sum;
		}
		for (i = k + 1; i < n ; ++i) {
			sum = 0;
			for (j = 0; j <= k - 1; ++j) {
				sum += l[k][j] * u[j][i];
			}
			u[k][i] = (a[k][i] - sum)/l[k][k];
		}

	}*/
	printmatr(ind,n);
	printmatr(a,n);
	printmatr(b,n);
	//multmatr(l,u,n);
}

int main(){
	cout << "size =";
	int n;
	cin >> n;
	double **a = new double *[n];
	double *b = new double[n];
	int i,j;
	for(i = 0; i < n; ++i) {
		a[i] = new double[n];
	}

	cout << endl << "1 - fromfile, 2 - generate" << endl;
	int genmatr;
	cin >> genmatr;
	if (genmatr == 1) {
		ifstream fin("input.txt");
		if (!fin.is_open()) {
			cout << "cant open input.txt" << endl;
			freemem(a,b,n);
			return 1;
		}
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				fin >> a[i][j];
			}
			fin >> b[i];
		}
		//printmatr(a,n);
		//printmatr(b,n);
	} else {
		double sum;
		for (i = 0; i < n; i++) {
			sum = 0;
			for (j = 0; j < n; j++) {
				a[i][j] = func(i,j);
				sum += a[i][j];
			}
			b[i] = sum;
		}
		printmatr(a,n);
		//printmatr(b,n);
	}

	double *x = new double[n];
	answer(n, a, b, x);
	return 0;
}