#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <termios.h>
#include <unistd.h>
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
	if(argc<4) {
	    cerr << "Arguments missing: should be input file, then coding file, then output file" << endl;
	    return -1;
	}
	stringstream sarg;
	string infile;
	string incode;
	string outfile;
	stringstream stringstartcode;
	infile = argv[1];
	incode = argv[2];
	outfile = argv[3];
	int startcode = 0;
	// first, the completely specified arguments: data file, code file, outfile, start byte
	if(argc==5) {
		stringstartcode << argv[4];
		stringstartcode >> startcode;
	}
	// now, data file, outfile, and the secret tag (-s or --secret)
	else if(argc==4 && (outfile=="-s" || outfile=="--secret")) {
		outfile = incode; // locations reverse
		// get code file
		string codecin;
		string startcin;
		cout << "Coding file:" << endl;
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		getline(cin,codecin);
		if(codecin.length() > 0) {
			stringstream(codecin) >> incode;
		}
		else {
			cerr << "Error! No code file has been specified." << endl;
			return -2;
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
		// get start byte
		cout << "Coding file start byte:" << endl;
    /*
		termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
		*/
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		getline(cin,startcin);
		if(startcin.length() > 0) {
			stringstream(startcin) >> startcode;
		}
		else {
			cout << "Warning! No start byte has been specified." << endl;
			cout << "Coding will start at the beginning of the code file, which may be vulnerable to attack because of predictable metadata." << endl;
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	}
	// now, the data file, code file and outfile
	else {
		string startcin;
		cout << "Coding file start byte:" << endl;
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
		getline(cin,startcin);
		if(startcin.length() > 0) {
			stringstream(startcin) >> startcode;
		}
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	}

	// get infile size
	int insize=0;
  ifstream inst;
  inst.open(infile, ios_base::binary);
  inst.seekg(0,ios_base::end);
  insize = inst.tellg();
	inst.seekg(0,ios_base::beg);

	// get codefile size
	int codesize=0;
  ifstream codest;
  codest.open(incode, ios_base::binary);
  codest.seekg(0,ios_base::end);
  codesize = codest.tellg();
	codesize = codesize - startcode;
  codest.seekg(startcode,ios_base::beg);
	if (codesize < insize) {
		cerr << "Error! The coding file (from the start point) is smaller than the input file." << endl;
		cout << "Input file length: " << insize << " bytes" << endl;
		cout << "Coding file length: " << codesize << " bytes" << endl;

	}


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
	        while(true) {
							inst.read(inbuff, 1);
							if(inst.eof()) {
								break;
							}
							inchar = inbuff[0];
//						cout << "inchar:" << inchar << endl;
							inint = (char)inchar;
//							cout << "inint:" << inint << endl;
							inbytes = inst.gcount(); 	// get number of bytes read from infile
							if(!codest) {
									cerr << "Error when attempting to read from the coding file" << endl;
									return -3;
							}
							else {
									codest.read(codebuff, 1);
									codechar = codebuff[0];
//									cout << "codechar:" << codechar << endl;
									codeint = (char)codechar;
//									cout << "codeint:" << codeint << endl;
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
			return -4;
  }
	inst.close();
	codest.close();
	outst.close();
	return 0;

}
