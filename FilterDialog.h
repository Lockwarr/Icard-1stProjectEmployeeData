#pragma once
#include "resource.h"
#include "Structures.h"
#include "EnumDialogMode.h"


// CFilterDialog dialog

class CFilterDialog : public CDialogEx
{
	enum { IDD = IDD_FILTER };

public:
	CFilterDialog(EMPLOYEE_DATA & oEmployee, FilterMode eDialogMode);
	virtual ~CFilterDialog();

	
public:

	DECLARE_MESSAGE_MAP()

	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	CString m_strFilterEmployeeInfo;
	CEdit m_StaticInfo;

	EMPLOYEE_DATA & m_oEmployee;
	FilterMode m_eMode;

};
