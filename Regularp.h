// regularp.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CRegularPeriod debit time object

class CPeriod;

class CTimelist;
class CShift;
class CBitvector;



//Global declarion




class CRegularPeriod : public CPeriod 
{   

DECLARE_SERIAL(CRegularPeriod)

// Attributes

private:

BOOL amend_start(CSpan*);


protected:
CTimeSpan m_balance;
CObArray* m_dayarray;
virtual UINT GetImage(void);
virtual void Clearbalance(void);

public:
	virtual LRESULT SetFromToPositionToCredit(const int, const long);
	virtual BOOL IsClearWeeks(void);
	CRegularPeriod();
	CRegularPeriod(						
					CObArray*,
					const long,
					const long,
					CPeriod*,
					CPeriod*
					);  
/* caution; builds object for testing purposes only - eg clash test 
destroy immediately after use in test do not add to data list */ 
 
    CRegularPeriod(
    				
    				CObArray*,
    				const long,
    				const long,
    				CPeriod*
    				);  

    				
/* Clone can produce exact clone (for export only in multidocument use case) 
	or copy an object to another account. */ 
	   				
virtual CObject* Clone(CPeriod*); // assigns clone to new parent and parents uncle
virtual CObject* Clone(void);
virtual void setid(void);
virtual CObject* split(void);    				
virtual	BOOL docket(const CTime, CAbsolutePeriod , const UINT, const int );
virtual long getbalance(void);
void ResetPeriod(CTimeSpan,CTimeSpan);
virtual	BOOL Edit(const CTime,const long weekstart);
//virtual BOOL move(void);     
virtual BOOL IsRecoverable(void);
virtual BOOL  IsWithin(const CTimeSpan , const CTimeSpan , const int );
virtual BOOL Overwrite(CAbsolutePeriod& );
#ifdef _DEBUG 
	virtual void Dump(CDumpContext& ) const;
#endif
    virtual ~CRegularPeriod(); 
    void Serialize(CArchive& ar);
    void login(const DWORD , CTimelist*,const BOOL );
   virtual BOOL showmenu(CView*, const CPoint&); 
   virtual BOOL proxydocket(const CTime , CAbsolutePeriod ,const UINT , const int , const BOOL );
   virtual BOOL IsEventfulDay(const UINT dayofweek);							   
   virtual BOOL Clashes(CRegularPeriod&);
   virtual BOOL Clashes(CRegularPeriod&,const UINT);
   virtual BOOL IsToil(const UINT);
   virtual BOOL IsCheckable(void);
   virtual BOOL dayshared(CRegularPeriod&);
   virtual BOOL dayshared(CRegularPeriod&,const UINT);
   virtual void fillvector(CBitvector&); //returns empty vector
  
	
};

/////////////////////////////////////////////////////////////////////////////
