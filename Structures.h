#pragma once

enum FilterMode
{
	eFilterMode_ByName,
	eFilterMode_ByDate
};

struct EMPLOYEE_DATA
{

	CString strFirstName;
	CString strSurname;
	CString strLastName;
	CString strPIN;
	CString strEmail;
	CString strPhoneNumber;
	CString strDate;
};