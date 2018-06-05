#include "Utils.h"

string i2s(int i)
{
    stringstream sout;
    string s;
    sout << i;
    sout >> s;
    return s;
}

string f2s(float fl)
{
    stringstream sout;
    string s;
    sout << fl;
    sout >> s;
    return s;
}

int s2i(string s)
{
    stringstream sout;
    int i;
    sout << s;
    sout >> i;
    return i;
}
void LOG_INIT()
{
    logfile.open("log.txt", ios::out|ios::trunc);
}

void LOG_FINIT()
{
    logfile.close();
}

void LOG_I(string str)
{
    logfile << str << "\n";
}

void read_file(string& str,string path)
{
    ifstream cv(path);
    char ch;
    if(cv.is_open())
    {
        while(!cv.eof())
        {
            cv.get(ch);
            str+=ch;
        }
        cv.close();
        return;

    }
    LOG_I("read "+path+" field");
}

LPCWSTR str2lpcwstr(string str)
{
    int cs = str.length() + 1;
    wchar_t* wc = new wchar_t[cs + 1];
    memset(wc, 0, (cs + 1) * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wc, cs);

    return wc;
}
