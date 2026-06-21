#include "pch.h"
#include "framework.h"
#include "ExtendModifier.h"
#include "ExtendModifierFORGE.h"
#include "commctrl.h"


#include <iostream>
#include <fstream>
using namespace std;

CExtendModifierFORGE::CExtendModifierFORGE(CWnd* pParent)
	: CDialogEx(IDD_EXTENDMODIFIER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtendModifierFORGE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_COMBO1, combo[0]);
	DDX_Control(pDX, IDC_COMBO2, combo[1]);
	DDX_Control(pDX, IDC_COMBO3, combo[2]);
	DDX_Control(pDX, IDC_COMBO4, combo[3]);
	DDX_Control(pDX, IDC_COMBO5, combo[4]);
	DDX_Control(pDX, IDC_COMBO6, combo[5]);
	DDX_Control(pDX, IDC_COMBO7, combo[6]);
	DDX_Control(pDX, IDC_COMBO8, combo[7]);
	DDX_Control(pDX, IDC_EDIT1, edit[0]);
	DDX_Control(pDX, IDC_EDIT2, edit[1]);
	DDX_Control(pDX, IDC_EDIT3, edit[2]);
	DDX_Control(pDX, IDC_EDIT4, edit[3]);
	DDX_Control(pDX, IDC_EDIT5, edit[4]);
	DDX_Control(pDX, IDC_EDIT6, edit[5]);
	DDX_Control(pDX, IDC_EDIT7, edit[6]);
	DDX_Control(pDX, IDC_EDIT8, edit[7]);
	DDX_Control(pDX, IDC_EDIT13, edit[8]);
	DDX_Control(pDX, IDC_EDIT14, edit[9]);
	DDX_Control(pDX, IDC_EDIT15, edit[10]);
	DDX_Control(pDX, IDC_EDIT16, edit[11]);
	DDX_Control(pDX, IDC_EDIT17, edit[12]);
	DDX_Control(pDX, IDC_CHECK2, check[0]);
}



BOOL CExtendModifierFORGE::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	wchar_t per_utf[30];

	ifstream file("Forge.e5", ios::binary);
	if (file) {
		for (int i = 0; i < 1024; i++) {
			file.seekg(i * 64);
			char id[30];
			_itoa_s(i, id, 10);
			strcat_s(id, ":");
			char name[40];
			file.read(reinterpret_cast<char*>(name), 30);
			name[30] = 0;
			strcat_s(id, name);

			int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);

			list.AddString(per_utf);
		}
		file.close();
	}

	/*ifstream file2("Data.e5", ios::binary | ios::in);
	if (file2) {
		for (int i = 0; i < 104; i++) {
			file2.seekg(0x818C + i * 0x19);
			char id[30];
			_itoa_s(i, id, 10);
			strcat_s(id, ":");
			char name[40];
			file2.read(reinterpret_cast<char*>(name), 12);
			name[12] = 0;
			strcat_s(id, name);

			int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);

			for (int j = 0; j < 8; j++)combo[j].AddString(per_utf);
		}
		file2.close();
	}*/
	ifstream file4("Star.e5", ios::binary | ios::in);
	if (file4) {
		for (int i = 0; i < 256 + 256; i++) {
			file4.seekg(i * 0x19);
			char id[30];
			_itoa_s(i + 0, id, 10);
			strcat_s(id, ":");
			char name[40];
			file4.read(reinterpret_cast<char*>(name), 12);
			name[12] = 0;
			strcat_s(id, name);

			int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);

			for (int j = 0; j < 8; j++)combo[j].AddString(per_utf);
		}
		file4.close();
	}
	for (int i = 0; i < 8; i++)combo[i].AddString(L"无");

	/*ifstream file3("Item.e5", ios::binary | ios::in);
	if (file3) {
		for (int i = 0; i < 255; i++) {
			file3.seekg(i * 0x19);
			char id[30];
			_itoa_s(i + 256, id, 10);
			strcat_s(id, ":");
			char name[40];
			file3.read(reinterpret_cast<char*>(name), 12);
			name[12] = 0;
			strcat_s(id, name);

			int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);

			for (int j = 0; j < 8; j++)combo[j].AddString(per_utf);
		}
		for (int i = 0; i < 8; i++)combo[i].AddString(L"无");
		file3.close();
	}*/

	list.SetCurSel(0);
	OnLbnSelchangeList1();

	OnModeChange(false, 0);
	return 0;
}

void CExtendModifierFORGE::loadData(int per)
{
	if (mode == false) {
		ifstream file("Forge.e5", ios::binary);
		if (file) {
			file.seekg(per * 64, ios::beg);
			file.read(reinterpret_cast<char*>(&item_data), 64);
			file.close();
		}
	}
	else {
		/*char* addr;
		ReadProcessMemory(hpro, (LPVOID)(0x4F0004), &addr, 4, 0);
		ReadProcessMemory(hpro, (LPVOID)(addr + per * 256 * 4), &person_effect, 256 * 4, 0);*/
		//ReadProcessMemory(hpro, (LPVOID)(0x530000 + per), &(item_data[0]), 1, 0);
	}

	//OnLbnSelchangeList1();
}

