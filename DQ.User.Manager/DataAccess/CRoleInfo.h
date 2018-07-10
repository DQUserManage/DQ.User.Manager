#pragma once

/********************************************************************
* Copyright (C), 博雅仟恒软件技术（北京）有限公司
*
* 创 建 者： 陈昌健
* 创建日期： 2018-7-9
* 功能描述： 角色信息操作类
*
********************************************************************/
class EXPORT_USER_MANAGER CRoleInfo
{
public:
	CRoleInfo();
	~CRoleInfo();

private:
	CString			m_sRoleID;			///<角色ID
	CString			m_sRoleName;		///<角色名称
	CString			m_sRemark;			///<备注

public:
	void SetRoleID(CString RoleID) { m_sRoleID = RoleID; }
	CString  GetRoleID() { return m_sRoleID; }

	void SetRoleName(CString RoleName) { m_sRoleName = RoleName; }
	CString  GetRoleName() { return m_sRoleName; }

	void SetRemark(CString Remark) { m_sRemark = Remark; }
	CString  GetRemark() { return m_sRemark; }
};