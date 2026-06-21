
// ExtendModifierDlg.h: 头文件
//

#pragma once

class CExtendModifierDlg : public CDialogEx
{
	// 构造
public:
	CExtendModifierDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTENDMODIFIER_DIALOG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();
protected:
	HICON m_hIcon;

	HANDLE hpro;
	BOOL mode;
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void ON_TEJI();
	afx_msg void ON_DAOJU();
	afx_msg void ON_MODE();
	afx_msg void ON_TEJI2();
	afx_msg void ON_MEFF();
	afx_msg void ON_FORGE();
	afx_msg void ON_ZHUANGBEI();
};
