#pragma once

class CDlgSysResEdit : public CUserDialogModelBase
{
	DECLARE_DYNAMIC(CDlgSysResEdit)

public:
	CDlgSysResEdit(CSysRes& res, bool bEdit = false,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSysResEdit();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RES_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
	CSysRes& m_SysRes;   ///<ϵͳ��Դ�ṹ��
	bool m_bEdit; ///<�Ƿ��Ǳ༭״̬
};
