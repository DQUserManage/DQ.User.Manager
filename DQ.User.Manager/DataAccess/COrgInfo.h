#pragma once


/********************************************************************
* Copyright (C), 博雅仟恒软件技术（北京）有限公司
*
* 创 建 者： 陈昌健
* 创建日期： 2018-7-3
* 功能描述： 部门信息操作类
*
********************************************************************/
class EXPORT_USER_MANAGER COrgInfo
{
public:
	COrgInfo();
	~COrgInfo();

private:
	///< 部门ID
	CString m_OrgID;

	///<父节点ID
	CString m_ParentID;

	///< 部门名称 
	CString m_OrgName;

	///< 简称 
	CString m_ShortName;

	///< 级别 
	CString m_Level;

	///< 领导
	CString m_Leader;

	///< 描述
	CString m_Description;

public:
	/** 设置部门名称 */
	void SetOrgID(CString OrgID) { m_OrgID = OrgID; }
	/** 获取部门名称 */
	CString GetOrgID() { return m_OrgID; }

	/** 设置部门名称 */
	void SetParentID(CString ParentID) { m_ParentID = ParentID; }
	/** 获取部门名称 */
	CString GetParentID() { return m_ParentID; }

	/** 设置部门名称 */
	void SetOrgName(CString OrgName) { m_OrgName = OrgName; }
	/** 获取部门名称 */
	CString GetOrgName() { return m_OrgName; }

	/** 设置部门名称 */
	void SetShortName(CString ShortName) { m_ShortName = ShortName; }
	/** 获取部门名称 */
	CString GetShortName() { return m_ShortName; }

	/** 设置部门名称 */
	void SetLevel(CString Level) { m_Level = Level; }
	/** 获取部门名称 */
	CString GetLevel() { return m_Level; }

	/** 设置部门名称 */
	void SetLeader(CString Leader) { m_Leader = Leader; }
	/** 获取部门名称 */
	CString GetLeader() { return m_Leader; }

	/** 设置部门名称 */
	void SetDescription(CString Description) { m_Description = Description; }
	/** 获取部门名称 */
	CString GetDescription() { return m_Description; }
	
};
