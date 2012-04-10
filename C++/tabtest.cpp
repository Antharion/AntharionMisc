#include "tabular.cpp"

int main(int argc, char *argv[]){

	double* matrix =  tab_read(5, "test.dat", " ,;", true); 
	int ncols = 5;
	int nrows = 3;
	cout << "Output 2:" << endl;
	for (int i=0;i<nrows; i++){
		for (int j=0;j<ncols; j++){
			cout << matrix[i*ncols+j] << " "; 
		}
		cout << endl;
	}


	tab_write(5, 3, matrix);
}
