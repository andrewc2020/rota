



 




class CRegularPeriod;
class CTimelist;
class CContract;



class CPeriodlist : public CObList
{
DECLARE_SERIAL(CPeriodlist)

private:

CRegularPeriod* pPd;
void Recover(CRegularPeriod* pPd);


protected:



 
public:
	LRESULT DeleteWeekless(void);

//constructor

CPeriodlist();

~CPeriodlist();






BOOL Add(const CTime,CTimelist*,CPeriod*, const long);
BOOL CreditConhrs(CContract*);
BOOL CreditCompensator(CContract* ,CObList& );
BOOL Removeall(void);


void login(const DWORD , CTimelist* );
void docket(const CTime ,CAbsolutePeriod , const UINT, const int );
BOOL Deleteitem(CObject*, BOOL warnings = TRUE);


};


