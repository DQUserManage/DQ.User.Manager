#include "stdafx.h"
#include "DataTableMediator.h"
#include "CSharpNameSpace.h"


CDataTableMediator::CDataTableMediator(CString sTableName)
{
	m_pDataTable = new SDataTable();
	m_pDataTable->s_DataTable = gcnew DataTable(gcnew System::String(sTableName));
}
CDataTableMediator::~CDataTableMediator(void)
{
	if (m_pDataTable)
		delete m_pDataTable;
	//ClearTempByte();
	ClearTempTable();
}

#pragma region 内部调用
/** 清空临时的Byte对象 */
// void	CDataTableMediator::ClearTempByte()
// {
// 	for (int i = 0; i < (int)m_vByteList.size(); i++)
// 	{
// 		delete[] m_vByteList[i];
// 	}
// 	m_vByteList.clear();
// }
/** 清空临时的table对象 */
void	CDataTableMediator::ClearTempTable()
{
	for (int i = 0; i < (int)m_vTableList.size(); i++)
	{
		delete m_vTableList[i];
	}
	m_vTableList.clear();
}
#pragma endregion

#pragma region 表操作
/** 设置表名 */
void	CDataTableMediator::SetTableName(CString m_TableName)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 		return;
	m_pDataTable->s_DataTable->TableName = gcnew System::String(m_TableName);
}
/** 获取表名 */
CString	CDataTableMediator::GetTableName()
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 		return L"";
	return m_pDataTable->s_DataTable->TableName->ToString();
}
/** 过滤 */
CDataTableMediator * CDataTableMediator::FilterReturnTable(CString sFilter)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return NULL;
	// 	}
	DataView ^dv = m_pDataTable->s_DataTable->DefaultView;
	dv->RowFilter = gcnew System::String(sFilter);
	CDataTableMediator *pTable = new CDataTableMediator();
	pTable->m_pDataTable->s_DataTable = dv->ToTable();
	m_vTableList.push_back(pTable);
	return pTable;
}
/** 获取列名称 */
CString	CDataTableMediator::GetsFieldName(int iIndex)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return L"";
	// 	}
	if (iIndex < 0 || iIndex >= m_pDataTable->s_DataTable->Columns->Count)
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return L"";
	}
	return m_pDataTable->s_DataTable->Columns[iIndex]->ColumnName->ToString();
}
/** 获取列数据烈性 */
CString	CDataTableMediator::GetColDataType(int iIndex)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return L"";
	// 	}
	if (iIndex < 0 || iIndex >= m_pDataTable->s_DataTable->Columns->Count)
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return L"";
	}
	return m_pDataTable->s_DataTable->Columns[iIndex]->DataType->ToString();
}
/** 获取列个数 */
int		CDataTableMediator::GetColCount()
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return 0;
	// 	}
	return m_pDataTable->s_DataTable->Columns->Count;
}
/** 获取行个数 */
int		CDataTableMediator::GetRowCount()
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return 0;
	// 	}
	return m_pDataTable->s_DataTable->Rows->Count;
}
/** 添加行 */
int		CDataTableMediator::AddRow()
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return -1;
	// 	}
	DataRow^ r = m_pDataTable->s_DataTable->NewRow();
	m_pDataTable->s_DataTable->Rows->Add(r);
	return m_pDataTable->s_DataTable->Rows->Count - 1;
}
/** 添加列 */
int		CDataTableMediator::AddCol(CString sColName)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return -1;
	// 	}
	DataColumn ^col = gcnew DataColumn(gcnew System::String(sColName));
	m_pDataTable->s_DataTable->Columns->Add(col);
	return m_pDataTable->s_DataTable->Columns->Count - 1;
}
#pragma endregion

