// absolute.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CAbsolutePeriod 


class CAbsolutePeriod : public CObject
{   
	DECLARE_DYNAMIC(CAbsolutePeriod)
private:

CTimeSpan m_start;
CTimeSpan m_duration;
CTime Getnearestmonday(const CTime anydate);

protected:

CTime m_absolute_midnight;			




// Attributes
public:  
CTime Get_start_time(void);
void getpriormonday(void);
void getnextmonday(void);

virtual CTimeSpan getduration(CAbsolutePeriod, CTimeSpan);
CTimeSpan getduration(void);

// Constructors
public:
   CAbsolutePeriod(void);// default base date
   CAbsolutePeriod(const CTime);
   CAbsolutePeriod(const CAbsolutePeriod& ); 
   CAbsolutePeriod(const CTime,const long,const long);
   CAbsolutePeriod(const CTime,const long,const long,const CTimeSpan);
   CAbsolutePeriod(const CAbsolutePeriod& , const CTimeSpan, const CTimeSpan);
   //CAbsolutePeriod(const CAbsolutePeriod , const CTimeSpan, const CTimeSpan);
   CAbsolutePeriod(const CTime, const CTimeSpan, const CTimeSpan);
   
   
   
   
//   Destructor
  
	~CAbsolutePeriod();
	
  //Other member functions
	
	/* 1. Information on m_absolute_midnight */
	
	virtual  int GetDay(void);
	    
	virtual  CString GetDayStr(void);
	    
	virtual	int GetDayOfWeek(void);
		
			
	virtual	int Getmonth(void);
		
	virtual	int Getyear(void);
		
	virtual	int Sun2Mon(int);
		
	virtual	long count_days(void);
		
	virtual	long gettotalstartmins(void);
	virtual	long gettotaldurmins(void);
	virtual long getstartoffset(const CTime);
	virtual long getfinishoffset(const CTime);
		
		
		
		//operators
 virtual void operator =(const CAbsolutePeriod&);
 virtual void operator +=(const CTimeSpan);
 virtual void operator -=(const CTimeSpan );
 virtual void operator ++(void);
 virtual void operator ++(int);
 virtual void operator --(void);
 virtual BOOL operator >=(const CAbsolutePeriod&);
 virtual BOOL operator <=(const CAbsolutePeriod&);
 virtual long operator /(const int denominator);
 //virtual void operator /(const int);
 virtual void operator *(const int multiple);
		
		
	///range finding methods
		
virtual BOOL IsWithinPeriod(CAbsolutePeriod);
	
		
		
		//Reset methods
		
virtual	void ResetPeriod(const int);
virtual	void ResetPeriod(const CTime,const long, const int);
virtual void ResetPeriod(const CAbsolutePeriod& );
virtual void ResetPeriod(const CTime, const CTimeSpan, const CTimeSpan);
virtual void ResetPeriod(const CTime,const long ,const long );
virtual void ResetPeriod(const CAbsolutePeriod&, const CTimeSpan, const CTimeSpan ); 
virtual void ResetPeriod(const CTimeSpan,const CTimeSpan);

	    //print methods
	    
virtual CString Get_start_string(void);
virtual CString Get_start_string(const CString);
virtual CString Get_finish_string(const CString);
virtual CString Get_near_finish_string(void);// returns end of last day
virtual CString Get_near_finish_string(const CString);// returns end of last day use date only format
virtual CString Get_finish_string(void);

virtual CString Get_absolute_start(void);
virtual CString Get_absolute_finish(void);
virtual CTime Get_absolute_starttime(void);
virtual CTime Get_absolute_finishtime(void);
virtual CTime Get_absolute_midnight(void);

		// rota info


virtual long Get_rota_num(const CTime); 
		
// Implementation

#ifdef _DEBUG 
virtual void Dump(CDumpContext& ) const;
#endif
	

};

/////////////////////////////////////////////////////////////////////////////
