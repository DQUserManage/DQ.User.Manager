#pragma once
#using "System.dll" 
#using "System.Data.dll"


//区分平台与编译环境

#if _DEBUG
#if _WIN64
#using "..\Debug\x64\DQ.OD.DBProvider.dll"
#else
#using "..\Debug\x86\DQ.OD.DBProvider.dll"
#endif
#else
#if _WIN64
#using "..\Release\x64\DQ.OD.DBProvider.dll"
#else
#using "..\Release\x86\DQ.OD.DBProvider.dll"
#endif
#endif

using namespace System;
using namespace DQ::OD::DBProvider;
using namespace System::Data;
using namespace System::Data::Common;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Xml;
using namespace System::Xml::Serialization;
using namespace System::Diagnostics::Contracts;

#include "DBStructPublic.h"

/** 表 */
class SDataTable 
{
public:
	SDataTable(){}
	~SDataTable(){}

public:
	gcroot<DataTable ^> s_DataTable;
};

/** 结果集 */
class SDataReader
{
public:
	SDataReader(){}
	~SDataReader(){}
public:
	gcroot<DbDataReader^> s_DataReader;
};

/** 数据库连接 */
class SDbUtility
{
public:
	gcroot<DbUtility^> s_DbUtility;
	CString			s_sConnectString;
	DQ::OD::DBProvider::DbProviderType	m_eType;	///<
	SDbUtility(CString sConnect, DBConnectType eType)
	{
		m_eType = (DQ::OD::DBProvider::DbProviderType)eType;
		s_sConnectString = sConnect;
		s_DbUtility = gcnew DbUtility(gcnew System::String(sConnect), m_eType);
	}
};

class CDbToolKit
{
public:
	CDbToolKit(){}
	~CDbToolKit(){}

public:
	/** 数值转Object */
	static gcroot<Object^> ValToObject(COleVariant Value)
	{
		Object^ obj = "";
		switch(Value.vt){
		case VT_BSTR://COleVariant是一个字串
			obj= gcnew System::String(V_BSTRT(&Value));
			break;
		case VT_I2://是短整型
			obj=V_I2(&Value);
			break;
		case VT_I4: //是长整型 
			obj=V_I4(&Value);
			break;
		case VT_R4://是浮点数
			obj=V_R4(&Value);
			break;			
		case VT_R8://是浮点数
			obj=V_R8(&Value);
			break;			
		case VT_CY://是货币值
			obj=gcnew System::String(COleCurrency(Value).Format());
			break;
		case VT_DATE: //是日期
			obj = System::DateTime::Parse(gcnew System::String(COleDateTime(Value).Format(L"%Y-%m-%d %H:%M:%S")));
			break;			
		case VT_BOOL://是布尔值
			obj = V_BOOL(&Value) ? "True" : "False";
			break;
		case VT_ARRAY|VT_UI1://是数组
			{
			     ///< modified by lqt 2018.07.0.5

				//BYTE ** ppBuf=NULL;
				unsigned long pcBufLen= Value.parray->rgsabound[0].cElements;
				cli::array< byte >^ byteArray = gcnew cli::array< byte >(pcBufLen);
				pin_ptr<byte> p = &byteArray[0];//非托管内存 
				//if(*ppBuf != NULL)
				{
					void * pArrayData;
					SafeArrayAccessData(Value.parray,&pArrayData);//Obtain safe pointer to the array			
					memcpy(p, pArrayData,pcBufLen * sizeof(byte)); 
					SafeArrayUnaccessData(Value.parray);//Unlock the variant data
					obj=byteArray;
				}			
				break;
			}
		default:
			obj=nullptr;
		}

		return(obj);
	}
};

//  gcroot<Object^> CDbToolKit::ValToObject(COleVariant Value)
//  {
// 	 Object^ obj = "";
// 	 switch(Value.vt){
// 	 case VT_BSTR://COleVariant是一个字串
// 		 obj= gcnew System::String(V_BSTRT(&Value));
// 		 break;
// 	 case VT_I2://是短整型
// 		 obj=V_I2(&Value);
// 		 break;
// 	 case VT_I4: //是长整型 
// 		 obj=V_I4(&Value);
// 		 break;
// 	 case VT_R4://是浮点数
// 		 obj=V_R4(&Value);
// 		 break;			
// 	 case VT_R8://是浮点数
// 		 obj=V_R8(&Value);
// 		 break;			
// 	 case VT_CY://是货币值
// 		 obj=gcnew System::String(COleCurrency(Value).Format());
// 		 break;
// 	 case VT_DATE: //是日期
// 		 obj=gcnew System::String(COleDateTime(Value).Format(L"%Y-%m-%d %H:%M:%S"));
// 		 break;			
// 	 case VT_BOOL://是布尔值
// 		 obj = V_BOOL(&Value) ? "True" : "False";
// 		 break;
// 	 case VT_ARRAY|VT_UI1://是数组
// 		 {
// 			 BYTE ** ppBuf=NULL;
// 			 unsigned long * pcBufLen=0;
// 			 *pcBufLen = Value.parray->rgsabound[0].cElements;
// 			 array< byte >^ byteArray = gcnew array< byte >(*pcBufLen);
// 			 pin_ptr<byte> p = &byteArray[0];//非托管内存 
// 			 if(*ppBuf != NULL)
// 			 {
// 				 void * pArrayData;
// 				 SafeArrayAccessData(Value.parray,&pArrayData);//Obtain safe pointer to the array			
// 				 memcpy(p, pArrayData,*pcBufLen * sizeof(byte)); 
// 				 SafeArrayUnaccessData(Value.parray);//Unlock the variant data
// 				 obj=byteArray;
// 			 }			
// 			 break;
// 		 }
// 	 default:
// 		 obj=nullptr;
// 	 }
// 
// 	 return(obj);
//  }