#pragma once

class CDlgSysRes : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgSysRes)

public:
	CDlgSysRes(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSysRes();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYS_RES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnEdit();
	afx_msg void OnBnClickedBtnDel();
	afx_msg void OnBnClickedBtnDelall();
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	/**��ʼ�����沼�� */
	void InitLayout();
	/** ��ʼ����Դ���ؼ� */
	BOOL InitControl();
	/** ��ʼ��ϵͳ��Դ */
	BOOL InitSysRes();
public:
	CBCGPGridCtrl  m_wndRes; ///<ϵͳ��Դ�б�
};
