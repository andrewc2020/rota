#include "stdafx.h"
#include "afx.h"
#include <iostream.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "timechar.h"



CTimechar::CTimechar(CString datetimestr):CTime(atoi(datetimestr.Mid(7,4)),((months.Find(datetimestr.Left(3))/3)+1),atoi(datetimestr.Mid(4,2)),0,0,0)
{

 


}

/* Test harness */
/*
void main(void)
{
 CTimechar  ch("Dec/01/2011");
 cout <<ch.Format("%a %d %B %Y") << "\n";
 
 
}
*/
