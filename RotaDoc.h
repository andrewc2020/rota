
// RotaDoc.h : interface of the CRotaDoc class
//


#pragma once
class CTimelist;
class CPeriodlist;

class CRotaDoc : public CDocument
{
protected: // create from serialization only
	CRotaDoc() noexcept;
	DECLARE_DYNCREATE(CRotaDoc)

// Attributes
private:
	void SetBaseDate(void);
	int GetFinYear(const CTime anydate);
public:
	CTimelist* listptr;
	CTimelist* listptr2;
	CTimelist* ptr;
	CPeriodlist* m_data;
	CObList* importptr;
// Operations
public:

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
	virtual ~CRotaDoc();
	virtual CTime GetBaseDate(void);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

private:
	CTime Getnearestmonday(const CTime anydate);
	CTime BASE_DATE;
	LRESULT AddBudget(void);
	LRESULT ResetBudget(void);
	LRESULT ClearBudget(void);
#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
