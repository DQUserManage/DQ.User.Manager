
// DQ.User.TestDlg.h : 头文件
//

#pragma once


// CDQUserTestDlg 对话框
class CDQUserTestDlg : public CBCGPDialog
{
// 构造
public:
	CDQUserTestDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CDQUserTestDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DQUSERTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedBtnUser();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnRes();
};
