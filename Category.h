// category.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCategory command target

class CShift;

class CCategory : public CTimelist
{   
	DECLARE_SERIAL(CCategory)
	
private:
CString table_ID;


protected:

CObList* m_codelist;

	CCategory();			// protected constructor used by dynamic creation
virtual WORD GetIndex(void);
virtual WORD GetIndent(void);
virtual void setid(void);
virtual void shareuncle(CPeriod*);


BOOL Is_dupe(CShift*);

BOOL Is_relative;


public:
CCategory(const CString,CPeriod*,CPeriod*); // constructor for user created
											// categories i.e not from database
											
CCategory(const CString,CPeriod*,CPeriod*,const CString); 
virtual ~CCategory();
#ifdef _DEBUG
virtual void Dump(CDumpContext& ) const;
#endif


virtual void set_relative_id(const UINT);
virtual void set_all_relative(void);
virtual void Get_uncle_colour(void);
virtual void setcolour(void);
virtual void resetcolour(void);
virtual CString Getcode(CSpan*);
virtual CString Getdlgcode(CSpan*);
virtual CString Getcodestring(CSpan*, CComboBox&);
virtual void Getcodelist(CObList*&);
virtual BOOL Setcodelist(CObList*);
virtual BOOL codelistUpdateable(void);
virtual BOOL IncrementNonstandard(CString&);
BOOL Addshift(CObject*& );
BOOL Delshift(CObject*);
virtual BOOL fillbox(CComboBox*& ,CPeriod* parent=NULL);
int IsDupeCode(const CString); // returns index of existing code
virtual int FindSpan(CSpan*,CComboBox&);	// selects index of existing span
virtual BOOL codelistIsActive(void);
virtual BOOL codelistEmptyOrInActive(void);
virtual CTimelist* Add(CTimelist*,const long,const long); 
virtual void set_uncle_id(void);
virtual BOOL Restore_Uncle(CPeriod* uncptr);
virtual CString get_table_ID(void);
virtual BOOL showmenu(CView*, const CPoint&);
virtual void Serialize(CArchive& ar);
virtual BOOL Addcodes(void);
virtual BOOL Is_Catview(void);
virtual BOOL CanAddChildren(void);
virtual BOOL Deleteitem(CTimelist*,CPeriodlist*);
virtual BOOL Edit(const CTime);
virtual BOOL Overwrite(CRegularPeriod*,CAbsolutePeriod&);
};

/////////////////////////////////////////////////////////////////////////////
