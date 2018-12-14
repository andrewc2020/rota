// debit.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CDebitPeriod debit time object

class CPeriod;

class CTimelist;
class CBitvector;


//Global declarion


class CDebitPeriod : public CRegularPeriod
{   
DECLARE_SERIAL(CDebitPeriod)

// Attributes

private:
	

BOOL m_IsFixed;
CTime m_basedate;
CBitvector* m_weekvector;
CBitvector* m_drpvector;
protected:
virtual BOOL  IsWithin(const CTimeSpan , const CTimeSpan , const int );
virtual BOOL proxydocket(const CTime , CAbsolutePeriod ,const UINT , const int , const BOOL );

public:
	virtual void ClearWeeks(void);
	virtual BOOL IsClearWeeks(void);
	virtual LRESULT SetFromToPositionToCredit(const int, const long);
	CDebitPeriod();
	CDebitPeriod(
					CBitvector*,
					CBitvector*,
					CObArray*,
					const long,
					const long,
					CPeriod*,
					CPeriod*,
					const BOOL,
					const CTime
					);  

/* caution; builds object for testing purposes only - eg clash test 
destroy immediately after use in test do not add to data list */ 
 
    CDebitPeriod(
    				CBitvector*,
					CBitvector*,
    				CObArray*,
    				const long,
    				const long,
    				CPeriod*,
					const BOOL,
					const CTime
    				);  
 
 
virtual BOOL showmenu(CView*, const CPoint&);  
virtual CObject* Clone(void); 
void Serialize(CArchive& ar);    				
virtual BOOL docket(const CTime, CAbsolutePeriod , const UINT , const int);
virtual BOOL Edit(const CTime,const long weekstart); 
virtual BOOL Clashes(CRegularPeriod&);
virtual BOOL Clashes(CRegularPeriod&,const UINT);
virtual BOOL IsToil(const UINT);
virtual BOOL IsCheckable(void);
virtual BOOL dayshared(CRegularPeriod&);
virtual BOOL dayshared(CRegularPeriod&,const UINT);
virtual BOOL IsEventfulDay(const UINT dayofweek);
virtual void fillvector(CBitvector&); 
void Fix(const BOOL);
CTime getbasedate(void);

#ifdef _DEBUG 
	virtual void Dump(CDumpContext& ) const;
#endif
    virtual ~CDebitPeriod(); 
    
   
	
};

/////////////////////////////////////////////////////////////////////////////
