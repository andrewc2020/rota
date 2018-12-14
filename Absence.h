/*    PortTool v2.2     Absence.h          */

/*    PortTool v2.2     Absence.h          */

/*    PortTool v2.2     Absence.h          */

// absence.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CAbsence account
class CCategory;
class CAbsence : public CCategory
{   
	DECLARE_SERIAL(CAbsence)
protected:
	CAbsence();			// protected constructor used by dynamic creation
	virtual BOOL file_codes(const BOOL storing);
// Attributes
public:


// Operations
public:
   CAbsence(const CString,CPeriod*,CPeriod*);
   CAbsence(const CString,CPeriod*,CPeriod*,const CString);
// Implementation
public:
	virtual ~CAbsence();
    virtual CTimelist* Add(CString,CTimelist*,const long,const long);
    virtual CTimelist* Add(CString,CTimelist*,const long,
    										  const long,
    										  const CString);
	virtual CString Getdlgcode(CSpan*);
	virtual CString Getcodestring(CSpan*, CComboBox&);
	virtual BOOL codelistIsActive(void);
	virtual BOOL codelistUpdateable(void);
	virtual BOOL fillbox(CComboBox*& ,CPeriod* parent=NULL);
	virtual int FindSpan(CSpan*,CComboBox&);
	virtual BOOL Overwrite(CRegularPeriod*,CAbsolutePeriod&);
    #ifdef _DEBUG 
	virtual void Dump(CDumpContext& ) const;
	#endif

};

/////////////////////////////////////////////////////////////////////////////
