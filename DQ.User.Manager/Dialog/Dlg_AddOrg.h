#pragma once

class CDlg_AddOrg : public CUserDialogModelBase
{
	DECLARE_DYNAMIC(CDlg_AddOrg)

public:
	CDlg_AddOrg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg_AddOrg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_ORG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	///< ������Ϣ������
	COrgInfo	m_OrgInfo;
	///< �������� 0����Ӳ�����Ϣ 1���޸Ĳ�����Ϣ
	int			m_OperateType;

public:
	virtual BOOL OnInitDialog();
	void InitLayout();
private:
	CEdit		m_OrgName;
	CEdit		m_ShortName;
	CEdit		m_Leader;
	CEdit		m_Description;
	CComboBox	m_Level;

public:
	COrgInfo GetOrgInfo() {return m_OrgInfo;}
	void SetOrgInfo(COrgInfo OrgInfo) { m_OrgInfo = OrgInfo; }
	void SetOperateType(int OperateType) { m_OperateType = OperateType; }

public:
	afx_msg void OnBnClickedOk();
};
