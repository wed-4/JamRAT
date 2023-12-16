
// Loader.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CLoaderApp:
// このクラスの実装については、Loader.cpp を参照してください
//

class CLoaderApp : public CWinApp
{
public:
	CLoaderApp();

// オーバーライド
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CLoaderApp theApp;
