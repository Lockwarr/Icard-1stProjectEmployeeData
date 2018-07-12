#pragma once
#include "Structures.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>

class ReadWriteToFile
{
public:
	ReadWriteToFile();
	BOOL WriteToFile(const EMPLOYEE_DATA & oEmployee);
	BOOL GetDataFromFile(std::vector<EMPLOYEE_DATA>& employeesData);
	void ReWriteFile(std::vector<EMPLOYEE_DATA> employeesData);

	BOOL GetDataAndDeleteEmployee(std::vector<EMPLOYEE_DATA>& employeeData, CString& employeePIN);

	BOOL GetDataAndEditEmployee(std::vector<EMPLOYEE_DATA>& employeeData, CString & employeePIN);

	BOOL RemoveAll();


};