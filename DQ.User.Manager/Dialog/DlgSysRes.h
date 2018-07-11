#pragma once

class CDlgSysRes : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgSysRes)

public:
	CDlgSysRes(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSysRes();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYS_RES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
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
	/**初始化界面布局 */
	void InitLayout();
	/** 初始化资源表格控件 */
	BOOL InitControl();
	/** 初始化系统资源 */
	BOOL InitSysRes();
	/** 编辑系统资源*/
	void EditSysRes(CBCGPGridRow* pRow);
	/** 删除系统资源*/
	void DelSysRes(CBCGPGridRow* pRow);
public:
	CBCGPGridCtrl  m_wndRes; ///<系统资源列表
};
