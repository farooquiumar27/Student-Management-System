#include<iostream>
using namespace std;
#include<dl/daoexception>
using namespace inventory;
using namespace data_layer;

DAOException::DAOException( )
{
this->message="";
}

DAOException::DAOException(string message)
{
this->message=message;
}

DAOException::DAOException(const DAOException &other)
{
this->message=other.message;
}
DAOException & DAOException::operator=(const DAOException &other)
{
this->message=other.message;
}

DAOException::~DAOException( ) throw( )
{
//do nothing
}

const char* DAOException::what( ) const throw( )
{
return this->message.c_str( );
}
