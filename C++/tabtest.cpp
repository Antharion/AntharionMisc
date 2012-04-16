#include "tabular.cpp"

int main(int argc, char *argv[]){
	char data[] 		= "THISLONGFILENAME.DAT";
	char delim[] 		= " ,;";
	int chars_per_line 	= 255;
	bool debug 		= true;

	
	double* matrix = tab_read(data, delim, chars_per_line, debug); 
	tab_output(matrix, tab_count_rows(data), tab_count_cols(data));
	tab_write (matrix, tab_count_rows(data), tab_count_cols(data));
}
