// BatchPasswordGenerator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBatchPasswordGeneratorApp:
// �йش����ʵ�֣������ BatchPasswordGenerator.cpp
//

class CBatchPasswordGeneratorApp : public CWinApp
{
public:
	CBatchPasswordGeneratorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBatchPasswordGeneratorApp theApp;