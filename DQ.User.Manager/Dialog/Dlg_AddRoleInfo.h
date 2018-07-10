#pragma once

#include "../DataAccess/CRoleInfo.h"

// CDlg_AddRoleInfo �Ի���

class CDlg_AddRoleInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_AddRoleInfo)

public:
	CDlg_AddRoleInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_AddRoleInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_ROLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CEdit			m_eRoleName;
	CEdit			m_eDescription;
	CString			m_RoleName;
	CString			m_Description;
	CBCGPTreeCtrl	m_wndMod;
	vector<CString>	m_pCurRola;
	int				m_OperateType;
	CString			m_RoleID;
public:
	void SetOperateType(int OperateType) { m_OperateType = OperateType; }
	CString GetRoleName() { return m_RoleName; }
	CString GetRoleDescription() { return m_Description; }
	/** ���õ�ǰѡ�н�ɫ */
	void		SetRola(vector<CString> pRola) { m_pCurRola = pRola; }
	/** ��ȡ��ǰѡ��Ȩ�� */
	vector<CString>		GetRolePower() { return m_pCurRola; }
	void FillModeTree(HTREEITEM hParent, const CString& csParent);
	void GetSelChildNode(vector<CString>* pRola, HTREEITEM pRoot);
	/** ���ø��ڵ�ѡ�� */
	void	SetParentCheck(HTREEITEM hTree, BOOL bCheck);
	/** �����ӽڵ�ѡ�� */
	void	SetChildCheck(HTREEITEM hTree, BOOL bCheck);
	/** �������ڵ�ѡ�� */
	void	SetTreeNodeSel(CDataTableMediator *pTable, CString sParentID, HTREEITEM hRoot);
	/** ���ý�ɫID */
	void	SerRoleID(CString RoleID) { m_RoleID = RoleID; }
	CString GetRoleID() { return m_RoleID; }
public:
	virtual BOOL OnInitDialog();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMClickTreeRolePower(NMHDR *pNMHDR, LRESULT *pResult);
};
