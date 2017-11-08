
// PZToolsDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PZTools.h"
#include "PZToolsDlg.h"
#include <Tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPZToolsDlg 对话框




CPZToolsDlg::CPZToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPZToolsDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPZToolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPZToolsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_TIMER()
    ON_EN_CHANGE(IDC_EDIT1, &CPZToolsDlg::OnEnChangeEdit1)
    ON_BN_CLICKED(IDC_CHECK1, &CPZToolsDlg::OnBnClickedCheck1)
    ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CPZToolsDlg::OnNMClickSyslink1)
    ON_EN_CHANGE(IDC_EDIT2, &CPZToolsDlg::OnEnChangeEdit2)
    ON_BN_CLICKED(IDC_CHECK2, &CPZToolsDlg::OnBnClickedCheck2)
    ON_BN_CLICKED(IDC_CHECK8, &CPZToolsDlg::OnBnClickedCheck8)
    ON_EN_CHANGE(IDC_EDIT3, &CPZToolsDlg::OnEnChangeEdit3)
    ON_EN_CHANGE(IDC_EDIT4, &CPZToolsDlg::OnEnChangeEdit4)
    ON_EN_CHANGE(IDC_EDIT5, &CPZToolsDlg::OnEnChangeEdit5)
    ON_EN_CHANGE(IDC_EDIT6, &CPZToolsDlg::OnEnChangeEdit6)
    ON_BN_CLICKED(IDC_CHECK3, &CPZToolsDlg::OnBnClickedCheck3)
    ON_BN_CLICKED(IDC_CHECK4, &CPZToolsDlg::OnBnClickedCheck4)
    ON_BN_CLICKED(IDC_CHECK5, &CPZToolsDlg::OnBnClickedCheck5)
    ON_BN_CLICKED(IDC_CHECK6, &CPZToolsDlg::OnBnClickedCheck6)
    ON_CBN_SELCHANGE(IDC_COMBO1, &CPZToolsDlg::OnCbnSelchangeCombo1)
    ON_CBN_SELCHANGE(IDC_COMBO2, &CPZToolsDlg::OnCbnSelchangeCombo2)
    ON_BN_CLICKED(IDC_CHECK7, &CPZToolsDlg::OnBnClickedCheck7)
END_MESSAGE_MAP()


// CPZToolsDlg 消息处理程序

BOOL CPZToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    // 启动定时器检测游戏是否启动
    SetTimer(RUNGAME,1000,NULL);

    InitComboxList();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPZToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CPZToolsDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CPZToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPZToolsDlg::OnTimer(UINT_PTR nIDEvent)
{
    if(nIDEvent == RUNGAME)
    {
        // 判断是否启动植物大战僵尸
        HWND hMainWnd = ::FindWindow(_T("MainWindow"),_T("植物大战僵尸中文版"));
        CString strText;
        GetDlgItemText(IDC_RUNGAMETIP,strText);
        if (hMainWnd != NULL)
        { // 启动中
            SetDlgItemText(IDC_RUNGAMETIP,L"状态:启动游戏中");
        }else
        { // 未启动
            SetDlgItemText(IDC_RUNGAMETIP,L"状态:未启动游戏");
                
        }
    }else
    { 
        if ( m_nProcessID == 0)
            return;
        switch (nIDEvent)
        {
        case SUNLIGHT:
            OnEnChangeEdit1();
            break;
        case MONEY:
            OnEnChangeEdit2( );
            break;
        case AUTO:
            Auto();
            break;
        case FERTILIZERS:
            OnEnChangeEdit3();
            break;
        case TREEFERTILIZER:
            OnEnChangeEdit4();
            break;
        case INSECTICIDE:
            OnEnChangeEdit5();
            break;
        case CHOCOLATES:
            OnEnChangeEdit6();
            break;
        case COOLING:
            OnCooling();
            break;

        }
    }
    
    CDialog::OnTimer(nIDEvent);
}

void CPZToolsDlg::OnEnChangeEdit1()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;
        
        //二级偏移
        DWORD SunShineOffsetSecond = 0x5560;
        //最后值
        DWORD SunShineNum=0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &SunShineNum, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD nData;
        nData = GetDlgItemInt(IDC_EDIT1);
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }

}

void CPZToolsDlg::OnBnClickedCheck1()
{
    if( static_cast<CButton*>(GetDlgItem(IDC_CHECK1))->GetCheck() == TRUE)
    { // 开启定时器
        SetTimer(SUNLIGHT,1000,NULL);
    }else
    { // 关闭定时器
        KillTimer(SUNLIGHT);
    }
    
}

void CPZToolsDlg::OnOK()
{
}

