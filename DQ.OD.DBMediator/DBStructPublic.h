#pragma  once

using namespace std;

/** ������Ϣ */
struct ParameterInfo
{
	CString		s_sName;		///<��������
	COleVariant s_sValue;		///<����ֵ
	byte *		s_pByteValue;	///<byte*ָ��
	int			s_iByteSize;	///<byte*ָ���С
	ParameterInfo()
	{
		s_sValue = COleVariant();
		s_sName = L"";
		s_pByteValue = NULL;
		s_iByteSize = 0;
	}
};

/** ���ݿ����� */
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

/** Cell�������� */
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