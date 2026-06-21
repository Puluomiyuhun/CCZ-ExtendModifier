#include "pch.h"
#include "framework.h"
#include "ExtendModifier.h"
#include "ExtendModifierDAOJU.h"
#include "commctrl.h"
#include <iostream>
#include <fstream>
using namespace std;

CExtendModifierDAOJU::CExtendModifierDAOJU(CWnd* pParent)
	: CDialogEx(IDD_EXTENDMODIFIER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtendModifierDAOJU::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, list);
	DDX_Control(pDX, IDC_COMBO1, combo[0]);
	DDX_Control(pDX, IDC_EDIT1, edit[0]);
	DDX_Control(pDX, IDC_EDIT2, edit[1]);
	DDX_Control(pDX, IDC_EDIT3, edit[2]);
	DDX_Control(pDX, IDC_EDIT9, edit[3]);
	DDX_Control(pDX, IDC_EDIT10, edit[4]);
	DDX_Control(pDX, IDC_EDIT11, edit[5]);
	DDX_Control(pDX, IDC_CHECK1, check[0]);
}



BOOL CExtendModifierDAOJU::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	wchar_t per_utf[30];

	ifstream file("Item.e5", ios::binary);
	if (file) {
		for (int i = 0; i < 256; i++) {
			file.seekg(i * 25);
			char id[30];
			_itoa_s(i, id, 10);
			strcat_s(id, ":");
			char name[20];
			file.read(reinterpret_cast<char*>(name), 17);
			name[17] = 0;
			strcat_s(id, name);

			int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);

			list.AddString(per_utf);
		}
		file.close();
	}

	ifstream file2("Ekd5.exe", ios::binary | ios::in);
	if (file2) {
		file2.seekg(0xA0270, ios::beg);
		char strings[0x2A5];
		file2.read(reinterpret_cast<char*>(strings), 0x2A5);
		char effects[57][20];
		int k = 0, p = 0, q = 0;
		while(1)
		{
			if (strings[k] == 0) {
				effects[q][p] = strings[k];
				if (p != 0)q++;
				p = 0;
			}
			else {
				effects[q][p] = strings[k];
				p++;
			}
			k++;
			if (q >= 57)break;
		}
		file2.close();
		for (int i = 0; i < 57; i++) {
			char str[30];
			_itoa_s(i + 0x1A, str, 16);
			strcat_s(str, ":");
			strcat_s(str, effects[i]);
			int wlen = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, str, -1, per_utf, wlen);
			combo[0].AddString(per_utf);
		}
	}

	list.SetCurSel(0);
	OnLbnSelchangeList1();

	OnModeChange(false, 0);
	return 0;
}

void CExtendModifierDAOJU::loadData(int per)
{
	if (mode == false) {
		ifstream file("Item.e5", ios::binary);
		if (file) {
			file.seekg(per * 25, ios::beg);
			file.read(reinterpret_cast<char*>(&item_data), 25);
			file.close();
		}
		ifstream file2("Itemmsg.e5", ios::binary);
		if (file2) {
			file2.seekg(per * 200, ios::beg);
			file2.read(reinterpret_cast<char*>(&item_message), 200);
			file2.close();
		}
	}
	else {
		/*char* addr;
		ReadProcessMemory(hpro, (LPVOID)(0x4F0004), &addr, 4, 0);
		ReadProcessMemory(hpro, (LPVOID)(addr + per * 256 * 4), &person_effect, 256 * 4, 0);*/
		ReadProcessMemory(hpro, (LPVOID)(0x530000 + per), &(item_data[0]), 1, 0);
	}

	//OnLbnSelchangeList1();
}

BEGIN_MESSAGE_MAP(CExtendModifierDAOJU, CDialogEx)
ON_LBN_SELCHANGE(IDC_LIST1, &CExtendModifierDAOJU::OnLbnSelchangeList1)
ON_BN_CLICKED(IDOK, &CExtendModifierDAOJU::OnBnClickedOk)
END_MESSAGE_MAP()


