#pragma once


/********************************************************************
* Copyright (C), ����Ǫ��������������������޹�˾
*
* �� �� �ߣ� �²���
* �������ڣ� 2018-7-3
* ���������� ������Ϣ������
*
********************************************************************/
class EXPORT_USER_MANAGER COrgInfo
{
public:
	COrgInfo();
	~COrgInfo();

private:
	///< ����ID
	CString m_OrgID;

	///<���ڵ�ID
	CString m_ParentID;

	///< �������� 
	CString m_OrgName;

	///< ��� 
	CString m_ShortName;

	///< ���� 
	CString m_Level;

	///< �쵼
	CString m_Leader;

	///< ����
	CString m_Description;

public:
	/** ���ò������� */
	void SetOrgID(CString OrgID) { m_OrgID = OrgID; }
	/** ��ȡ�������� */
	CString GetOrgID() { return m_OrgID; }

	/** ���ò������� */
	void SetParentID(CString ParentID) { m_ParentID = ParentID; }
	/** ��ȡ�������� */
	CString GetParentID() { return m_ParentID; }

	/** ���ò������� */
	void SetOrgName(CString OrgName) { m_OrgName = OrgName; }
	/** ��ȡ�������� */
	CString GetOrgName() { return m_OrgName; }

	/** ���ò������� */
	void SetShortName(CString ShortName) { m_ShortName = ShortName; }
	/** ��ȡ�������� */
	CString GetShortName() { return m_ShortName; }

	/** ���ò������� */
	void SetLevel(CString Level) { m_Level = Level; }
	/** ��ȡ�������� */
	CString GetLevel() { return m_Level; }

	/** ���ò������� */
	void SetLeader(CString Leader) { m_Leader = Leader; }
	/** ��ȡ�������� */
	CString GetLeader() { return m_Leader; }

	/** ���ò������� */
	void SetDescription(CString Description) { m_Description = Description; }
	/** ��ȡ�������� */
	CString GetDescription() { return m_Description; }
	
};
