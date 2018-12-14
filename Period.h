// period.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CPeriod Object

//// Global constants
class CLog;
class CSpan;
class CAbsolutePeriod;

class CPeriod : public CSpan
{   
	DECLARE_SERIAL(CPeriod)
private:

COLORREF colour;
DWORD id;
BOOL drpstatus;
CString name;
CRect* box;
long m_from_position;
long m_to_position; 


protected:
	
	virtual void resetcolour(void);

	virtual void Serialize(CArchive& ar);
    
    virtual CPeriod* GetOtherRelative(const CPeriod* caller); 
    virtual BOOL Restore_Uncle( CPeriod*);
    virtual void picture(CRect* , CView* );
    virtual UINT GetImage(void);
    
    // Attributes
    
    
	
	
	
	BOOL is_open;
	
	CPeriod* parent;
	CPeriod* uncle;

public:

   CPeriod(void);
	~CPeriod(void);
	CPeriod(const CTimeSpan&, const CTimeSpan&,CPeriod*,CPeriod*);
	CPeriod(const CTimeSpan& start, const CTimeSpan& duration, const long, const long,CPeriod*,CPeriod*);
    virtual void setbox(const CRect*);
	virtual void SetDRPstatus(const BOOL);
	virtual BOOL GetDRPstatus(void);
	virtual void Clearbalance(void);

    #ifdef _DEBUG 
	virtual void Dump(CDumpContext& ) const;
	#endif 
	virtual BOOL CanCutandPaste(const UINT);
	virtual void setid(void);
    virtual void resetid(void);
	virtual void setid_direct(const DWORD newid); 
	virtual WORD GetIndex(void);
	virtual DWORD get_id(void);
    virtual BOOL Edit(const CTime);
    virtual BOOL showmenu(CView* , const CPoint& ); 
    virtual BOOL display(const CTime,CAbsolutePeriod,CDC*,CView*);
    virtual BOOL displaydata(const CRect*,CDC*, CView* );
	virtual BOOL displaysum(const CRect* , CDC* ,CView* );
	virtual void print(const CTime,CAbsolutePeriod,CDC*);
    virtual void setboxempty(void); 
    virtual CString Getname(void);
	virtual CString Getbriefname(void);
	virtual int GetFirstBalance(void);
    virtual void Setname(const CString);
    virtual long GetFromToPosition(const int flag);
    virtual void SetFromToPosition(const int flag,const long value);
    virtual BOOL CheckAddresses(void);
    virtual CPeriod* Getuncle(void);
    virtual BOOL datalogin(CObject* );
	virtual BOOL datalogout(CObject*);
	virtual CPeriod* Getparent(void);
	virtual CPeriod* Getultiparent(void);
	virtual void set_uncle(CPeriod*);
	virtual BOOL Is_uncle(const CPeriod*);
	virtual void Get_uncle_colour(void); 
	virtual COLORREF getcolour(void);
	virtual CRect* getbox(void);
	virtual int getboxWidth(void);
	virtual CPeriod* GetStaff(void);
	virtual BOOL IsWithin(const long, const long);
	virtual CObject* Clone(void);
    virtual void setcolour(COLORREF);
	#ifndef STANDALONE
    virtual void UpdateDatabase(CLog&, CString, const long, const CString,  CAbsolutePeriod);
	#endif
	void SetTracker(CDC* pDC, const int style);
	
};

/////////////////////////////////////////////////////////////////////////////
