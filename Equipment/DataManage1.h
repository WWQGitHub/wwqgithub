// DataManage1.h: interface for the CDataManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAMANAGE1_H__DEAF610B_455E_4555_B534_B856E70F2E46__INCLUDED_)
#define AFX_DATAMANAGE1_H__DEAF610B_455E_4555_B534_B856E70F2E46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataManage  
{
public:
	CDataManage();
	virtual ~CDataManage();
public:
	_RecordsetPtr Record1;
protected:
	_ConnectionPtr DataConn;
	_RecordsetPtr DataRecord;
	
public:
	_ConnectionPtr GetConn();//获取adoConnection对象
	_RecordsetPtr GetRecordset();//获取adoRecordset对象
	bool ConnectDatabase(CString constr); //连接数据库
	bool ExecSQL(CString sql);
};

#endif // !defined(AFX_DATAMANAGE1_H__DEAF610B_455E_4555_B534_B856E70F2E46__INCLUDED_)
