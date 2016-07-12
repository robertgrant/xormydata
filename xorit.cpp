#include <iostream>
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

int main(int argc, char *argv[]) {
string xinstr;
string yinstr;
xinstr=argv[1];
yinstr=argv[2];
char xin=xinstr[0];
char yin=yinstr[0];
int xout=(char)xin;
int yout=(char)yin;
int zout=xout ^ yout;
char zch=char(zout);
cout << xin << " (" << xout << ") XOR " << yin << " ("<< yout << ") = " ;
cout << zch << " (" << zout << ")" << endl;
return 0;
}
