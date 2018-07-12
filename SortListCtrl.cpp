/*----------------------------------------------------------------------
Copyright (C)2001 MJSoft. All Rights Reserved.
This source may be used freely as long as it is not sold for
profit and this copyright information is not altered or removed.
Visit the web-site at www.mjsoft.co.uk
e-mail comments to info@mjsoft.co.uk
File:     SortListCtrl.cpp
Purpose:  Provides a sortable list control, it will sort text, numbers
and dates, ascending or descending, and will even draw the
arrows just like windows explorer!
----------------------------------------------------------------------*/

#include "stdafx.h"
#include "SortListCtrl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


LPCTSTR g_pszSection = _T("ListCtrls");


CSortListCtrl::CSortListCtrl()
	: m_iSortColumn(-1)
	, m_bSortAscending(TRUE)
{
}


CSortListCtrl::~CSortListCtrl()
{
}


BEGIN_MESSAGE_MAP(CSortListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnClick)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSortListCtrl message handlers

void CSortListCtrl::PreSubclassWindow()
{

	// the list control must have the report style.
}


int CALLBACK CSortListCtrl::CompareFunction(LPARAM lParam1, LPARAM lParam2, LPARAM lParamData)
{
	CSortListCtrl* pListCtrl = reinterpret_cast<CSortListCtrl*>(lParamData);
	ASSERT(pListCtrl->IsKindOf(RUNTIME_CLASS(CListCtrl)));

	EMPLOYEE_DATA* pid1 = reinterpret_cast<EMPLOYEE_DATA*>(lParam1);
	EMPLOYEE_DATA* pid2 = reinterpret_cast<EMPLOYEE_DATA*>(lParam2);

	ASSERT(pid1);
	ASSERT(pid2);
	int iSortColumn = pListCtrl->m_iSortColumn;
	CString pszText1;
	CString pszText2;
	switch (iSortColumn)
	{
	case 0:
		pszText1 = pid1->strFirstName;
		pszText2 = pid2->strFirstName;
		break;
	case 1:
		pszText1 = pid1->strSurname;
		pszText2 = pid2->strSurname;
		break;
	case 2:
		pszText1 = pid1->strLastName;
		pszText2 = pid2->strLastName;
		break;
	case 3:
		pszText1 = pid1->strPIN;
		pszText2 = pid2->strPIN;
		break;
	case 4:
		pszText1 = pid1->strEmail;
		pszText2 = pid2->strEmail;
		break;
	case 5:
		pszText1 = pid1->strPhoneNumber;
		pszText2 = pid2->strPhoneNumber;
		break;
	case 6:
		pszText1 = pid1->strDate;
		pszText2 = pid2->strDate;
		break;

	}
	return strcmp(pszText1, pszText2);

}


void CSortListCtrl::OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;

	// if it's a second click on the same column then reverse the sort order,
	// otherwise sort the new column in ascending order.
	Sort(iColumn, iColumn == m_iSortColumn ? !m_bSortAscending : TRUE);

	*pResult = 0;
}


void CSortListCtrl::Sort(int iColumn, BOOL bSortAscending)
{
	m_iSortColumn = iColumn;
	m_bSortAscending = bSortAscending;

	VERIFY(SortItems(CompareFunction, reinterpret_cast<DWORD>(this)));
}
void CSortListCtrl::Submenu(CMenu & m_Menu)
{
	CMenu submenu;
	submenu.CreatePopupMenu();
	submenu.AppendMenu(MF_STRING, IDC_ADD_EMPLOYEE, "&Add");
	submenu.AppendMenu(MF_STRING, IDC_EDIT_EMPLOYEE, "&Edit");
	submenu.AppendMenu(MF_SEPARATOR);
	submenu.AppendMenu(MF_STRING, IDC_DELETE_EMPLOYEE, "&Delete");

	m_Menu.AppendMenu(MF_POPUP, reinterpret_cast<UINT_PTR>(submenu.m_hMenu), "");
	submenu.Detach();
}
