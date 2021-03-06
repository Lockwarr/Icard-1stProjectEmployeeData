
// HumanResourcesDoc.h : interface of the CHumanResourcesDoc class
//


#pragma once

#include "Structures.h"
#include "EnumDialogMode.h"
#include "ReadWriteToFile.h"
#include "HumanResources.h"



#include <propkey.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>


#include <vector>

class CHumanResourcesDoc : public CDocument
{
protected: // create from serialization only
	CHumanResourcesDoc();
	DECLARE_DYNCREATE(CHumanResourcesDoc)

// Attributes
public:

// Operations
public:

	BOOL AddEmployee(const EMPLOYEE_DATA& oEmployee);
	BOOL ClearAll();
	void EditEmployee(EMPLOYEE_DATA & oEmployee, CString& strPIN);
	void LoadEmployee(EMPLOYEE_DATA & oEmployee,const CString& pin);
	void PrintEmployeeData(const CString &PIN, EMPLOYEE_DATA & oEmployee);
	void GetEmployeesData(std::vector<EMPLOYEE_DATA>& employeesData);
	void DeleteEmployee(CString employeePIN);
	BOOL FilterBy(std::vector<EMPLOYEE_DATA> & employeesData, CString filter, FilterMode eMode);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
#ifdef _DEBUG

	virtual ~CHumanResourcesDoc();
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;



#endif

private:

protected:

	DECLARE_MESSAGE_MAP()
public:

	std::vector<EMPLOYEE_DATA> m_allEmployees;

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};








