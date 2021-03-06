
// HumanResourcesView.h : interface of the CHumanResourcesView class
//

#pragma once
#include "HumanResourcesDoc.h"
#include "SortListCtrl.h"
#include "EnumDialogMode.h"
#include "Structures.h"
#include "EmployeeDialog.h"
#include "ReadWriteToFile.h"
#include "FilterDialog.h"

#include "HumanResources.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

enum RefreshMode
{
	eFileMode_filtered,
	eFileMode_showAll
};

class CHumanResourcesView : public CFormView
{
	DECLARE_DYNCREATE(CHumanResourcesView)

public:
	CHumanResourcesView();
	virtual ~CHumanResourcesView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HUMANRESOURCES_FORM };
#endif

	// Attributes
public:
	CHumanResourcesDoc * GetDocument() const;

	// Operations
public:
	void LoadEmployees(std::vector<EMPLOYEE_DATA> employeesData, RefreshMode refreshMode);
	void OnFilterByDate();
	void OnFilterLoadAll();
	void LoadEmployee(NMHDR * pNMHDR, LRESULT * pResult);
	void OnFilterByFirstName();
	void LoadAll();


	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);



	// Implementation
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;

#endif


	// Generated message map functions
protected:
	
	DECLARE_MESSAGE_MAP()
private:
	afx_msg	void OnBnClickedAddEmployee();
	afx_msg void OnBnClickedEditEmployee();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnBnClickedDeleteEmployee();

protected:

	int m_nSortedCol = -1;
	CMenu m_Menu;
	BOOL m_bSortAscending = TRUE;
	CSortListCtrl m_Listcontrol_LIST1;
	int m_iSortColumn;

	std::vector<EMPLOYEE_DATA> m_employeesData;
public:
	afx_msg void OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedHumanresourcesClear();
};

#ifndef _DEBUG  // debug version in HumanResourcesView.cpp
inline CHumanResourcesDoc* CHumanResourcesView::GetDocument() const
{
	return reinterpret_cast<CHumanResourcesDoc*>(m_pDocument);
}
#endif

