#pragma once

#include "../Layout/UserDialogBase.h"
#include "COrgInfo.h"
#include "CUserInfo.h"
#include <map>

class CDlgUserOrg : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgUserOrg)

public:
	CDlgUserOrg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgUserOrg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USER_ORG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl						m_tOrgTree;					///<部门 树控件
	CBCGPGridCtrl*					m_pGridCtrl;				///<定义Grid控件变量
	vector<COrgInfo>				m_VecOrgInfo;				///<部门信息列表
	//map<CString, vector<CUserInfo>> m_MapUserInfo;				///<用户信息列表  《部门名称，用户信息》
public:
	afx_msg void OnTvnSelchangedTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult);
	/** 部门填充树控件 */
	void FillBranchTree(CDataTableMediator *pTable, CString sParentID, HTREEITEM hRoot);
	/** 根据树控件部门的选择情况显示部门人员 */
	void ShowBranchUser();
	/** 左键点击树控件 */
	afx_msg void OnNMClickTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult);
	/** 右键点击树控件弹出菜单 */
	afx_msg void OnNMRClickTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult);
	/** 右键菜单 添加部门 */
	afx_msg void OnAddOrg();
	/** 右键菜单 删除部门 */
	afx_msg void OnDelOrg();
	/** 右键菜单 更新部门 */
	afx_msg void OnUpdateOrgName();
	/** 添加用户信息 */
	afx_msg void OnBnClickedBtnAddUser();
	/** 删除用户信息 */
	afx_msg void OnBnClickedBtnDelUser();
	/** 修改用户信息 */
	afx_msg void OnBnClickedBtnUpdateUser();
	/** 删除全部用户信息 */
	afx_msg void OnBnClickedBtnAllDelete();
};