BEGIN_MESSAGE_MAP(CExtendModifierFORGE, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST1, &CExtendModifierFORGE::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CExtendModifierFORGE::OnBnClickedOk)
END_MESSAGE_MAP()


void CExtendModifierFORGE::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int per = list.GetCurSel();
	loadData(per);

	if (!mode) {
		char id[30];
		wchar_t name[40];
		strcpy_s(id, 30, item_data);
		int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, id, -1, name, wlen);
		edit[8].SetWindowTextW(name);

		wchar_t value[10];
		for (int i = 0; i < 8; i++) {
			unsigned int k = unsigned char(item_data[30 + i * 3]) + unsigned char(item_data[30 + i * 3 + 1]) * 256;
			if (k % 256 == 255) k = 255;
			combo[i].SetCurSel(k);
			_itow_s(unsigned char(item_data[30 + i * 3 + 2]), value, 10);
			edit[i].SetWindowTextW(value);
		}

		unsigned int* money = (unsigned int*)&item_data[54];
		_itow_s(*money, value, 10);
		edit[9].SetWindowTextW(value);

		for (int i = 0; i < 2; i++) {
			_itow_s(unsigned char(item_data[58 + i]), value, 10);
			edit[10 + i].SetWindowTextW(value);
		}

		check[0].SetCheck((bool)item_data[60]);

		_itow_s(unsigned char(item_data[61]), value, 10);
		edit[12].SetWindowTextW(value);
	}
	else {
		/*wchar_t value[10];
		_itow_s(unsigned char(item_data[0]), value, 10);
		edit[4].SetWindowTextW(value);*/
	}
}


void CExtendModifierFORGE::OnModeChange(bool mode_, HANDLE hpro_)
{
	// TODO: 在此添加控件通知处理程序代码
	mode = mode_;
	if (hpro_ != 0)
		hpro = hpro_;

	int per = list.GetCurSel();
	OnLbnSelchangeList1();

	for (int i = 0; i < 8; i++) {
		edit[i].EnableWindow(!mode);
		combo[i].EnableWindow(!mode);
	}
	for (int i = 8; i < 12; i++)edit[i].EnableWindow(!mode);
	check[0].EnableWindow(!mode);
	edit[12].EnableWindow(1);
}

void CExtendModifierFORGE::OnBnClickedOk()
{
	int per = list.GetCurSel();
	if (!mode) {
		ofstream file("Forge.e5", ios::binary | ios::in);
		if (file) {
			char id[40];
			CString name;
			edit[8].GetWindowTextW(name);
			int len = WideCharToMultiByte(CP_OEMCP, 0, name, -1, NULL, 0, NULL, FALSE);
			WideCharToMultiByte(CP_OEMCP, 0, name, -1, id, len, NULL, FALSE);
			file.seekp(per * 64, ios::beg);
			id[30] = 0;
			file.write(reinterpret_cast<char*>(id), strlen(id) + 1);

			CString value;
			int p;
			for (int i = 0; i < 8; i++) {
				file.seekp(per * 64 + 30 + i * 3, ios::beg);
				int id = combo[i].GetCurSel();
				if (id % 256 == 255)id = 255;
				file.write(reinterpret_cast<char*>(&id), 2);

				file.seekp(per * 64 + 30 + i * 3 + 2, ios::beg);
				CString value;
				edit[i].GetWindowTextW(value);
				p = _wtoi(value);
				file.write(reinterpret_cast<char*>(&p), 1);
			}

			file.seekp(per * 64 + 54, ios::beg);
			edit[9].GetWindowTextW(value);
			p = _wtoi(value);
			file.write(reinterpret_cast<char*>(&p), 4);

			file.seekp(per * 64 + 58, ios::beg);
			edit[10].GetWindowTextW(value);
			p = _wtoi(value);
			file.write(reinterpret_cast<char*>(&p), 1);

			file.seekp(per * 64 + 59, ios::beg);
			edit[11].GetWindowTextW(value);
			p = _wtoi(value);
			file.write(reinterpret_cast<char*>(&p), 1);

			file.seekp(per * 64 + 60, ios::beg);
			p = check->GetCheck();
			file.write(reinterpret_cast<char*>(&p), 1);

			file.seekp(per * 64 + 61, ios::beg);
			edit[12].GetWindowTextW(value);
			p = _wtoi(value);
			file.write(reinterpret_cast<char*>(&p), 1);

			file.close();

			wchar_t id2[30];
			_itow_s(per, id2, 10);
			wcscat_s(id2, L":");
			wcscat_s(id2, name);
			list.DeleteString(per);
			list.InsertString(per, id2);
			list.SetCurSel(per);
		}
	}
	else {
		char p[5];
		CString value;
		edit[12].GetWindowTextW(value);
		p[0] = _wtoi(value);
		char* addr;
		ReadProcessMemory(hpro, (LPVOID)(0x4F0048), &addr, 4, 0);
		WriteProcessMemory(hpro, (LPVOID)(addr + per * 64 + 61), &p[0], 1, 0);
	}
}
