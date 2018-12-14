




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// Daystate Object
//forward declarations


class CPeriod;

class CAbsolutePeriod;
class CTimelist;
class CPeriodlist;
class Calstate;

class CDaystate : public Calstate
{

private:





protected:

CString set_column_heading(CAbsolutePeriod&, CString& );


virtual void OnPrepareDC(CDC*);


public:

CDaystate();
 
~CDaystate();




};


