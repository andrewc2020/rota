




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// Calstate Object
//forward declaration




class CState : public CObject

{

private:




protected:

UINT ID;



public:

CState();
CState(const UINT);

~ CState();
// called by view when updating visual representations of state
// e.g checks on menu items

virtual UINT Getstate(void);
virtual BOOL Is_state(const UINT&);

// called by view or parent states
// when gap between view and object state arises or has been eliminated

virtual void InvalidateRect(CRect* to_be_painted);



};





