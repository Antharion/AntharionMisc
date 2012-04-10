/*
This program reads a tabular and saves the result in an 2D double array and vice versa.
What should work:
Numbers in the formats: 123.123, 123.123e123, 123.123E123
Setting the number of coumns
The Matrix is iniatalized with zeros

double* tab_read (unsigned int ncols, string data = "data.dat", char* delim = " ,;", bool debug = false){
void 	tab_write(unsigned int ncols, unsigned int nrows, double matrix[], char delim = ' '){

*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;

double* tab_read(unsigned int ncols, char* data = "data.dat", char* delim = " ,;", bool debug = false){
	int 	nrows 		= -1			;
	char* 	pcBuff		= new char[255]	;
	char* 	itBuff		= new char[255]	;
	char* 	pch			= new char[255]	;

	ifstream infile;
	infile.open(data);

	if(debug){cout << "Counting rows" << endl;}
	while (!(infile.eof())){
		infile.getline (pcBuff,255);
		if(debug){cout << pcBuff << endl;}
		nrows++;
	}

	infile.close();
	double* matrix = new double[nrows*ncols];
	for(int i = 0; i < nrows*ncols; i++){
		matrix[i]=0;
	}
	if(debug){cout << "Created Matrix with "  << nrows  << " rows and " << ncols << " Columns" << endl;}

	infile.open("test.dat");

	int mrows = 0;
	int mcols = 0;

	if (!(infile.is_open())){
		cout << "Fehler:Datei konnte nicht geöffnet werden" << endl; 
		return NULL;
	}

	if(debug){cout << infile.eof()  << endl;}
	while (!(infile.eof()))
	{
		infile.getline(pcBuff,255);
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
		cout << "Output" << endl;
		for (int i=0;i<nrows; i++){
			for (int j=0;j<ncols; j++){
				cout << matrix[i*ncols+j] << " "; 
			}
			cout << endl;
		}
	}

//	delete [] delim;
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
