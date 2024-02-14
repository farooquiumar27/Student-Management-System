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
string title;
cout<<"Enter title : ";
cin>>title;
if(manager.unitOfMeasurmentTitleExists(title))
{
cout<<"Title found : "<<title<<endl;
}
else
{
cout<<"Title not found : "<<title<<endl;
}
return 0;
}