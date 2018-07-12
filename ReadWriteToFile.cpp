#include "stdafx.h"
#include "ReadWriteToFile.h"

ReadWriteToFile::ReadWriteToFile()
{
}

BOOL ReadWriteToFile::WriteToFile(const EMPLOYEE_DATA & oEmployee)
{
	std::fstream outFile;
	outFile.open("employeeData.txt", std::ofstream::app);
//	SaveDataForUndo(oEmployee);
	if (outFile.is_open())
	{
		outFile << (CStringA)oEmployee.strFirstName << "\t" << (CStringA)oEmployee.strSurname << "\t" << (CStringA)oEmployee.strLastName
			<< "\t" << (CStringA)oEmployee.strPIN << "\t" << (CStringA)oEmployee.strEmail << "\t" << (CStringA)oEmployee.strPhoneNumber
			<< "\t" << (CStringA)oEmployee.strDate << std::endl;
		outFile.close();
	}
	return TRUE;
}


BOOL ReadWriteToFile::GetDataFromFile(std::vector<EMPLOYEE_DATA> & employeesData)
{
	std::string readLine;
	std::fstream myFile;

	//string to hold different mode file names
	std::string mode;

	int counter = 0;
	int vectorSize = 1;

	myFile.open("employeeData.txt");

	if (!myFile.is_open())
		return FALSE;

	while (getline(myFile, readLine))
	{
		employeesData.resize(vectorSize);
		std::istringstream iss(readLine);
		std::vector<std::string> CurrentEmployeeInfo;
		std::string token;

		while (std::getline(iss, token, '\t'))
			CurrentEmployeeInfo.push_back(token);

		employeesData[counter].strFirstName = CurrentEmployeeInfo[0].c_str();
		employeesData[counter].strSurname = CurrentEmployeeInfo[1].c_str();
		employeesData[counter].strLastName = CurrentEmployeeInfo[2].c_str();
		employeesData[counter].strPIN = CurrentEmployeeInfo[3].c_str();
		employeesData[counter].strEmail = CurrentEmployeeInfo[4].c_str();
		employeesData[counter].strPhoneNumber = CurrentEmployeeInfo[5].c_str();
		employeesData[counter].strDate = CurrentEmployeeInfo[6].c_str();

		counter++;
		vectorSize++;
	}

	myFile.close();

	return TRUE;
}
void ReadWriteToFile::ReWriteFile(std::vector<EMPLOYEE_DATA> employeesData)
{
	//Clear file 
	std::ofstream ofs;
	ofs.open("employeeData.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	//Filling file with new data 
	std::fstream outFile;
	outFile.open("employeeData.txt", std::ofstream::app);

	if (outFile.is_open())
	{
		for (int i = 0; i < employeesData.size(); i++) {
			outFile << (CStringA)employeesData[i].strFirstName << "\t" << (CStringA)employeesData[i].strSurname << "\t" << (CStringA)employeesData[i].strLastName
				<< "\t" << (CStringA)employeesData[i].strPIN << "\t" << (CStringA)employeesData[i].strEmail << "\t" << (CStringA)employeesData[i].strPhoneNumber
				<< "\t" << (CStringA)employeesData[i].strDate << std::endl;
		}
		outFile.close();
	}
}
BOOL ReadWriteToFile::GetDataAndDeleteEmployee(std::vector<EMPLOYEE_DATA>& employeeData, CString& employeePIN)
{
	if (!GetDataFromFile(employeeData))
	{
		return FALSE;
	}

	for (int i = employeeData.size() - 1; i >= 0; i--)
	{
		if (employeeData[i].strPIN == employeePIN)
		{
			employeeData.erase(employeeData.begin() + i);
		}
	}
	return TRUE;
}
BOOL ReadWriteToFile::GetDataAndEditEmployee(std::vector<EMPLOYEE_DATA> & employeeData, CString & employeePIN)
{
	EMPLOYEE_DATA oEmployee;

	if (!GetDataFromFile(employeeData))
	{
		return FALSE;
	}
	
	for (int i = 0; i < employeeData.size(); i++)
	{
		if (employeeData[i].strPIN == employeePIN)
		{
			employeeData[i] = oEmployee;
		}
	}
	return TRUE;
}

BOOL ReadWriteToFile::RemoveAll()
{
	std::ofstream ofs;
	ofs.open("employeeData.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();

	return TRUE;
}










//void ReadWriteToFile::SaveDataForUndo(const CEmployeeData & oEmployee)
//{
//	std::fstream outFile;
//
//	outFile.open("UNDOemployeeData.txt", std::ofstream::app);
//	if (outFile.is_open())
//	{
//		outFile << (CStringA)oEmployee.strFirstName << "\t" << (CStringA)oEmployee.strSurname << "\t" << (CStringA)oEmployee.strLastName
//			<< "\t" << (CStringA)oEmployee.strPIN << "\t" << (CStringA)oEmployee.strEmail << "\t" << (CStringA)oEmployee.strPhoneNumber
//			<< "\t" << (CStringA)oEmployee.strDate << std::endl;
//		outFile.close();
//	}
//}
//std::string ReadWriteToFile::GetLastLineFromUndoData()
//{
//#define _LL_BUFFSIZE_ 2048 
//
//	char buff[_LL_BUFFSIZE_];
//
//	std::string lastLine;
//	std::fstream outFile;
//
//	outFile.open("UNDOemployeeData.txt");
//
//	if (outFile.is_open()) {
//
//		outFile.seekg(0, std::ios::end);            // go to end of file 
//		int length = outFile.tellg();        // find out how large it is 
//		outFile.seekg(length - min(length, _LL_BUFFSIZE_), std::ios::beg);    // seek back from end a short ways 
//
//																	// read in each line of the file until we're done 
//		buff[0] = 0;
//		while (outFile.getline(buff, _LL_BUFFSIZE_)) {
//			lastLine = buff;
//		}
//	}
//	outFile.close();
//	outFile.open("UNDoemployeeData.txt");
//	std::vector<std::string> lastAddedEmployees;
//	std::string currentLine;
//	int vectorSize = 1;
//	int i = 0;
//	while (getline(outFile, currentLine)) //put all the data from file into a vector<string>
//	{
//		lastAddedEmployees.resize(vectorSize);
//		lastAddedEmployees[i] = currentLine;
//		vectorSize++;
//		i++;
//	}
//
//	outFile.close();
//	//Clear file 
//	std::ofstream ofs;
//	ofs.open("UNDOemployeeData.txt", std::ofstream::out | std::ofstream::trunc);
//	ofs.close();
//
//	if (lastAddedEmployees.size() != 0)
//	{
//		outFile.open("UNDOemployeeData.txt");
//		for (int i = 0; i < lastAddedEmployees.size() - 1; i++)
//		{
//			outFile << lastAddedEmployees[i] << std::endl;
//		}
//	}
//	return lastLine;
//}
//void ReadWriteToFile::DeleteLastAddedItem()
//{
//
//	std::fstream myFile;
//	myFile.open("employeeData.txt");
//
//	std::string lastAdded = GetLastLineFromUndoData();
//	std::string line;
//
//	int i = 0;
//	int vectorSize = 1;
//	std::vector<std::string> employeesData;
//
//	bool AnyChangesMade = FALSE;
//	while (getline(myFile, line))
//	{
//		employeesData.resize(vectorSize);
//		employeesData[i] = line;
//		i++;
//		vectorSize++;
//		if (line == lastAdded)
//		{
//			AnyChangesMade = TRUE;
//		}
//	}
//
//	if (AnyChangesMade) {
//		//Clear file 
//		std::ofstream ofs;
//		ofs.open("employeeData.txt", std::ofstream::out | std::ofstream::trunc);
//		ofs.close();
//
//		//Filling file with new data 
//		myFile.close();
//		myFile.open("employeeData.txt", std::ofstream::app);
//		for (int i = 0; i < employeesData.size() - 1; i++)
//		{
//			myFile << employeesData[i] << std::endl;
//		}
//	}
//}
//void ReadWriteToFile::AddLastDeletedItem()
//{
//	std::fstream myFile;
//	myFile.open("employeeData.txt");
//	std::string lastDeleted = GetLastLineFromUndoData();
//	std::string line;
//
//	bool AnyDeletedEmployees = TRUE;
//	while (getline(myFile, line))
//	{
//		if (line == lastDeleted)
//		{
//			AnyDeletedEmployees = FALSE;
//		}
//	}
//	myFile.close();
//
//	if (AnyDeletedEmployees)
//	{
//		myFile.open("employeeData.txt", std::ofstream::app);
//
//		CEmployeeData deletedEmployee;
//
//		std::istringstream iss(lastDeleted);
//		std::vector<std::string> CurrentEmployeeInfo;
//		std::string token;
//		while (std::getline(iss, token, '\t'))
//			CurrentEmployeeInfo.push_back(token);
//		deletedEmployee.strFirstName = CurrentEmployeeInfo[0].c_str();
//		deletedEmployee.strSurname = CurrentEmployeeInfo[1].c_str();
//		deletedEmployee.strLastName = CurrentEmployeeInfo[2].c_str();
//		deletedEmployee.strPIN = CurrentEmployeeInfo[3].c_str();
//		deletedEmployee.strEmail = CurrentEmployeeInfo[4].c_str();
//		deletedEmployee.strPhoneNumber = CurrentEmployeeInfo[5].c_str();
//		deletedEmployee.strDate = CurrentEmployeeInfo[6].c_str();
//
//		WriteToFile(deletedEmployee);
//	}
//}