
// PZTools.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPZToolsApp:
// �йش����ʵ�֣������ PZTools.cpp
//

class CPZToolsApp : public CWinAppEx
{
public:
	CPZToolsApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPZToolsApp theApp;