#pragma once

/********************************************************************
* Copyright (C), ����Ǫ��������������������޹�˾
*
* �� �� �ߣ� �²���
* �������ڣ� 2018-7-9
* ���������� ��ɫ��Ϣ������
*
********************************************************************/
class EXPORT_USER_MANAGER CRoleInfo
{
public:
	CRoleInfo();
	~CRoleInfo();

private:
	CString			m_sRoleID;			///<��ɫID
	CString			m_sRoleName;		///<��ɫ����
	CString			m_sRemark;			///<��ע

public:
	void SetRoleID(CString RoleID) { m_sRoleID = RoleID; }
	CString  GetRoleID() { return m_sRoleID; }

	void SetRoleName(CString RoleName) { m_sRoleName = RoleName; }
	CString  GetRoleName() { return m_sRoleName; }

	void SetRemark(CString Remark) { m_sRemark = Remark; }
	CString  GetRemark() { return m_sRemark; }
};