#include "stdafx.h"
#include "EmployeeDialog.h"
#include <string>

BEGIN_MESSAGE_MAP(CEmployeeDialog, CDialogEx)

	ON_BN_CLICKED(IDC_EMPLOYEE_SEARCH_OK, &CEmployeeDialog::OnOK)
	ON_BN_CLICKED(IDC_CANCEL, &CEmployeeDialog::OnCancel)

END_MESSAGE_MAP()

CEmployeeDialog::CEmployeeDialog(EMPLOYEE_DATA & oEmployee, DialogMode eDialogMode)
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

	if (!ValidatePIN())
	{
		AfxMessageBox(_T("Invalid PIN!"));
	}
	else if (!ValidateDate())
	{
		AfxMessageBox(_T("Invalid Date!"));
	}
	else
	{
		if (AreEmptyBoxesLeft())
		{
			AfxMessageBox(_T("Cannot leave empty boxes!"));
		}
		else
		{
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
}

BOOL CEmployeeDialog::AreEmptyBoxesLeft()
{
	//validating that there are no empty edit controls
	if (m_strFirstName == "" || m_strSurName == "" || m_strLastName == "" || m_strPIN == "" ||
		m_strEmail == "" || m_strPhoneNumber == "" || m_strDate == "")
	{
		return 1;

	}
	return 0;
}
BOOL CEmployeeDialog::ValidatePIN()
{
	for (int i = 0; i < m_strPIN.GetLength(); i++) {
		if (!isdigit(m_strPIN[i]))
			return FALSE;
	}

	int lengthOfPIN = strlen(m_strPIN);

	if (lengthOfPIN != 10)
	{
		return FALSE;
	}

	std::string firstNum;
	firstNum.push_back(m_strPIN[0]);

	std::string monthNums;
	monthNums.push_back(m_strPIN[2]);
	monthNums.push_back(m_strPIN[3]);

	std::string yearNums;
	yearNums.push_back(m_strPIN[0]);
	yearNums.push_back(m_strPIN[1]);


	if (stoi(firstNum) == 0)
	{
		if (!((stoi(monthNums) > 20 && stoi(monthNums) <= 32)
			|| (stoi(monthNums) > 40 && stoi(monthNums) <= 52)))
		{
			return FALSE;
		}
	}
	else
	{
		if (!((stoi(monthNums) >= 0 && stoi(monthNums) <= 12)
			|| (stoi(monthNums) > 20 && stoi(monthNums) <= 32)
			|| (stoi(monthNums) > 40 && stoi(monthNums) <= 52)))
		{
			return FALSE;
		}
	}

	std::string dayNums;//5th and 6th numbers
	dayNums.push_back(m_strPIN[4]);
	dayNums.push_back(m_strPIN[5]);


	if (stoi(monthNums) == 1 || stoi(monthNums) == 3 || stoi(monthNums) == 5 || stoi(monthNums) == 7
		|| stoi(monthNums) == 8 || stoi(monthNums) == 10 || stoi(monthNums) == 12

		|| stoi(monthNums) == 21 || stoi(monthNums) == 23 || stoi(monthNums) == 25 || stoi(monthNums) == 27
		|| stoi(monthNums) == 28 || stoi(monthNums) == 30 || stoi(monthNums) == 32

		|| stoi(monthNums) == 41 || stoi(monthNums) == 43 || stoi(monthNums) == 45 || stoi(monthNums) == 47
		|| stoi(monthNums) == 48 || stoi(monthNums) == 50 || stoi(monthNums) == 52)
	{
		if (stoi(dayNums) < 0 || stoi(dayNums) > 31)
		{
			return FALSE;
		}
	}
	else if (stoi(monthNums) == 2 || stoi(monthNums) == 22 || stoi(monthNums) == 42)
	{
		if (stoi(yearNums) % 4 == 0)
		{
			if (stoi(dayNums) < 0 || stoi(dayNums) > 29)
			{
				return FALSE;
			}
		}
		else
		{
			if (stoi(dayNums) < 0 || stoi(dayNums) > 28)
			{
				return FALSE;
			}
		}
	}
	else
	{
		if (stoi(dayNums) < 0 || stoi(dayNums) > 30)
		{
			return FALSE;
		}
	}

	return TRUE;
}
BOOL CEmployeeDialog::ValidateDate()
{
	std::string yearDateNums;

	BOOL sevenNumbersDateValid = FALSE;
	BOOL isDaySingleNumber = FALSE;
	BOOL isMonthSingleNumber = FALSE;

	int dateLenght = strlen(m_strDate);
	if (dateLenght == 10)
	{
		yearDateNums.push_back(m_strDate[6]);
		yearDateNums.push_back(m_strDate[7]);
		yearDateNums.push_back(m_strDate[8]);
		yearDateNums.push_back(m_strDate[9]);

		if (!(isdigit(m_strDate[0]) && isdigit(m_strDate[1]) && isdigit(m_strDate[3])
			&& isdigit(m_strDate[4]) && isdigit(m_strDate[6]) && isdigit(m_strDate[7])
			&& isdigit(m_strDate[8]) && isdigit(m_strDate[8])))
			return FALSE;
	}
	else if (dateLenght == 8)
	{

			yearDateNums.push_back(m_strDate[6]);
			yearDateNums.push_back(m_strDate[7]);
			if (!(isdigit(m_strDate[0]) && isdigit(m_strDate[1]) && isdigit(m_strDate[3])
				&& isdigit(m_strDate[4]) && isdigit(m_strDate[6]) && isdigit(m_strDate[7])))
				return FALSE;

	}
	else
	{
		return FALSE;
	}

	std::string dayDateNums;
	dayDateNums.push_back(m_strDate[0]);
	dayDateNums.push_back(m_strDate[1]);

	std::string monthDateNums;
	monthDateNums.push_back(m_strDate[3]);
	monthDateNums.push_back(m_strDate[4]);

	if (stoi(monthDateNums) > 12 || stoi(monthDateNums) <= 0)
		return FALSE;

	if (stoi(monthDateNums) == 1 || stoi(monthDateNums) == 3 || stoi(monthDateNums) == 5 || stoi(monthDateNums) == 7
		|| stoi(monthDateNums) == 8 || stoi(monthDateNums) == 10 || stoi(monthDateNums) == 12)
	{

		if (stoi(dayDateNums) > 31 || stoi(dayDateNums) <= 0)
			return FALSE;

	}
	else if (stoi(monthDateNums) == 2)
	{
		if (stoi(yearDateNums) % 4 == 0)
		{
			if (stoi(dayDateNums) > 29 || stoi(dayDateNums) <= 0)
				return FALSE;
		}
		else
		{
			if (stoi(dayDateNums) > 28 || stoi(dayDateNums) <= 0)
				return FALSE;
		}
	}
	else
	{
		if (stoi(dayDateNums) > 30 || stoi(dayDateNums) <= 0)
			return FALSE;
	}

	if (dateLenght == 7)
	{
		if (isMonthSingleNumber)
		{
			if (m_strDate[2] != '.' && m_strDate[4] != '.')
				return FALSE;

		}
		else if (isDaySingleNumber)
		{
			if (m_strDate[1] != '.' && m_strDate[4] != '.')
				return FALSE;
		}

	}
	else if (dateLenght == 6)
	{
		if (m_strDate[1] != '.' && m_strDate[3] != '.')
			return FALSE;
	}
	else
	{
		if (m_strDate[2] != '.' && m_strDate[5] != '.')
			return FALSE;
	}
	return TRUE;
}
