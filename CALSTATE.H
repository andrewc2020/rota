




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// Calstate Object
//forward declaration


class CPeriod;

class CAbsolutePeriod;
class CTimelist;
class CPeriodlist;
class CCalendar;

class Calstate : public CState

{

private:

virtual void display(CView* ,
			 CDC*,
			 CTimelist* ,
			 CPeriodlist*,CAbsolutePeriod&);
virtual CString set_column_heading(CAbsolutePeriod&, CString& );


protected:

CCalendar* calendar;

 
CSize bigdiv;
UINT m_divisions;
UINT m_subdivisions;
UINT m_offset;
CTimeSpan m_div_span;
CTimeSpan m_sub_div_span;

public:

Calstate();

~ Calstate();

//virtual UINT Getstate(void);
void set_calendar_ptr(CCalendar*);

virtual void display(CView* ,
			 CDC*,
			 CTimelist* ,
			 CPeriodlist*);
virtual BOOL print(CView*,
			CDC* ,
			CTimelist*,
			CPeriodlist*);
virtual void DrawMe(CPeriod*,CRect&, CDC*);
virtual void OnPrepareDC(CDC*);
};





