// credit.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CCreditPeriod debit time object

class CPeriod;

class CTimelist;



//Global declarion


class CCreditPeriod : public CRegularPeriod
{   
DECLARE_SERIAL(CCreditPeriod)

// Attributes

private:



protected: 

virtual BOOL proxydocket(const CTime , CAbsolutePeriod ,const UINT , const int , const BOOL );

public:
	virtual LRESULT SetFromToPositionToCredit(const int, const long);
	CCreditPeriod();
	CCreditPeriod(					
					CObArray*,
					const long,
					const long,
					CPeriod*,
					CPeriod*
					);  

/* caution; builds object for testing purposes only - eg clash test 
destroy immediately after use in test do not add to data list */ 
 
    CCreditPeriod(
    					
    				CObArray*,
    				const long,
    				const long,
    				CPeriod*
    				);  
 
 
virtual CObject* Clone(CPeriod*);
virtual UINT GetImage(void);    				
void Serialize(CArchive& ar);    				

virtual BOOL showmenu(CView*, const CPoint& );
virtual CObject* split(CObList*);
virtual CObject* split(const double);
virtual BOOL Edit(const CTime,const long weekstart);
virtual BOOL Clashes(CRegularPeriod&);
virtual BOOL Clashes(CRegularPeriod&,const UINT);
virtual BOOL IsRecoverable(void);

#ifdef _DEBUG 
	virtual void Dump(CDumpContext& ) const;
#endif
    virtual ~CCreditPeriod(); 
    

      
	
};

/////////////////////////////////////////////////////////////////////////////
