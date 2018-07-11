
// HumanResourcesView.cpp : implementation of the CHumanResourcesView class
//

#include "stdafx.h"

// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HumanResources.h"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#endif

#include "HumanResourcesDoc.h"
#include "HumanResourcesView.h"
#include "EnumDialogMode.h"
#include "Structures.h"
#include "EmployeeDialog.h"
#include "ReadWriteToFile.h"
#include "FilterDialog.h"
#include "SortListCtrl.h"

int employeesCounter = 0;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHumanResourcesView

IMPLEMENT_DYNCREATE(CHumanResourcesView, CFormView)

BEGIN_MESSAGE_MAP(CHumanResourcesView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHumanResourcesView::OnFilePrintPreview)

	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_BN_CLICKED(IDC_ADD_EMPLOYEE, &CHumanResourcesView::OnBnClickedAddEmployee)
	ON_BN_CLICKED(IDC_EDIT_EMPLOYEE, &CHumanResourcesView::OnBnClickedEditEmployee)
	ON_BN_CLICKED(IDC_HUMAN_RESOURCES_UNDO, &CHumanResourcesView::OnBnClickedHumanResourcesUndo)
	ON_BN_CLICKED(IDC_DELETE_EMPLOYEE, &CHumanResourcesView::OnBnClickedDeleteEmployee)

	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST1, &CHumanResourcesView::OnLvnKeydownList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CHumanResourcesView::ViewEmployee)

	ON_COMMAND(ID_FILTER_BYFIRSTNAME, &CHumanResourcesView::OnFilterByFirstName)
	ON_COMMAND(ID_FILTER_BYPIN, &CHumanResourcesView::OnFilterByPIN)
	ON_COMMAND(ID_FILTER_SHOWALL, &CHumanResourcesView::OnFilterShowall)

END_MESSAGE_MAP()

// CHumanResourcesView construction/destruction

CHumanResourcesView::CHumanResourcesView()
	: CFormView(IDD_HUMANRESOURCES_FORM)
{

}

CHumanResourcesView::~CHumanResourcesView()
{

}

void CHumanResourcesView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST1, m_Listcontrol_LIST1);
}

