
// glassDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "glass.h"
#include "glassDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CglassDlg 对话框




CglassDlg::CglassDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CglassDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CglassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CglassDlg, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


const COLORREF maskColor = RGB(0, 0, 0);	// 透明颜色
const COLORREF textColor = RGB(0, 255, 0);	// 标签文本颜色


// CglassDlg 消息处理程序

BOOL CglassDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码 
	//////////////////////////////////////////////////////////////////////////
	// 鼠标穿透要带WS_EX_TRANSPARENT，并且要设置窗口置顶
	LONG lWindLong = GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE);
	::SetWindowLong(m_hWnd, GWL_EXSTYLE, lWindLong | WS_EX_TRANSPARENT | WS_EX_LAYERED | WS_EX_TOPMOST);
	SetLayeredWindowAttributes(maskColor, 0, LWA_COLORKEY);

	//::SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//////////////////////////////////////////////////////////////////////////

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


HBRUSH CglassDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
	HBRUSH hBrush = __super::OnCtlColor(pDC, pWnd, nCtlColor);
	
	switch(pWnd->GetDlgCtrlID()) {
		case IDC_STATIC:
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(textColor);
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		default:
				break; 
	}

	return hBrush;
}

BOOL CglassDlg::OnEraseBkgnd(CDC *pDC) {
	CRect clientRect ;

	GetClientRect(&clientRect) ;
	pDC->FillSolidRect(clientRect, maskColor);

	return FALSE  ;
}
