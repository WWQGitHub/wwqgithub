// DeleteEquipment.cpp : implementation file
//

#include "stdafx.h"
#include "Equipment.h"
#include "DeleteEquipment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CEquipmentApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CDeleteEquipment dialog


CDeleteEquipment::CDeleteEquipment(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteEquipment::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINTITLE);
	currentrow = -1;
	//{{AFX_DATA_INIT(CDeleteEquipment)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDeleteEquipment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteEquipment)
	DDX_Control(pDX, IDC_QUERYCONDITION, querycondition);
	DDX_Control(pDX, IDC_QUERY, query);
	DDX_Control(pDX, IDC_LIST1, list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDeleteEquipment, CDialog)
	//{{AFX_MSG_MAP(CDeleteEquipment)
	ON_COMMAND(ID_BUTTONREFRESH, OnButtonrefresh)
	ON_BN_CLICKED(IDC_QUERY, OnQuery)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_COMMAND(ID_BUTTONDELETE, OnButtondelete)
	ON_COMMAND(ID_BUTTONCLOSE, OnButtonclose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteEquipment message handlers

void CDeleteEquipment::OnOK() 
{
	// TODO: Add extra validation here
	

}

void CDeleteEquipment::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDeleteEquipment::OnInitDialog() 
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
	TBBUTTON  buttons[4];
	for (int i =0; i<4;i++)
	{
		CString str;
		int strlength;
		TCHAR *temp;
		if (i<1)
			buttons[i].fsStyle =TBSTYLE_SEP;
		else
		{
			buttons[i].fsStyle =TBSTYLE_BUTTON;
		}
		buttons[i].fsState =TBSTATE_ENABLED;
		buttons[i].dwData =0;
		if ((i ==2)|(i==3))
		{
			buttons[i].idCommand = ID_BUTTONADD+i+1;
			buttons[i].iBitmap = i+1;
			str.LoadString(ID_BUTTONADD+i+1);
		}
		else
		{
			buttons[i].idCommand = ID_BUTTONADD+i+1;
			buttons[i].iBitmap = i+1;
			str.LoadString(ID_BUTTONADD+i+1);//��һ����ťΪ�ָ���
		}
		strlength = str.GetLength()+1;
		temp = str.GetBufferSetLength(strlength);
		temp[strlength]= '\0';
		temp[strlength-1]= '\0';
		buttons[i].iString = toolbar.AddStrings(temp);		
		str.ReleaseBuffer();
	}
	toolbar.AutoSize();
	toolbar.AddButtons(4,buttons);
	toolbar.ShowWindow(SW_SHOW);
	list.SetExtendedStyle(LVS_EX_ONECLICKACTIVATE|LVS_REPORT|LVS_EX_FULLROWSELECT|LVS_OWNERDRAWFIXED |LVS_EX_FLATSB|LVS_SHOWSELALWAYS|LVS_EX_HEADERDRAGDROP);
	list.InsertColumn(100,_T("�ʲ����"));
	list.InsertColumn(100,_T("�ʲ�����"));
	list.InsertColumn(100,_T("���"));
	list.InsertColumn(100,_T("���ӷ�ʽ"));
	list.InsertColumn(100,_T("����ԭֵ"));
	list.InsertColumn(100,_T("�ۼ��۾�"));
	for (int i =0 ;i<6;i++)
		list.SetColumnWidth(i,100);
	OnButtonrefresh();
	return TRUE;  
}


void CDeleteEquipment::AddEquipName()
{
	_RecordsetPtr temp;
	temp =theApp.datamanage->Record1; 
	temp->raw_Close();
	temp->Open("select distinct name from EquipmentManage.dbo.tb_equipmentinfo",theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);
	querycondition.ResetContent();
	while (!temp->ADOEOF)
	{
		CString str;
		str = temp->GetFields()->GetItem("name")->Value.bstrVal;
		querycondition.AddString(str);
		temp->MoveNext();
	}
}

void CDeleteEquipment::OnButtonrefresh() 
{
	AddEquipName();
	list.DeleteAllItems();
}

void CDeleteEquipment::OnQuery() 
{
	CString str;
	querycondition.GetWindowText(str);
	if(!str.IsEmpty())
	{
		_RecordsetPtr temp;
		list.DeleteAllItems();
		temp =theApp.datamanage->Record1; 
		temp->raw_Close();
		CString sql;
		sql.Format(_T("select * from EquipmentManage.dbo.tb_equipmentinfo where name = '%s'"),str);
		temp->Open((_bstr_t)sql,theApp.datamanage->GetConn().GetInterfacePtr(),adOpenKeyset,adLockPessimistic,adCmdText);		
		if (temp->RecordCount>0)
		{
			int row = 0;
			while (!temp->ADOEOF)
			{
				list.InsertItem(row,_T(""),0);
				for (int i= 0;i<6;i++)
				{
					CString str;
					_variant_t value;
					value = temp->GetFields()->GetItem((long)i)->Value;
					str = (TCHAR *)(_bstr_t)value;
					list.SetItemText(row,i,str);
				}
				row +=1;
				temp->MoveNext();
			}
		}
		else
			MessageBox(_T("û�з��ַ�������������"),_T("��ʾ"),64);		
	}
	else
		MessageBox(_T("�����ò�ѯ����"),_T("��ʾ"),64);	
}

void CDeleteEquipment::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	// TODO: Add your control notification handler code here
	currentrow = list.GetSelectionMark(); 	
	*pResult = 0;
}

void CDeleteEquipment::OnButtondelete() 
{
	if (MessageBox(_T("ȷʵҪɾ����ǰ������?"),_T("��ʾ"),MB_YESNO)==IDYES)	
	{
		if (currentrow!=-1)
		{
			CString id;
			id = list.GetItemText(currentrow,0); //����ʲ����
			try
			{
				CString sql;
				sql.Format(_T("delete from EquipmentManage.dbo.tb_equipmentinfo where equipmentid = '%s'"),id);
				theApp.datamanage->ExecSQL(sql);
				MessageBox(_T("�����ɹ�."),_T("��ʾ"),64);
			}
			catch(...)
			{
				MessageBox(_T("����ʧ��."),_T("��ʾ"),64);	
			}
			OnButtonrefresh();
			currentrow = -1;
		}
		else
		{
			MessageBox(_T("��ѡ����ɾ��������."),_T("��ʾ"),64);
		}
	}
}

void CDeleteEquipment::OnButtonclose() 
{
	EndDialog(0);	
}
