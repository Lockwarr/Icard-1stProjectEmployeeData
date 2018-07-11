
// HumanResourcesDoc.h : interface of the CHumanResourcesDoc class
//


#pragma once

#include "Structures.h"
#include "EnumDialogMode.h"
#include "EnumFileMode.h"

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

	BOOL AddToFile(const CEmployeeData& oEmployee);
	BOOL FilterBy(CString filter, DialogMode eMode);
	void EditFile(CEmployeeData & oEmployee, int selectedRow);
	void ViewEmployee(CEmployeeData & oEmployee, CString pin);
	void PrintEmployeeData(CString &PIN, CEmployeeData & oEmployee);
	void GetEmployeesData(std::vector<CEmployeeData>& employeesData, FileMode eMode);
	void DeleteEmployee(CString employeePIN);
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

	std::vector<CEmployeeData> m_allEmployees;

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};








