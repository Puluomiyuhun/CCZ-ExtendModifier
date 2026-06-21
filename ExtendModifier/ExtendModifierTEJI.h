#pragma once
// CExtendModifierDlg 对话框
class CExtendModifierTEJI : public CDialogEx
{
	// 构造
public:
	CExtendModifierTEJI(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTENDMODIFIER_TEJI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox list;
	CComboBox combo[9];
	CEdit edit[8];
	byte person_effect[256][4];
	int page = 0;

	bool mode = false;//0是初值模式，1是内存模式
	HANDLE hpro;

	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedOk();
	void OnModeChange(bool mode_, HANDLE hpro_);

	void loadData(int per);
	void SaveData(int per);
	afx_msg void OnSelchangeCombo9();
	afx_msg void OnBnClickedButton1();
};
