/*
This program reads a tabular and saves the result in an 2D double array and vice versa.
What should work:
Numbers in the formats: 123.123, 123.123e123, 123.123E123
Setting the number of coumns
The Matrix is iniatalized with zeros

ToDo:
improve the 256 char limit per line

double* tab_read (unsigned int ncols, string data = "data.dat", char* delim = " ,;", bool debug = false){
void 	tab_write(double matrix[], int nrows, int ncols, char delim = ' '){

*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int tab_count_rows(char data[], int chars_per_line = 255, bool debug = false){
	if(debug){cout << "Entering tab_count_rows()" << endl;}
	// nrows: number of rows in file data
	int nrows = -1;
	// pcBuff is a buffer for the line, which is currently read
	char* 	pcBuff	= new char[chars_per_line];

	ifstream infile;
	infile.open(data);

	// Check if the Infile is open
	if (!(infile.is_open())){
		cout << "Fehler:Datei konnte nicht geöffnet werden" << endl; 
		return -1;
	}

	if(debug){cout << "Counting rows" << endl;}
	while (!(infile.eof())){
		if(debug){cout << "Still Counting, current count:" << nrows << endl;}
		infile.getline (pcBuff,255);
		nrows++;
	}
	infile.close();
	if(debug){cout << "Finished counting, final count:" << nrows << endl;}
	return nrows;
}

int tab_count_cols(char data[] = "data.dat", char delim[] = " ,;", int chars_per_line = 255, bool debug = false){
	if(debug){cout << "Entering tab_count_cols()" << endl;}
	// ncols: number of cols in file data
	int ncols = 0;
	// pcBuff is a buffer for the line, which is currently read	
	char*	pcBuff	= new char[chars_per_line];
	char* 	pch	= new char[chars_per_line];

	ifstream infile;
	infile.open(data);

	// Check if the Infile is open
	if (!(infile.is_open())){
		cout << "Fehler:Datei konnte nicht geöffnet werden" << endl; 
		return -1;
	}

	if(debug){cout << "Counting cols" << endl;}
	while (!(infile.eof())){
		infile.getline(pcBuff,chars_per_line);
		int mcols 	= 0;
		pch	= strtok(pcBuff,delim)	;
		while (pch != NULL){
			pch = strtok(NULL,delim);
			mcols++;
		}
		if(debug){cout << "Still Counting, current count:" << mcols << endl;}
		if(ncols < mcols){
			ncols=mcols;
		}
	}
	infile.close();
	if(debug){cout << "Finished counting, final count:" << ncols << endl;}
	return ncols;
}


// printing the matrix to the cout
void tab_output(double* matrix, int nrows, int ncols, int chars_per_line = 255, bool debug = false){
	if(debug){cout << "Entering tab_output()" << endl;}
	cout << "Output" << endl;
	for (int i=0;i<nrows; i++){
		for (int j=0;j<ncols; j++){
			cout << matrix[i*ncols+j] << " "; 
		}
		cout << endl;
	}
}

double* tab_read(char data[] = "data.dat", char delim[] = " ,;", int chars_per_line = 255, bool debug = false){
	if(debug){cout << "Entering tab_read()" << endl;}
	// pcBuff is a buffer for the line, which is currently read
	char* 	pcBuff	= new char[chars_per_line];
	// Currently i do not know what itBuff does.
	char* 	itBuff	= new char[chars_per_line];
	// pch contains the most recently found table entry
	char* 	pch	= new char[chars_per_line];
	// Counting rows and columns
	int	nrows 	= tab_count_rows(data,        chars_per_line, debug);
	int	ncols 	= tab_count_cols(data, delim, chars_per_line, debug);
	// Allocating and initializing the array
	double* matrix = new double[nrows*ncols];
	if(debug){cout << "Creating Matrix with "  << nrows  << " rows and " << ncols << " Columns" << endl;}
	for(int i = 0; i < nrows*ncols; i++){
		matrix[i]=0;
	}
	if(debug){cout << "Created Matrix with "  << nrows  << " rows and " << ncols << " Columns" << endl;}

	// Open the infile data, specified with the function call
	ifstream infile;
	infile.open(data);

	// Counter for the current position
	int mrows = 0;
	int mcols = 0;

	// Check if the Infile is open
	if (!(infile.is_open())){
		cout << "Fehler:Datei konnte nicht geöffnet werden" << endl; 
		return NULL;
	}

	// Parsing the file
	if(debug){cout << infile.eof()  << endl;}
	while (!(infile.eof())){
		infile.getline(pcBuff,chars_per_line);
		pch		= strtok(pcBuff,delim)	;
		mcols 	= 0						;
		while (pch != NULL){
			matrix[mrows*ncols + mcols] = atof(pch);
			pch = strtok(NULL,delim);
			mcols++;
		}
		mrows++;
	}


	if(debug){
		tab_output(matrix, nrows, ncols);
	}

	delete [] pcBuff;
	delete [] itBuff;
	delete [] pch;

	delim  = NULL;
	pcBuff = NULL;
	itBuff = NULL;
	pch    = NULL;

	return matrix;
}


void tab_write(double matrix[], int nrows, int ncols, char delim = ' '){
   FILE * pFile;
   int n;
 
   pFile = fopen ("outdata.dat","w");
	for(int i=0;i < nrows; i++){
		for(int j=0;j < ncols; j++){
			fprintf (pFile, "%.2e", matrix[i*ncols + j]);
			fputc(' ', pFile);
   		}
		fputc('\n', pFile);
	}   
	fclose (pFile);
}
