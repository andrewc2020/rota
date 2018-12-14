// bitvector.cpp : implementation file
//

//#include "stdafx.h"
#include "bitvector.h"
#include "iostream.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



/////////////////////////////////////////////////////////////////////////////
// CBitvector

const unsigned char highbit = 1 << (CHAR_BIT -1);

CBitvector::CBitvector()
{



m_vector = (unsigned char*) new unsigned char[1];

m_vector[0]=0;


}


CBitvector::CBitvector(CBitvector& another )
{

 m_vector = (unsigned char*) new unsigned char[1]; 
 
 m_vector[0]=0;

 for(int offset=0; offset <=3; offset++)
 {
     if(another.read(offset))
     {
 	  set(offset);}
	

 }


}

CBitvector::~CBitvector()
{

delete m_vector;

}


void CBitvector::set(const int pos)
{

  

  int index(pos / CHAR_BIT);
  int offset(pos % CHAR_BIT);
  unsigned char mask = (1 << offset);
  m_vector[index] |= mask;

}

void CBitvector::clear(const int pos)
{

  int index(pos / CHAR_BIT);
  int offset(pos % CHAR_BIT);
  unsigned char mask = ~(1 << offset);
  m_vector[index] &= mask;


}

int CBitvector::read(const int pos)
{

 int index(pos / CHAR_BIT);
 int offset(pos % CHAR_BIT);
 unsigned char mask = (1 << offset);

return m_vector[index] & mask;


}




void CBitvector::operator &=(CBitvector& another)
{

                                      
*m_vector &= *another.m_vector ;

}


int CBitvector::IsClear(void)
{




return m_vector[0];

}











