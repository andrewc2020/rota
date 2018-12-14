




//#include <afxwin.h>
//#include <afx.h>


/////////////////////////////////////////////////////////////////////////////
// Span Object - relative interval


#define FALSE 0;

class CBitvector 

{



private:


unsigned char* m_vector;



protected:







public :

CBitvector(CBitvector&);  //copy constructor
CBitvector();
~ CBitvector();
void set(const int);
void clear(const int);
int read(const int);
void operator &=(CBitvector& );
int IsClear(void);






};





