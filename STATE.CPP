// daystate.cpp : implementation file
//

#include "stdafx.h"
#include "state.h"
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CState virtual base class

CState::CState():ID(0),CObject()
{




}

CState::CState(const UINT id):ID(id),CObject()
{



}

CState::~CState()
{

 

}

UINT CState::Getstate(void)
{

return ID;

}


BOOL CState::Is_state(const UINT& possible_state)
{

return ID == possible_state;

}

void CState::InvalidateRect(CRect* to_be_painted)
{

to_be_painted=NULL;	// default repaint all

}
