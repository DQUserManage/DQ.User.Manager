
// DQ.User.TestDlg.h : ͷ�ļ�
//

#pragma once


// CDQUserTestDlg �Ի���
class CDQUserTestDlg : public CBCGPDialog
{
// ����
public:
	CDQUserTestDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CDQUserTestDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DQUSERTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnUser();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRes();
};
