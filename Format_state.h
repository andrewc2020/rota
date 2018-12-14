#pragma once

class CPeriod;
class CState;
class Format_state : public CState {



public:

	Format_state(const CString, const CString, const WORD);
	~Format_state();


	const CString long_formatstring; /*limited options for now */
	const CString short_formatstring;
	const CString* pCurrent_setting;
	const WORD m_fontwidth;
	void longstring(const BOOL Is_long_format);
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
	virtual double Getdur(void);
	virtual void  SummaryFormat(UINT&);

};

class Format_SF : public Format_state {
public:
	Format_SF(const CString, const CString, const WORD);
	~Format_SF();
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
};

class Format_CD : public Format_SF {
public:
	Format_CD(const CString, const CString, const WORD);
	~Format_CD();
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
};

class Format_BL : public Format_state {
public:
	Format_BL(const CString, const CString, const WORD);
	~Format_BL();
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
};
