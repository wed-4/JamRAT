
// Loader.cpp : アプリケーションのクラス動作を定義します。
//

#include "pch.h"
#include "framework.h"
#include "Loader.h"
#include "LoaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLoaderApp

BEGIN_MESSAGE_MAP(CLoaderApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CLoaderApp の構築

CLoaderApp::CLoaderApp()
{
	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}


// 唯一の CLoaderApp オブジェクト

CLoaderApp theApp;

const GUID CDECL BASED_CODE _tlid =
		{0x9f4faad7,0xf1e9,0x4e6f,{0xa2,0x71,0x3e,0x79,0x0c,0xa0,0x1f,0x7c}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CLoaderApp の初期化

BOOL CLoaderApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// OLE ライブラリを初期化します。
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ダイアログにシェル ツリー ビューまたはシェル リスト ビュー コントロールが
	// 含まれている場合にシェル マネージャーを作成します。
	CShellManager *pShellManager = new CShellManager;

	// MFC コントロールでテーマを有効にするために、"Windows ネイティブ" のビジュアル マネージャーをアクティブ化
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("アプリケーション ウィザードで生成されたローカル アプリケーション"));
	// オートメーションまたは reg/unreg スイッチのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// アプリケーションが /Embedding または /Automation スイッチで起動されました。
	// アプリケーションをオートメーション サーバーとして実行します。
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// CoRegisterClassObject() 経由でクラス ファクトリを登録します。
		COleTemplateServer::RegisterAll();
	}
	// アプリケーションが /Unregserver または /Unregister スイッチで起動されました。
	// レジストリからエントリを削除します。
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		COleObjectFactory::UpdateRegistryAll(FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
		return FALSE;
	}
	// アプリケーションがスタンドアロンまたは/Register や /Regserver などのスイッチで起動されました。
	// タイプ ライブラリを含むレジストリ エントリを更新します。
	else
	{
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
		if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppRegister)
			return FALSE;
	}

	CLoaderDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ダイアログが <OK> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ダイアログが <キャンセル> で消された時のコードを
		//  記述してください。
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: ダイアログの作成に失敗しました。アプリケーションは予期せずに終了します。\n");
		TRACE(traceAppMsg, 0, "警告: ダイアログで MFC コントロールを使用している場合、#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS を指定できません。\n");
	}

	// 上で作成されたシェル マネージャーを削除します。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// ダイアログは閉じられました。アプリケーションのメッセージ ポンプを開始しないで
	//  アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

int CLoaderApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
