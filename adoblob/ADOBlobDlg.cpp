// ADOBlobDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ADOBlob.h"
#include "ADOBlobDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CADOBlobApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADOBlobDlg dialog

CADOBlobDlg::CADOBlobDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CADOBlobDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CADOBlobDlg)
	m_UserName = _T("");
	m_Old = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bModify = FALSE;
	m_hPhotoBitmap = NULL;
	m_pBMPBuffer = NULL;
}

void CADOBlobDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADOBlobDlg)
	DDX_Control(pDX, IDC_DELETEUSER, m_buttonDeleteUser);
	DDX_Control(pDX, IDC_PREVIOUSUSER, m_buttonPreviousUser);
	DDX_Control(pDX, IDC_NEXTUSER, m_buttonNextUser);
	DDX_Control(pDX, IDC_OLD, m_editOld);
	DDX_Control(pDX, IDC_USERNAME, m_editUserName);
	DDX_Control(pDX, IDC_SELECTPHOTO, m_buttonSelectPhoto);
	DDX_Control(pDX, IDC_SAVEINFO, m_buttonSaveInfo);
	DDX_Text(pDX, IDC_USERNAME, m_UserName);
	DDX_Text(pDX, IDC_OLD, m_Old);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Control(pDX, IDC_OPEN, m_open);
	DDX_Control(pDX, IDC_EDIT1, m_older);
}

BEGIN_MESSAGE_MAP(CADOBlobDlg, CDialog)
	//{{AFX_MSG_MAP(CADOBlobDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADDUSER, OnAddUser)
	ON_EN_CHANGE(IDC_USERNAME, OnChangeUsername)
	ON_EN_CHANGE(IDC_OLD, OnChangeOld)
	ON_BN_CLICKED(IDC_SAVEINFO, OnSaveinfo)
	ON_BN_CLICKED(IDC_SELECTPHOTO, OnSelectphoto)
	ON_BN_CLICKED(IDC_NEXTUSER, OnNextUser)
	ON_BN_CLICKED(IDC_PREVIOUSUSER, OnPreviousUser)
	ON_BN_CLICKED(IDC_DELETEUSER, OnDeleteUser)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPEN, &CADOBlobDlg::OnOpen)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CADOBlobDlg::OnCombo1)
	ON_BN_CLICKED(IDC_READ, &CADOBlobDlg::OnRead)
	ON_BN_CLICKED(IDC_AGE, &CADOBlobDlg::OnClickedAge)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADOBlobDlg message handlers

BOOL CADOBlobDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_bNewUser = FALSE;
	m_pRecordset.CreateInstance("ADODB.Recordset");
	HRESULT hr = m_pRecordset->Open("SELECT * FROM userphoto",_variant_t((IDispatch *)theApp.m_pConnection,true),adOpenDynamic,adLockPessimistic,adCmdText);
    if(SUCCEEDED(hr))
	{
		ReadData();
	}
	ResetControls();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////��ȡ��¼����ǰ��¼�����ݣ�����ͼ������//////////////
void CADOBlobDlg::ReadData()
{
	DestroyPhoto();						///���ԭͼ��
	if(m_pRecordset->adoEOF||m_pRecordset->BOF) 
	{
		m_UserName.Empty();
		m_Old.Empty();
		UpdateData(FALSE);
		return;
	}
	long lDataSize = m_pRecordset->GetFields()->GetItem("photo")->ActualSize;
	if(lDataSize > 0)
	{
		_variant_t			varBLOB;
		varBLOB = m_pRecordset->GetFields()->GetItem("photo")->GetChunk(lDataSize);
		if(varBLOB.vt == (VT_ARRAY | VT_UI1))
		{
			if(m_pBMPBuffer = new char[lDataSize+1])				///���·����Ҫ�Ĵ洢�ռ�
			{	
				char *pBuf = NULL;
				SafeArrayAccessData(varBLOB.parray,(void **)&pBuf);
				memcpy(m_pBMPBuffer,pBuf,lDataSize);				///�������ݵ�������m_pBMPBuffer
				SafeArrayUnaccessData (varBLOB.parray);
				m_nFileLen = lDataSize;
				m_hPhotoBitmap = BufferToHBITMAP();					///����BITMAP����
			}
		}
	}
	m_UserName = m_pRecordset->GetCollect("username").bstrVal;
	m_Old.Format("%d",m_pRecordset->GetCollect("old").lVal);
	m_editUserName.EnableWindow();
	m_editOld.EnableWindow();
	m_buttonSelectPhoto.EnableWindow();
	m_buttonDeleteUser.EnableWindow();
	UpdateData(FALSE);
}

void CADOBlobDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

/////////////////����Ļ����ʾͼ��///////////////////
void CADOBlobDlg::DrawUserPhoto(int x, int y, CDC *pDC)
{
	if(!m_hPhotoBitmap) return;
	HBITMAP OldBitmap;
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	OldBitmap=(HBITMAP)MemDC.SelectObject(m_hPhotoBitmap);
	pDC->BitBlt(x,y,100,130,&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(OldBitmap);
}

void CADOBlobDlg::OnPaint() 
{
	CPaintDC dc(this);
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DrawUserPhoto(50,30,&dc);
		CDialog::OnPaint();
	}
}

HCURSOR CADOBlobDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CADOBlobDlg::OnAddUser() 
{
	if(m_bModify)
	{
		int nRet = MessageBox("��ǰ�û���Ϣ��δ���棬�Ƿ񱣴�?","VC֪ʶ�� WWW.VCKBASE.COM",MB_YESNOCANCEL);
		switch(nRet)
		{
		case IDCANCEL:
			return;
		case IDYES:
			OnSaveinfo();
			break;
		case IDNO:
		default:
			break;
		}
	}
	m_editUserName.EnableWindow();
	m_editOld.EnableWindow();
	m_buttonSelectPhoto.EnableWindow();
	m_buttonDeleteUser.EnableWindow(FALSE);
	m_Old = "";
	m_UserName = "";
	m_bModify = FALSE;
	m_bNewUser = TRUE;
	UpdateData(FALSE);
	DestroyPhoto();
	Invalidate();
}

//////////////ɾ���û�//////////////
void CADOBlobDlg::OnDeleteUser() 
{
	m_pRecordset->Delete(adAffectCurrent);
	if(m_pRecordset->adoEOF)
		m_pRecordset->MoveLast();
	ResetControls();
	m_buttonDeleteUser.EnableWindow(FALSE);
	ReadData();
	Invalidate();
}

void CADOBlobDlg::OnChangeUsername()
{
	m_bModify = TRUE;
	m_buttonSaveInfo.EnableWindow();
}

void CADOBlobDlg::OnChangeOld() 
{
	m_bModify = TRUE;
	m_buttonSaveInfo.EnableWindow();
}

////////////////�����û���Ϣ/////////////////
void CADOBlobDlg::OnSaveinfo() 
{
	if(!m_bModify) return;
	UpdateData();
	if(m_pBMPBuffer == NULL || m_hPhotoBitmap == NULL || m_UserName == "" || m_Old == "")
	{
		AfxMessageBox("��û���ṩ�������û���Ϣ��\r\n��Щ��Ϣ����:�û��������䡢��Ƭ");
		return;
	}
	m_buttonSaveInfo.EnableWindow(FALSE);
	char			*pBuf = m_pBMPBuffer;
	VARIANT			varBLOB;
	SAFEARRAY		*psa;
    SAFEARRAYBOUND	rgsabound[1];

	if(m_bNewUser)
		m_pRecordset->AddNew();
	m_pRecordset->PutCollect("username",_variant_t(m_UserName));
	m_pRecordset->PutCollect("old",atol(m_Old));
	if(pBuf)
	{    
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = m_nFileLen;
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for (long i = 0; i < (long)m_nFileLen; i++)
			SafeArrayPutElement (psa, &i, pBuf++);
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
		m_pRecordset->GetFields()->GetItem("photo")->AppendChunk(varBLOB);
	}
	m_pRecordset->Update();
	m_buttonDeleteUser.EnableWindow();
	ResetControls();
	m_bNewUser = FALSE;
	m_bModify = FALSE;
}

