// DataManage.cpp: implementation of the CDataManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Equipment.h"
#include "DataManage.h"

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


}

 CDataManage::~CDataManage()
{

}
_ConnectionPtr CDataManage::GegConn()
{
	return DataConn; 
}

_RecordsetPtr CDataManage::DataRecord()
{
	return DataRecord; 

}
