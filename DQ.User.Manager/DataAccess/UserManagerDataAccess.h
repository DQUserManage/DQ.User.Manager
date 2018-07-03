#pragma once

//////////////////////////////////////////////////////////////////////////////////                                                                            ///  @file     UserManagerDataAccess.h                                                       ///  @brief    �û�����ģ�����ݷ��ʽӿڣ����ж����ݵķ��ʶ�Ӧд�ڴ��ļ��У�                                                                             ///  @author   lqt                                                                                                        ///  @version  1.0.0                                                ///  @date     2018.06.28                                                                                ///                                                                          ///////////////////////////////////////////////////////////////////////////////

class CDbUtilityMediator;

/**   ���ݷ��ʽӿڣ�����ģʽ��*/class EXPORT_USER_MANAGER CUserManagerDataService
{
public:
	~CUserManagerDataService(void);
public:
	static CUserManagerDataService*		GetInstance(void);
	static void					        DestoryInstance(void);
private:
	CUserManagerDataService();
	CUserManagerDataService(const CUserManagerDataService& rhs) { operator=(rhs); }
	CUserManagerDataService& operator=(const CUserManagerDataService&) { return *this; }
private:
	static CUserManagerDataService*		m_pSingleton;  ///<���ݷ���ʵ��

public:
	/** ��ʼ�����ݷ��ʽӿ�
	@param csConn ���ݿ����Ӵ�
	@param nType  ���ݿ�����
	*/
	bool DBInit(const CString& csConn, int nType);

	/**  �ͷ����ݿ�����н��� */
	void FreeDB();

public:
	/** ���ݷ��ʼ򵥲���*/
	bool DoTest();

private:
	CDbUtilityMediator*  m_pDB;  ///<���ݷ����н���
};