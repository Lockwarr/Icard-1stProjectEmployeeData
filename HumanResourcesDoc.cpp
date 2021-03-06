
// HumanResourcesDoc.cpp : implementation of the CHumanResourcesDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#endif

#include "HumanResourcesDoc.h"

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
	std::vector<EMPLOYEE_DATA> employeeData;

	//getting employees data from the file containing all emplyoees
	if (read.GetDataAndDeleteEmployee(employeeData, employeePIN))
	{
		AfxMessageBox(_T("There is no data available in the file!"));
	}
	else
	{
		read.ReWriteFile(employeeData);
	}

}

BOOL CHumanResourcesDoc::AddEmployee(const EMPLOYEE_DATA& oEmployee)
{
	ReadWriteToFile readWrite;
	std::vector<EMPLOYEE_DATA> employeesData;
	readWrite.GetDataFromFile(employeesData);
	for (int i = 0; i < employeesData.size(); i++)
	{
		if (employeesData[i].strPIN == oEmployee.strPIN)
		{

			AfxMessageBox(_T("Employee with this PIN already exists!"));
			return 0;
		}
	}
	if (readWrite.WriteToFile(oEmployee))
	{
		AfxMessageBox(_T("Employee added successfully!"));
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL CHumanResourcesDoc::ClearAll()
{
	ReadWriteToFile clear;
	clear.RemoveAll();
	return TRUE;
}
BOOL CHumanResourcesDoc::FilterBy(std::vector<EMPLOYEE_DATA> & filteredEmployees, CString filter, FilterMode eMode)
{
	ReadWriteToFile write;
	std::vector<EMPLOYEE_DATA> employeesData;
	int filteredEmployeesSizeCount = 1;
	int filteredEmployeesIndexCounter = 0;

	write.GetDataFromFile(employeesData);

	//Check for coincidencess
	if (eMode == eFilterMode_ByName) {
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
	else if (eMode == eFilterMode_ByDate)
	{
		for (int i = 0; i < employeesData.size(); i++)
		{
			if (filter == employeesData[i].strDate)
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
	return TRUE;
}

void CHumanResourcesDoc::EditEmployee(EMPLOYEE_DATA & oEmployee, CString& strPIN)
{

	ReadWriteToFile readWrite;
	std::vector<EMPLOYEE_DATA> employeesData;

	//getting data from file which contains all employees
	readWrite.GetDataAndEditEmployee(employeesData, strPIN);
	readWrite.ReWriteFile(employeesData);

}

void CHumanResourcesDoc::LoadEmployee(EMPLOYEE_DATA & oEmployee, const CString& PIN)
{
	PrintEmployeeData(PIN, oEmployee);
}

void CHumanResourcesDoc::PrintEmployeeData(const CString &PIN, EMPLOYEE_DATA & oEmployee)
{
	ReadWriteToFile read;
	std::vector<EMPLOYEE_DATA> employeesData;
	read.GetDataFromFile(employeesData);

	for (int employeeCount = 0; employeeCount < employeesData.size(); employeeCount++)
	{
		if (employeesData[employeeCount].strPIN == PIN)
		{
			oEmployee = employeesData[employeeCount];
			employeeCount = employeesData.size();
		}
	}
}

void CHumanResourcesDoc::GetEmployeesData(std::vector<EMPLOYEE_DATA> & employeesData)
{
	ReadWriteToFile read;
	read.GetDataFromFile(employeesData);

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
