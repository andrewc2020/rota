#include <afxcoll.h>
#pragma warning(disable : 4995)



class CPeriod;
class CAbsolutePeriod;
class CRegularPeriod;
class CPeriodlist;
class CCategory;
class CLog;
class CDaoDatabase;


class CTimelist : public CPeriod
{
DECLARE_SERIAL(CTimelist)


private:



//CPoint& GetPoint(void);
CString truncate(CString );



protected:

DWORD parent_id;
CObList* m_mainlist;
CObList* m_dataptrs;
 
virtual UINT GetImage(void);
virtual int GetScrollIndex(CView*);




virtual void setopen(const BOOL);
virtual void Place(CPeriod*);
virtual void setid(void);
virtual void print(const CTime,CAbsolutePeriod ,CDC*);




public:
	
	void SetFromToPositionYouAndBelow(const int,const long);
	virtual BOOL IsExtraProv(void);

//constructor

CTimelist(void);
CTimelist(CString, CTimelist*,CTimelist*,const long,const long);
virtual CObList* Getmainlist(void);
void pop(CPeriod* placeholder,const int index);
virtual int getcount(void);
virtual BOOL Is_Root_Contract(void);
virtual BOOL IsEstablishment(void); 
virtual BOOL ContainsNoEstab(void);
virtual ~CTimelist();
virtual CPeriod* Find_AT_Index(int);
virtual CPeriod* Find_BY_Name(const CString);
virtual CPeriod* GetAt(POSITION&);
virtual CPeriod* GetNext(POSITION&);
virtual CPeriod* GetPrev(POSITION&);
void GetPrev(CObject*&);
virtual POSITION GetHeadPosition(void);
virtual POSITION GetTailPosition(void);
virtual CTimelist* GetHead(void);
virtual CTimelist* GetTail(void);
virtual int GetFirstBalance(void);
virtual void AddTail(CObList*);
virtual POSITION AddTail(CObject*);
virtual void AddTail(CTimelist* feeder, BOOL strip=TRUE);
virtual BOOL showmenu(CView*, const CPoint&); 
virtual void Serialize(CArchive& ar); 
virtual BOOL Removeall(void);
virtual CObject* Clone(void);
virtual CTimelist* Add(const CTime, const CString);
virtual void AddAll(CTimelist*,const long,const long);
virtual CTimelist* Add(CString,CTimelist*,const long,const long,const CString);
virtual CTimelist* Add(CTimelist*,const long,const long);
virtual POSITION Add(CObject*, const BOOL);// used for import export
virtual int getdisplaycount(void);
virtual BOOL prioritise(const CTime , CAbsolutePeriod , const UINT , const int, BOOL&);
virtual BOOL DeleteInstruction(CPeriod*,CPeriodlist*);
virtual BOOL Removedata(CPeriodlist* ,BOOL Warnings=TRUE);


virtual void displayall(const CTime,CAbsolutePeriod,CDC*,CView*);
virtual BOOL sum_all_data(CRect* , CDC* ,CView* );
virtual BOOL printall(const CTime,CAbsolutePeriod,CDC*,CView*);
virtual BOOL printdata(CRect* , CDC* ,CView* );
virtual BOOL printalldata(const CTime, CRect*,CAbsolutePeriod,CDC*,CView*);


#ifdef _DEBUG 
virtual void Dump(CDumpContext& ) const;
#endif

virtual void Clearbalance(void);
virtual void rebalance(void);


virtual CTimelist* getnext_indent(CTimelist*);

virtual void setboxesempty(void);
virtual BOOL datalogin(CObject* );
virtual BOOL datalogout(CObject*);

virtual BOOL Deleteitem(CTimelist*,CPeriodlist*);
virtual BOOL Edit(const CTime);
virtual BOOL displayalldata(
							const CTime,
							const CRect*,
							CAbsolutePeriod,
							CDC*,
							CView* );

virtual BOOL displayallSum(
							const CTime,
							const CRect*,
							CAbsolutePeriod,
							CDC*,
							CView* );



virtual BOOL CheckAddresses(void);
virtual BOOL has_this_uncle(const CPeriod* );
virtual BOOL Is_Catview(void);
virtual void Fill(CObList*);
virtual CTimelist* Findit(CObject*);
virtual BOOL Append(void);
virtual BOOL IsConflict(CRegularPeriod&, CPeriod*, const BOOL = FALSE);
virtual BOOL IsConflictDay(CRegularPeriod&, CPeriod*, const UINT );
virtual void restore_children(void);
virtual void flushmain(const BOOL);
virtual void flushdata(const BOOL);

virtual BOOL scoopdata(CObList*);
virtual DWORD getparent_id(void);
void doit(void (*) (void) );
virtual void setallid(void); // sets id polymorphic.
virtual void resetallid(void);
#ifndef STANDALONE
virtual void OnFileUpdateDatabase(CLog&, CString, const long, const CString, CAbsolutePeriod);
#endif
virtual CString Getcode(CSpan*);
};


