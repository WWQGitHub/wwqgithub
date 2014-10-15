// DataManage.h: interface for the CDataManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAMANAGE_H__EBD6AE58_C9B5_426C_ACF2_75A651ADFCAF__INCLUDED_)
#define AFX_DATAMANAGE_H__EBD6AE58_C9B5_426C_ACF2_75A651ADFCAF__INCLUDED_
#include "StdAfx.h"
#include "EquipmentDlg.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDataManage  
{
public:
	CDataManage();
	 _ConnectionPtr GegConn();
	// _RecordsetPtr GetRecord();
	virtual ~CDataManage();
protected:
	_ConnectionPtr DataConn;
	_RecordsetPtr DataRecord;

};

#endif // !defined(AFX_DATAMANAGE_H__EBD6AE58_C9B5_426C_ACF2_75A651ADFCAF__INCLUDED_)
