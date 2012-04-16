#include "tabular.cpp"

int main(int argc, char *argv[]){

	double* matrix =  tab_read(5, "test.dat", " ,;", true); 
	int ncols = 5;
	int nrows = 5;
	tab_output(matrix, nrows, ncols);
	tab_write(matrix, nrows, ncols);
}
