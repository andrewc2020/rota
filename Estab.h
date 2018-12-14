// contract.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CContract account

	
class CDaoDatabase;
class CContract;
class CEstab : public CContract
{   
	DECLARE_SERIAL(CEstab)



public:

	CEstab();		//	constructor used by dynamic creation

// Attributes

    virtual ~CEstab();
private:
	LRESULT FillWithNewStaffOnRota(CDaoRecordset*& recordset ,CObList*& list);

  			
CTimelist* AddEstab(CString,// name
				CTimelist*,// parent
				const long,// from
				const long,// to
				const CString,// contract number
				const long ID,
				const CString package,// Terms and conditions
				const double conhrs); // weekly hours




BOOL ContainsNoContract(void); 

public:
	virtual LRESULT SubstituteConID(CDaoDatabase& db, const CTime endrota, const long days_into_period);
	
	LRESULT GetExtraProv(CContract*&);
	LRESULT ClearBudget(CPeriodlist*&);
	LRESULT Get_not_catered_for(CObList&,double&);
	
	LRESULT SetTCSPackage(const CString);
	LRESULT SetBudget(const double);

   			
   			
CEstab(const CString,       
   			CPeriod*,
   			CPeriod*,
   			const long,
   			const long,
   			const CString contractno,
   			const long ID,
   			const CString package,
			const double conhrs
   			); 
   			   			
   	CTimelist* EstabStarter(const CTime);
   	 
   	virtual BOOL CanCutandPaste(const UINT);		
   	virtual COLORREF getcolour(void);
	
   /* method to add a contract */

CTimelist* AddBank(CString,// name
				CTimelist*,// parent
				const long,// from
				const long,// to
				const CString,// contract number
				const long ID,
				const CString package,// Terms and conditions
				const double conhrs); // weekly hours

CTimelist* AddExtraProvision(CString,// name
				CTimelist*,// parent
				const long,// from
				const long,// to
				const CString,// contract number
				const long ID,
				const CString package,// Terms and conditions
				const double conhrs); // weekly hours
  			
CTimelist* Add(CString,// name
				CTimelist*,// parent
				const long,// from
				const long,// to
				const CString,// contract number
				const long ID,
				const CString package,// Terms and conditions
				const double conhrs, // weekly hours
				BOOL IsManual=FALSE); // when adding from dialog

  virtual void Addbeforebank(CObject*); //sites new contract in list

/* method to discover contracts held by same staff member. */
 virtual void get_contracts_held_by(const long, CObList&);

/* method to get contracts other than those with current ID */

 virtual LRESULT get_staff_bar_this_one(const long, CObList&);
 /* clash test methods */
 virtual BOOL Does_Clash_From_Top(CObList*,CContract*);
 virtual CObject* Clone(void);
 virtual BOOL prioritise(const CTime , CAbsolutePeriod , const UINT trans_type, const int , BOOL&);

	
	virtual BOOL EditBank(CDaoDatabase& db, const CTime, const long);
	virtual BOOL RestoreContractNo(void);
	virtual BOOL IsEstablishment(void);	
   	virtual UINT GetImage(void);// custom folder icon	
   	virtual BOOL showmenu(CView*, const CPoint&);//overidden menu	
   	virtual BOOL ContainsNoEstab(void);
	 /*overridden to prevent sub headings */

	virtual void print(const CTime,CAbsolutePeriod ,CDC*);
protected:    
 
   virtual BOOL displaydata(const CRect*,CDC*, CView* );// to break up summary
   
  
   
  
};

/////////////////////////////////////////////////////////////////////////////
