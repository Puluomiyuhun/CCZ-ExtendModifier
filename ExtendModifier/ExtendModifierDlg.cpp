
// ExtendModifierTEJI.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ExtendModifier.h"
#include "ExtendModifierDlg.h"
#include "ExtendModifierTEJI.h"
#include "ExtendModifierTEJI2.h"
#include "ExtendModifierDAOJU.h"
#include "ExtendModifierMEFF.h"
#include "ExtendModifierFORGE.h"
#include "ExtendModifierZHUANGBEI.h"
#include "afxdialogex.h"
#include "commctrl.h"
#include <iostream>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CExtendModifierTEJI* pDlg_TEJI;
CExtendModifierTEJI2* pDlg_TEJI2;
CExtendModifierDAOJU* pDlg_DAOJU;
CExtendModifierMEFF* pDlg_MEFF;
CExtendModifierFORGE* pDlg_FORGE;
CExtendModifierZHUANGBEI* pDlg_ZHUANGBEI;

// CExtendModifierTEJI 对话框
CExtendModifierDlg::CExtendModifierDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXTENDMODIFIER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtendModifierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CExtendModifierDlg::OnInitDialog()
{
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	//SetWindowLong(this->m_hWnd, GWL_EXSTYLE, GetWindowLong(this->m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);//要使使窗体拥有透明效果,首先要有WS_EX_LAYERED扩展属性
	//this->SetLayeredWindowAttributes(0, 230, LWA_ALPHA);//整个窗口按透明度透明化			

	if (pDlg_TEJI == NULL) {
		pDlg_TEJI = new CExtendModifierTEJI;
		pDlg_TEJI->Create(IDD_EXTENDMODIFIER_TEJI, this);    //创建对话框
	}
	pDlg_TEJI->ShowWindow(SW_SHOW);
	if (pDlg_TEJI2 == NULL) {
		pDlg_TEJI2 = new CExtendModifierTEJI2;
		pDlg_TEJI2->Create(IDD_EXTENDMODIFIER_TEJI2, this);    //创建对话框
	}
	pDlg_TEJI2->ShowWindow(SW_HIDE);
	/*if (pDlg_DAOJU == NULL) {
		pDlg_DAOJU = new CExtendModifierDAOJU;
		pDlg_DAOJU->Create(IDD_EXTENDMODIFIER_DAOJU, this);    //创建对话框
	}
	pDlg_DAOJU->ShowWindow(SW_HIDE);*/
	if (pDlg_MEFF == NULL) {
		pDlg_MEFF = new CExtendModifierMEFF;
		pDlg_MEFF->Create(IDD_EXTENDMODIFIER_MEFF, this);    //创建对话框
	}
	pDlg_MEFF->ShowWindow(SW_HIDE);
	if (pDlg_FORGE == NULL) {
		pDlg_FORGE = new CExtendModifierFORGE;
		pDlg_FORGE->Create(IDD_EXTENDMODIFIER_FORGE, this);    //创建对话框
	}
	pDlg_FORGE->ShowWindow(SW_HIDE);
	/*if (pDlg_ZHUANGBEI == NULL) {
		pDlg_ZHUANGBEI = new CExtendModifierZHUANGBEI;
		pDlg_ZHUANGBEI->Create(IDD_EXTENDMODIFIER_ZHUANGBEI, this);    //创建对话框
	}
	pDlg_ZHUANGBEI->ShowWindow(SW_HIDE);*/
	return 0;
}


BEGIN_MESSAGE_MAP(CExtendModifierDlg, CDialogEx)
	ON_COMMAND(ID_32771, &CExtendModifierDlg::ON_TEJI)
	ON_COMMAND(ID_32772, &CExtendModifierDlg::ON_DAOJU)
	ON_COMMAND(ID_32773, &CExtendModifierDlg::ON_MODE)
	ON_COMMAND(ID_32774, &CExtendModifierDlg::ON_TEJI2)
	ON_COMMAND(ID_32775, &CExtendModifierDlg::ON_MEFF)
	ON_COMMAND(ID_32776, &CExtendModifierDlg::ON_FORGE)
	ON_COMMAND(ID_32777, &CExtendModifierDlg::ON_ZHUANGBEI)
END_MESSAGE_MAP()

void CExtendModifierDlg::ON_TEJI()
{
	pDlg_TEJI->ShowWindow(SW_SHOW);
	pDlg_TEJI2->ShowWindow(SW_HIDE);
	//pDlg_DAOJU->ShowWindow(SW_HIDE);
	pDlg_MEFF->ShowWindow(SW_HIDE);
	pDlg_FORGE->ShowWindow(SW_HIDE);
	//pDlg_ZHUANGBEI->ShowWindow(SW_HIDE);
}


