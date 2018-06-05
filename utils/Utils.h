#include<windows.h>
#include<winuser.h>
#include<fstream>
#include<sstream>
#include<vector>


using namespace std;


static ofstream logfile;

string i2s(int i);
string f2s(float fl);

int s2i(string s);

void LOG_INIT();

void LOG_FINIT();

void LOG_I(string str);

void read_file(string& str,string path);

LPCWSTR str2lpcwstr(string str);
