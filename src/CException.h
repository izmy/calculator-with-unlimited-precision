#ifndef CEXCEPTION_H_869418648645184165__
#define	CEXCEPTION_H_869418648645184165__

#include <iostream>

//------------------------------------------------------------------------------
/**
 * @brief Class for call exception.
 */
class CException
{
public:
    /**
     * @brief Save a variable from the parameter to class.
     * @param checker Number indicating the erroneous character.
     */
    CException( int checker );
    /**
     * @brief Overloaded operator << for output error message.
     * @param out Send message on ostream.
     * @param x Reference on number indicating the erroneous character.
     */
    friend std::ostream & operator<< ( std::ostream & out, const CException &x );
    /**
     * @brief Virtual destructor, functionality depends on branch type.
     */
    virtual ~CException( void );
protected:
    int checker;
};
//------------------------------------------------------------------------------
/**
 * @brief Subclass of CException for call exception at work with files.
 */
class CExceptionFile : public CException
{
public:
    /**
     * @brief Constructor without parameters, constructor does nothing.
     */
    CExceptionFile();
    /**
     * @brief Overloaded operator << for output error message.
     * @param out Send message on ostream.
     * @param x Reference on number indicating the erroneous character.
     */
    friend std::ostream & operator<< ( std::ostream & out, const CExceptionFile &x );
};
//------------------------------------------------------------------------------
#endif	/* CEXCEPTION_H_869418648645184165__ */