BOOL CHumanResourcesView::PreCreateWindow(CREATESTRUCT& cs)
{
	m_Menu.CreateMenu(); //Call this once only (I do it in PreSubclassWindow)

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CHumanResourcesView::OnInitialUpdate()
{

	CFormView::OnInitialUpdate();

	//Clear file which contains last log deleted employees 
	std::ofstream ofs;
	ofs.open("UNDOemployeeData.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	m_Listcontrol_LIST1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_INFOTIP | LVS_EX_ONECLICKACTIVATE);

	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	CRect rect;
	m_Listcontrol_LIST1.GetClientRect(&rect);

	int nColInterval = rect.Width() / 7;

	m_Listcontrol_LIST1.InsertColumn(0, "First name", LVCFMT_LEFT, nColInterval);
	m_Listcontrol_LIST1.InsertColumn(1, "Surname", LVCFMT_LEFT, nColInterval);
	m_Listcontrol_LIST1.InsertColumn(2, "Last name", LVCFMT_LEFT, nColInterval);
	m_Listcontrol_LIST1.InsertColumn(4, "PIN", LVCFMT_LEFT, nColInterval);
	m_Listcontrol_LIST1.InsertColumn(5, "Email", LVCFMT_LEFT, nColInterval);
	m_Listcontrol_LIST1.InsertColumn(6, "Phone number", LVCFMT_LEFT, nColInterval);
	m_Listcontrol_LIST1.InsertColumn(7, "Date", LVCFMT_LEFT, nColInterval);

	m_Listcontrol_LIST1.Submenu(m_Menu);
	Refresh(eFileMode_showAll);
}


// CHumanResourcesView printing


void CHumanResourcesView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHumanResourcesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void CHumanResourcesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHumanResourcesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CHumanResourcesView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void CHumanResourcesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHumanResourcesView::OnContextMenu(CWnd *pWnd, CPoint ptMousePos)
{
	//Some people might use a keyboard and not the mouse
	if (ptMousePos.x == -1 && ptMousePos.y == -1)
	{
		int nSelectedItem = m_Listcontrol_LIST1.GetSelectionMark();
		if (nSelectedItem == -1)
			return;
	
		//Find the position
		CRect itemRect;
		m_Listcontrol_LIST1.GetItemRect(nSelectedItem, &itemRect, LVIR_BOUNDS);
		ClientToScreen(&itemRect);
		ptMousePos.x = itemRect.left + (itemRect.Width() / 10); //Some offset to display the menu user-friendly
		ptMousePos.y = itemRect.top + itemRect.Height() / 2;
	}
	
	
	CPoint hitPoint = ptMousePos;
	ScreenToClient(&hitPoint);
	
	//Fix header pop-up bug
	CHeaderCtrl *pHeader = m_Listcontrol_LIST1.GetHeaderCtrl();
	HDHITTESTINFO hitTestHeader = { 0 };
	hitTestHeader.pt = hitPoint;
	
	//The header doesn't need a context-menu, the item does
	if (pHeader->HitTest(&hitTestHeader) != -1)
		return;
	
	UINT uFlags = 0;
	int nItemIndex = m_Listcontrol_LIST1.HitTest(hitPoint, &uFlags);
	
	if (uFlags & LVHT_NOWHERE)
		return;
	
	//Get the previously created menu
	CMenu *pPopUp = nullptr;
	pPopUp = m_Menu.GetSubMenu(0);

	if (pPopUp)
		pPopUp->TrackPopupMenu(TPM_LEFTALIGN, ptMousePos.x, ptMousePos.y, this);
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, ptMousePos.x, ptMousePos.y, this, TRUE);
#endif
}


// CHumanResourcesView diagnostics

#ifdef _DEBUG
void CHumanResourcesView::AssertValid() const
{
	CFormView::AssertValid();
}

void CHumanResourcesView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CHumanResourcesDoc* CHumanResourcesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHumanResourcesDoc)));
	return (CHumanResourcesDoc*)m_pDocument;
}
#endif //_DEBUG


// CHumanResourcesView message handlers

void CHumanResourcesView::OnBnClickedDeleteEmployee() //care when you modify this function because it will affect on PreTranslateMessage
{
	CEmployeeData employee;

	//get the index of currently selected row
	int selectedRow = m_Listcontrol_LIST1.GetSelectionMark();

	//3 is the position of the PIN in the structure
	employee.strPIN = m_Listcontrol_LIST1.GetItemText(selectedRow, 3);

	if (selectedRow != -1)
	{
		GetDocument()->DeleteEmployee(employee.strPIN);
		Refresh(eFileMode_showAll);
	}
	else
	{
		AfxMessageBox(_T("You haven't clicked on any employee!"));
	}

}

void CHumanResourcesView::OnBnClickedAddEmployee()
{
	UpdateData();

	CEmployeeData employee;

	CEmployeeDialog oDialogAdd(employee, eDialogMode_Add);

	if (oDialogAdd.DoModal() == IDOK)
		GetDocument()->AddToFile(employee);
	Refresh(eFileMode_showAll);


}

void CHumanResourcesView::OnBnClickedEditEmployee()
{
	//get the index of currently selected row
	int selectedRow = m_Listcontrol_LIST1.GetSelectionMark();

	CEmployeeData employee;

	//3 is the position of the PIN in the structure
	employee.strPIN = m_Listcontrol_LIST1.GetItemText(selectedRow, 3);


	if (selectedRow != -1)
	{
		GetDocument()->PrintEmployeeData(employee.strPIN, employee);

		CEmployeeDialog oDialogEdit(employee, eDialogMode_Edit);

		if (oDialogEdit.DoModal() == IDOK)
		{
			GetDocument()->EditFile(employee, selectedRow);
		}
		Refresh(eFileMode_showAll);
	}
	else
	{
		AfxMessageBox(_T("Please select edit choice!"));
	}

}

