
// PZToolsDlg.h : 头文件
//

#pragma once


// CPZToolsDlg 对话框
class CPZToolsDlg : public CDialog
{
// 构造
public:
	CPZToolsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PZTOOLS_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
    // 进程ID
    DWORD m_nProcessID;
    // 进程句柄
    HANDLE m_hProcess;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnEnChangeEdit1();
    afx_msg void OnBnClickedCheck1();
protected:
    virtual void OnOK();
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
    void InitComboxList();
    afx_msg void OnEnChangeEdit2();
    afx_msg void OnBnClickedCheck2();
    afx_msg void OnBnClickedCheck8();
    void Auto();
    afx_msg void OnEnChangeEdit3();
    afx_msg void OnEnChangeEdit4();
    afx_msg void OnEnChangeEdit5();
    afx_msg void OnEnChangeEdit6();
    afx_msg void OnBnClickedCheck3();
    afx_msg void OnBnClickedCheck4();
    afx_msg void OnBnClickedCheck5();
    afx_msg void OnBnClickedCheck6();
    afx_msg void OnCbnSelchangeCombo1();
    afx_msg void OnCbnSelchangeCombo2();
    void Jump();
    afx_msg void OnBnClickedCheck7();
    void OnCooling();
    void Cooling1();
    void Cooling2();
    void Cooling3();
    void Cooling4();
    void Cooling5();
    void Cooling6();
    void Cooling7();
    void Cooling8();
    void Cooling9();
    void Cooling10();
};

#define RUNGAME  1
#define SUNLIGHT 2
#define MONEY 3
#define AUTO 4
#define FERTILIZERS 5
#define TREEFERTILIZER 6
#define INSECTICIDE 7
#define CHOCOLATES 8
#define COOLING 9