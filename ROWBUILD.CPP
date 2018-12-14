#include "stdafx.h"
#include "state.h"
#include "resource.h"
#include "rowbuild.h"
#include "CONSTANT.H"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


//rowbuild.cpp

/////////////////////////////////////////////////////////////////////////////
// Rowbuilder virtual base class of shallow_rowbuilder and deep_rowbuilder

Rowbuilder::Rowbuilder(const UINT id):CState(id)
{



}

Rowbuilder::Rowbuilder():CState()
{



}

Rowbuilder::~Rowbuilder()
{



}

void Rowbuilder::SetRow(CRect& row)
{




}

void Rowbuilder::overflow_reset(int& left_to_show)
{





}

void Rowbuilder::max_rows(int& cnt)
{




}

void Rowbuilder::fontheight(int& cnt)
{




}


/////////////////////////////////////////////////////////////////////////////
// Shallow_Rowbuilder 

Shallow_Rowbuilder::Shallow_Rowbuilder(const UINT id):Rowbuilder(id)
{




}

Shallow_Rowbuilder::Shallow_Rowbuilder():Rowbuilder()
{

 ID = ID_FORMAT_ROWSTYLE_SHALLOW;


}

Shallow_Rowbuilder::~Shallow_Rowbuilder()
{




}

void Shallow_Rowbuilder::SetRow(CRect& row)
{

 row.SetRect(0,20,row.Width(),25);


}

void Shallow_Rowbuilder::overflow_reset(int& left_to_show)
{


if(left_to_show >11){ left_to_show=11;}


}

void Shallow_Rowbuilder::max_rows(int& cnt)
{


cnt = 10;


}

void Shallow_Rowbuilder::fontheight(int& cnt)
{

 cnt = 2;


}

/////////////////////////////////////////////////////////////////////////////
// Deep_Rowbuilder

Deep_Rowbuilder::Deep_Rowbuilder(const UINT id):Rowbuilder(id)
{




}

Deep_Rowbuilder::Deep_Rowbuilder():Rowbuilder()
{


ID = ID_FORMAT_ROWSTYLE_DEEP;

}

Deep_Rowbuilder::~Deep_Rowbuilder()
{




}


void Deep_Rowbuilder::SetRow(CRect& row)
{


row.SetRect(0,20,row.Width(),30);

}


void Deep_Rowbuilder::overflow_reset(int& left_to_show)
{


if(left_to_show >6){ left_to_show=6;}


}


void Deep_Rowbuilder::max_rows(int& cnt)
{


cnt = 5;


}

void Deep_Rowbuilder::fontheight(int& cnt)
{

 cnt = 2;


}
