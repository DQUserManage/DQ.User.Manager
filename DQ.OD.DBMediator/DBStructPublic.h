#pragma  once

using namespace std;

/** 参数信息 */
struct ParameterInfo
{
	CString		s_sName;		///<参数名称
	COleVariant s_sValue;		///<参数值
	byte *		s_pByteValue;	///<byte*指针
	int			s_iByteSize;	///<byte*指针大小
	ParameterInfo()
	{
		s_sValue = COleVariant();
		s_sName = L"";
		s_pByteValue = NULL;
		s_iByteSize = 0;
	}
};

/** 数据库类型 */
enum DBConnectType
{
	DB_SqlServer,
	DB_MySql,
	DB_SQLite,
	DB_Oracle,
	DB_ODBC,
	DB_OleDb,
	DB_Firebird,
	DB_PostgreSql,
	DB_DB2,
	DB_Informix,
	DB_SqlServerCe
};

/** Cell数据类型 */
enum CellDataType
{
	DATA_BLANK,
	DATA_BOOLEAD,
	DATA_ERROR,
	DATA_FORMULA,
	DATA_NUMERIC,
	DATA_STRING,
	DATA_UNKNOWN
};