///////////ѡ��BMP�ļ������ص��ڴ�/////////////
void CADOBlobDlg::OnSelectphoto() 
{
	static char BASED_CODE szFilter[] = "BMP Files (*.bmp)|*.bmp|All Files (*.*)|*.*||";
	CFileDialog dlg(TRUE,"BMP",NULL,  OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		CString pathname = dlg.GetPathName();
		DestroyPhoto();
		LoadBMPFile(pathname);
		m_hPhotoBitmap = BufferToHBITMAP();
		m_bModify = TRUE;
		m_buttonSaveInfo.EnableWindow();
		Invalidate();
	}
}

/////////////�������Ķ���/////////////
void CADOBlobDlg::DestroyPhoto()
{
	if(m_hPhotoBitmap)
	{
		DeleteObject(m_hPhotoBitmap);
		m_hPhotoBitmap = NULL;
	}
	if(m_pBMPBuffer)
	{
		delete m_pBMPBuffer;
		m_pBMPBuffer = NULL;
	}
}

/////////////����BMP�ļ����ڴ�//////////////
BOOL CADOBlobDlg::LoadBMPFile(const char *pBMPPathname)
{
	CFile file;
	if( !file.Open( pBMPPathname, CFile::modeRead) )
		return FALSE;
	m_nFileLen = file.GetLength();
	m_pBMPBuffer = new char[m_nFileLen + 1];
	if(!m_pBMPBuffer)
		return FALSE;
	if(file.Read(m_pBMPBuffer,m_nFileLen) != m_nFileLen)
		return FALSE;
	return TRUE;
}

///////////���ڴ��е�BMP�ļ�����ת����HBITMAP///////
HBITMAP CADOBlobDlg::BufferToHBITMAP()
{
	HBITMAP				hBmp;
	LPSTR				hDIB,lpBuffer = m_pBMPBuffer;
	LPVOID				lpDIBBits;
	BITMAPFILEHEADER	bmfHeader;
	DWORD				bmfHeaderLen;

	bmfHeaderLen = sizeof(bmfHeader);
	strncpy((LPSTR)&bmfHeader,(LPSTR)lpBuffer,bmfHeaderLen);
//	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B')) return NULL;
	if (bmfHeader.bfType != (*(WORD*)"BM")) return NULL;//��copy��Windows������ơ��ϵ�������
	hDIB = lpBuffer + bmfHeaderLen;
	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
/*	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 1 << bmiHeader.biBitCount; 
	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
			((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);
*///ԭ���Ĵ��롣
	lpDIBBits=(lpBuffer)+((BITMAPFILEHEADER *)lpBuffer)->bfOffBits;//���й��ܺ����汻ע�͵��Ĵ�����ͬ��������⡣
	CClientDC dc(this);
	hBmp = CreateDIBitmap(dc.m_hDC,&bmiHeader,CBM_INIT,lpDIBBits,&bmInfo,DIB_RGB_COLORS);
	return hBmp;
}


BOOL CADOBlobDlg::DestroyWindow() 
{
	DestroyPhoto();
	return CDialog::DestroyWindow();
}

//////////////��һ���û���Ϣ///////////////
void CADOBlobDlg::OnNextUser() 
{
	if(m_bModify)///���統ǰ��¼�Ķ������򱣴�
		OnSaveinfo();
	m_pRecordset->MoveNext();
	if(m_pRecordset->adoEOF)
		m_pRecordset->MoveLast();
	ReadData();
	ResetControls();
	Invalidate();
}

