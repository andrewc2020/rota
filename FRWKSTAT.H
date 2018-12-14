




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// fourweekstate Object
//forward declarations


class CPeriod;

class CAbsolutePeriod;
class CTimelist;
class CPeriodlist;
class Calstate;

class CFourweekstate : public Calstate
{

private:





protected:

CString set_column_heading(CAbsolutePeriod&, CString& );


virtual void OnPrepareDC(CDC*);


public:



CFourweekstate();
 
~CFourweekstate();



};


