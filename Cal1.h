




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// CCalendar Object
//forward declaration


class CPeriod;

class CAbsolutePeriod;
class CTimelist;
class CPeriodlist;
class CCalendar;
class Calstate;
class CBitvector;
class CDaoDatabase;


class CCalendar : public CObject

{

 
private:
CTime m_BASE_DATE;
UINT m_copyshowing;
CPoint m_content_org;





long getdayoffset(void);
long getweekoffset(void);






Calstate* pCalstate;
CMapWordToOb* Calendar_options;

 
struct Offset{
public:
UINT m_WeekFrag;
UINT m_DayFrag;
long fourweekoffset;
long weekoffset;
long dayoffset;


};

Offset* pOffset;


struct Budget_state {
public:
enum Transaction content;
BOOL Is_Cummulative;
};

Budget_state* pBudget_state;



CAbsolutePeriod* m_currentperiod;
CAbsolutePeriod* m_currentfourweek;
CAbsolutePeriod* m_currentyear;

public:



CCalendar::CCalendar(CTime);

CCalendar::~CCalendar();

void set_special_format(CWnd*);
void restore_special_format(CWnd*);

/* Calendar offset data retrieval (days etc from base date)*/ 

long getfourweekoffset(void);
long get_days_into_period(void);
long GetTotalOffset(void);
/* Calendar Budget data retrieval*/
enum Transaction GetBudgetState(void);
BOOL Is_Budget_Cummulative(void);
CString set_totals_heading(CString,CView* handle=NULL);

/* Calendar state data retrieval & setting */
UINT Getstate(void);
void SetBudgetcontent(const Transaction);
void SetBudgetCummulative(const BOOL);
CTime GetBaseDate(void);
BOOL Is_shortperiod(void);
int GetcurrentDayOfWeek(void);
void setrepeater(CBitvector&);

/* amend balances according to date viewed */

void docket(CPeriodlist*, CTimelist*);

BOOL EditBank(CDaoDatabase& , CTimelist* , CPeriodlist*);

void OnPrepareDC(CDC*);
CString set_column_heading(CAbsolutePeriod&, CString& );
CPoint GetContentOrg(void);
void ResetBasedate(CTime basedate);
void DrawMe(CPeriod*,CRect&, CDC*);
CString Getday(const long);
CString Getcurrent_startstring(void);
CString Getcurrent_finishstring(void);
CString Getcurrent_near_finishstring(void);
CAbsolutePeriod GetCurrentPeriod(void);
CString Get_fwkweek(void);
void getcurrentweek(long&);
BOOL print(CView*,CDC* pDC,CTimelist*,CPeriodlist*);
void display(CView*,CDC*, CTimelist*,CPeriodlist*);
void OnCalendarYear();
void OnUpdateCalendarYear(CCmdUI* pCmdUI);
void OnFourweek(const long);
void OnUpdateFourweek(CCmdUI* pCmdUI);

void OnWeekOne(void);
void OnUpdateWeekOne(CCmdUI* pCmdUI);
void OnWeekTwo(void);
void OnUpdateWeekTwo(CCmdUI* pCmdUI);
void OnWeekThree(void);
void OnUpdateWeekThree(CCmdUI* pCmdUI);
void OnWeekFour(void);
void OnUpdateWeekFour(CCmdUI* pCmdUI);
void OnBudgetCredit(void);
void OnBudgetDebit(void);
void OnBudgetBalance(void);
void OnBudgetCummulative(const BOOL);
void OnDayMonday(void);
void OnUpdateDayMonday(CCmdUI* pCmdUI);   
void OnDayTuesday(void);
void OnUpdateDayTuesday(CCmdUI* pCmdUI); 
void OnDayWednesday(void);
void OnUpdateDayWednesday(CCmdUI* pCmdUI); 
void OnDayThursday(void);
void OnUpdateDayThursday(CCmdUI* pCmdUI);
void OnDayFriday(void);
void OnUpdateDayFriday(CCmdUI* pCmdUI);
void OnDaySaturday(void);
void OnUpdateDaySaturday(CCmdUI* pCmdUI);
void OnDaySunday(void);
void OnUpdateDaySunday(CCmdUI* pCmdUI);          
void OnUpdateViewFormatHrs(CCmdUI* pCmdUI);
void OnUpdateViewFormatStartfinish(CCmdUI* pCmdUI);
void OnUpdateViewFormatBlockgraph(CCmdUI* pCmdUI);
void OnUpdateBudgetCurrentCredit(CCmdUI* pCmdUI);
void OnUpdateBudgetCurrentDebit(CCmdUI* pCmdUI);
void OnUpdateBudgetCurrentBalance(CCmdUI* pCmdUI);
void OnUpdateBudgetCummulativeCredit(CCmdUI* pCmdUI);
void OnUpdateBudgetCummulativeDebit(CCmdUI* pCmdUI);
void OnUpdateBudgetCummulativeBalance(CCmdUI* pCmdUI);
#ifndef STANDALONE
void OnFileUpdatedatabase(CLog&,CTimelist*,CPeriodlist*);
#endif
};

/////////////////////////////////////////////////////////////////////////////
