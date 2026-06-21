#include "pch.h"
#include "framework.h"
#include "ExtendModifier.h"
#include "ExtendModifierTEJI2.h"
#include "commctrl.h"
#include <iostream>
#include <fstream>
using namespace std;

CExtendModifierTEJI2::CExtendModifierTEJI2(CWnd* pParent)
	: CDialogEx(IDD_EXTENDMODIFIER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtendModifierTEJI2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_EDIT1, edit[0]);
	DDX_Control(pDX, IDC_EDIT2, edit[1]);
	DDX_Control(pDX, IDC_EDIT3, edit[2]);
	DDX_Control(pDX, IDC_EDIT9, edit[3]);
	DDX_Control(pDX, IDC_EDIT10, edit[4]);
	DDX_Control(pDX, IDC_EDIT11, edit[5]);
	DDX_Control(pDX, IDC_EDIT12, edit[6]);
	DDX_Control(pDX, IDC_CHECK1, check[0]);
}



BOOL CExtendModifierTEJI2::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	wchar_t per_utf[30];

	ifstream file3("Ekd5.exe", ios::binary);
	if (file3) {
		DWORD addr = 0x9E800;
		file3.seekg(addr);
		char test[10];
		file3.read(reinterpret_cast<char*>(test), 1);
		if (test[0] == 0) addr = 0xD0D60;
		for (int i = 0; i < 255; i++) {
			file3.seekg(addr + i * 16);
			char id[30];
			_itoa_s(i, id, 10);
			strcat_s(id, ":");
			char name[16];
			file3.read(reinterpret_cast<char*>(name), 15);
			name[15] = 0;
			strcat_s(id, name);

			int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);

			list.AddString(per_utf);
		}
		file3.close();
	}

	list.SetCurSel(0);
	OnLbnSelchangeList1();

	OnModeChange(false, 0);
	return 0;
}

void CExtendModifierTEJI2::loadData(int per)
{
	if (mode == false) {
		wchar_t per_utf[30];
		ifstream file("Effectmsg.e5", ios::binary);
		if (file) {
			file.seekg(per * 8);
			file.read(reinterpret_cast<char*>(item_data), 8);
			file.close();
		}
	}
}

BEGIN_MESSAGE_MAP(CExtendModifierTEJI2, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CExtendModifierTEJI2::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CExtendModifierTEJI2::OnBnClickedOk)
END_MESSAGE_MAP()


void CExtendModifierTEJI2::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int per = list.GetCurSel();
	loadData(per);

	if (!mode) {
		check[0].SetCheck((int)item_data[0]);

		wchar_t value[10];
		for (int i = 1; i < 8; i++) {
			_itow_s(unsigned char(item_data[i]), value, 10);
			edit[i - 1].SetWindowTextW(value);
		}
	}
}


void CExtendModifierTEJI2::OnModeChange(bool mode_, HANDLE hpro_)
{
	// TODO: 在此添加控件通知处理程序代码
	mode = mode_;
	if (hpro_ != 0)
		hpro = hpro_;

	int per = list.GetCurSel();
	OnLbnSelchangeList1();

	for (int i = 0; i < 7; i++)edit[i].EnableWindow(!mode);
	check[0].EnableWindow(!mode);
}

void CExtendModifierTEJI2::OnBnClickedOk()
{
	int per = list.GetCurSel();
	if (!mode) {
		ofstream file("Effectmsg.e5", ios::binary | ios::in);
		if (file) {
			char p[5];
			CString value;

			file.seekp(per * 8 , ios::beg);
			p[0] = check[0].GetCheck();
			file.write(reinterpret_cast<char*>(p), 1);

			for (int i = 0; i < 7; i++) {
				file.seekp(per * 8 + i + 1, ios::beg);
				edit[i].GetWindowTextW(value);
				p[0] = _wtoi(value);
				file.write(reinterpret_cast<char*>(p), 1);
			}

			file.close();
		}
	}
}
