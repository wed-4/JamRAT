
// DlgProxy.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "Loader.h"
#include "DlgProxy.h"
#include "LoaderDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLoaderDlgAutoProxy

IMPLEMENT_DYNCREATE(CLoaderDlgAutoProxy, CCmdTarget)

CLoaderDlgAutoProxy::CLoaderDlgAutoProxy()
{
	EnableAutomation();

	// オートメーション オブジェクトがアクティブである限り、アプリケーションを
	//	実行状態にしてください、コンストラクターは AfxOleLockApp を呼び出します。
	AfxOleLockApp();

	// アプリケーションのメイン ウィンドウ ポインターをとおしてダイアログ
	//  へアクセスします。プロキシの内部ポインターからダイアログへのポイ
	//  ンタを設定し、ダイアログの戻りポインターをこのプロキシへ設定しま
	//  す。
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CLoaderDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CLoaderDlg)))
		{
			m_pDialog = reinterpret_cast<CLoaderDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CLoaderDlgAutoProxy::~CLoaderDlgAutoProxy()
{
	// すべてのオブジェクトがオートメーションで作成された場合にアプリケーション
	//	を終了するために、デストラクターが AfxOleUnlockApp を呼び出します。
	//  他の処理の間に、メイン ダイアログを破壊します。
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CLoaderDlgAutoProxy::OnFinalRelease()
{
	// オートメーション オブジェクトに対する最後の参照が解放されるときに
	// OnFinalRelease が呼び出されます。基底クラスは自動的にオブジェクトを
	// 削除します。追加のクリーンアップが必要です
	// 別な後処理を追加してください。

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CLoaderDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CLoaderDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// メモ: VBA からタイプ セーフなバインドをサポートするために、IID_ILoader のサポートを追加します
//  この IID は、.IDL ファイルのディスパッチ インターフェイスへアタッチされる
//  GUID と一致しなければなりません。

// {d0428a44-69c1-4997-8471-412d6db38327}
static const IID IID_ILoader =
{0xd0428a44,0x69c1,0x4997,{0x84,0x71,0x41,0x2d,0x6d,0xb3,0x83,0x27}};

BEGIN_INTERFACE_MAP(CLoaderDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CLoaderDlgAutoProxy, IID_ILoader, Dispatch)
END_INTERFACE_MAP()

// IMPLEMENT_OLECREATE2 マクロが、このプロジェクトの pch.h で定義されます。
// {8f985ffa-9ead-4e3a-a1af-0e66d2d65bf4}
IMPLEMENT_OLECREATE2(CLoaderDlgAutoProxy, "Loader.Application", 0x8f985ffa,0x9ead,0x4e3a,0xa1,0xaf,0x0e,0x66,0xd2,0xd6,0x5b,0xf4)


// CLoaderDlgAutoProxy メッセージ ハンドラー
