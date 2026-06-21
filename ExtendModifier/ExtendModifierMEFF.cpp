#include "pch.h"
#include "framework.h"
#include "ExtendModifier.h"
#include "ExtendModifierMEFF.h"
#include "afxdialogex.h"
#include "commctrl.h"
#include <iostream>
#include <fstream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CExtendModifierMEFF::CExtendModifierMEFF(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXTENDMODIFIER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtendModifierMEFF::DoDataExchange(CDataExchange* pDX)
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
	DDX_Control(pDX, IDC_COMBO9, combo[8]);
	DDX_Control(pDX, IDC_EDIT1, edit[0]);
	DDX_Control(pDX, IDC_EDIT2, edit[1]);
	DDX_Control(pDX, IDC_EDIT3, edit[2]);
	DDX_Control(pDX, IDC_EDIT4, edit[3]);
	DDX_Control(pDX, IDC_EDIT5, edit[4]);
	DDX_Control(pDX, IDC_EDIT6, edit[5]);
	DDX_Control(pDX, IDC_EDIT7, edit[6]);
	DDX_Control(pDX, IDC_EDIT8, edit[7]);
}

BEGIN_MESSAGE_MAP(CExtendModifierMEFF, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_LBN_SELCHANGE(IDC_LIST1, &CExtendModifierMEFF::OnLbnSelchangeList1)
	ON_BN_CLICKED(IDOK, &CExtendModifierMEFF::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO9, &CExtendModifierMEFF::OnSelchangeCombo9)
	ON_BN_CLICKED(IDC_BUTTON1, &CExtendModifierMEFF::OnBnClickedButton1)
END_MESSAGE_MAP()


// CExtendModifierMEFF 消息处理程序

BOOL CExtendModifierMEFF::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	wchar_t per_utf[30];

	ifstream file2("Data.e5", ios::binary);
	if (file2) {
		for (int i = 0; i < 1024; i++) {
			file2.seekg(0x190 + i * 48);
			char id[30];
			_itoa_s(i, id, 10);
			strcat_s(id, ":");
			char name[16];
			file2.read(reinterpret_cast<char*>(name), 12);
			name[12] = 0;
			strcat_s(id, name);

			int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);

			list.AddString(per_utf);
		}
		file2.close();
	}

	ifstream file3("Magic.e5", ios::binary);
	if (file3) {
		DWORD addr = 0;
		for (int i = 0; i < 255; i++) {
			file3.seekg(addr + i * 0x80);
			char id[30];
			_itoa_s(i, id, 10);
			strcat_s(id, ":");
			char name[16];
			file3.read(reinterpret_cast<char*>(name), 12);
			name[12] = 0;
			strcat_s(id, name);

			int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
			MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);

			for (int j = 0; j < 8; j++)
				combo[j].AddString(per_utf);
		}
		file3.close();
	}
	list.SetCurSel(0);
	loadData(0);

	for (int i = 0; i < 8; i++) {
		combo[i].AddString(L"无");
		combo[i].SetMinVisibleItems(30);
		combo[i].SetCurSel(0);
	}

	for (int i = 0; i < 32 / 8; i++) {
		char id[5];
		_itoa_s(i, id, 10);
		int wlen = MultiByteToWideChar(CP_ACP, 0, id, -1, NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, id, -1, per_utf, wlen);
		combo[8].AddString(per_utf);
	}
	combo[8].SetCurSel(0);

	OnLbnSelchangeList1();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CExtendModifierMEFF::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CExtendModifierMEFF::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExtendModifierMEFF::OnLbnSelchangeList1()
{
	page = 0;
	combo[8].SetCurSel(0);
	int per = list.GetCurSel();
	loadData(per);
	for (int i = page * 8; i < page * 8 + 8; i++) {
		combo[i].SetCurSel(person_effect[i][0]);
		wchar_t value[10];
		_itow_s(person_effect[i][1], value, 10);
		edit[i].SetWindowTextW(value);
	}
}


void CExtendModifierMEFF::OnBnClickedOk()
{
	int per = list.GetCurSel();
	for (int i = page * 8; i < page * 8 + 8; i++) {
		person_effect[i][0] = combo[i - page * 8].GetCurSel();
		CString value;
		edit[i - page * 8].GetWindowTextW(value);
		person_effect[i][1] = _wtoi(value);
	}
	SaveData(per);

	//CDialogEx::OnOK();
}

void CExtendModifierMEFF::OnModeChange(bool mode_, HANDLE hpro_)
{
	// TODO: 在此添加控件通知处理程序代码
	mode = mode_;
	if (hpro_ != 0)
		hpro = hpro_;

	int per = list.GetCurSel();
	OnLbnSelchangeList1();
}

void CExtendModifierMEFF::loadData(int per)
{
	if (mode == false) {
		ifstream file("MeffStudy.e5", ios::binary);
		if (file) {
			file.seekg(per * 32 * 2, ios::beg);
			file.read(reinterpret_cast<char*>(&person_effect), 32 * 2);
			file.close();
		}
	}
	else {
		char* addr;
		ReadProcessMemory(hpro, (LPVOID)(0x4F0034), &addr, 4, 0);
		ReadProcessMemory(hpro, (LPVOID)(addr + per * 32 * 2), &person_effect, 32 * 2, 0);
	}

	//OnLbnSelchangeList1();
}

void CExtendModifierMEFF::SaveData(int per)
{
	if (mode == false) {
		ofstream file("MeffStudy.e5", ios::binary | ios::in);
		if (file) {
			file.seekp(per * 32 * 2, ios::beg);
			file.write(reinterpret_cast<char*>(&person_effect), 32 * 2);
			file.close();
		}
	}
	else {
		char* addr;
		ReadProcessMemory(hpro, (LPVOID)(0x4F0034), &addr, 4, 0);
		WriteProcessMemory(hpro, (LPVOID)(addr + per * 32 * 2), &person_effect, 32 * 2, 0);
	}
}


void CExtendModifierMEFF::OnSelchangeCombo9()
{
	// TODO: 在此添加控件通知处理程序代码
	page = combo[8].GetCurSel();
	for (int i = page * 8; i < page * 8 + 8; i++) {
		combo[i - page * 8].SetCurSel(person_effect[i][0]);
		wchar_t value[10];
		_itow_s(person_effect[i][1], value, 10);
		edit[i - page * 8].SetWindowTextW(value);
	}
}

void CExtendModifierMEFF::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	int per = list.GetCurSel();
	int list[32], cnt = 0;
	for (int i = 0; i < 32; i++) {
		if (person_effect[i][0] != 0xFF) list[cnt++] = i;
	}
	for (int i = 0; i < cnt; i++) {
		for (int j = 0; j < 4; j++) {
			person_effect[i][j] = person_effect[list[i]][j];
		}
	}
	for (int i = cnt; i < 32; i++) {
		person_effect[i][0] = 0xFF;
		person_effect[i][1] = 0xFF;
	}
	SaveData(per);
	OnLbnSelchangeList1();
}
