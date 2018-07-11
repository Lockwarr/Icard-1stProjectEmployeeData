#include "stdafx.h"
#include "EmployeeDialog.h"

BEGIN_MESSAGE_MAP(CEmployeeDialog, CDialogEx)

	ON_BN_CLICKED(IDC_OK, &CEmployeeDialog::OnOK)
	ON_BN_CLICKED(IDC_CANCEL, &CEmployeeDialog::OnCancel)

END_MESSAGE_MAP()

CEmployeeDialog::CEmployeeDialog(CEmployeeData & oEmployee, DialogMode eDialogMode)
	: CDialogEx(IDD)
	, m_oEmployee(oEmployee)
{
	m_eMode = eDialogMode;

}


CEmployeeDialog::~CEmployeeDialog()
{

}


/*virtual*/
void CEmployeeDialog::DoDataExchange(CDataExchange* pDX)    // DDX/DDV support
{
	__super::DoDataExchange(pDX);

	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_FIRSTNAME, m_strFirstName);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_SURNAME, m_strSurName);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_LASTNAME, m_strLastName);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_PIN, m_strPIN);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_EMAIL, m_strEmail);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_PHONENUMBER, m_strPhoneNumber);
	DDX_Text(pDX, IDD_EMPLOYEE_SEARCH_DATE, m_strDate);

	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_FIRSTNAME, m_EdbFirstName);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_SURNAME, m_EdbSurName);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_LASTNAME, m_EdbLastName);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_PIN, m_EdbPIN);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_PHONENUMBER, m_EdbPhoneNumber);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_EMAIL, m_EdbEmail);
	DDX_Control(pDX, IDD_EMPLOYEE_SEARCH_DATE, m_EdbDate);
}

/*virtual*/
BOOL CEmployeeDialog::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	//checking the mode of the Dialog
	if (m_eMode == eDialogMode_Edit)
	{
		m_strCaption = m_oEmployee.strPIN;

		//setting dialog's caption
		SetWindowText(_T("Edit employee with PIN " + m_strCaption));

		m_strFirstName = m_oEmployee.strFirstName;
		m_strSurName = m_oEmployee.strSurname;
		m_strLastName = m_oEmployee.strLastName;
		m_strPIN = m_oEmployee.strPIN;
		m_strEmail = m_oEmployee.strEmail;
		m_strPhoneNumber = m_oEmployee.strPhoneNumber;
		m_strDate = m_oEmployee.strDate;


		m_EdbPIN.SetReadOnly();


	}
	else if (m_eMode == eDialogMode_View)
	{
		m_strCaption = m_oEmployee.strPIN;

		//setting dialog's caption
		SetWindowText(_T("View employee with PIN " + m_strCaption));

		m_strFirstName = m_oEmployee.strFirstName;
		m_strSurName = m_oEmployee.strSurname;
		m_strLastName = m_oEmployee.strLastName;
		m_strPIN = m_oEmployee.strPIN;
		m_strEmail = m_oEmployee.strEmail;
		m_strPhoneNumber = m_oEmployee.strPhoneNumber;
		m_strDate = m_oEmployee.strDate;


		m_EdbFirstName.SetReadOnly();
		m_EdbSurName.SetReadOnly();
		m_EdbLastName.SetReadOnly();
		m_EdbPIN.SetReadOnly();
		m_EdbPhoneNumber.SetReadOnly();
		m_EdbEmail.SetReadOnly();
		m_EdbDate.SetReadOnly();
	}

	UpdateData(FALSE);

	return TRUE;

}


/*virtual*/
void CEmployeeDialog::OnOK()
{

	UpdateData();

	//validating that there are no empty edit controls
	if (m_strFirstName == "" || m_strSurName == "" || m_strLastName == "" || m_strPIN == "" ||
		m_strEmail == "" || m_strPhoneNumber == "" || m_strDate == "")
	{
		AfxMessageBox(_T("Cannot leave empty boxes!"));
	}
	else {

		m_oEmployee.strFirstName = m_strFirstName;
		m_oEmployee.strSurname = m_strSurName;
		m_oEmployee.strLastName = m_strLastName;
		m_oEmployee.strPIN = m_strPIN;
		m_oEmployee.strEmail = m_strEmail;
		m_oEmployee.strPhoneNumber = m_strPhoneNumber;
		m_oEmployee.strDate = m_strDate;

		__super::OnOK();

	}
}

