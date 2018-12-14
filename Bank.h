// bank.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CContract account


class CBank : public CContract
{   
	DECLARE_SERIAL(CBank)

	class CCalendar;

public:

	CBank();		//	constructor used by dynamic creation

// Attributes

    virtual ~CBank();
private:

CString m_tempno;
long m_tempID;  			
 

public:

   			
   			
CBank(const CString,       
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
	virtual BOOL EditBank(void);
	virtual BOOL RestoreContractNo(void);
  	virtual UINT GetImage(void);// custom folder icon
	virtual BOOL IsBank(void);
	virtual void get_contracts_held_by(const long, CObList&);
   	BOOL IsConflict(CObList&, const CTime, const long);
  	
};

/////////////////////////////////////////////////////////////////////////////
