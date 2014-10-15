// CustomBar.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "CustomBar.h"
#include "EquipmentDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomBar

extern CEquipmentApp theApp;
//extern CEquipmentDlg dlg;
CCustomBar::~CCustomBar()
{
	delete (imagelist);
}


BEGIN_MESSAGE_MAP(CCustomBar, CToolBarCtrl)
	//{{AFX_MSG_MAP(CCustomBar)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomBar message handlers

CCustomBar::CCustomBar()
{
	imagelist = new CImageList();
}

BOOL CCustomBar::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
	CToolBarCtrl::Create(dwStyle,rect,pParentWnd,nID);//调用父类的Create方法
	m_ButtonCount =IDS_QUIT-IDS_EQUIPKIND+1; //设计按钮数量
	TBBUTTON* m_pButtons;
	SetBitmapSize(CSize(32,32));//设置按钮位图大小
	imagelist->Create(32,32,ILC_COLOR32|ILC_MASK,0,0);
	for (int n =0;n<13;n++)
	{
		imagelist->Add(theApp.LoadIcon(n+IDI_TOOLBAR1));
	}
	SetImageList(imagelist);
	m_pButtons = new TBBUTTON[m_ButtonCount];
	for (int i = 0; i<m_ButtonCount; i++)
	{
		CString string;
		string.LoadString(i+IDS_EQUIPKIND);
		int stringlength = string.GetLength()+1;
		TCHAR * char1 = string.GetBufferSetLength(stringlength);
		char1[stringlength]=0;
		char1[stringlength-1]=0;
		VERIFY((m_pButtons[i].iString =AddStrings(char1))!=-1);
		m_pButtons[i].fsState = TBSTATE_ENABLED;
		m_pButtons[i].dwData = 0;
		m_pButtons[i].fsStyle = TBSTYLE_BUTTON;
		m_pButtons[i].iBitmap = i; //设置按钮位图
		m_pButtons[i].idCommand = i+IDS_EQUIPKIND;	
		string.ReleaseBuffer();
	}
	m_pButtons[m_ButtonCount-1].idCommand = ID_BUTTONCLOSE;
	/******************设置工具栏分割条***********************/
	TBBUTTON sepButton;
	sepButton.idCommand = 0;
	sepButton.fsStyle = TBSTYLE_SEP;
	sepButton.fsState = TBSTATE_ENABLED;
	sepButton.iString = 0;
	sepButton.iBitmap = 0;
	sepButton.dwData = 0;
	/******************设置工具栏分割条***********************/
	for (int j = 0; j <m_ButtonCount;j++)
	{
		VERIFY(AddButtons(1,&m_pButtons[j]));
		if (!((j+1) % 3))
		{
			VERIFY(AddButtons(1,&sepButton));	
		}
	}
	return true;
}

void CCustomBar::OnMouseMove(UINT nFlags, CPoint point) 
{
	CToolBarCtrl::OnMouseMove(nFlags, point);
	int i;
	for (i=0;i<17;i++)
	{
		CRect  rect;
		GetItemRect(i,&rect);
		if ((rect.right>=point.x)&&(rect.bottom>=point.y))
		{
			CString str;
			DoMouseMove(i);
			return ;
		}
	}
	DoMouseLeave();	
}


void CCustomBar::DoMouseMove(int strid)
{	
	CString str;
	int temp;
	temp = strid / 4; //每3个工具栏按钮间有1个分隔条
	str.LoadString(strid+IDS_EQUIPKIND-temp);
	CEquipmentDlg * dlg;
	dlg = (CEquipmentDlg *)theApp.m_pMainWnd;
	dlg->statusbar.SetText(str,1,0);	
}

void CCustomBar::DoMouseLeave()
{
	CEquipmentDlg * dlg;
	dlg = (CEquipmentDlg *)theApp.m_pMainWnd;
	dlg->statusbar.SetText(_T(""),1,0);
}
