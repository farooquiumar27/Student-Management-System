#include<iostream>
#include<bl/blexception>
#include<map>
using namespace std;
using namespace inventory;
using namespace buissness_layer;



BLException::BLException( )
{
this->genericException="";
}


BLException::BLException(string message)
{
this->genericException=message;
}


BLException::BLException(const BLException &other)
{
this->genericException=other.genericException;
this->exceptions=other.exceptions;
}


BLException & BLException::operator=(const BLException &other)
{
this->genericException=other.genericException;
this->exceptions=other.exceptions;
}


BLException::~BLException( ) throw( )
{
//do nothing
}


const char* BLException::what( ) const throw( )
{
return this->genericException.c_str( );
}


void BLException::setBLException(string genericException)
{
this->genericException=genericException;
}


string BLException::getBLException( )
{
return this->genericException;
}


void BLException::addPropertyException(string property, string exception)
{
this->exceptions.insert(pair<string,string>(property,exception));
}


string BLException::getPropertyException(string property)
{
map<string,string>::iterator i=this->exceptions.begin( );
i=exceptions.find(property);
if(i==exceptions.end( ))
{
return string("");
}
return i->second;
}


int BLException::hasPropertyException(string property)
{
return this->getPropertyException(property).length( )>0;
}

int BLException::hasGenericException( )
{
return this->genericException.length( )>0;
}

int BLException::hasException( )
{
int count=0;
if(this->genericException.length( )>0)count++;
if(this->exceptions.size( )>0)count++;
return count;
}


int BLException::hasPropertyExceptions( )
{
return this->getPropertyExceptionsCount( )>0;
}


int BLException::getPropertyExceptionsCount( )
{
return this->exceptions.size( );
}
