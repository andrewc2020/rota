// gensup.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CGensup command target
class CShift;
class CCategory;

class CGensup : public CCategory
{   
	DECLARE_SERIAL(CGensup)

private :



CShift* m_shift;



protected:
	CGensup();			// protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
   CGensup(const CString, CPeriod*,CPeriod*);
   CGensup(const CString, CPeriod*,CPeriod*,const CString);
// Implementation
public:
	virtual ~CGensup(); 
    virtual BOOL IncrementNonstandard(CString&);
	virtual CString Getcode(CSpan*);
	virtual CString Getdlgcode(CSpan*);
    #ifdef _DEBUG 
	virtual void Dump(CDumpContext& ) const;
	#endif
    virtual CTimelist* Add(CString ,
						CTimelist*,
						const long from,
						const long to,
						const CString table_id);

 	virtual BOOL Addcodes(void);
	virtual void Serialize(CArchive& ar);
	virtual BOOL Setcodelist(CObList*);
   };

/////////////////////////////////////////////////////////////////////////////
