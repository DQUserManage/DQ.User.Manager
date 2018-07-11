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
	afx_msg void OnBnClickedBtnAll();
	afx_msg void OnBnClickedBtnRevert();
	virtual BOOL OnInitDialog();
	LRESULT afx_msg OnDblClk(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	/**��ʼ�����沼�� */
	void InitLayout();
	/** ��ʼ����Դ���ؼ� */
	BOOL InitControl();
	/** ��ʼ��ϵͳ��Դ */
	BOOL InitSysRes();
	/** �༭ϵͳ��Դ*/
	void EditSysRes(CBCGPGridRow* pRow);
	/** ɾ��ϵͳ��Դ*/
	void DelSysRes(CBCGPGridRow* pRow);
public:
	CBCGPGridCtrl  m_wndRes; ///<ϵͳ��Դ�б�
};
