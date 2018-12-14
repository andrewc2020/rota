// heading.h : header file
//

#define STANDALONE
/////////////////////////////////////////////////////////////////////////////
// CHeading command target
#include <afxwin.h>
#include <afx.h>


class CPeriod;
class CTimelist;
class CCategory;

class CHeading : public CCategory
{   
	DECLARE_SERIAL(CHeading)
protected:
	

// Attributes
public:





// Operations
public:
   CHeading();			// protected constructor used by dynamic creation	
   CHeading(const CString,CPeriod*,CPeriod*);

   #ifndef STANDALONE
   virtual CTimelist* Add(CTimelist*,CDaoDatabase&,const long,const long);
   #endif

   CTimelist* Add(CTimelist*,const long,const long); 
   virtual void set_all_relative(void);
   virtual BOOL showmenu(CView*, const CPoint&);
   BOOL shareuncle(void);
   BOOL load_codes(void);
   virtual BOOL CanAddChildren(void);
   virtual BOOL file_codes(const BOOL storing);
   virtual void Serialize(CArchive& ar); 
   virtual void Get_uncle_colour(void);
// Implementation
public:
	virtual ~CHeading();

protected:

};

/////////////////////////////////////////////////////////////////////////////
