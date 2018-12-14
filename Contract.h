// contract.h : header file
//

#define STANDALONE

/////////////////////////////////////////////////////////////////////////////
// CContract account
class CDaoRecordset;

class CContract : public CTimelist
{   
	DECLARE_SERIAL(CContract)
public:

	CContract();		//	constructor used by dynamic creation

// Attributes

    virtual ~CContract();
private:





protected:

double m_Conhrs;
CString m_Package;
long	m_IDfrn;
CString	m_ContractNo;



// Operations
public:
	virtual BOOL FilltempConTable(CDaoRecordset*&);
	
	virtual BOOL IsExtraProv(void);
	virtual LRESULT GetExtraProv(CContract*);
	virtual LRESULT ClearBudget(CPeriodlist*&);
	void GetTCSpackage(CString&);
	virtual LRESULT Get_not_catered_for(CObList&,double&);

   			
   			
CContract(const CString,       
   			CPeriod*,
   			CPeriod*,
   			const long,
   			const long,
   			const CString contractno,
   			const long ID,
   			const CString package,
			const double conhrs
   			); 
   			   			
   	virtual void Serialize(CArchive& ar);
   	virtual BOOL CanCutandPaste(const UINT);		
   	virtual double Getconhrs(void);
   
	

   /* method to add a contract */

CTimelist* AddStarter(const CTime, CPeriodlist*&);   			
CTimelist* Add(CString,// name
				CTimelist*,// parent
				const long,// from
				const long,// to
				const CString,// contract number
				const long ID,
				const CString package,// Terms and conditions
				const double conhrs,
				BOOL IsManual= FALSE); // weekly hours

/* method to discover contracts held by same staff member. */
virtual void get_contracts_held_by(const long, CObList&);

/* method to get all bar this one */

virtual LRESULT  get_staff_bar_this_one(const long, CObList&);

/* Clash test methods */

virtual BOOL IsConflict(CRegularPeriod&, CPeriod*, const BOOL = FALSE);
virtual BOOL IsConflictDay(CRegularPeriod&, CPeriod*, const UINT);
virtual BOOL IsConflictWithOwn(CRegularPeriod&, CPeriod*,const BOOL = FALSE);
virtual BOOL Does_Clash_From_Top(CObList*,CContract*);
virtual BOOL prioritise(const CTime , CAbsolutePeriod , const UINT , const int, BOOL&);
virtual CObject* Clone(void);
/* double booking tests */

	virtual BOOL IsBank(void);
	virtual void Addbeforebank(CObject*);
	virtual BOOL EditBank(void);
	virtual BOOL RestoreContractNo(void);
	void get_contractNo(CString&);
	void set_contractNo(const CString);	
   	virtual CString get_table_ID(void);
   	virtual long get_contract_holder_ID(void);
	void get_contract_holder_ID(long);
	void set_contract_holder_ID(const long);
   	virtual BOOL showmenu(CView*, const CPoint&);//overidden menu	
   #ifdef _DEBUG 
	virtual void Dump(CDumpContext& ) const;
	#endif
   BOOL Deleteitem(CTimelist* , CPeriodlist* , const UINT );

private:


protected:    
   
   virtual BOOL displaydata(const CRect*,CDC*, CView* );// to break up summary
   #ifndef STANDALONE
   virtual void UpdateDatabase(CLog&, CString, const long, const CString,  CAbsolutePeriod); 
   #endif
   virtual BOOL Edit(const CTime basedate);
   

};

/////////////////////////////////////////////////////////////////////////////
