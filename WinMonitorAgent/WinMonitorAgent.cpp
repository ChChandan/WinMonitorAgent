#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
using namespace std;

void getRam() {
	MEMORYSTATUSEX memoryStatus;
	memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memoryStatus);

    DWORDLONG totalVirtualMem = memoryStatus.ullTotalPageFile;
    DWORDLONG virtualMemUsed = memoryStatus.ullTotalPageFile - memoryStatus.ullAvailPageFile;

    DWORDLONG totalPhysMem = memoryStatus.ullTotalPhys;
    DWORDLONG physMemUsed = memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;

    std::ofstream logFile("C:\\Users\\chandan\\source\\repos\\WinMonitorAgent\\logfile.txt", std::ios::app);
    SYSTEMTIME st; 
    GetSystemTime(&st);
    logFile << "\n[LOG " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << "]\n";
    logFile << "RAM Usage: " << (physMemUsed / (1024 * 1024)) << " MB / " << (totalPhysMem / (1024 * 1024)) << " MB\n";
    logFile.close();

}


int main()
{
	getRam();
	
    return 0;
}

