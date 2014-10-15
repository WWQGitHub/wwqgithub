// DataManage1.cpp: implementation of the CDataManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Equipment.h"
#include "DataManage1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataManage::CDataManage()
{
	DataConn.CreateInstance(_uuidof(Connection));
	DataRecord.CreateInstance(_uuidof(Recordset));
	Record1.CreateInstance(_uuidof(Recordset));
}

CDataManage::~CDataManage()
{
	DataConn->Release();
	DataRecord->Release();
	Record1->Release();
}

_ConnectionPtr CDataManage::GetConn()
{
	return DataConn; 
}

_RecordsetPtr CDataManage::GetRecordset()
{
	return (DataRecord);
}

bool CDataManage::ConnectDatabase(CString constr)
{
	DataConn->ConnectionString = (_bstr_t)constr;
	try
	{
		DataConn->Open("","","",-1);
	}
	catch(...)
	{
		return false;	
	}
	return true;

}

bool CDataManage::ExecSQL(CString sql)
{
	_bstr_t sqltext =sql;
	try
	{
		DataConn->Execute(sqltext,NULL,adCmdText);	
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.ErrorMessage(),0,0);
		return false;	
	}
	return true;
}
