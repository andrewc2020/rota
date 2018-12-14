




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// Span Object - relative interval

class CPeriod;

class CSpan : public CObject

{

DECLARE_SERIAL(CSpan)

private:


CTimeSpan m_start;
CTimeSpan m_duration;







protected:







public :
	void dur_as_decimal(double&);



CSpan();
~ CSpan();
CSpan(const CTimeSpan,const CTimeSpan);
CSpan(CSpan*);
CSpan(const CTimeSpan,const double);
CTimeSpan getstart(void);
CTimeSpan getduration(void);
void setstart(const CTimeSpan);
void setduration(const CTimeSpan);
virtual int GetFirstBalance(void);
virtual CObject* clone(void);
BOOL IsWithin(const CTimeSpan, const CTimeSpan);
virtual void Serialize(CArchive& ar);
virtual void operator +=(const CTimeSpan);
virtual void operator -=(const CTimeSpan );
virtual void operator +=(CSpan*);
virtual void operator -=(CSpan*);
virtual void operator -=(const double);
virtual BOOL operator ==(CSpan*);

virtual long getbalance(void);
virtual void ResetPeriod(CSpan&);
virtual void ResetPeriod(CSpan*);
virtual void ResetPeriod(const CTimeSpan, const CTimeSpan);

//conversion utilites
void decimal_to_time(const double , CTimeSpan&);


};





