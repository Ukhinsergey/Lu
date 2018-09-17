#include <iostream>
#include <fstream>
#include <iomanip> 
#include <cmath>
#include <cfloat>


using namespace std;
const int w = 8;
const double eps = FLT_EPSILON;



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
	for ( i = n - 1; i >= 0; --i) {
		x[i] = y[i];
		for (j = n - 1; j > i; --j) {
			x[i] -= a[ind[i]][j] * x[j];
		}
	}
	delete []y;
}

void answer(int n, double **&a, double *&b, double *&x) {
	
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

	if (n <= 10) {
		cout << "L: \n";
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (i >= j) {
					cout << setw(w) << a[ind[i]][j] << ' ';
				} else {
					cout << setw(w) << 0 << ' ';
				}
			}
			cout << endl;
		}
		cout << "\n\n";
		cout << "U: \n";
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (i < j) {
					cout << setw(w) << a[ind[i]][j] << ' ';
				} else  if (i == j) {
					cout << setw(w) << 1 << ' ';
				} else {
					cout << setw(w) << 0 << ' ';
				}
			}
			cout << endl;
		}
		cout << "\n\n";
		cout << "X: \n";
		printmatr(x,n);
	} else {
		ofstream fout("output.txt"); 
		fout << "L: \n";
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (i >= j) {
					fout << setw(w) << a[ind[i]][j] << ' ';
				} else {
					fout << setw(w) << 0 << ' ';
				}
			}
			fout << endl;
		}
		fout << "\n\n";
		fout << "U: \n";
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				if (i < j) {
					fout << setw(w) << a[ind[i]][j] << ' ';
				} else  if (i == j) {
					fout << setw(w) << 1 << ' ';
				} else {
					fout << setw(w) << 0 << ' ';
				}
			}
			fout << endl;
		}
		fout << "\n\n";
		fout << "X: \n";
		for (i = 0; i < n; ++i) {
			fout << setw(w) << x[i] << endl;
		}
	}
	
	dif(n, a, b, x, ind) ;

}

int main(){
	int n;
	double **a;
	double *b;

	cout << "1 - fromfile, 2 - generate" << endl;
	int genmatr;
	cin >> genmatr;
	if (genmatr == 1) {
		ifstream fin("input.txt");
		if (!fin.is_open()) {
			cout << "cant open input.txt" << endl;
			return 1;
		}
		fin >> n;
		a = new double *[n];
		b = new double[n];
		int i,j;
		for(i = 0; i < n; ++i) {
			a[i] = new double[n];
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
		cout << "size = ";
		cin >> n;
		a = new double *[n];
		b = new double[n];
		int i,j;
		for(i = 0; i < n; ++i) {
			a[i] = new double[n];
		}
		for (i = 0; i < n; i++) {
			b[i] = 0;
			for (j = 0; j < n; j++) {
				a[i][j] = func(i,j);
				b[i] += a[i][j];
			}
		}
		printmatr(a,n);
		printmatr(b,n);
	}
	//printmatr(a,n);
	double *x = new double[n];
	answer(n, a, b, x);
	delete []x;
	freemem(a,b,n);
	return 0;
}