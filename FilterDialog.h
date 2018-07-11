#pragma once
#include "resource.h"
#include "Structures.h"
#include "EnumDialogMode.h"


// CFilterDialog dialog

class CFilterDialog : public CDialogEx
{
	enum { IDD = IDD_FILTER };

public:
	CFilterDialog(CEmployeeData & oEmployee, DialogMode eDialogMode);
	virtual ~CFilterDialog();

	
public:

	DECLARE_MESSAGE_MAP()

	virtual void OnOK();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	CString m_strFilterEmployeeInfo;
	CEdit m_StaticInfo;

	CEmployeeData & m_oEmployee;
	DialogMode m_eMode;

};
