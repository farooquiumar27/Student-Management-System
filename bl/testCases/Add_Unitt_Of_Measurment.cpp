#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>

using namespace inventory;
using namespace buissness_layer;
using namespace std;

int main( )
{
UnitOfMeasurmentManager unitOfMeasurmentManager;
UnitOfMeasurment unitOfMeasurment;
string title;
try
{
cout<<"Enter title to add: ";
cin>>title;
unitOfMeasurment.setTitle(title);
unitOfMeasurment.setCode(0);
unitOfMeasurmentManager.addUnitOfMeasurment(&(unitOfMeasurment));
cout<<"Add successfully"<<endl;
}
catch(BLException blException)
{
if(blException.hasGenericException( ))cout<<blException.getBLException( )<<endl;
if(blException.hasPropertyException("code"))cout<<blException.getPropertyException("code")<<endl;
if(blException.hasPropertyException("title"))cout<<blException.getPropertyException("title")<<endl;
}
return 0;
}