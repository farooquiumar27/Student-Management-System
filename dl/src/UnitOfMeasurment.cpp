#include<dl/iuom>
#include<dl/uom>
using namespace inventory;
using namespace data_layer;

#include<iostream>
using namespace std;

UnitOfMeasurment::UnitOfMeasurment( )
{
this->code=0;
this->title="";
}

UnitOfMeasurment::UnitOfMeasurment(string str)
{
this->code=0;
this->title=str;
}

UnitOfMeasurment::UnitOfMeasurment(const UnitOfMeasurment &other)
{
this->code=other.code;
this->title=other.title;
}

UnitOfMeasurment:: ~UnitOfMeasurment( )
{
//do nothing
}

void UnitOfMeasurment::setCode(int code)
{
this->code=code;
}

int UnitOfMeasurment::getCode( )const
{
return this->code;
}
void UnitOfMeasurment::setTitle(string title)
{
this->title=title;
}

string UnitOfMeasurment::getTitle( )const
{
return this->title;
}

abc::IUnitOfMeasurment & UnitOfMeasurment::operator=(const abc::IUnitOfMeasurment &other)
{
this->code=other.getCode( );
this->title=other.getTitle( );
return *this;
}

int UnitOfMeasurment::operator==(const abc::IUnitOfMeasurment &other)
{
return this->code==other.getCode( );
}

int UnitOfMeasurment::operator!=(const abc::IUnitOfMeasurment &other)
{
return this->code!=other.getCode( );
}

int UnitOfMeasurment::operator<=(const abc::IUnitOfMeasurment &other)
{
return this->code<=other.getCode( );
}

int UnitOfMeasurment::operator>=(const abc::IUnitOfMeasurment &other)
{
return this->code>=other.getCode( );
}

int UnitOfMeasurment::operator<(const abc::IUnitOfMeasurment &other)
{
return this->code<other.getCode( );
}

int UnitOfMeasurment::operator>(const abc::IUnitOfMeasurment &other)
{
return this->code>other.getCode( );
}
