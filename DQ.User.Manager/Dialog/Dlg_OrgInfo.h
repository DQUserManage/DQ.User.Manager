#pragma once


// CDlg_OrgInfo �Ի���

class CDlg_OrgInfo : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlg_OrgInfo)

public:
	CDlg_OrgInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_OrgInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ORG_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

private:
	HTREEITEM						m_hItem;					///<���ڵ� ���
	CTreeCtrl						m_tOrgTree;					///<���� ���ؼ�
	CBCGPGridCtrl					m_GridCtrl;				///<����Grid�ؼ�����
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
};
