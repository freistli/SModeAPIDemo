// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <wldp.h>  
#include "PowerManager.h"
#pragma comment (lib,"wldp.lib") 
 
 
int IsSmode(void) {
    WLDP_WINDOWS_LOCKDOWN_MODE mode;
    WldpQueryWindowsLockdownMode(&mode);
    if (mode == WLDP_WINDOWS_LOCKDOWN_MODE_UNLOCKED) {
        return 0;
    }
    else if (mode == WLDP_WINDOWS_LOCKDOWN_MODE_TRIAL || mode == WLDP_WINDOWS_LOCKDOWN_MODE_LOCKED) {
        return 1;
    }
}
 

int main()
{

    CPowerManager *cpm = new CPowerManager();
     
    cpm->Start();
    int i = 0;
    std::cin >> i;
    std::cout << "Hello World!\n" << IsSmode();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
