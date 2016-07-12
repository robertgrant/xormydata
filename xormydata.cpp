#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
using std::ios;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::ios_base;


// args: infile incode outfile [startcode remove?]
int main(int argc, char *argv[]) {
	// get arguments
	if(argc!=4) {
	    cerr << "Arguments missing: should be input file, then coding file, then output file" << endl;
	    return -1;
	}
	stringstream sarg;
	string infile;
	string incode;
	string outfile;
	infile = argv[1];
	incode = argv[2];
	outfile = argv[3];

	// get infile size
	int insize=0;
  ifstream inst;
  inst.open(infile, ios_base::binary);
  inst.seekg(0,ios_base::end);
  insize = inst.tellg();
	inst.seekg(0,ios_base::beg);
	cout << "Input file length: " << insize << " bytes" << endl;

	// get codefile size
	int codesize=0;
  ifstream codest;
  codest.open(incode, ios_base::binary);
  codest.seekg(0,ios_base::end);
  codesize = codest.tellg();
  codest.seekg(0,ios_base::beg);
	if (codesize < insize) {
		cerr << "Warning! The coding file is smaller than the input file. Coding will repeat from the beginning. Technically, this increases the risk of code breaking." << endl;
	}
	cout << "Coding file length: " << codesize << " bytes" << endl;


	/* Note: If you are a GNU g++ user (version 2.7.x or earlier), then do not use i/o mode flags when opening ifstream objects. Because of a bug in the GNU libg++ implementation, the flags will not be correctly interpreted. If you are working under Unix, omit the i/o mode flags entirely; if you are working with g++ under MS-DOS, then use an fstream object. This note applies to g++ users only.

	From http://courses.cs.vt.edu/~cs2604/fall00/binio.html */

	ofstream outst;
	outst.open(outfile, ios::out | ios::binary);


	char inbuff[1];
	char inchar;
	int inbytes;
	int codebytes;
	char codebuff[1];
	char codechar;
	char outbuff[1];
	char outchar;
	int inint;
	int codeint;
	int outint;
	if(inst) {
	        while(!inst.eof()) {
							inst.read(inbuff, 1);
							inchar = inbuff[0];
							inint = (char)inchar;
							inbytes = inst.gcount(); 	// get number of bytes read from infile
							if(!codest) {
									cerr << "Error when attempting to read from the coding file" << endl;
									return -1;
							}
							else {
									codest.read(codebuff, 1);
									codechar = codebuff[0];
									codeint = (char)codechar;
									codebytes = codest.gcount(); 	// get number of bytes read from codefile
									outint = inint ^ codeint;
									outchar = (int)outint;
									outbuff[0] = outchar;
									outst.write(outbuff, 1);
							}
					}
	}
	else {
		  cerr << "Error when attempting to read from the input file" << endl;
			return -1;
  }
	inst.close();
	codest.close();
	outst.close();
	return 0;

}
