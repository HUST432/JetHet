#include "Console.h"
#include <windows.h>
#define INITCOLOR(handle)  auto conh = GetStdHandle(handle)
#define SETCOLOR(color,op)  SetConsoleTextAttribute(conh, color);op;    SetConsoleTextAttribute(conh, 7)
#define FOREGROUND_INTSRED 0x004F
#define FOREGROUND_YELLOW  0x0006
#define FOREGROUND_INTSYELLOW 0x006F
#define FOREGROUND_INTSGREEN 0x002F
#define FOREGROUND_INTSBLUE 0x001F
void Console::Error(string err)
{
    INITCOLOR(STD_ERROR_HANDLE);
    SETCOLOR( FOREGROUND_INTSRED,cerr << "[Error]" );
    SETCOLOR(FOREGROUND_RED,cerr  << err << endl);
}

void Console::Error(int code, string err)
{
    err += "\t Error Code:";
    char msg[100];
    strcpy_s(msg, err.c_str());
    sprintf_s(msg + err.length(), 20, "%d", code);
    INITCOLOR(STD_ERROR_HANDLE);
    SETCOLOR(FOREGROUND_INTSRED, cerr << "[Error]");
    SETCOLOR(FOREGROUND_RED, cerr << err << endl);
}

void Console::Warning(string warn)
{
    INITCOLOR(STD_OUTPUT_HANDLE);
    SETCOLOR(FOREGROUND_INTSYELLOW, cout << "[Warning]");
    SETCOLOR(FOREGROUND_YELLOW, cout << warn << endl);
    
}

void Console::Log(string msg)
{
    INITCOLOR(STD_OUTPUT_HANDLE);
    SETCOLOR( FOREGROUND_INTSGREEN, cout << "[Info]");
    SETCOLOR(FOREGROUND_GREEN,cout << msg << endl);
}

void Console::Throw(int code, string err)
{ 
    err += "\t Error Code:";
    char msg[100];
    strcpy_s(msg, err.c_str());
    sprintf_s(msg + err.length(), 20, "%d", code);
    throw msg;
}

void Console::SendInfo(string msg)
{
    INITCOLOR(STD_OUTPUT_HANDLE);
    SETCOLOR(FOREGROUND_INTSBLUE, cout << "[Send]");
    SETCOLOR(FOREGROUND_BLUE, cout << msg << endl);
}
