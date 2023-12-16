
// LoaderDlg.h : ヘッダー ファイル
//

#pragma once

class CLoaderDlgAutoProxy;


// CLoaderDlg ダイアログ
class CLoaderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoaderDlg);
	friend class CLoaderDlgAutoProxy;

// コンストラクション
public:
	CLoaderDlg(CWnd* pParent = nullptr);	// 標準コンストラクター
	virtual ~CLoaderDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOADER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	CLoaderDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
};
