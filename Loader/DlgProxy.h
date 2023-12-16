
// DlgProxy.h : ヘッダー ファイル
//

#pragma once

class CLoaderDlg;


// CLoaderDlgAutoProxy コマンド ターゲット

class CLoaderDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CLoaderDlgAutoProxy)

	CLoaderDlgAutoProxy();           // 動的生成で使用される protected コンストラクター

// 属性
public:
	CLoaderDlg* m_pDialog;

// 操作
public:

// オーバーライド
	public:
	virtual void OnFinalRelease();

// 実装
protected:
	virtual ~CLoaderDlgAutoProxy();

	// 生成された、メッセージ割り当て関数

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CLoaderDlgAutoProxy)

	// 生成された OLE ディスパッチ割り当て関数

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