#pragma region 设置、获取值
/** 设置数值 */
void	CDataTableMediator::SetFieldValue(int iRowIndex, int iColIndex, COleVariant val)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return;
	}
	if (iColIndex < 0 || iColIndex >= m_pDataTable->s_DataTable->Columns->Count)
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return;
	}
	Object ^objVal = CDbToolKit::ValToObject(val);
	m_pDataTable->s_DataTable->Rows[iRowIndex][iColIndex] = objVal;
}
/** 设置数值 */
void	CDataTableMediator::SetFieldValue(int iRowIndex, CString sFieldName, COleVariant val)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return;
	}
	if (sFieldName.IsEmpty() || !(m_pDataTable->s_DataTable->Columns->Contains(gcnew System::String(sFieldName))))
	{
		MessageBox(NULL, L"列字段错误", L"错误", MB_ICONERROR);
		return;
	}
	Object ^objVal = CDbToolKit::ValToObject(val);
	m_pDataTable->s_DataTable->Rows[iRowIndex][gcnew System::String(sFieldName)] = objVal;
}

/** 获取字符型数值 */
CString		CDataTableMediator::GetStringField(int iRowIndex, CString sFieldName)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return L"";
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return L"";
	}
	if (sFieldName.IsEmpty() || !(m_pDataTable->s_DataTable->Columns->Contains(gcnew System::String(sFieldName))))
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return L"";
	}
	return m_pDataTable->s_DataTable->Rows[iRowIndex][gcnew System::String(sFieldName)]->ToString();
}
/** 获取整型数值 */
int			CDataTableMediator::GetIntField(int iRowIndex, CString sFieldName)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return -1;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return -1;
	}
	if (sFieldName.IsEmpty() || !(m_pDataTable->s_DataTable->Columns->Contains(gcnew System::String(sFieldName))))
	{
		MessageBox(NULL, L"列字段错误", L"错误", MB_ICONERROR);
		return -1;
	}
	return _ttoi(CString(m_pDataTable->s_DataTable->Rows[iRowIndex][gcnew System::String(sFieldName)]->ToString()));
}
/** 获取浮点数值 */
float		CDataTableMediator::GetFloatField(int iRowIndex, CString sFieldName)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return 0.f;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return 0.f;
	}
	if (sFieldName.IsEmpty() || !(m_pDataTable->s_DataTable->Columns->Contains(gcnew System::String(sFieldName))))
	{
		MessageBox(NULL, L"列字段错误", L"错误", MB_ICONERROR);
		return 0.f;
	}
	return (float)_ttof(CString(m_pDataTable->s_DataTable->Rows[iRowIndex][gcnew System::String(sFieldName)]->ToString()));
}
/** 获取日期数值 */
COleDateTime CDataTableMediator::GetDateField(int iRowIndex, CString sFieldName)
{
	COleDateTime datevalue;
	datevalue.SetDate(0,0,0);
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return datevalue;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return datevalue;
	}
	if (sFieldName.IsEmpty() || !(m_pDataTable->s_DataTable->Columns->Contains(gcnew System::String(sFieldName))))
	{
		MessageBox(NULL, L"列字段错误", L"错误", MB_ICONERROR);
		return datevalue;
	}
	CString value(m_pDataTable->s_DataTable->Rows[iRowIndex][gcnew System::String(sFieldName)]->ToString());
	if(value == L"")
		return datevalue;

	datevalue.ParseDateTime(value);
	return datevalue;
}	
/** 获取BLOB数值 */
byte*		CDataTableMediator::GetBlobField(int iRowIndex, CString sFieldName,int &size)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return NULL;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return NULL;
	}
	if (sFieldName.IsEmpty() || !(m_pDataTable->s_DataTable->Columns->Contains(gcnew System::String(sFieldName))))
	{
		MessageBox(NULL, L"列字段错误", L"错误", MB_ICONERROR);
		return NULL;
	}

	cli::array< byte >^ byteArray= (cli::array< byte >^)(m_pDataTable->s_DataTable->Rows[iRowIndex][gcnew System::String(sFieldName)]);
	size = byteArray->GetLength(0);
	byte *pBuf = new byte[size];


	Marshal::Copy(byteArray,0,(System::IntPtr)(pBuf),size);
	return pBuf;
}

