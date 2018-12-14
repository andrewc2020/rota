




#include <afxwin.h>
#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// CBitvector Object - manages repeating pattern




class CBitvector : public CObject

{

DECLARE_SERIAL(CBitvector)

private:


unsigned char* m_vector;
int read(const int);


protected:







public :
CBitvector(CBitvector*);  //copy constructor
CBitvector(CBitvector&);  //copy constructor
CBitvector();
~CBitvector();
void set(const int);
void clear(const int);
void set(const int pos, const BOOL);
BOOL IsSet(const int);
BOOL IsClear(void);
void reset(void);
int firstset(void);	//retrieves first set position
void operator &=(CBitvector& );// performs bitwise and between vectors
void operator >>(const int);// performs bitwise shift 0001 to 0010 on vector
void operator <<(const int);// performs bitwise shift 1000 to 0100 on vector 
void CBitvector::operator =( CBitvector&);
virtual void Serialize(CArchive& ar);





};





