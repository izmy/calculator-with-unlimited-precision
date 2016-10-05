#include "CExpSeg.h"

//------------------------------------------------------------------------------
CExpSeg::~CExpSeg( void ) { }
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
COperator::COperator(char sign, int priority) : sign ( sign ), 
                                                priority ( priority ) { }
//------------------------------------------------------------------------------
CNumber COperator::getValue() const
{
    return CNumber("","",true);
}
//------------------------------------------------------------------------------
char COperator::getSign() const
{
    return sign;
}
//------------------------------------------------------------------------------
int COperator::getPriority() const
{
    return priority;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
COperand::COperand( CNumber number ) : number (number) { }
//------------------------------------------------------------------------------
CNumber COperand::getValue() const
{
    return number;
}
//------------------------------------------------------------------------------
char COperand::getSign() const
{
    return '/';
}
//------------------------------------------------------------------------------
int COperand::getPriority() const
{
    return -1;
}
//------------------------------------------------------------------------------