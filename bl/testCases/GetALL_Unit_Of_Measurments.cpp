#include<iostream>
#include<forward_list>
#include<bl/iuom>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>

using namespace std;
using namespace inventory;
using namespace buissness_layer;

int main( )
{
UnitOfMeasurmentManager unitOfMeasurmentManager;
abc::IUnitOfMeasurment *unitOfMeasurment;
forward_list<abc::IUnitOfMeasurment *> *list;
try
{
list=unitOfMeasurmentManager.getAllUnitOfMeasurments( );
forward_list<abc::IUnitOfMeasurment *>::iterator i;
for(i=list->begin( );i!=list->end( );++i)
{
unitOfMeasurment=*i;
cout<<"Code : "<<unitOfMeasurment->getCode( );
cout<<"-----Title : "<<unitOfMeasurment->getTitle( )<<endl;
}
}
catch(BLException blException)
{
cout<<blException.getBLException( )<<endl;
}
return 0;
}