CString CDataTableMediator::GetBlobField(int iRowIndex, CString sFieldName)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return NULL;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return L"";
	}
	if (sFieldName.IsEmpty() || !(m_pDataTable->s_DataTable->Columns->Contains(gcnew System::String(sFieldName))))
	{
		MessageBox(NULL, L"列字段错误", L"错误", MB_ICONERROR);
		return L"";
	}

	cli::array< byte >^ byteArray= (cli::array< byte >^)(m_pDataTable->s_DataTable->Rows[iRowIndex][gcnew System::String(sFieldName)]);

	System::Text::Encoding  ^ textEncoding =  System::Text::Encoding::Default;
	System::String^ strResult = textEncoding->GetString(byteArray);
	delete textEncoding;
	return strResult;
}

/** 获取字符型数值 */
CString		CDataTableMediator::GetStringField(int iRowIndex, int iColIndex)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return L"";
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return L"";
	}
	if (iColIndex < 0 || iColIndex >= m_pDataTable->s_DataTable->Columns->Count)
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return L"";
	}
	return m_pDataTable->s_DataTable->Rows[iRowIndex][iColIndex]->ToString();
}
/** 获取整型数值 */
int			CDataTableMediator::GetIntField(int iRowIndex, int iColIndex)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return -1;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return -1;
	}
	if (iColIndex < 0 || iColIndex >= m_pDataTable->s_DataTable->Columns->Count)
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return -1;
	}
	return _ttoi(CString(m_pDataTable->s_DataTable->Rows[iRowIndex][iColIndex]->ToString()));
}
/** 获取浮点数值 */
float		CDataTableMediator::GetFloatField(int iRowIndex, int iColIndex)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return 0.f;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return 0.f;
	}
	if (iColIndex < 0 || iColIndex >= m_pDataTable->s_DataTable->Columns->Count)
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return 0.f;
	}
	return (float)_ttof(CString(m_pDataTable->s_DataTable->Rows[iRowIndex][iColIndex]->ToString()));
}
/** 获取日期数值 */
COleDateTime CDataTableMediator::GetDateField(int iRowIndex, int iColIndex)
{
	COleDateTime datevalue;
	datevalue.SetDate(0,0,0);
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return datevalue;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return datevalue;
	}
	if (iColIndex < 0 || iColIndex >= m_pDataTable->s_DataTable->Columns->Count)
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return datevalue;
	}
	CString value(m_pDataTable->s_DataTable->Rows[iRowIndex][iColIndex]->ToString());
	if(value == L"")
		return datevalue;

	datevalue.ParseDateTime(value);
	return datevalue;
}	
/** 获取BLOB数值 */
byte*		CDataTableMediator::GetBlobField(int iRowIndex, int iColIndex,int &size)
{
	// 	if (m_pDataTable->s_DataTable == nullptr)
	// 	{
	// 		  MessageBox(NULL, L"DataTable为空", L"错误", MB_ICONERROR);
	// 		return NULL;
	// 	}
	if (iRowIndex < 0 || iRowIndex >= m_pDataTable->s_DataTable->Rows->Count)
	{
		MessageBox(NULL, L"行索引错误", L"错误", MB_ICONERROR);
		return NULL;
	}
	if (iColIndex < 0 || iColIndex >= m_pDataTable->s_DataTable->Columns->Count)
	{
		MessageBox(NULL, L"列索引错误", L"错误", MB_ICONERROR);
		return NULL;
	}

	cli::array< byte >^ byteArray= (cli::array< byte >^)(m_pDataTable->s_DataTable->Rows[iRowIndex][iColIndex]);
	size = byteArray->GetLength(0);
	byte *pBuf = new byte[size];
	Marshal::Copy(byteArray,0,(System::IntPtr)(pBuf),size);
	return pBuf;
}
#pragma endregion
