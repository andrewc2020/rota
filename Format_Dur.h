#pragma once

class Format_Dur : public Format_state {
private:



public:

	Format_Dur(const CString, const CString, const WORD);
	~Format_Dur();
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
	virtual void  SummaryFormat(UINT&);

};

class Format_Dur_Sevenhalf : public Format_Dur {

public:
	Format_Dur_Sevenhalf(const CString, const CString, const WORD);
	~Format_Dur_Sevenhalf();
	double Getdur();
	void SummaryFormat(UINT&);
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
};

class Format_Dur_SevenTwelve : public Format_Dur {
public:
	Format_Dur_SevenTwelve(const CString, const CString, const WORD);
	~Format_Dur_SevenTwelve();
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
	double Getdur();
	void SummaryFormat(UINT&);
};

class Format_Dur_SevenTwentyfour : public Format_Dur{

public:
	Format_Dur_SevenTwentyfour(const CString, const CString, const WORD);
	~Format_Dur_SevenTwentyfour();
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
	double Getdur();
	void SummaryFormat(UINT&);

};

class Format_Dur_SevenThirtysix : public Format_Dur{
public:
	Format_Dur_SevenThirtysix(const CString, const CString, const WORD);
	~Format_Dur_SevenThirtysix();
	virtual void DrawMe(CPeriod*, CRect&, CDC*, CView*);
	double Getdur();
	void SummaryFormat(UINT&);


};

