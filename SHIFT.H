




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// Shift Object - standard shift encoder



class CShift : public CSpan

{

DECLARE_SERIAL(CShift)

private:



CString codeletter;


protected:


public :



CShift();
~ CShift();
CShift(const CTimeSpan,const CTimeSpan,const CString);

CString getletter(void);

CObject* clone(void);

virtual void Serialize(CArchive& ar);


// encapsulates standard shift data. Also provides serialisation






};





