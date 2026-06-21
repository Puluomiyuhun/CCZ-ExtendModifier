#pragma once

#pragma once

class CExtendModifierTEJI2 :
	public CDialogEx
{
public:
	CExtendModifierTEJI2(CWnd* pParent = nullptr);	// 标准构造函数

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
	void loadData(int per);

public:
	void OnModeChange(bool mode_, HANDLE hpro_);
public:
	bool mode = false;//0是初值模式，1是内存模式
	HANDLE hpro;

	CListBox list;
	CEdit edit[7];
	CButton check[1];
	char item_data[8];
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnBnClickedOk();
};

