#pragma once

class CDlgSysResEdit : public CUserDialogModelBase
{
	DECLARE_DYNAMIC(CDlgSysResEdit)

public:
	CDlgSysResEdit(CSysRes& res, bool bEdit = false,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSysResEdit();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RES_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

public:
	void InitControl();
public:
	CBCGPEdit m_edtUpload;
	CBCGPDateTimeCtrl m_btnDate;
	CDeptBrowserEdit m_edtOrg;

private:
	CSysRes& m_SysRes;   ///<系统资源结构体
	bool m_bEdit; ///<是否是编辑状态
};
