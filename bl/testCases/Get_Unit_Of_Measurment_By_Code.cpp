#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>

using namespace std;
using namespace inventory;
using namespace buissness_layer;

int main( )
{
int code;
UnitOfMeasurmentManager manager;
abc::IUnitOfMeasurment *unitOfMeasurment;
try
{
cout<<"Enter the code to search : ";
cin>>code;
unitOfMeasurment=manager.getUnitOfMeasurmentByCode(code);
cout<<"Code : "<<unitOfMeasurment->getCode();
cout<<" --- Title : "<<unitOfMeasurment->getTitle( )<<endl;
}
catch(BLException blException)
{
cout<<blException.getBLException( )<<endl;
}
return 0;
}