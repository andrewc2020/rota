// bitvector.cpp : implementation file
//

#include "stdafx.h"
#include "bitvec.h"
#include "CONSTANT.H"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "resource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CBitvector 
// uses a char as an array of up seven  boolean values

const unsigned char highbit = 1 << (CHAR_BIT -1);

IMPLEMENT_SERIAL(CBitvector, CObject,1) 

CBitvector::CBitvector()
{



m_vector = (unsigned char*) new unsigned char[1];

m_vector[0]=0;


}

CBitvector::CBitvector(CBitvector* anotherptr)
{

TRY
{

if(!anotherptr){AfxThrowUserException();}


 m_vector = (unsigned char*) new unsigned char[1]; 
 
 m_vector[0]=0;

 for(int offset=0; offset <=6; offset++)
 {
     if(anotherptr->read(offset))
     {
 	  set(offset);}
	

 }

 }

 CATCH(CUserException,e)
 {

  AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION  ,0);

 }

 END_CATCH
 {




 }


}


CBitvector::CBitvector(CBitvector& another )
{

TRY
{



 m_vector = (unsigned char*) new unsigned char[1]; 
 
 m_vector[0]=0;

 for(int offset=0; offset <=6; offset++)
 {
     if(another.read(offset))
     {
 	  set(offset);}
	

 }

 }

 CATCH(CUserException,e)
 {

  AfxMessageBox(IDS_PGERR ,MB_OK|MB_ICONEXCLAMATION  ,0);

 }

 END_CATCH
 {




 }
}

CBitvector::~CBitvector()
{

delete m_vector;

}


void CBitvector::set(const int pos)
{

TRY
{ 

if(pos<0 || pos > 6){AfxThrowUserException();} 

  int index(pos / CHAR_BIT);
  int offset(pos % CHAR_BIT);
  unsigned char mask = (1 << offset);
  m_vector[index] |= mask;

}

CATCH(CUserException,e)
{

AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

}

END_CATCH
{



}

}

void CBitvector::clear(const int pos)
{

TRY
{
  if(pos<0 || pos > 6){AfxThrowUserException();} 

  int index(pos / CHAR_BIT);
  int offset(pos % CHAR_BIT);
  unsigned char mask = ~(1 << offset);
  m_vector[index] &= mask;

}

CATCH(CUserException,e)
{

AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

}

END_CATCH
{



}

}

void CBitvector::set(const int pos, const BOOL option)
{
TRY
{

if(pos<0 || pos > 6){AfxThrowUserException();} 

if(option)
{

set(pos);
}
else
{

clear(pos);

}

}// end try

CATCH(CUserException,e)
{

AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

}

END_CATCH
{



}

}

BOOL CBitvector::IsSet(const int pos)
{
	BOOL verdict = false;

TRY
{

if(pos<0 || pos > 6){AfxThrowUserException();} 

 if(read(pos)){verdict = TRUE;}

 else { verdict = FALSE;}


}
CATCH(CUserException,e)
{

AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

}

END_CATCH
{



}
return verdict;
}


BOOL CBitvector::read(const int pos)
{
	BOOL verdict = false;

TRY
{

if(pos<0 || pos > 6){AfxThrowUserException();} 

 int index(pos / CHAR_BIT);
 int offset(pos % CHAR_BIT);
 unsigned char mask = (1 << offset);

if( m_vector[index] & mask)
	{

	verdict = TRUE;

	}
	else
	{

	verdict = FALSE;

	}
}

CATCH(CUserException,e)
{

AfxMessageBox(IDS_PGERR,MB_OK|MB_ICONEXCLAMATION,0);

}

END_CATCH
{



}
return verdict;
}


void  CBitvector::reset(void)
{

m_vector[0]=0;

}

void CBitvector::operator &=(CBitvector& another)
{

                                      
*m_vector &= *another.m_vector ;

} 

void CBitvector::operator >>(const int offset)
{

*m_vector = *m_vector	<< offset;



}
  
void CBitvector::operator <<(const int offset)
{

*m_vector = *m_vector	>> offset;



}

void CBitvector::operator =(CBitvector& another)
{

reset();

 for(int offset=0; offset < 7; offset++)
 {
     if(another.read(offset))
     {
 	  set(offset);}

  }

}




BOOL CBitvector::IsClear(void)
{




return m_vector[0]==0;

}

int CBitvector::firstset(void)
{

int cnt(0);

while(!read(cnt) && cnt <=4)
{
   cnt++;


}

return 	cnt; //NB a fourth position means empty

}


void CBitvector::Serialize(CArchive& ar)
{     
    
	  if(ar.IsStoring())
	  {

	   ar << *m_vector;

	  }

	  else

	  {

	  ar >> *m_vector;


	  }
		
}

#ifdef _standalone

void main(void)
{

 CBitvector v;
 CBitvector c;
 


 v.set(4,TRUE);
 c=v;

 for(int cnt=0; cnt <7 ; cnt++)
 {

 c.set(cnt,TRUE);

 }

 for(int cnt=0; cnt <7 ; cnt++)
 {

 cout << v.IsSet(cnt);
 

 }
 for(int cnt=0; cnt <7 ; cnt++)
 {

 cout << c.IsSet(cnt);
 

 }



}

#endif
