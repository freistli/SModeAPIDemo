#include <Windows.h>
#include <fstream>

#include <iostream>

#define SIZE 26

using namespace std;

class CPowerManager
{
public:
	CPowerManager();
	~CPowerManager(void);

	void Start();
	void Close();
protected:
	HPOWERNOTIFY m_registrationHandle;
};

