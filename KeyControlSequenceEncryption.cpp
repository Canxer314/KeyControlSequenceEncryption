//KCSE    -option keyString  fileName
//argv[0] argv[1] argv[2]    argv[3]
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;
using std::swap;

#include <cctype> //providing the function propertype of toupper()

#include <fstream>
using std::ofstream;
using std::ifstream;

int encryption( string fileName, string keyString );
int decryption( string fileName, string keyString );
void bubbleSort1( string r, int n, vector< string > & arry );
void bubbleSort2( string r, int n, vector< string > & arry );

int main( int argc, char * argv[] )
{
  string optionString;
  string keyString;
  string fileName;
  try
  {
      if ( argc < 2 || argc > 4 )
          throw -1;
  }
  catch ( int x )
  {
      cout << "Error: the number of the argument provided not correct." << endl;
      cout << "Please input \"-h\" for help." << endl;
      return -1;
  }
  optionString = argv[ 1 ];
  keyString = argv[ 2 ];
  for ( int i = 0; i < keyString.size(); i++ )
  {
      keyString.at( i ) = toupper( keyString.at( i ) );
  }
  fileName = argv[ 3 ];
  if ( ( optionString == "-e" ) || ( optionString == "--encrypt" ) )
  {
      encryption( fileName, keyString );
  }
  else if ( ( optionString == "-d" ) || ( optionString == "--decrypt" ) )
      {
          decryption( fileName, keyString );
      }
      else if ( ( optionString == "-h" ) || ( optionString == "--help" ) )
          {
              cout << "Usage: [-option] [key] [fileName]" << endl;
              cout << "option:" << endl;
              cout << "\t-e --encrypt     : encryption" << endl;
              cout << "\t-d --decrypt     : decryption" << endl;
              cout << "\t-h --help        : see for help" << endl;
              cout << "key:" << endl;
              cout << "\tthe string of characters which used for encryption or decryption." << endl;
              return 1;
          }
          else
          {
              cout << "Incorrect option.Please input \"-h\" for help." << endl;
              return -2;
          }
  return 0;
}

int encryption( string fileName, string keyString )
{
    string tmpString1;
    string tmpString2;
    size_t keySize = keyString.size();
    vector< string > arryVector( keySize );
    ifstream inputFile( fileName, ifstream::in );
    ofstream outputFile( fileName + ".encrypted", ofstream::out | ofstream::trunc );
    cout << "Encryption finish." << endl;
    while ( inputFile >> tmpString1 )
    {
        tmpString2 += tmpString1;
    }
    for ( auto &i : tmpString2 )
    {
        i = toupper( i );//change all lowercase characters to uppercase
    }
    for ( size_t count = 0; count < tmpString2.size(); count++ )
    {
        arryVector[ count % keySize ] += tmpString2[ count ];
    }
    bubbleSort1( keyString, keySize, arryVector );
    for ( auto i : arryVector )
    {
        outputFile << i;
    }
    inputFile.close();
    outputFile.close();
    return 0;
}
int decryption( string fileName, string keyString )
{
    int count = 0;
    string tmpStr1;
    string tmpStr2;
    size_t keySize = keyString.size();
    vector< string > arryVec( keySize );
    ifstream inputFile( fileName, ifstream::in );
    ofstream outputFile( fileName + ".decrypted", ofstream::out | ofstream::trunc );
    cout << "Decryption finish." << endl;
    while ( inputFile >> tmpStr2 )
    {
        tmpStr2 += tmpStr1;
    }
    auto itStr2 = tmpStr2.begin();
    for ( int i = 0; i < tmpStr2.size() % keySize; i++, count++ )
    {
        for ( int j = 0; j < tmpStr2.size() / keySize + 1; j++ )
        {
            arryVec[ count ] += *itStr2++;
        }
    }
    for ( ; count < keySize; count++ )
    {
        for ( int j = 0; j < tmpStr2.size() / keySize; j++ )
        {
            arryVec[ count ] += *itStr2++;
        }
    }
    bubbleSort2( keyString, keySize, arryVec );
    for ( int i = 0; i < tmpStr2.size(); i++ )
    {
        outputFile << arryVec[ i % keySize ][ i / keySize ];
    }
    inputFile.close();
    outputFile.close();
    return 0;
}

void bubbleSort1( string r, int n, vector< string > & arry )
{
    int low = 0;
    int high= n -1; //设置变量的初始值
    int j;
    char tmp;
    while ( low < high )
    {
        for ( j= low; j < high; ++j ) //正向冒泡,找到最大者
            if ( r[ j ] > r[ j + 1 ] )
            {
                tmp = r[ j ];
                r[ j ] = r[ j + 1 ];
                r[ j + 1 ] = tmp;
                swap( arry[ j ], arry[ j + 1 ] );
            }
        --high;                 //修改high值, 前移一位
        for ( j = high; j > low; --j ) //反向冒泡,找到最小者
            if ( r[ j ] < r[ j - 1 ] )
            {
                tmp = r[ j ];
                r[ j ] = r[ j - 1 ];
                r[ j - 1 ] = tmp;
                swap( arry[ j ], arry[ j - 1 ] );
            }
        ++low;                  //修改low值,后移一位
    }
}

void bubbleSort2( string r, int n, vector< string > & arry )
{
    int low = 0;
    int high= n -1; //设置变量的初始值
    int j;
    char tmp;
    string s = r;
    while ( low < high )
    {
        for ( j= low; j < high; ++j ) //正向冒泡,找到最大者
            if ( r[ j ] > r[ j + 1 ] )
            {
                tmp = r[ j ];
                r[ j ] = r[ j + 1 ];
                r[ j + 1 ] = tmp;
            }
        --high;                 //修改high值, 前移一位
        for ( j = high; j > low; --j ) //反向冒泡,找到最小者
            if ( r[ j ] < r[ j - 1 ] )
            {
                tmp = r[ j ];
                r[ j ] = r[ j - 1 ];
                r[ j - 1 ] = tmp;
            }
        ++low;                  //修改low值,后移一位
    }
    for ( int i = 0; i < n; i++ )
    {
        for ( int k = 0; k < n; k++ )
        {
            if ( r[ i ] == s[ k ] )
            {
                r[ k ] = '#';
                swap( arry[ i ], arry[ k ] );
                break;
            }
        }
    }
}