void CExtendModifierDAOJU::OnLbnSelchangeList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int per = list.GetCurSel();
	loadData(per);

	if (!mode) {
		char id[30];
		wchar_t name[30];
		strcpy_s(id, 17, item_data);
		int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, id, -1, name, wlen);
		name[15] = 0;
		edit[0].SetWindowTextW(name);

		combo[0].SetCurSel(item_data[0x11] - 0x1A);

		wchar_t value[10];
		_itow_s(unsigned char(item_data[0x13]), value, 10);
		edit[1].SetWindowTextW(value);
		_itow_s(unsigned char(item_data[0x14]), value, 10);
		edit[2].SetWindowTextW(value);
		int a = unsigned char(item_data[0x15]);
		int b = unsigned char(item_data[0x16]) * 256;
		int c = a + b;
		_itow_s(c, value, 10);
		edit[3].SetWindowTextW(value);

		check[0].SetCheck((int)item_data[0x18]);

		char id2[210];
		wchar_t name2[400];
		strcpy_s(id2, 200, item_message);
		wlen = MultiByteToWideChar(CP_ACP, 0, id2, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, id2, -1, name2, wlen);
		edit[5].SetWindowTextW(name2);
	}
	else {
		wchar_t value[10];
		_itow_s(unsigned char(item_data[0]), value, 10);
		edit[4].SetWindowTextW(value);
	}
}


void CExtendModifierDAOJU::OnModeChange(bool mode_, HANDLE hpro_)
{
	// TODO: 在此添加控件通知处理程序代码
	mode = mode_;
	if (hpro_ != 0)
		hpro = hpro_;

	int per = list.GetCurSel();
	OnLbnSelchangeList1();

	edit[4].EnableWindow(mode);
	combo[0].EnableWindow(!mode);
	for (int i = 0; i < 6; i++)if (i != 4)edit[i].EnableWindow(!mode);
	check[0].EnableWindow(!mode);
}

void CExtendModifierDAOJU::OnBnClickedOk()
{
	int per = list.GetCurSel();
	if (!mode) {
		ofstream file("Item.e5", ios::binary | ios::in);
		if (file) {
			char id[30];
			CString name;
			edit[0].GetWindowTextW(name);
			int len = WideCharToMultiByte(CP_OEMCP, 0, name, -1, NULL, 0, NULL, FALSE);
			WideCharToMultiByte(CP_OEMCP, 0, name, -1, id, len, NULL, FALSE);
			file.seekp(per * 25, ios::beg);
			id[15] = 0;
			file.write(reinterpret_cast<char*>(id), strlen(id) + 1);

			char p[5];
			file.seekp(per * 25 + 0x11, ios::beg);
			p[0] = combo[0].GetCurSel() + 0x1A;
			file.write(p, 1);

			file.seekp(per * 25 + 0x12, ios::beg);
			p[0] = 3;
			file.write(reinterpret_cast<char*>(p), 1);

			CString value;
			edit[1].GetWindowTextW(value);
			p[0] = _wtoi(value);
			file.seekp(per * 25 + 0x13, ios::beg);
			file.write(reinterpret_cast<char*>(p), 1);

			edit[2].GetWindowTextW(value);
			p[0] = _wtoi(value);
			file.seekp(per * 25 + 0x14, ios::beg);
			file.write(reinterpret_cast<char*>(p), 1);

			edit[3].GetWindowTextW(value);
			int q = _wtoi(value);
			p[0] = q % 256;
			p[1] = q / 256;
			file.seekp(per * 25 + 0x15, ios::beg);
			file.write(reinterpret_cast<char*>(p), 2);

			file.seekp(per * 25 + 0x18, ios::beg);
			p[0] = check[0].GetCheck();
			file.write(reinterpret_cast<char*>(p), 1);

			file.close();

			wchar_t id2[30];
			_itow_s(per, id2, 10);
			wcscat_s(id2, L":");
			wcscat_s(id2, name);
			list.DeleteString(per);
			list.InsertString(per, id2);
			list.SetCurSel(per);
		}

		ofstream file2("Itemmsg.e5", ios::binary | ios::in);
		if (file2) {
			char id[200];
			CString name;
			edit[5].GetWindowTextW(name);
			int len = WideCharToMultiByte(CP_OEMCP, 0, name, -1, NULL, 0, NULL, FALSE);
			WideCharToMultiByte(CP_OEMCP, 0, name, -1, id, len, NULL, FALSE);
			file2.seekp(per * 200, ios::beg);
			id[199] = 0;
			file2.write(reinterpret_cast<char*>(id), strlen(id) + 1);

			file2.close();
		}
	}
	else {
		char p[5];
		CString value;
		edit[4].GetWindowTextW(value);
		p[0] = _wtoi(value);
		WriteProcessMemory(hpro, (LPVOID)(0x530000 + per), &p, 1, 0);
	}
}
