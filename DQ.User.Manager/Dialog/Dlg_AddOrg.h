#pragma once

class CDlg_AddOrg : public CUserDialogModelBase
{
	DECLARE_DYNAMIC(CDlg_AddOrg)

public:
	CDlg_AddOrg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg_AddOrg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_ADD_ORG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	///< 部门信息操作类
	COrgInfo	m_OrgInfo;
	///< 操作类型 0：添加部门信息 1：修改部门信息
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