/////////////��һ���û���Ϣ/////////////////
void CADOBlobDlg::OnPreviousUser() 
{
	if(m_bModify)///���統ǰ��¼�Ķ������򱣴�
		OnSaveinfo();
	m_pRecordset->MovePrevious();
	if(m_pRecordset->BOF)
		m_pRecordset->MoveFirst();
	ReadData();
	ResetControls();
	Invalidate();
}

////////////////�ж��Ƿ������һ����¼//////////////
BOOL CADOBlobDlg::LastRecord()
{
	if(m_pRecordset->adoEOF)
	{
		m_editUserName.EnableWindow(FALSE);
		m_editOld.EnableWindow(FALSE);
		m_buttonSelectPhoto.EnableWindow(FALSE);
		return TRUE;
	}
	m_pRecordset->MoveNext();
	if(m_pRecordset->adoEOF)
	{
		m_pRecordset->MovePrevious();
		return TRUE;
	}
	else
	{
		m_pRecordset->MovePrevious();
		return FALSE;
	}

}

////////////////�ж��Ƿ��ǵ�һ����¼////////////////
BOOL CADOBlobDlg::FirstRecord()
{
	if(m_pRecordset->BOF)
	{
		m_editUserName.EnableWindow(FALSE);
		m_editOld.EnableWindow(FALSE);
		m_buttonSelectPhoto.EnableWindow(FALSE);
		return TRUE;
	}
	m_pRecordset->MovePrevious();
	if(m_pRecordset->BOF)
	{
		m_pRecordset->MoveFirst();
		return TRUE;
	}
	else
	{
		m_pRecordset->MoveNext();
		return FALSE;
	}
}

void CADOBlobDlg::ResetControls()
{
	BOOL IsFirstRecord = FirstRecord();
	BOOL IsLastRecord = LastRecord();
	m_buttonPreviousUser.EnableWindow(!IsFirstRecord);
	m_buttonNextUser.EnableWindow(!IsLastRecord);
}


void CADOBlobDlg::OnOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//m_combo.SetWindowText��"");
	m_pRecordset->Close();

	try
	{
		m_pRecordset->Open("select username from userphoto", _variant_t(theApp.m_pConnection, true), adOpenKeyset, adLockPessimistic, adCmdText);//(IDispatch *)
	}
	catch (_com_error e)
	{

		AfxMessageBox(e.Description());
	}
	if (m_pRecordset->RecordCount > 0)
	{
		m_combo.ResetContent();
		while (!m_pRecordset->adoEOF)
		{

			CString str;
			str = m_pRecordset->GetFields()->GetItem("username")->Value.bstrVal;
			m_combo.AddString(str);
			m_pRecordset->MoveNext();

		}
	}
	
}


void CADOBlobDlg::OnCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