void CHumanResourcesView::Refresh(FileMode eMode)
{
	m_Listcontrol_LIST1.DeleteAllItems();
	m_employeesData.clear(); //clearing the list everytime before we get new data (if we have just deleted the last item ,
	// GetEmployees won't fill m_employeesData because the file will be empty and fill method wont be invoked )
	GetDocument()->GetEmployeesData(m_employeesData, eMode);
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;
	for (int i = 0; i < m_employeesData.size(); i++)
	{
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(m_employeesData[i].strFirstName);
		//inserting item in the first column
		m_Listcontrol_LIST1.InsertItem(&lvi);

		//inserting in all subColumns
		lvi.iSubItem = 1;
		lvi.pszText = (LPTSTR)(LPCTSTR)(m_employeesData[i].strSurname);
		m_Listcontrol_LIST1.SetItem(&lvi);

		lvi.iSubItem = 2;
		lvi.pszText = (LPTSTR)(LPCTSTR)(m_employeesData[i].strLastName);
		m_Listcontrol_LIST1.SetItem(&lvi);

		lvi.iSubItem = 3;
		lvi.pszText = (LPTSTR)(LPCTSTR)(m_employeesData[i].strPIN);
		m_Listcontrol_LIST1.SetItem(&lvi);

		lvi.iSubItem = 4;
		lvi.pszText = (LPTSTR)(LPCTSTR)(m_employeesData[i].strEmail);
		m_Listcontrol_LIST1.SetItem(&lvi);

		lvi.iSubItem = 5;
		lvi.pszText = (LPTSTR)(LPCTSTR)(m_employeesData[i].strPhoneNumber);
		m_Listcontrol_LIST1.SetItem(&lvi);

		lvi.iSubItem = 6;
		lvi.pszText = (LPTSTR)(LPCTSTR)(m_employeesData[i].strDate);
		m_Listcontrol_LIST1.SetItem(&lvi);

		m_Listcontrol_LIST1.SetItemData(i, (DWORD_PTR)&m_employeesData[i]); //the data of each item will be equal to it's index


	}
}


void CHumanResourcesView::ViewEmployee(NMHDR * pNMHDR, LRESULT * pResult)
{

	CEmployeeData employee;

	//get the index of currently selected row
	int selectedRow = m_Listcontrol_LIST1.GetSelectionMark();

	//3 is the position of the PIN in the structure
	employee.strPIN = m_Listcontrol_LIST1.GetItemText(selectedRow, 3);


	if (selectedRow != -1)
	{
		GetDocument()->ViewEmployee(employee, employee.strPIN);

		CEmployeeDialog oDialogView(employee, eDialogMode_View);

		oDialogView.DoModal();
	}
	else
	{
		AfxMessageBox(_T("You didn't click on any employee!"));
	}
	Refresh(eFileMode_showAll);

}

void CHumanResourcesView::OnFilterByFirstName()
{
	UpdateData();

	CEmployeeData employee;

	CString filter;

	CFilterDialog filterName(employee, fDialogMode_ByName);

	if (filterName.DoModal() == IDOK)
	{
		GetDocument()->FilterBy(employee.strFirstName, fDialogMode_ByName);
		Refresh(eFileMode_filtered);

	}
}

void CHumanResourcesView::OnFilterByPIN()
{
	UpdateData();

	CEmployeeData employee;

	CString filter;

	CFilterDialog filterName(employee, fDialogMode_ByPIN);

	if (filterName.DoModal() == IDOK)
	{
		GetDocument()->FilterBy(employee.strPIN, fDialogMode_ByPIN);
		Refresh(eFileMode_filtered);

	}

}

void CHumanResourcesView::OnFilterShowall()
{
	Refresh(eFileMode_showAll);
}

void CHumanResourcesView::OnLvnKeydownList1(NMHDR *pNMHDR, LRESULT *pResult)
{

	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;
	if (pLVKeyDown->wVKey == 46)
		OnBnClickedDeleteEmployee();  //Virtual key code for Delete is 46 -> checking if the user has pressed Delete key

	*pResult = 0;
}

void CHumanResourcesView::OnBnClickedHumanResourcesUndo()
{
	ReadWriteToFile undo;
	undo.DeleteLastAddedItem();
	Refresh(eFileMode_showAll);
}
