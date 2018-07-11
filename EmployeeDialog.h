#pragma once
#include "resource.h"
#include "Structures.h"
#include <vector>
#include "EnumDialogMode.h"

class CEmployeeDialog : public CDialogEx
{

	enum { IDD = IDD_EMPLOYEE_SEARCH};

public:
	CEmployeeDialog(CEmployeeData & oEmployee, DialogMode eMode);
	~CEmployeeDialog();

public:
	

	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	CString m_strFirstName;
	CString m_strSurName;
	CString m_strLastName;
	CString m_strPhoneNumber;
	CString m_strEmail;
	CString m_strPIN;
	CString m_strDate; 
	CString m_strCaption;

	CEdit m_EdbFirstName;
	CEdit m_EdbSurName;
	CEdit m_EdbLastName;
	CEdit m_EdbPhoneNumber;
	CEdit m_EdbEmail;
	CEdit m_EdbPIN;
	CEdit m_EdbDate;

	CEmployeeData & m_oEmployee;

	std::vector<CEmployeeData>  m_EmployeesData;

	DialogMode m_eMode;



};