void CADOBlobDlg::OnRead()
{
// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*		CString str1;
	m_combo.GetWindowText(str1);
	if (!str1.IsEmpty())
	{
		
		_variant_t TheValue;//�洢����photo��������
		DWORD DataSize;//�����ݿ��ж�ȡ������λͼ�Ĵ�С
		char *pBuff;//���ڴ��λͼ���ڴ�ռ�
		CString str = "select photo from userphoto where username=str1";//SQL���^_^
		BSTR bstrRecordset = str.AllocSysString();//���Ҳ���ý����˰�
		HBITMAP hBitmap;
		try
		{
	//		m_pRecordset->Open(bstrRecordset, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
			m_pRecordset->MoveLast();
			TheValue = m_pRecordset->GetCollect("photo");//��ȡ�ֶ�һ
			DataSize = m_pRecordset->GetFields()->GetItem("photo")->ActualSize;//�õ�λͼ�ֶεĴ�С
			if (DataSize>0)//�ж��Ǹ�λͼ�ֶ��Ƿ�Ϊ��
			{
				if (TheValue.vt == (VT_ARRAY | VT_UI1))
				{
					if (pBuff = new char[DataSize + 1])
					{
						char *buff;
						
						SafeArrayAccessData(TheValue.parray, (void**)&buff);//��λͼ���ݷŵ�buff��ȥ
						memcpy(pBuff, buff, DataSize);//��λͼ���ݷŵ�pBuff��
						SafeArrayUnaccessData(TheValue.parray);//�ͷ�
						hBitmap = MemTOPic(pBuff);//����һ��������
					}
				}
			}
		}
		catch (_com_error e)
		{
			MessageBox("�����ݱ�ʧ��!");
			return;
		}
		
		CBitmap cBitmap;
		CClientDC *pDC = new CClientDC(this);
		BITMAP bitmap;
		CDC MemDC;
		cBitmap.Attach(hBitmap);
		MemDC.CreateCompatibleDC(pDC);
		MemDC.SelectObject(&cBitmap);
		cBitmap.GetBitmap(&bitmap);
		pDC->StretchBlt(0, 0, bitmap.bmWidth, bitmap.bmHeight, &MemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		MemDC.DeleteDC();
		::DeleteObject(&bitmap);
		
	}
	*/
}


HBITMAP CADOBlobDlg::MemTOPic(char *buff)
{

/*	HBITMAP hBitmap = NULL;
	LPSTR hDib = NULL;
	LPSTR PicBuff = NULL;
	PicBuff = buff;
	LPVOID pDibBit = NULL;
	BITMAPFILEHEADER bmpHead;//λͼͷ�ṹ
	DWORD LenBmpHead;
	LenBmpHead = sizeof(BITMAPFILEHEADER);
	strncpy((LPSTR)&bmpHead, PicBuff, LenBmpHead);
	// memcpy((LPSTR)&bmpHead,PicBuff,LenBmpHead);
	if (bmpHead.bfType != (*(WORD*)"BM"))//(*(WORD*)"BM")
	{
		MessageBox("��ѡ���ͼƬ����bmpͼƬ!");
		return NULL;
	}
	hDib = PicBuff + LenBmpHead;//hDib=PicBuff
	BITMAPINFOHEADER  &BitmapInfoHead = *(LPBITMAPINFOHEADER)hDib;
	BITMAPINFO &BitmapInfo = *(LPBITMAPINFO)hDib;
	pDibBit = PicBuff + ((BITMAPFILEHEADER*)PicBuff)->bfOffBits;
	CClientDC dc(this);
	hBitmap = CreateDIBitmap(dc.m_hDC, &BitmapInfoHead, CBM_INIT, pDibBit, &BitmapInfo, DIB_RGB_COLORS);
	*/
	return HBITMAP();
}


void CADOBlobDlg::OnClickedAge()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	CString str;
	m_combo.GetWindowText(str);

	if (!str.IsEmpty())
	{
		m_pRecordset->Close();

		try
		{
			CString str1;
			str1.Format("select old  from userphoto where username = '%s'", str);
			m_pRecordset->Open(str1.AllocSysString(), _variant_t((IDispatch *)theApp.m_pConnection, true), adOpenKeyset, adLockPessimistic, adCmdText);//(IDispatch *)
			//	m_pRecordset->Open((_bstr_t)str1, _variant_t((IDispatch *)theApp.m_pConnection, true), adOpenKeyset, adLockPessimistic, adCmdText);
		}
		catch (_com_error e)
		{

			AfxMessageBox(e.Description());
		}

		CString str2;
		_variant_t value;
		if (m_pRecordset->RecordCount > 0)
		{
			try
			{
				value = m_pRecordset->GetFields()->GetItem("old")->Value;//.bstrVal
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.Description());
			}
			str2 = (TCHAR *)(_bstr_t)value;
			m_older.SetWindowText("");
			m_older.SetWindowText(str2);
			//m_older.AddString(str1);
			m_pRecordset->MoveNext();
		}

	}
}
