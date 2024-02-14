#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/uommanager>

using namespace inventory;
using namespace buissness_layer;
using namespace std;

int main( )
{
UnitOfMeasurmentManager manager;
int code;
cout<<"Enter the code : ";
cin>>code;
if(manager.unitOfMeasurmentCodeExists(code))
{
cout<<"Code found : "<<code<<endl;
}
else
{
cout<<"Code not found : "<<code<<endl;
}
return 0;
}