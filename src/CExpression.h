#ifndef CEXPRESSION_H_4681861816881_
#define	CEXPRESSION_H_4681861816881_

#include <stack>
#include <queue>
#include <string>
#include <fstream>

#include "CExpSeg.h"

//------------------------------------------------------------------------------
/**
 *  @brief Class for operating with expression.
 */ 
class CExpression
{
public:
    /**
     * @brief Constructor that creates an empty instance.
     */
    CExpression();
    /**
     * @brief Destructor that removes every queues.
     */
    ~CExpression();
    /**
     * @brief Function for check input - correct expression.
     * @param exp Expression in string.
     * @return Number of wrong character or number for continues.
     */
    int checkInput( std::string & exp );
    /**
     * @brief Function for parsing expression
     * @param exp Expression in string.
     */
    void parser( std::string & exp );
    /**
     * @brief Function for converse expression from the infix notation to the postfix notation.
     * @param infix Expression in the infix notation save in queue.
     */
    void shuntingYard( std::queue<CExpSeg *> &infix );
    /**
     * @brief Function for calculating the expression.
     * @param postfix Expression int the postfix notation save in queue.
     */
    void calculate( std::queue<CExpSeg *> &postfix );
    /**
     * @brief Function for works with expression - check input, use Shunting Yard algoritm and calculation expression.
     * @param exp Expression in string.
     */
    void number( std::string exp );
    /**
     * @brief Function for works with files - read and write.
     * @param inFileName Input file name.
     * @param outFileName Output file name.
     * @return Return 1, if parsing in file is ok, return 0 if parsing in file is not ok.
     */
    bool readFile( const std::string inFileName, const std::string outFileName );
    /**
     * @brief Function for get result from variable "result".
     * @return Contents of the variable result.
     */
    std::string getResult() const;
    /**
     * @brief Overloaded operator >> for input expression from the terminal.
     * @param in Send input on istream.
     * @param x Variable save the expression to the class CExpression.
     */
    friend std::istream & operator>> ( std::istream & in, CExpression & x );
    /**
     * @brief Overloaded operator << for output result.
     * @param out Send result on ostream.
     * @param x Variable load the data from the class CExpression.
     */
    friend std::ostream & operator<< ( std::ostream & out, const CExpression & x );
private:
    std::queue<CExpSeg *> q;
    std::queue<CExpSeg *> rpn;
    CExpSeg * value;
    std::string result;
};
//------------------------------------------------------------------------------

#endif	/* CEXPRESSION_H_4681861816881_ */