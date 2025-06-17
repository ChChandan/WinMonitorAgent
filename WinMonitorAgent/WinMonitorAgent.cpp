#include <windows.h>
#include <psapi.h>
#include <tchar.h>
#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include <iostream>
using namespace std;


void getRunningProcess() {
	DWORD processes[1024], cbNeeded, processCount;
    unsigned int i;

    if(!EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
        std::cerr << "Failed to enumerate processes." << std::endl;
        return;
	}

	processCount = cbNeeded / sizeof(DWORD);
    std::ofstream logFile("C:\\Users\\chandan\\source\\repos\\WinMonitorAgent\\logfile.txt", std::ios::app);
    

    for (i = 0; i < processCount; i++) {
		if (processes[i] == 0) continue; // Skip if process ID is 0
        TCHAR processName[MAX_PATH] = TEXT("<unknown>");
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
        if (hProcess) {
            HMODULE hmod;
            DWORD cbNeededMod;
            if (EnumProcessModules(hProcess, &hmod, sizeof(hmod), &cbNeededMod)) {
                GetModuleBaseName(hProcess, hmod, processName, sizeof(processName) / sizeof(TCHAR));

            }

            logFile << processName << " (PID: " << processes[i] << ")\n";
            CloseHandle(hProcess);

        }
    
    }
        logFile.close();
}

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
    //getRam();
	getRunningProcess();
	
    return 0;
}

