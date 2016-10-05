#include "CNumber.h"

using namespace std;

//------------------------------------------------------------------------------
CNumber::CNumber(string left, string right, bool sign)
{
    for ( int i = left.size() - 1; i >= 0; i-- )
    {
        this->NLeft.push_back( left[i] - '0' );
    }
    
    for ( unsigned int i = 0; i < right.size(); i++ )
    {
        this->NRight.push_back( right[i] - '0' );
    }
    
    if ( right.size() == 0 )
    {
        this->NRight.push_back( 0 );
    }

    this->NSign = sign;
    this->left = left;
    this->right = right;
}
//------------------------------------------------------------------------------
CNumber::CNumber(const CNumber &from)
{
    if ( this != &from )
    {
        NLeft = from.NLeft;
        NRight = from.NRight;
        NSign = from.NSign;
    }
}
//------------------------------------------------------------------------------
CNumber & CNumber::operator =(const CNumber& x)
{
    if ( this != &x )
    {
        NLeft = x.NLeft;
        NRight = x.NRight;
        NSign = x.NSign;
    }
    return (*this);
}
//------------------------------------------------------------------------------
CNumber CNumber::operator -()
{
    CNumber ret("","", 1);
    ret.NLeft = NLeft;
    ret.NRight = NRight;
    
    if ( NSign == 0 ) ret.NSign = 1;
    if ( NSign == 1 ) ret.NSign = 0;
    
    return ret;
}
//------------------------------------------------------------------------------
CNumber CNumber::operator +( CNumber& x)
{
    CNumber ret("","", 1);
    int leftSize;
    int rightSize;
    bool overflow = 0;
    
    if ( NSign == x.NSign ) ret.NSign = NSign;
    if ( NSign != x.NSign ) ret.NSign = !NSign;
    
    if ( x.NLeft.size() >= NLeft.size() )
    {
        leftSize = x.NLeft.size();
        NLeft.resize( leftSize, 0 );
        
    } else 
    {
        leftSize = NLeft.size();
        x.NLeft.resize( leftSize, 0);
    }
    
    if ( x.NRight.size() >= NRight.size() )
    {
        rightSize = x.NRight.size();
        NRight.resize( rightSize, 0 );
    } else 
    {
        rightSize = NRight.size();
        x.NRight.resize( rightSize, 0);
    }
    
    ret.NLeft.clear();
    ret.NLeft.resize( leftSize, 0 );
    
    ret.NRight.clear();
    ret.NRight.resize( rightSize, 0 );
            
    for ( int i = rightSize - 1; i >= 0; i-- )
    {
        if ( ( NRight[i] + x.NRight[i] ) >= 10 && !overflow )
        {
            ret.NRight[i] = NRight[i] + x.NRight[i] - 10;
            overflow = 1;
        } 
        else if ( ( NRight[i] + x.NRight[i] ) >= 10 && overflow )
        {
            ret.NRight[i] = NRight[i] + x.NRight[i] - 9;
            overflow = 1;
        }
        else if ( ( NRight[i] + x.NRight[i] ) < 9 && overflow )
        {
            ret.NRight[i] = NRight[i] + x.NRight[i] + 1;
            overflow = 0;
        }
        else if ( ( NRight[i] + x.NRight[i] ) < 10 && !overflow )
        {
            ret.NRight[i] = NRight[i] + x.NRight[i];
            overflow = 0;
        }
    }
    
    for ( int i = 0; i < leftSize; i++ )
    {
        if ( ( NLeft[i] + x.NLeft[i] ) >= 10 && !overflow )
        {
            ret.NLeft[i] = NLeft[i] + x.NLeft[i] - 10;
            overflow = 1;
        } 
        else if ( ( NLeft[i] + x.NLeft[i] ) >= 10 && overflow )
        {
            ret.NLeft[i] = NLeft[i] + x.NLeft[i] - 9;
            overflow = 1;
        }
        else if ( ( NLeft[i] + x.NLeft[i] ) < 9 && overflow )
        {
            ret.NLeft[i] = NLeft[i] + x.NLeft[i] + 1;
            overflow = 0;
        }
        else if ( ( NLeft[i] + x.NLeft[i] ) < 10 && !overflow )
        {
            ret.NLeft[i] = NLeft[i] + x.NLeft[i];
            overflow = 0;
        }        
    }

    if ( overflow )
    {
        ret.NLeft.resize( leftSize + 1, 1 );
    }
    
    for ( int i = rightSize - 1; i >= 0; i-- )
    {
        if ( ret.NRight[i] == 0 )
        {
            ret.NRight.pop_back();
        } else break;
    }
    
    return ret;
}
//------------------------------------------------------------------------------
CNumber CNumber::operator -( CNumber& x)
{
    CNumber ret("","", 1);
    int leftSize;
    int rightSize;
    int borrow = 0;
    int value;
        
    if ( x.NLeft.size() >= NLeft.size() )
    {
        leftSize = x.NLeft.size();
        NLeft.resize( leftSize, 0 );
    } else 
    {
        leftSize = NLeft.size();
        x.NLeft.resize( leftSize, 0);
    }
    
    if ( x.NRight.size() >= NRight.size() )
    {
        rightSize = x.NRight.size();
        NRight.resize( rightSize, 0 );
    } else 
    {
        rightSize = NRight.size();
        x.NRight.resize( rightSize, 0);
    }
    
    ret.NLeft.clear();
    ret.NLeft.resize( leftSize, 0 );
    
    ret.NRight.clear();
    ret.NRight.resize( rightSize, 0 );
    
    // zjisteni, ktere cislo je vetsi
    for ( int i = leftSize - 1; i >= 0; i-- )
    {
        if ( NLeft[i] > x.NLeft[i] )
        {
            value = 0;
            ret.NSign = 1;
            break;
        }
        else if ( NLeft[i] < x.NLeft[i] )
        {
            value = 1;
            ret.NSign = 0;
            break;
        }
        else if ( NLeft[i] == x.NLeft[i] )
        {
            if ( i == 0 ) value = 2;
        }
    }
    
    if ( value == 2 )
    {
        for ( int i = 0; i < rightSize; i++ )
        {
            if ( NRight[i] > x.NRight[i] )
            {
                value = 0;
                ret.NSign = 1;
                break;
            }
            else if ( NRight[i] < x.NRight[i] )
            {
                value = 1;
                ret.NSign = 0;
                break;
            }
            else if ( NRight[i] == x.NRight[i] )
            {
                if ( i == 0 ) 
                {
                    value = 0;
                    ret.NSign = 0;
                }
            }
        }
    }
            
    for ( int i = rightSize - 1; i >= 0; i-- )
    {
        if ( value == 0 )
        {
            ret.NRight[i] = NRight[i] - x.NRight[i] + 10 - borrow;
            
            if ( ret.NRight[i] >= 10 )
            {
                ret.NRight[i] -= 10;
                borrow = 0;
            } else
            {
                borrow = 1;
            }
        } else
        {
            ret.NRight[i] = x.NRight[i] - NRight[i] + 10 - borrow;
            
            if ( ret.NRight[i] >= 10 )
            {
                ret.NRight[i] -= 10;
                borrow = 0;
            } else
            {
                borrow = 1;
            }
        }
    }
    
    for ( int i = 0; i < leftSize; i++ )
    {
        if ( value == 0 )
        {
            ret.NLeft[i] = NLeft[i] - x.NLeft[i] + 10 - borrow;
            
            if ( ret.NLeft[i] >= 10 )
            {
                ret.NLeft[i] -= 10;
                borrow = 0;
            } else
            {
                borrow = 1;
            }
        } else
        {
            ret.NLeft[i] = x.NLeft[i] - NLeft[i] + 10 - borrow;
            
            if ( ret.NLeft[i] >= 10 )
            {
                ret.NLeft[i] -= 10;
                borrow = 0;
            } else
            {
                borrow = 1;
            }
        }
    }

    for ( int i = leftSize - 1; i >= 0; i-- )
    {
        if ( ret.NLeft[i] == 0 )
        {
            if ( i != 0 ) ret.NLeft.pop_back();
        } else break;
    }
    
    for ( int i = rightSize - 1; i >= 0; i-- )
    {
        if ( ret.NRight[i] == 0 )
        {
            ret.NRight.pop_back();
        } else break;
    }
    
    return ret;
}
//------------------------------------------------------------------------------
CNumber CNumber::operator *( CNumber& x)
{
    CNumber ret("","", 1);
    int leftSize;
    int rightSize;
    int decimalSize;
    int allSize;
    vector<char> allFirst;
    vector<char> allSecond;
    vector<char> tempLeft;
    int carry = 0;
    
    if ( NSign == x.NSign ) ret.NSign = true;
    if ( NSign != x.NSign ) ret.NSign = false;
    
    if ( x.NLeft.size() >= NLeft.size() )
    {
        leftSize = x.NLeft.size();
        NLeft.resize( leftSize, 0 );
    } else 
    {
        leftSize = NLeft.size();
        x.NLeft.resize( leftSize, 0);
    }
    
    if ( x.NRight.size() >= NRight.size() )
    {
        rightSize = x.NRight.size();
        NRight.resize( rightSize, 0 );
    } else 
    {
        rightSize = NRight.size();
        x.NRight.resize( rightSize, 0);
    }
    
    allSize = leftSize + rightSize;
    decimalSize = rightSize * 2;
    
    // naplneni vectoru celym prvnim vyrazem
    for ( int i = rightSize - 1; i >= 0; i-- )
    {
        allFirst.push_back( NRight[i] );
    }
    
    for ( int i = 0; i < leftSize; i++ )
    {
        allFirst.push_back( NLeft[i] );
    }
    
    // naplneni vectoru celym druhym vyrazem
    for ( int i = rightSize - 1; i >= 0; i-- )
    {
        allSecond.push_back( x.NRight[i] );
    }
    
    for ( int i = 0; i < leftSize; i++ )
    {
        allSecond.push_back( x.NLeft[i] );
    }
    
    ret.NLeft.resize( allSize * 2, 0 );
    
    for ( int i = 0; i < allSize; i++ )
    {
        for ( int j = 0; j < allSize; j++ )
        {
            ret.NLeft[i + j] = ret.NLeft[i + j] + allSecond[i] * allFirst[j] + carry;
            
            carry = ret.NLeft[i + j] / 10;
            ret.NLeft[i + j] %= 10;
            
            if ( j == allSize - 1 )
            {
                ret.NLeft[i + j + 1] += carry;
            }
        }
        carry = 0;
    }
    
    ret.NLeft[ret.NLeft.size() - 1] += carry;
    
    ret.NRight.clear();
    ret.NRight.resize( decimalSize, 0 );
                
    for ( int i = 0; i < decimalSize; i++ )
    {
        ret.NRight[i] = ret.NLeft[decimalSize - 1 - i];
        ret.NLeft[decimalSize - 1 - i] = 0;
    }
    
    for ( int i = ret.NRight.size() - 1; i >= 0; i-- )
    {
        if ( ret.NRight[i] == 0 )
        {
            ret.NRight.pop_back();
        } else break;
    }
    
    int edge = ret.NLeft.size() - decimalSize - 1;

    for ( int i = ret.NLeft.size() - 1; i >= 0; i-- )
    {
        tempLeft.push_back( ret.NLeft[i] );
        edge--;
        if ( edge < 0 ) break;
    }
    
    ret.NLeft.clear();
    ret.NLeft.resize( tempLeft.size(), 0 );
    
    int i = 0;
    while ( !tempLeft.empty() )
    {
        ret.NLeft[i] = tempLeft.back();
        tempLeft.pop_back();
        i++;
    }
    
    for ( int i = ret.NLeft.size() - 1; i > 0; i-- )
    {
        if ( ret.NLeft[i] == 0 )
        {
            ret.NLeft.pop_back();
        } else break;
    }

    return ret;
}
//------------------------------------------------------------------------------
string CNumber::getNumber() const
{
    string number;
    
    if ( NSign != true ) number += "-";
    
    for ( vector<char>::const_reverse_iterator it = NLeft.rbegin(); it != NLeft.rend(); ++it )
    {
        number += *it + '0';
    }
    
    if ( !NRight.empty() )
    {
        number += '.';
    }
    
    for ( vector<char>::const_iterator it = NRight.begin(); it != NRight.end(); ++it )
    {
        number += *it + '0';
    }
    
    return number;
}
//------------------------------------------------------------------------------
bool CNumber::getPlusMinus() const
{
    return NSign;
}
//------------------------------------------------------------------------------
