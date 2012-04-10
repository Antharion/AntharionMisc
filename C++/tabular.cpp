/*
This program reads a tabular and saves the result in an 2D double array and vice versa.
What should work:
Numbers in the formats: 123.123, 123.123e123, 123.123E123
Setting the number of coumns
The Matrix is iniatalized with zeros

ToDo:
improve the 256 char limit per line

double* tab_read (unsigned int ncols, string data = "data.dat", char* delim = " ,;", bool debug = false){
void 	tab_write(unsigned int ncols, unsigned int nrows, double matrix[], char delim = ' '){

*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int tab_count_rows(char* data){
	// nrows: number of rows in file data
	int			nrows 	= -1;

	ifstream infile;
	infile.open(data);

	if(debug){cout << "Counting rows" << endl;}
		while (!(infile.eof())){
			infile.getline (pcBuff,255);
			if(debug){cout << pcBuff << endl;
			}
		nrows++;
	}
	infile.close();
	return nrows;
	
}

// printing the matrix to the cout
void tab_output(double* matrix){
	cout << "Output" << endl;
	for (int i=0;i<nrows; i++){
		for (int j=0;j<ncols; j++){
			cout << matrix[i*ncols+j] << " "; 
		}
		cout << endl;
	}
}

double* tab_read(unsigned int ncols, char* data = "data.dat", char* delim = " ,;", bool debug = false){
	//  chars_per_line is the maximum number of characters per line.
	int chars_per_line = 255;
	// pcBuff is a buffer for the line, which is currently read
	char* 	pcBuff	= new char[chars_per_line];
	// Currently i do not know what itBuff does.
	char* 	itBuff	= new char[chars_per_line];
	// pch contains the most recently found table entry
	char* 	pch			= new char[chars_per_line];
	// nrows: number of rows in file data
	int			nrows 	= tab_count_rows(data)

	// Allocating and initializing the array
	double* matrix = new double[nrows*ncols];
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
	while (!(infile.eof()))
	{
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
		tab_output(matrix);
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


void tab_write(unsigned int ncols, unsigned	int nrows, double matrix[], char delim = ' '){
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
