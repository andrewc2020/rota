// rowbuild.h : interface of the Rowbuilder class
//
/////////////////////////////////////////////////////////////////////////////
// virtual base class to derived rowbuilder classes
class CState;

class Rowbuilder : public CState {



public:
Rowbuilder();
Rowbuilder(const UINT);
~Rowbuilder();
virtual void SetRow(CRect&);
virtual void overflow_reset(int&);
virtual void max_rows(int&);
virtual void fontheight(int&);
};


class Shallow_Rowbuilder : public Rowbuilder {



public:
Shallow_Rowbuilder();
Shallow_Rowbuilder(const UINT);
~Shallow_Rowbuilder();
virtual void SetRow(CRect&);
virtual void overflow_reset(int&);
virtual void max_rows(int&);
virtual void fontheight(int&);
};


class Deep_Rowbuilder : public Rowbuilder {



public:
Deep_Rowbuilder();
Deep_Rowbuilder(const UINT);
~Deep_Rowbuilder();
virtual void SetRow(CRect&);
virtual void overflow_reset(int&);
virtual void max_rows(int&);
virtual void fontheight(int&);
};    
