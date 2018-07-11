
#pragma once


class CSortListCtrl : public CListCtrl
{
	// Construction
public:
	CSortListCtrl();

	// Attributes
public:

	// Operations
public:
	void Sort(int iColumn, BOOL bAscending);
	void Submenu(CMenu & m_Menu);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSortListCtrl)
protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CSortListCtrl();
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	static int CALLBACK CompareFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamData);

	// Generated message map functions
protected:

	int m_iSortColumn;
	BOOL m_bSortAscending;
	CMenu m_Menu;
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
