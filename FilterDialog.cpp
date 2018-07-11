// FilterDialog.cpp : implementation file
//

#include "stdafx.h"
#include "FilterDialog.h"


// CFilterDialog dialog


BEGIN_MESSAGE_MAP(CFilterDialog, CDialogEx)

	ON_BN_CLICKED(IDC_FILTER_OK, &CFilterDialog::OnOK)
	ON_BN_CLICKED(IDC_FILTER_CANCEL, &CFilterDialog::OnCancel)

END_MESSAGE_MAP()

CFilterDialog::CFilterDialog(CEmployeeData & oEmployee, DialogMode eDialogMode)
	: CDialogEx(IDD)
	, m_oEmployee(oEmployee)

{

	m_eMode = eDialogMode;

}

CFilterDialog::~CFilterDialog()
{
}

void CFilterDialog::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);

	DDX_Text(pDX, IDD_FILTER_EMPLOYEE, m_strFilterEmployeeInfo);

	DDX_Control(pDX, IDC_FILTER_STATIC, m_StaticInfo);

}



// CFilterDialog message handlers

BOOL CFilterDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	//checking dialog's mode
	if (m_eMode == fDialogMode_ByName)
	{
		//setting dialog's caption
		m_StaticInfo.SetWindowText(_T(" First name: "));
		SetWindowText(_T("Filter by First name"));
	}
	else if (m_eMode == fDialogMode_ByPIN)
	{
		//setting dialog's caption
		m_StaticInfo.SetWindowText(_T(" PIN: "));
		SetWindowText(_T("Filter by PIN"));

	}
	
	return TRUE;
}



void CFilterDialog::OnOK()
{
	UpdateData();

	//checking dialog's mode
	if (m_eMode == fDialogMode_ByName)
	{
		//setting dialog's caption
		m_StaticInfo.SetWindowText(_T(" First name: "));
		SetWindowText(_T("Filter by First name"));
		m_oEmployee.strFirstName = m_strFilterEmployeeInfo;
	}
	else if (m_eMode == fDialogMode_ByPIN)
	{
		//setting dialog's caption
		m_StaticInfo.SetWindowText(_T(" PIN: "));
		SetWindowText(_T("Filter by PIN"));
		m_oEmployee.strPIN = m_strFilterEmployeeInfo;

	}

	__super::OnOK();
}