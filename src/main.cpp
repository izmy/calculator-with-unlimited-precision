//------------------------------------------------------------------------------
// Program: Calculator with unlimited precision
// Author: Jaroslav Hrach
//------------------------------------------------------------------------------
#include <iostream>
#include <sstream>

using namespace std;

#include "CException.h"
#include "CExpression.h"

//------------------------------------------------------------------------------

int main( int argc, char** argv ) 
{
    CExpression c;
    string menu;
    string exp;
    string file, fileIn, fileOut;
    bool check = 0;
    bool check2 = 0;

    if ( argc == 1 )
    {
        cout << "Calculator with unlimited precision" << endl;
        cout << "1 - Write expression in terminal" << endl;
        cout << "2 - Load file" << endl;
        cout << "3 - Close" << endl << endl;
        while ( menu != "3" )
        {
            if ( menu == "1" )
            {
                cout << "Type your expression:" << endl;
                cin >> exp;
                try {
                    c.number(exp);
                } catch (const CException & e) {
                    cout << e;
                    check = 1;
                }
                if ( check != 1 ) cout << "Result:" << endl << c;
            } 
            else if ( menu == "2" )
            {
                cout << "Type filename:" << endl;
                cin >> file;
                fileIn = file;
                fileOut = file + "_out";
                try {
                    check2 = c.readFile(fileIn, fileOut);
                } catch (const CExceptionFile & e) {
                    cout << e;
                    check = 1;
                }
                if ( check != 1 && check2 == 1 ) cout << "Result is saved in " << fileOut << endl;
            }
            check = 0;
            cout << "Choose option (1-3): ";
            cin >> menu;
            if ( menu != "1" && menu != "2" && menu != "3" ) cout << "Bad choice (please type number 1-3)" << endl;
        }
    } else {
        for ( int i = 1; i < argc; i++ )
        {
            file = argv[i];
                fileIn = file;
                fileOut = file + "_out";
            try {
                    c.readFile(fileIn, fileOut);
                } catch (const CExceptionFile & e) {
                    cout << e;
                }
        }
    }
    
    return 0;
}