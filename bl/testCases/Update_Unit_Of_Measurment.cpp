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
UnitOfMeasurment unitOfMeasurment;
int code;
string title;
try
{
cout<<"Enter code: ";
cin>>code;
cout<<"Enter title to update: ";
cin>>title;
unitOfMeasurment.setTitle(title);
unitOfMeasurment.setCode(code);
UnitOfMeasurmentManager manager;
manager.updateUnitOfMeasurment(&unitOfMeasurment);
cout<<"Updated successfully"<<endl;
}catch(BLException blException)
{
if(blException.hasGenericException( ))cout<<blException.getBLException( )<<endl;
if(blException.hasPropertyException("code"))cout<<blException.getPropertyException("code")<<endl;
if(blException.hasPropertyException("title"))cout<<blException.getPropertyException("title")<<endl;
}
return 0;
}