#pragma once
#include "afx.h"

class CUtil : public CObject
{
public:
	CUtil(void);
	~CUtil(void);
	CString GetRegString(CString , CString );
	UINT GetRegInt(CString ,CString );
	LRESULT GetPathWithoutObject(CString, CString);
	CString GetPathFromConnect(CString ,CString);
	bool filefound(CString,CString);
};
