// bank.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CExtraProvision account


class CExtraProvision : public CContract
{   
	DECLARE_SERIAL(CExtraProvision)

	

public:

	CExtraProvision();		//	constructor used by dynamic creation

// Attributes

    virtual ~CExtraProvision();
	virtual UINT GetImage(void);// custom folder icon	

private:
	

			
 

public:
	virtual BOOL showmenu(CView*, const CPoint&);
	virtual BOOL IsExtraProv(void);
	virtual LRESULT GetExtraProv(CContract*);
	virtual LRESULT ClearBudget(CPeriodlist*&);

   			
   			
CExtraProvision(const CString,       
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
  	virtual LRESULT Get_not_catered_for(CObList&,double&);
};

/////////////////////////////////////////////////////////////////////////////
