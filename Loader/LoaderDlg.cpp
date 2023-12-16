
// LoaderDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "Loader.h"
#include "LoaderDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLoaderDlg ダイアログ


IMPLEMENT_DYNAMIC(CLoaderDlg, CDialogEx);

CLoaderDlg::CLoaderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOADER_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
}

CLoaderDlg::~CLoaderDlg()
{
	// このダイアログ用のオートメーション プロキシがある場合は、このダイアログ
	//  へのポインターを null に戻します。それによってダイアログが削除されたこと
	//  がわかります。
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;
}

void CLoaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLoaderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CLoaderDlg メッセージ ハンドラー

BOOL CLoaderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CLoaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CLoaderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CLoaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// コントローラーがオブジェクトの 1 つをまだ保持している場合、
//  オートメーションサーバーはユーザーが UI を閉じる際に終了で
//  きません。これらのメッセージ ハンドラーはプロキシがまだ使用中
//  かどうかを確認し、それから UI が非表示になりますがダイアロ
//  グはそれが消された場合その場所に残ります。

void CLoaderDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CLoaderDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CLoaderDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CLoaderDlg::CanExit()
{
	// プロキシ オブジェクトがまだ残っている場合、オートメーション
	//  コントローラーはこのアプリケーションをまだ保持しています。
	//  ダイアログの周囲は残しますが UI は非表示になります。
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

