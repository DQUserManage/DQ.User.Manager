#pragma once


class CDlgSysMod : public CUserDialogBase
{
	DECLARE_DYNAMIC(CDlgSysMod)

public:
	CDlgSysMod(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgSysMod();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYS_MOD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnNMRClickModTree(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnAdd();
	afx_msg void OnEdt();
	afx_msg void OnDel();
	afx_msg void OnTop();
	afx_msg void OnUp();
	afx_msg void OnDown();
	afx_msg void OnBottom();

	DECLARE_MESSAGE_MAP()

public:
	void InitLayout();
	void InitMod();
	void FillModeTree(HTREEITEM hParent, const CString& csParent);
	void PopupMenu(HTREEITEM hItem);
	void DeleteChildBranch(HTREEITEM hParent);
	bool SaveModTree();
	bool SaveChildModTree(HTREEITEM hParent, const CString& csParent,CStringArray& vSQL);
	HTREEITEM CopyBranch(HTREEITEM hItem,CSysMod& mod, HTREEITEM hParent, HTREEITEM hAfter);
	BOOL CopyChildBranch(HTREEITEM hParent,HTREEITEM hItem);
private:
	CBCGPTreeCtrl m_wndMod;
	CMap<HTREEITEM, HTREEITEM, CSysMod, CSysMod> m_Ids;   ///<树节点ID映射
};
