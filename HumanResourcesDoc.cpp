
// HumanResourcesDoc.cpp : implementation of the CHumanResourcesDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#endif

#include "HumanResourcesDoc.h"
#include "ReadWriteToFile.h"
#include "HumanResources.h"



#include <propkey.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


int i = 0;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHumanResourcesDoc

IMPLEMENT_DYNCREATE(CHumanResourcesDoc, CDocument)

BEGIN_MESSAGE_MAP(CHumanResourcesDoc, CDocument)
END_MESSAGE_MAP()


// CHumanResourcesDoc construction/destruction

CHumanResourcesDoc::CHumanResourcesDoc()
{
	// TODO: add one-time construction code here

}

CHumanResourcesDoc::~CHumanResourcesDoc()
{
}

void CHumanResourcesDoc::DeleteEmployee(CString employeePIN)
{
	ReadWriteToFile read;
	std::vector<CEmployeeData> employeeData;

	//getting employees data from the file containing all emplyoees
	read.GetDataFromFile(employeeData, eFileMode_showAll);

	//deleting employee by PIN 
	for (int i = employeeData.size() - 1; i >= 0; i--)
	{
		if (employeeData[i].strPIN == employeePIN)
		{
	//		read.SaveDataForUndo(employeeData[i]);
			employeeData.erase(employeeData.begin() + i);
		}
	}
	read.ReWriteFile(employeeData);

}

BOOL CHumanResourcesDoc::AddToFile(const CEmployeeData& oEmployee)
{
	ReadWriteToFile write;
	if (write.WriteToFile(oEmployee))
	{
		AfxMessageBox(_T("Employee added successfully!"));
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CHumanResourcesDoc::FilterBy(CString filter, DialogMode eMode)
{
	ReadWriteToFile write;
	std::vector<CEmployeeData> employeesData;
	std::vector<CEmployeeData> filteredEmployees;
	int filteredEmployeesSizeCount = 1;
	int filteredEmployeesIndexCounter = 0;

	//Get current emlps data
	write.GetDataFromFile(employeesData, eFileMode_showAll);

	//Check for coincidencess
	if (eMode == fDialogMode_ByName) {
		for (int i = 0; i < employeesData.size(); i++)
		{
			if (filter == employeesData[i].strFirstName)
			{
				//Filling and resizing after each new coincidence
				filteredEmployees.resize(filteredEmployeesSizeCount);
				filteredEmployees[filteredEmployeesIndexCounter].strFirstName = employeesData[i].strFirstName;
				filteredEmployees[filteredEmployeesIndexCounter].strSurname = employeesData[i].strSurname;
				filteredEmployees[filteredEmployeesIndexCounter].strLastName = employeesData[i].strLastName;
				filteredEmployees[filteredEmployeesIndexCounter].strPIN = employeesData[i].strPIN;
				filteredEmployees[filteredEmployeesIndexCounter].strEmail = employeesData[i].strEmail;
				filteredEmployees[filteredEmployeesIndexCounter].strPhoneNumber = employeesData[i].strPhoneNumber;
				filteredEmployees[filteredEmployeesIndexCounter].strDate = employeesData[i].strDate;
				filteredEmployeesIndexCounter++;
				filteredEmployeesSizeCount++;

			}
		}
	}
	else if (eMode == fDialogMode_ByPIN)
	{
		for (int i = 0; i < employeesData.size(); i++)
		{
			if (filter == employeesData[i].strPIN)
			{
				//Filling and resizing after each new coincidence
				filteredEmployees.resize(filteredEmployeesSizeCount);
				filteredEmployees[filteredEmployeesIndexCounter].strFirstName = employeesData[i].strFirstName;
				filteredEmployees[filteredEmployeesIndexCounter].strSurname = employeesData[i].strSurname;
				filteredEmployees[filteredEmployeesIndexCounter].strLastName = employeesData[i].strLastName;
				filteredEmployees[filteredEmployeesIndexCounter].strPIN = employeesData[i].strPIN;
				filteredEmployees[filteredEmployeesIndexCounter].strEmail = employeesData[i].strEmail;
				filteredEmployees[filteredEmployeesIndexCounter].strPhoneNumber = employeesData[i].strPhoneNumber;
				filteredEmployees[filteredEmployeesIndexCounter].strDate = employeesData[i].strDate;
				filteredEmployeesIndexCounter++;
				filteredEmployeesSizeCount++;

			}
		}
	}
	//Filling new file containing only filtered employees;
	write.FillFilteredFile(filteredEmployees);

	return TRUE;
}

void CHumanResourcesDoc::EditFile(CEmployeeData & oEmployee, int selectedRow)
{

	ReadWriteToFile readWrite;
	std::vector<CEmployeeData> employeesData;

	//getting data from file which contains all employees
	readWrite.GetDataFromFile(employeesData, eFileMode_showAll);

	//check for matching PIN
	for (int i = 0; i < employeesData.size(); i++)
	{
		if (employeesData[i].strPIN == employeesData[selectedRow].strPIN)
		{
			employeesData[i] = oEmployee;

			break;
		}
	}

	readWrite.ReWriteFile(employeesData);

}

void CHumanResourcesDoc::ViewEmployee(CEmployeeData & oEmployee, CString PIN)
{
	PrintEmployeeData(PIN, oEmployee);
}

void CHumanResourcesDoc::PrintEmployeeData(CString &PIN, CEmployeeData & oEmployee)
{
	ReadWriteToFile read;
	std::vector<CEmployeeData> employeesData;
	read.GetDataFromFile(employeesData, eFileMode_showAll);

	for (int employeeCount = 0; employeeCount < employeesData.size(); employeeCount++)
	{
		if (employeesData[employeeCount].strPIN == PIN)
		{
			oEmployee = employeesData[employeeCount];
			employeeCount = employeesData.size();
		}
	}
}

void CHumanResourcesDoc::GetEmployeesData(std::vector<CEmployeeData> & employeesData, FileMode eMode)
{
	ReadWriteToFile read;
	read.GetDataFromFile(employeesData, eMode);

}



BOOL CHumanResourcesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CHumanResourcesDoc serialization

void CHumanResourcesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CHumanResourcesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CHumanResourcesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHumanResourcesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CHumanResourcesDoc diagnostics

#ifdef _DEBUG
void CHumanResourcesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHumanResourcesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CHumanResourcesDoc commands
