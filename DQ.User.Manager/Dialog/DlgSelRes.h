#pragma once

class CDlgSelRes : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgSelRes)

public:
	CDlgSelRes(const CString& csResID,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSelRes();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEL_RES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	LRESULT OnDblClk(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	void InitLayout();
	void InitControl();
	void InitData();

public:
	CString m_csResID;  ///<ѡ�����ԴID
	CString m_csResName;   ///<ѡ�����Դ����

private:
	CBCGPGridCtrl  m_wndRes; ///<ϵͳ��Դ�б�
	CBCGPGridRow*  m_pSelRow;  ///<Ҫѡ�����
public:
	afx_msg void OnBnClickedOk();
};
