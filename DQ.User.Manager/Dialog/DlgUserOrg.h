#pragma once

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
	
	
};