void CExtendModifierDlg::ON_DAOJU()
{
	// TODO: 在此添加命令处理程序代码
	pDlg_TEJI->ShowWindow(SW_HIDE);
	pDlg_TEJI2->ShowWindow(SW_HIDE);
	//pDlg_DAOJU->ShowWindow(SW_SHOW);
	pDlg_MEFF->ShowWindow(SW_HIDE);
	pDlg_FORGE->ShowWindow(SW_HIDE);
	//pDlg_ZHUANGBEI->ShowWindow(SW_HIDE);
}


void CExtendModifierDlg::ON_TEJI2()
{
	// TODO: 在此添加命令处理程序代码
	pDlg_TEJI->ShowWindow(SW_HIDE);
	pDlg_TEJI2->ShowWindow(SW_SHOW);
	//pDlg_DAOJU->ShowWindow(SW_HIDE);
	pDlg_MEFF->ShowWindow(SW_HIDE);
	pDlg_FORGE->ShowWindow(SW_HIDE);
	//pDlg_ZHUANGBEI->ShowWindow(SW_HIDE);
}


void CExtendModifierDlg::ON_MEFF()
{
	// TODO: 在此添加命令处理程序代码
	pDlg_TEJI->ShowWindow(SW_HIDE);
	pDlg_TEJI2->ShowWindow(SW_HIDE);
	//pDlg_DAOJU->ShowWindow(SW_HIDE);
	pDlg_MEFF->ShowWindow(SW_SHOW);
	pDlg_FORGE->ShowWindow(SW_HIDE);
	//pDlg_ZHUANGBEI->ShowWindow(SW_HIDE);
}


void CExtendModifierDlg::ON_FORGE()
{
	// TODO: 在此添加命令处理程序代码
	pDlg_TEJI->ShowWindow(SW_HIDE);
	pDlg_TEJI2->ShowWindow(SW_HIDE);
	//pDlg_DAOJU->ShowWindow(SW_HIDE);
	pDlg_MEFF->ShowWindow(SW_HIDE);
	pDlg_FORGE->ShowWindow(SW_SHOW);
	//pDlg_ZHUANGBEI->ShowWindow(SW_HIDE);
}


void CExtendModifierDlg::ON_ZHUANGBEI()
{
	// TODO: 在此添加命令处理程序代码
	pDlg_TEJI->ShowWindow(SW_HIDE);
	pDlg_TEJI2->ShowWindow(SW_HIDE);
	//pDlg_DAOJU->ShowWindow(SW_HIDE);
	pDlg_MEFF->ShowWindow(SW_HIDE);
	pDlg_FORGE->ShowWindow(SW_HIDE);
	//pDlg_ZHUANGBEI->ShowWindow(SW_SHOW);
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)// 回调函数
{
	TCHAR szBuff[256];
	GetClassName(hwnd, szBuff, sizeof(szBuff) / sizeof(TCHAR));
	if (szBuff[0] == 'S' && szBuff[1] == 'O' && szBuff[2] == 'U' && szBuff[3] == 'S' && szBuff[4] == 'O' && szBuff[5] == 'U')
	{
		/*std::ofstream outputFile;
		outputFile.open("debug.txt");
		outputFile << szBuff;
		outputFile.close();*/
		DWORD dwProcessId = 0;
		GetWindowThreadProcessId(hwnd, &dwProcessId);
		*((HANDLE*)lParam) = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, dwProcessId);
		return FALSE;
	}

	return TRUE;
}

void CExtendModifierDlg::ON_MODE()
{
	// TODO: 在此添加命令处理程序代码
	mode = !mode;

	if (mode == true) {
		bool res = EnumWindows(EnumWindowsProc, (LPARAM)(&hpro));
		if (res == true) mode = false;
	}

	if (mode == false) {
		GetMenu()->ModifyMenu(6, MF_BYPOSITION, ID_32773, L"模式:初始");
		pDlg_TEJI->OnModeChange(mode, 0);
		pDlg_TEJI2->OnModeChange(mode, 0);
		//pDlg_DAOJU->OnModeChange(mode, 0);
		pDlg_MEFF->OnModeChange(mode, 0);
		pDlg_FORGE->OnModeChange(mode, 0);
		//pDlg_ZHUANGBEI->OnModeChange(mode, 0);
	}
	else {
		GetMenu()->ModifyMenu(6, MF_BYPOSITION, ID_32773, L"模式:内存");
		pDlg_TEJI->OnModeChange(mode, hpro);
		pDlg_TEJI2->OnModeChange(mode, hpro);
		//pDlg_DAOJU->OnModeChange(mode, hpro);
		pDlg_MEFF->OnModeChange(mode, hpro);
		pDlg_FORGE->OnModeChange(mode, hpro);
		//pDlg_ZHUANGBEI->OnModeChange(mode, hpro);
	}

	return;
}