#pragma once
#include "Structures.h"
#include "EnumFileMode.h"
#include <vector>


class ReadWriteToFile
{
public:
	ReadWriteToFile();
	BOOL WriteToFile(const CEmployeeData & oEmployee);
	BOOL FillFilteredFile(std::vector<CEmployeeData> employeesData);
	void GetDataFromFile(std::vector<CEmployeeData>& employeesData, FileMode eMode);
	void ReWriteFile(std::vector<CEmployeeData> employeesData);
	void SaveDataForUndo(const CEmployeeData & oEmployee);
	std::string GetLastLineFromUndoData();

	//void AddLastDeletedItem();

	void DeleteLastAddedItem();

};