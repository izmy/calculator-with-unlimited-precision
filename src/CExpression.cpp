#include "CExpression.h"

using namespace std;

//------------------------------------------------------------------------------
CExpression::CExpression()
{
    this->result = result;
}
//------------------------------------------------------------------------------
CExpression::~CExpression()
{
    while ( !q.empty() )
    {
        delete q.front();
        q.pop();
    }
    
    while ( !rpn.empty() )
    {
        delete rpn.front();
        rpn.pop();
    }
}
//------------------------------------------------------------------------------
int CExpression::checkInput(string & exp)
{
    int bracket = 0;
    int dot = 0;
    
    string expNew = "";
    
    // remove white characters
    for (unsigned int i = 0; i < exp.length(); i++)
    {
        if ( exp[i] != ' ' ) expNew += exp[i];
    }
    
    exp = expNew;
    
    // check of empty input
    if ( exp == "" || exp == " " ) return -1;
    
    if ( exp[0] == ')' || exp[0] == '.' || exp[0] == '*' ) return -1;
    
    for (unsigned int i = 0; i < exp.length(); i++)
    {
        // check of correct characters
        if ( ( exp[i] < '0' || exp[i] > '9' ) && 
             ( exp[i] < '(' || exp[i] > '+' ) &&
               exp[i] != '-' && exp[i] != '.' ) return i;
        
        // check of decimal point
        if ( i != 0 && exp[i] == '.' )
        {
            if ( exp[i-1] < '0' || exp[i-1] > '9' ) return i;
            dot++;
            if ( dot > 1 ) return i;
        }
        
        if ( exp[i] == '+' || exp[i] == '-' || 
             exp[i] == '*' || exp[i] == ')' ) dot = 0;
        
        // check of existence sign before '('
        if ( i != 0 && exp[i] == '(' &&
                   ( exp[i-1] != '+' && 
                     exp[i-1] != '-' &&
                     exp[i-1] != '*' &&
                     exp[i-1] != '(' ) ) return i;
        
        if ( exp[i] == '(' ) bracket += 1;
        if ( exp[i] == ')' ) bracket -= 1;
        if ( bracket < 0 ) return -2;
        
        // check of last character
        if ( i == exp.length() - 1 && 
                ( exp[i] < '0' || exp[i] > '9' ) && 
                  exp[i] != ')' ) return i;
        
        // check of existence number/sign after '('
        if ( i != exp.length() - 1 && exp[i] == '(' && 
                exp[i + 1] != '(' && exp[i + 1] != '-' &&
             ( exp[i + 1] < '0' || exp[i + 1] > '9' ) ) return i;
        
        // check of wrong signs
        if ( i != 0 && ( exp[i] == '+' || exp[i] == '-' || exp[i] == '*' ) &&
                ( exp[i-1] == '+' || exp[i-1] == '-' || exp[i-1] == '*' ) ) return i;

    }
    
    if ( bracket != 0 ) return -2;

    return -3;
}
//------------------------------------------------------------------------------
void CExpression::parser(string& exp)
{
    string NFull = "";
    string NLeft = "";
    string NRight = "";
    bool sign = true;
    bool dot = false;
    char oper = ' ';
        
    for ( unsigned int i = 0; i < exp.length(); i++ )
    {
        // operandy
        if ( ( exp[i] >= '0' && exp[i] <= '9' ) || exp[i] == '.' )
        {
            NFull += exp[i];
            
            if ( ( exp[i + 1] < '0' || exp[i + 1] > '9' ) && exp[i + 1] != '.' )
            {
                for ( unsigned int j = 0; j < NFull.length(); j++ )
                {
                    if ( NFull[j] == '.' ) dot = true;
                    if ( dot == false ) NLeft += NFull[j];
                    if ( NFull[j] != '.' )
                    {
                        if ( dot == true ) NRight += NFull[j];
                    }
                }
                
                CNumber number( NLeft, NRight, sign );
                q.push( new COperand( number ) );
                NFull = "";
                NLeft = "";
                NRight = "";
                sign = true;
                dot = false;
            }
        }
        else if ( exp[i] == '(' || exp[i] == ')'  )
        {
            oper = exp[i];
            q.push( new COperator(oper, 1) );
        }
        else if ( exp[i] == '+' )
        {
            oper = exp[i];
            q.push( new COperator(oper, 2) );
        }
        else if ( exp[i] == '-'  )
        {
            if ( i != 0 )
            {
                if ( exp[i-1] != '(' )
                {
                    oper = exp[i];
                    q.push( new COperator(oper, 2) );
                }
                
                if ( exp[i-1] == '(' )
                {
                    CNumber number( "1", "", 0 );
                    q.push( new COperand( number ) );
                    q.push( new COperator('*', 3) );
                }
            } else
            {
                CNumber number( "1", "", 0 );
                q.push( new COperand( number ) );
                q.push( new COperator('*', 3) );
            }
        }
        else if ( exp[i] == '*' )
        {
            oper = exp[i];
            q.push( new COperator( oper, 3 ) );
        }
    }
}
//------------------------------------------------------------------------------
void CExpression::shuntingYard(queue<CExpSeg *> &infix)
{
    stack<CExpSeg *> stOper;
    
    while ( !infix.empty() )
    {
        if ( infix.front()->getPriority() == -1 )
        {
            rpn.push( new COperand( infix.front()->getValue() ) );
        }
        
        if ( infix.front()->getSign() == '(' )
        {
            stOper.push( new COperator( infix.front()->getSign(), 1 ) );
        }
        
        if ( infix.front()->getSign() == ')' )
        {
            if ( !stOper.empty() )
            {
                while ( stOper.top()->getSign() != '(' )
                {
                    rpn.push( new COperator( stOper.top()->getSign(), stOper.top()->getPriority() ) );
                    delete stOper.top();
                    stOper.pop();
                }
                delete stOper.top();
                stOper.pop();
            }
        }
        
        if ( infix.front()->getSign() == '+' || infix.front()->getSign() == '-' )
        {
            if ( !stOper.empty() )
            {
                while ( !stOper.empty() )
                {
                    if ( stOper.top()->getPriority() >= 2 )
                    {
                        rpn.push( new COperator( stOper.top()->getSign(), 2 ) );
                        delete stOper.top();
                        stOper.pop();
                    } else break;
                }
                stOper.push( new COperator( infix.front()->getSign(), 2 ) );
            } else 
            {
                stOper.push( new COperator( infix.front()->getSign(), 2 ) );
            }
        }
        
        if ( infix.front()->getSign() == '*' )
        {
            if ( !stOper.empty() )
            {
                while ( !stOper.empty() )
                {
                    if ( stOper.top()->getPriority() >= 3 )
                    {
                        rpn.push( new COperator( stOper.top()->getSign(), 3 ) );
                        delete stOper.top();
                        stOper.pop();
                    } else break;
                }
                stOper.push( new COperator( infix.front()->getSign(), 3 ) );
            } else 
            {
                stOper.push( new COperator( infix.front()->getSign(), 3 ) );
            }
        }
        
        delete infix.front();
        infix.pop();
    }
    
    while ( !stOper.empty() )
    {
        rpn.push( new COperator( stOper.top()->getSign(), stOper.top()->getPriority() ) );
        delete stOper.top();
        stOper.pop();
    }
}
//------------------------------------------------------------------------------
void CExpression::calculate( queue<CExpSeg*> &postfix )
{
    stack<CExpSeg *> stNumber;
    stack<CExpSeg *> temp;
    CNumber ret( "", "", 1 );
    
    while ( !postfix.empty() )
    {
        if ( postfix.front()->getSign() == '/' )
        {
            stNumber.push( new COperand ( postfix.front()->getValue() ) );
        } else
        {
            if ( stNumber.size() >= 2 )
            {
                temp.push( new COperand( stNumber.top()->getValue() ) );
                delete stNumber.top();
                stNumber.pop();
                
                CNumber a = stNumber.top()->getValue();
                CNumber b = temp.top()->getValue();
                
                if ( postfix.front()->getSign() == '*' )
                {
                    ret = a * b;
                }
                else if ( postfix.front()->getSign() == '+' )
                {
                    if ( stNumber.top()->getValue().getPlusMinus() == 1 &&
                         temp.top()->getValue().getPlusMinus() == 1 )
                    {
                        ret = a + b;
                    } 
                    else if ( stNumber.top()->getValue().getPlusMinus() == 1 &&
                         temp.top()->getValue().getPlusMinus() == 0 )
                    {
                        ret = a - b;
                    }
                    else if ( stNumber.top()->getValue().getPlusMinus() == 0 &&
                         temp.top()->getValue().getPlusMinus() == 1 )
                    {
                        ret = b - a;
                    }
                    else if ( stNumber.top()->getValue().getPlusMinus() == 0 &&
                         temp.top()->getValue().getPlusMinus() == 0 )
                    {
                        ret = a + b;
                    }
                }
                else if ( postfix.front()->getSign() == '-' )
                {
                    if ( stNumber.top()->getValue().getPlusMinus() == 1 &&
                         temp.top()->getValue().getPlusMinus() == 1 )
                    {
                        ret = a - b;
                    } 
                    else if ( stNumber.top()->getValue().getPlusMinus() == 1 &&
                         temp.top()->getValue().getPlusMinus() == 0 )
                    {
                        ret = a + b;
                        ret = -ret;
                    }
                    else if ( stNumber.top()->getValue().getPlusMinus() == 0 &&
                         temp.top()->getValue().getPlusMinus() == 1 )
                    {
                        ret = a + b;
                        ret = -ret;
                    }
                    else if ( stNumber.top()->getValue().getPlusMinus() == 0 &&
                         temp.top()->getValue().getPlusMinus() == 0 )
                    {
                        ret = b - a;
                    }
                }
                delete stNumber.top();
                stNumber.pop();
                delete temp.top();
                temp.pop();
                    
                stNumber.push( new COperand( ret ) );
            }
        }
        
        delete postfix.front();
        postfix.pop();
    }
    
    while ( !temp.empty() )
    {
        delete temp.top();
        temp.pop();
    }
    
    while ( !stNumber.empty() )
    {
        result = stNumber.top()->getValue().getNumber();
        delete stNumber.top();
        stNumber.pop();
    }
    
    if ( result.size() > 2 )
    {
        if ( result[ result.size() - 1 ] == '0' && result[ result.size() - 2 ] == '.' )
        {
            result[ result.size() - 1 ] = '\0';
            result[ result.size() - 2 ] = '\0';
        }
    }
    
    if ( result.size() == 2 )
    {
        if ( result[0] == '-' && result[1] == '0' ) result = "0";
    }
}
//------------------------------------------------------------------------------
void CExpression::number( string exp )
{
    int checker;
    checker = checkInput(exp);
    if ( checker != -3 )
    { 
        throw CException ( checker + 1 );
    }
    
    parser( exp );
    shuntingYard( q );
    calculate( rpn );
}
//------------------------------------------------------------------------------
bool CExpression::readFile( const string inFileName, const string outFileName )
{
    string line;
    
    ifstream inputFile;
    ofstream outputFile;
    
    inputFile.open( inFileName.c_str() );
    
    if ( inputFile.fail() ) 
    {
        throw CExceptionFile();
    }
    
    while ( getline(inputFile, line) )
    {
        if ( inputFile.eof() && line.empty() ) break;
        
        try { number(line); }
        catch (const CException & e) {
            cout << e;
            inputFile.close();
            return 0;
        }
    }
    
    outputFile.open( outFileName.c_str() );
    
    if ( outputFile.fail() ) 
    {
        throw CExceptionFile();
    }
    
    outputFile << result << endl;
    
    inputFile.close();
    outputFile.close();
    
    return 1;
}
//------------------------------------------------------------------------------
string CExpression::getResult() const
{
    return result;
}
//------------------------------------------------------------------------------
istream & operator >>( istream & in, CExpression & x )
{
    string line;
    
    while ( getline( in, line ) )
    {
        x.number(line);
    }
    return in;
}
//------------------------------------------------------------------------------
ostream & operator<<( ostream & out, const CExpression &x )
{
    out << x.getResult() << endl;
    
    return out;
}
//------------------------------------------------------------------------------