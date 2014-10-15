// UseState.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "UseState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CUseState dialog


CUseState::CUseState(CWnd* pParent /*=NULL*/)
	: CDialog(CUseState::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
}


void CUseState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUseState)
	DDX_Control(pDX, IDC_EDIT1, kind);
	DDX_Control(pDX, IDC_LIST, list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUseState, CDialog)
	//{{AFX_MSG_MAP(CUseState)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_COMMAND(ID_BUTTONADD, OnButtonadd)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	ON_COMMAND(ID_BUTTONDELETE, OnButtondelete)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_COMMAND(ID_BUTTONUPDATE, OnButtonupdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseState message handlers

void CUseState::OnOK() 
{
	// TODO: Add extra validation here
	

}

void CUseState::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CUseState::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetIcon(m_hIcon,true);
	toolbar.Create(TBSTYLE_FLAT|CCS_TOP|WS_CHILD|WS_VISIBLE|WS_BORDER|CCS_ADJUSTABLE|TBSTYLE_WRAPABLE,CRect(0,0,0,0),this,IDR_TOOLBAR2);
	toolbar.SetBitmapSize(CSize(32,32));
	imagelist.Create(32,32,ILC_COLOR32|ILC_MASK,0,0);
	for (int n =0;n<5;n++)
	{
		imagelist.Add(theApp.LoadIcon(n+IDI_ICON1));
	}	
	toolbar.SetImageList(&imagelist);
	TBBUTTON  buttons[6];
	for (int i =0; i<6;i++)
	{
			CString str;
			int strlength;
			TCHAR *temp;
			str.LoadString(ID_BUTTONADD+i-1);//��һ����ťΪ�ָ���
			strlength = str.GetLength()+1;
			temp = str.GetBufferSetLength(strlength);
			temp[strlength]= '\0';
			temp[strlength-1]= '\0';
		if (i<1)
			buttons[i].fsStyle =TBSTYLE_SEP;
		else
		{
			buttons[i].fsStyle =TBSTYLE_BUTTON;
		}
		buttons[i].fsState =TBSTATE_ENABLED;
		buttons[i].dwData =0;
		buttons[i].idCommand = ID_BUTTONADD+i-1;		
		buttons[i].iString = toolbar.AddStrings(temp);
		buttons[i].iBitmap = i-1;
		str.ReleaseBuffer();
	}	
	toolbar.AutoSize();
	toolbar.AddButtons(6,buttons);
	toolbar.ShowWindow(SW_SHOW);
	list.SetExtendedStyle(LVS_REPORT|LVS_EX_FULLROWSELECT|LVS_OWNERDRAWFIXED |LVS_EX_FLATSB|LVS_SHOWSELALWAYS|LVS_EX_HEADERDRAGDROP);
	list.InsertColumn(1,_T("�ʲ�ʹ��״��"));//���б��������
	list.SetColumnWidth(0,340);//�����п��
	OnButtonrefresh();
	return TRUE;  
}

bool CUseState::IsRepeated(CString str)
{
	CString sql;
	sql.Format(_T("select * from EquipmentManage.dbo.tb_usestate where usestate = '%s'"),str);
	theApp.datamanage->Record1->raw_Close();	
	theApp.datamanage->Record1->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockOptimistic,adCmdText);
	if(theApp.datamanage->Record1->RecordCount>0)
		return true;
	return false;
}


void CUseState::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int currentrow = list.GetSelectionMark();//�õ���ǰ��
	if (currentrow!=-1)
	{
		kind.SetWindowText(list.GetItemText(currentrow,0));
	}
	else
		kind.SetWindowText(_T(""));	
	*pResult = 0;
}

void CUseState::OnButtonadd() 
{
	CString str;
	kind.GetWindowText(str);
	if (!str.IsEmpty())
	{
		if (!IsRepeated(str))
		{
			try
			{
				CString sql;
				sql.Format(_T("insert into EquipmentManage.dbo.tb_usestate values ('%s')"),str);
				theApp.datamanage->ExecSQL(sql);
				MessageBox(_T("�����ɹ�."),_T("��ʾ"),64);
				kind.SetWindowText(_T(""));
				kind.SetFocus();
			}
			catch(...)
			{
				MessageBox(_T("����ʧ��."),_T("��ʾ"),64);
				kind.SetFocus();
				kind.SetSel(0);
			}
			OnButtonrefresh() ;
		}
		else
			MessageBox(_T("������Ѵ���."),_T("��ʾ"),64);
	}
	else
		AfxMessageBox(_T("������Ϣ����Ϊ��."),0,0);	
}

