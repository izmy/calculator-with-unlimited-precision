#ifndef CNUMBER_H_16846184981891891__
#define	CNUMBER_H_16846184981891891__

#include <vector>
#include <string>

#include "CException.h"

//------------------------------------------------------------------------------
/**
 * @brief Class for operating with numbers - save, addition, subtraction and multiplication.
 */
class CNumber
{
public:
    /**
     * @brief Constructor for to save number to two vectors.
     * @param left Integer part of number.
     * @param right Fractional part of number.
     * @param sign Sign of number - plus (1) or minus (0).
     */
    CNumber( std::string left, std::string right, bool sign );
    /**
     * @brief Copy constructor.
     * @param from Original CNumber from which to copy data.
     */
    CNumber ( const CNumber &from );
    /**
     * @brief Overloaded operator = for copy constructor.
     * @param x Original CNumber object.
     * @return New object.
     */
    CNumber & operator= ( const CNumber &x );
    /**
     * @brief Overloaded operator - for unary minus.
     * @return CNumber with opposite sign.
     */
    CNumber operator- ( );
    /**
     * @brief Function for addition two numbers.
     * @param x Second number on counting.
     * @return Result.
     */
    CNumber operator+ ( CNumber &x );
    /**
     * @brief Function for subtraction two numbers.
     * @param x Second number on counting.
     * @return Result.
     */
    CNumber operator- ( CNumber &x );
    /**
     * @brief Function for multiplication two numbers.
     * @param x Second number on counting.
     * @return Result.
     */
    CNumber operator* ( CNumber &x );
    /**
     * @brief Function gets number with sign in string.
     * @return Number with sign in string.
     */
    std::string getNumber() const;
    /**
     * @brief Function gets sign plus or minus.
     * @return Sign.
     */
    bool getPlusMinus() const;
private:
    std::vector<char> NLeft;
    std::vector<char> NRight;
    std::string left;
    std::string right;
    bool NSign;
};
//------------------------------------------------------------------------------
#endif	/* CNUMBER_H_16846184981891891__ */

