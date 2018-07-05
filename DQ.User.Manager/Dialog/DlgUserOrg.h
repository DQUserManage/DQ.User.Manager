#pragma once

#include "../Layout/UserDialogBase.h"
#include "COrgInfo.h"
#include "CUserInfo.h"
#include <map>

class CDlgUserOrg : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgUserOrg)

public:
	CDlgUserOrg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgUserOrg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_USER_ORG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl						m_tOrgTree;					///<���� ���ؼ�
	CBCGPGridCtrl*					m_pGridCtrl;				///<����Grid�ؼ�����
	vector<COrgInfo>				m_VecOrgInfo;				///<������Ϣ�б�
	//map<CString, vector<CUserInfo>> m_MapUserInfo;				///<�û���Ϣ�б�  ���������ƣ��û���Ϣ��
public:
	afx_msg void OnTvnSelchangedTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult);
	/** ����������ؼ� */
	void FillBranchTree(CDataTableMediator *pTable, CString sParentID, HTREEITEM hRoot);
	/** �������ؼ����ŵ�ѡ�������ʾ������Ա */
	void ShowBranchUser();
	/** ���������ؼ� */
	afx_msg void OnNMClickTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult);
	/** �Ҽ�������ؼ������˵� */
	afx_msg void OnNMRClickTreeUserOrg(NMHDR *pNMHDR, LRESULT *pResult);
	/** �Ҽ��˵� ��Ӳ��� */
	afx_msg void OnAddOrg();
	/** �Ҽ��˵� ɾ������ */
	afx_msg void OnDelOrg();
	/** �Ҽ��˵� ���²��� */
	afx_msg void OnUpdateOrgName();
	/** ����û���Ϣ */
	afx_msg void OnBnClickedBtnAddUser();
	/** ɾ���û���Ϣ */
	afx_msg void OnBnClickedBtnDelUser();
	/** �޸��û���Ϣ */
	afx_msg void OnBnClickedBtnUpdateUser();
	/** ɾ��ȫ���û���Ϣ */
	afx_msg void OnBnClickedBtnAllDelete();
};
