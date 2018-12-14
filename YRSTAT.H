




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// Calstate Object
//forward declaration


class CPeriod;

class CAbsolutePeriod;
class CTimelist;
class CPeriodlist;
class Calstate;

class CYearstate : public Calstate
{

private:





protected:

CString set_column_heading(CAbsolutePeriod&, CString& );

virtual void OnPrepareDC(CDC*);


public:



CYearstate();
 
~CYearstate();



};


