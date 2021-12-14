#include "PowerManager.h"
#include <Windows.h> 
#include <iostream>
#include <tchar.h>
#include <powrprof.h>

using namespace std;
static ULONG PowerChanged(PVOID Context, ULONG Type, PVOID Setting);

ULONG PowerChanged(PVOID Context, ULONG Type, PVOID Setting)
{
	time_t ltime;
	wchar_t buf[SIZE];
	errno_t err;

	time(&ltime);

	err = _wctime_s(buf, SIZE, &ltime);

	if (err != 0)
	{
		cout << "Invalid Arguments for _wctime_s. Error Code:  " << err;
	}
	cout << L"The time is" << buf;

	if (Type == PBT_APMSUSPEND)
	{
		//had reports of the main window not showing clips after resuming (report was from a vmware vm), catch the resuming callback from windows
		//and close and reopen the database
		cout <<  L"windows is Suspending" ;
	}
	if (Type == PBT_APMRESUMESUSPEND)
	{
		//had reports of the main window not showing clips after resuming (report was from a vmware vm), catch the resuming callback from windows
		//and close and reopen the database
		cout << L"windows is RESUMING, sending message to main window to close and reopen the database/qpastewnd";

	}
	return 0;
}
CPowerManager::CPowerManager()
{
	m_registrationHandle = 0;
}


CPowerManager::~CPowerManager(void)
{
}


void CPowerManager::Start()
{

	HMODULE powrprof = LoadLibrary(_T("powrprof.dll"));
	if (powrprof != NULL)
	{
		DWORD(_stdcall * PowerRegisterSuspendResumeNotification)(_In_ DWORD, _In_ HANDLE, _Out_ PHPOWERNOTIFY);
		PowerRegisterSuspendResumeNotification = (DWORD(_stdcall*)(_In_ DWORD, _In_ HANDLE, _Out_ PHPOWERNOTIFY))GetProcAddress(powrprof, "PowerRegisterSuspendResumeNotification");
		if (PowerRegisterSuspendResumeNotification)
		{
			static _DEVICE_NOTIFY_SUBSCRIBE_PARAMETERS testCallback = { (DEVICE_NOTIFY_CALLBACK_ROUTINE*)&PowerChanged, nullptr };

			PowerRegisterSuspendResumeNotification(DEVICE_NOTIFY_CALLBACK, &testCallback, &m_registrationHandle);
		}

		::FreeLibrary(powrprof);
	}
}

void CPowerManager::Close()
{
	if (m_registrationHandle != 0)
	{
		HMODULE powrprof = LoadLibrary(_T("powrprof.dll"));
		if (powrprof != NULL)
		{
			DWORD(_stdcall * PowerUnregisterSuspendResumeNotification)(_Inout_ PHPOWERNOTIFY);
			PowerUnregisterSuspendResumeNotification = (DWORD(_stdcall*)(_Inout_ PHPOWERNOTIFY))GetProcAddress(powrprof, "PowerUnregisterSuspendResumeNotification");
			if (PowerUnregisterSuspendResumeNotification)
			{
				PowerUnregisterSuspendResumeNotification(&m_registrationHandle);
			}

			::FreeLibrary(powrprof);
		}
	}
}