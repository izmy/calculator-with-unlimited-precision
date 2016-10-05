#include "CException.h"

using namespace std;

//------------------------------------------------------------------------------
CException::CException(int checker)
{
    this->checker = checker;
}
//------------------------------------------------------------------------------
CExceptionFile::CExceptionFile( ) : CException ( 1 ) { }
//------------------------------------------------------------------------------
CException::~CException() { }
//------------------------------------------------------------------------------
ostream & operator<<( ostream & out, const CException &x )
{
    if ( x.checker == 0 )
    {
        out << "Parsing error on start." << endl;
    } else if ( x.checker == -1 )
    {
        out << "Parsing error on brackets." << endl;
    } else{
        out << "Parsing error on character " << x.checker << "." << endl;
    }
    
    return out;
}
//------------------------------------------------------------------------------
ostream & operator<<( ostream & out, const CExceptionFile &x )
{
    out << "Error of reading file." << endl;

    return out;
}
//------------------------------------------------------------------------------