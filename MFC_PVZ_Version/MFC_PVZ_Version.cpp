// MFC_PVZ_Version.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "MFC_PVZ_Version.h"
#include "Plants.h"
#include "module/readwrite/memory.h"
#include "Global.h"
int VersionResult = 0;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFCPVZVersionApp

BEGIN_MESSAGE_MAP(CMFCPVZVersionApp, CWinApp)
END_MESSAGE_MAP()


// CMFCPVZVersionApp 构造

CMFCPVZVersionApp::CMFCPVZVersionApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFCPVZVersionApp 对象

CMFCPVZVersionApp theApp;
//检测版本
int CheckVersion() {

    uintptr_t SteamVersionModule = memory::GetModuleAddress("popcapgame1.exe");
    uintptr_t ProcessExeModule = memory::GetModuleAddress("PlantsVsZombies.exe");

    if (SteamVersionModule != 0) {
        return 1;
    }

    if (ProcessExeModule != 0)
    {
      
        memory Mem;

        bool isGotyMemory = false;

        // 安全检查：如果地址可读且不为0
        if (!IsBadReadPtr((void*)0x731C50, 4)) {
            uintptr_t val = Mem.Read<uintptr_t>(0x731C50);
            if (val != 0) {
                isGotyMemory = true;
            }
        }

        if (isGotyMemory) {
            return 2; 
        }
        else {
            return 0;
        }
    }

    return -1;
}
DWORD WINAPI MainLogicThread(LPVOID lpThreadParameter) {

// CMFCPVZVersionApp 初始化
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	VersionResult = CheckVersion();
	Plants plant;
	plant.DoModal();
    HMODULE hModule = NULL;
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)&MainLogicThread, &hModule);
    if (hModule != NULL)
    {
        FreeLibraryAndExitThread(hModule, 0);
    }
	return 1;
}


BOOL CMFCPVZVersionApp::InitInstance()
{
	CWinApp::InitInstance();
    ::CreateThread(0,0, MainLogicThread,0,0,0);
	return TRUE;
}