void CUseState::OnButtonclose() 
{
	EndDialog(01);		
}

void CUseState::OnButtondelete() 
{
	if(MessageBox(_T("ȷʵҪɾ����ǰ��¼��?"),_T("��ʾ"),MB_YESNO)==IDYES)
		if (theApp.datamanage->GetRecordset()->RecordCount>0)
		{
			int currentrow = list.GetSelectionMark();//�õ���ǰ��
			if (currentrow !=-1)
			{
				CString sql,olddata;
				olddata = list.GetItemText(currentrow,0);
				sql.Format(_T("delete EquipmentManage.dbo.tb_usestate where usestate = '%s'"),olddata);
				try
				{
					theApp.datamanage->ExecSQL(sql);
					MessageBox(_T("�����ɹ�."),_T("��ʾ"),64);
				}
				catch(...)
				{
					MessageBox(_T("����ʧ��."),_T("��ʾ"),64);			
				}
				OnButtonrefresh() ;
			}
			else
			{
				MessageBox(_T("���ڱ����ѡ����ɾ��������."),_T("��ʾ"),64);	
			}
		}			
		else
			MessageBox(_T("��ǰû�п�ɾ���ļ�¼."),_T("��ʾ"));		
}

void CUseState::OnButtonrefresh() 
{
	kind.SetWindowText(_T(""));
	list.DeleteAllItems();
	theApp.datamanage->GetRecordset()->raw_Close();
	theApp.datamanage->GetRecordset()->Open("select usestate as ʹ��״�� from EquipmentManage.dbo.tb_usestate",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	if (theApp.datamanage->GetRecordset()->RecordCount >0)
	{
		while (! theApp.datamanage->GetRecordset()->ADOEOF)
		{
			CString str;
			_variant_t temp;
			temp =theApp.datamanage->GetRecordset()->GetCollect((long)0);
			str = temp.bstrVal;
			list.InsertItem(0,str,0);
			theApp.datamanage->GetRecordset()->MoveNext();
		}
	}	
}
void CUseState::OnButtonupdate() 
{
	if (theApp.datamanage->GetRecordset()->RecordCount >0)
	{
		if(MessageBox(_T("ȷʵҪ�޸ĵ�ǰ������?"),_T("��ʾ"),MB_YESNO)==IDYES )
		{
			CString str;
			kind.GetWindowText(str);			
			if (str.IsEmpty()) //�ж�����������Ϣ�Ƿ�Ϊ��
			{
				MessageBox(_T("������Ϣ����Ϊ��"),_T("��ʾ"),64);
			}
			else if (!IsRepeated(str))
			{
				int currentrow = list.GetSelectionMark();//�õ���ǰ��
				if (currentrow!=-1)
				{
					try
					{
						CString sql,olddata;
						olddata = list.GetItemText(currentrow,0);		
						sql.Format(_T("update EquipmentManage.dbo.tb_usestate set usestate = '%s' where usestate = '%s'"),str,olddata);
						theApp.datamanage->ExecSQL(sql);
						MessageBox(_T("�����ɹ�."),_T("��ʾ"),64);
						kind.SetWindowText(_T(""));
						kind.SetFocus();					
					}
					catch(...)
					{
						MessageBox(_T("����ʧ��."),_T("��ʾ"),64);				
					}
					OnButtonrefresh() ;
				}
				else
				{
					MessageBox(_T("��ǰû�п��޸ĵ�����."),_T("��ʾ"),64);	
				}
			}
			else
				MessageBox(_T("������Ѿ�����."),_T("��ʾ"),64);
		}
	}
	else
		MessageBox(_T("��ǰû�п��޸ĵ�����."),_T("��ʾ"),64);	
}