BOOL CPZToolsDlg::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_KEYDOWN)
    {
        if(pMsg->wParam == VK_ESCAPE )
        {
            if( AfxMessageBox(_T("是否退出程序?"),MB_YESNO) == IDYES )
                PostQuitMessage(0);
            else
                return TRUE;
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}

void CPZToolsDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
    ShellExecute(NULL, _T("OPEN"), _T("http://www.weibo.com/ClearSeve"), NULL, NULL, SW_SHOWNORMAL); 
    *pResult = 0;
}

void CPZToolsDlg::InitComboxList()
{
    for (int i=1; i<=5; ++i)
    {
        CString str;
        str.Format(_T("%d"),i);
        static_cast<CComboBox*>(GetDlgItem(IDC_COMBO1))->AddString(str);
    }
    
    for (int i=1; i<=10; ++i)
    {
        CString str;
        str.Format(_T("%d"),i);
        static_cast<CComboBox*>(GetDlgItem(IDC_COMBO2))->AddString(str);
    }

    // 设置选中
    static_cast<CComboBox*>(GetDlgItem(IDC_COMBO1))->SetCurSel(0);
    static_cast<CComboBox*>(GetDlgItem(IDC_COMBO2))->SetCurSel(0);
}



void CPZToolsDlg::OnEnChangeEdit2()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x82c;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;
        
        ////二级偏移
        //DWORD SunShineOffsetSecond = 0x28;
        ////最后值
        //DWORD SunShineNum=0;
        //if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &SunShineNum, sizeof(DWORD), NULL) == FALSE)
        //    __leave;


        DWORD SunShineOffsetSecond = 0x28;

        DWORD nData;
        nData = GetDlgItemInt(IDC_EDIT2);
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::OnBnClickedCheck2()
{
    // MONEY
    if( static_cast<CButton*>(GetDlgItem(IDC_CHECK2))->GetCheck() == TRUE )
    {
        // 设置定时器
        SetTimer(MONEY,1000,NULL);
    }else
    {
        // 取消定时器
        KillTimer(MONEY);
    }
}

void CPZToolsDlg::OnBnClickedCheck8()
{
    if( static_cast<CButton*>(GetDlgItem(IDC_CHECK8))->GetCheck() == TRUE )
    {   
        // 设置定时器
        SetTimer(AUTO,1000,NULL);
    }else
    {
        // 取消定时器
        KillTimer(AUTO);
    }
}

void CPZToolsDlg::Auto()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0xe4;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        ////二级偏移
        //DWORD SunShineOffsetSecond = 0x28;
        ////最后值
        //DWORD SunShineNum=0;
        //if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &SunShineNum, sizeof(DWORD), NULL) == FALSE)
        //    __leave;


        DWORD SunShineOffsetSecond2 = 0x50;

        DWORD nData =1 ;
        //nData = GetDlgItemInt(IDC_EDIT2);
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}
// 花肥
void CPZToolsDlg::OnEnChangeEdit3()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x82c;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        ////二级偏移
        //DWORD SunShineOffsetSecond = 0x28;
        ////最后值
        //DWORD SunShineNum=0;
        //if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &SunShineNum, sizeof(DWORD), NULL) == FALSE)
        //    __leave;


        DWORD SunShineOffsetSecond = 0x1f8;

        DWORD nData;
        nData = GetDlgItemInt(IDC_EDIT3);
        nData += 1000;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

// 树肥
void CPZToolsDlg::OnEnChangeEdit4()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x82c;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        ////二级偏移
        //DWORD SunShineOffsetSecond = 0x28;
        ////最后值
        //DWORD SunShineNum=0;
        //if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &SunShineNum, sizeof(DWORD), NULL) == FALSE)
        //    __leave;


        DWORD SunShineOffsetSecond = 0x230;

        DWORD nData;
        nData = GetDlgItemInt(IDC_EDIT4);
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}
// 杀虫剂
void CPZToolsDlg::OnEnChangeEdit5()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x82c;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        ////二级偏移
        //DWORD SunShineOffsetSecond = 0x28;
        ////最后值
        //DWORD SunShineNum=0;
        //if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &SunShineNum, sizeof(DWORD), NULL) == FALSE)
        //    __leave;


        DWORD SunShineOffsetSecond = 0x1fc;

        DWORD nData;
        nData = GetDlgItemInt(IDC_EDIT5);
        nData += 1000;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}
// 巧克力
void CPZToolsDlg::OnEnChangeEdit6()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x82c;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        ////二级偏移
        //DWORD SunShineOffsetSecond = 0x28;
        ////最后值
        //DWORD SunShineNum=0;
        //if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &SunShineNum, sizeof(DWORD), NULL) == FALSE)
        //    __leave;


        DWORD SunShineOffsetSecond = 0x228;

        DWORD nData;
        nData = GetDlgItemInt(IDC_EDIT6);
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }

}

