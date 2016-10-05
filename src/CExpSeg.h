#ifndef CEXPSEG_H_18996419846185186__
#define	CEXPSEG_H_18996419846185186__

#include "CNumber.h"

//------------------------------------------------------------------------------
/**
 * @brief Class for work with operators and operands.
 */
class CExpSeg
{
public:
    /**
     * @brief Pure virtual function, gets complete expression in CNumber.
     */
    virtual CNumber getValue() const = 0;
    /**
     * @brief Pure virtual function, gets priority of operators.
     */
    virtual int getPriority() const = 0;
    /**
     * @brief Pure virtual function, gets sign from numbers.
     */
    virtual char getSign() const = 0;
    
    /**
     * @brief Virtual destructor, functionality depends on branch type.
     */
    virtual ~CExpSeg ( void );
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/**
 * @brief Class represent operators.
 */
class COperator : public CExpSeg
{
public:
    /**
     * @brief Constructor that save the operator and his priority.
     * @param sign Operator.
     * @param priority Operator priority.
     */
    COperator( char sign, int priority );
    /**
     * @brief Function gets complete expression in CNumber.
     * @return Nothing, because this is function primary from operands.
     */
    CNumber getValue() const;
    /**
     * @brief Function gets sign from number.
     * @return Operator.
     */
    char getSign() const;
    /**
     * @brief Function gets priority operators.
     * @return Operator priority.
     */
    int getPriority() const;
private:
    char sign;
    int priority;
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/**
 * @brief Class represent operands.
 */
class COperand : public CExpSeg
{
public:
    /**
     * @brief Constructor that save number in CNumber.
     * @param number Number in CNumber.
     */
    COperand( CNumber number );
    /**
     * @brief Function gets complete expression in CNumber.
     * @return Operand in CNumber.
     */
    CNumber getValue() const;
    /**
     * @brief Function gets sign from number.
     * @return Character '/', because this is function primary from operators.
     */
    char getSign() const;
    /**
     * @brief Function gets priority operators.
     * @return Number -1, because this is function primary from operators.
     */
    int getPriority() const;
private:
    CNumber number;
};
#endif	/* CEXPSEG_H_18996419846185186__ */