void CPZToolsDlg::OnBnClickedCheck3()
{
    if( static_cast<CButton*>(GetDlgItem(IDC_CHECK3))->GetCheck() == TRUE)
    {
        SetTimer(FERTILIZERS,1000,NULL);
    }else
    {
        KillTimer(FERTILIZERS);
    }

}

void CPZToolsDlg::OnBnClickedCheck4()
{
    if( static_cast<CButton*>(GetDlgItem(IDC_CHECK4))->GetCheck() == TRUE)
    {
        SetTimer(TREEFERTILIZER,1000,NULL);
    }else
    {
        KillTimer(TREEFERTILIZER);
    }

}

void CPZToolsDlg::OnBnClickedCheck5()
{
    if( static_cast<CButton*>(GetDlgItem(IDC_CHECK5))->GetCheck() == TRUE)
    {
        SetTimer(INSECTICIDE,1000,NULL);
    }else
    {
        KillTimer(INSECTICIDE);
    }
}

void CPZToolsDlg::OnBnClickedCheck6()
{
    if( static_cast<CButton*>(GetDlgItem(IDC_CHECK5))->GetCheck() == TRUE)
    {
        SetTimer(CHOCOLATES,1000,NULL);
    }else
    {
        KillTimer(CHOCOLATES);
    }
}

void CPZToolsDlg::OnCbnSelchangeCombo1()
{
    Jump();
}

void CPZToolsDlg::OnCbnSelchangeCombo2()
{
    Jump();
}
// 跳关
void CPZToolsDlg::Jump()
{
    int nSelect1 = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO1))->GetCurSel();
    int nSelect2 = static_cast<CComboBox*>(GetDlgItem(IDC_COMBO2))->GetCurSel();

    nSelect1++;
    nSelect2++;

    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x82c;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        ////二级偏移
        //DWORD SunShineOffsetSecond = 0x28;
        ////最后值
        //DWORD SunShineNum=0;
        //if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &SunShineNum, sizeof(DWORD), NULL) == FALSE)
        //    __leave;


        DWORD SunShineOffsetSecond = 0x24;

        DWORD nData = nSelect1*nSelect2;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetSecond), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }

}

void CPZToolsDlg::OnBnClickedCheck7()
{
    if( static_cast<CButton*>(GetDlgItem(IDC_CHECK7))->GetCheck() == TRUE)
    {
        SetTimer(COOLING,500,NULL);
    }else
    {
        KillTimer(COOLING);
    }

}

void CPZToolsDlg::OnCooling()
{
    Cooling1();
    Cooling2();
    Cooling3();
    Cooling4();
    Cooling5();
    Cooling6();
    Cooling7();
    Cooling8();
    Cooling9();
    Cooling10();
}

void CPZToolsDlg::Cooling1()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0x50;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling2()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0xa0;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling3()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0xf0;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling4()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0x140;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling5()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0x190;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling6()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0x1e0;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling7()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0x230;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling8()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0x280;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling9()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0x2d0;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}

void CPZToolsDlg::Cooling10()
{
    HANDLE hProcess = NULL;
    __try
    {
        HWND hMainWnd = ::FindWindowW(NULL, L"植物大战僵尸中文版");
        DWORD dwPID = 0;
        GetWindowThreadProcessId(hMainWnd, &dwPID);	//获取进程标识
        if(dwPID == 0)
            __leave;

        // 打开进程
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, dwPID);
        if (hProcess == NULL)
            __leave;

        //基址
        DWORD SunShineBaseAddress = 0x6A9EC0;
        //基址值
        DWORD SunShineBaseAddressValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)SunShineBaseAddress, &SunShineBaseAddressValue, sizeof(DWORD), NULL) == FALSE)
            __leave;

        //一级偏移
        DWORD SunShineOffsetFirst = 0x768;
        //一级偏移值
        DWORD SunShineOffsetFirstValue = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineBaseAddressValue + SunShineOffsetFirst), &SunShineOffsetFirstValue, sizeof(DWORD), NULL) == FALSE)
            __leave;


        //二级偏移
        DWORD SunShineOffsetFirst1 = 0x144;
        //一级偏移值
        DWORD SunShineOffsetFirstValue1 = 0;
        if (ReadProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue + SunShineOffsetFirst1), &SunShineOffsetFirstValue1, sizeof(DWORD), NULL) == FALSE)
            __leave;

        DWORD SunShineOffsetSecond2 = 0x320;

        DWORD nData =0 ;
        WriteProcessMemory(hProcess, (LPVOID)(SunShineOffsetFirstValue1 + SunShineOffsetSecond2), &nData, sizeof(DWORD), NULL);
    }
    __finally
    {
        if(hProcess != NULL)
            CloseHandle(hProcess);
    }
}
