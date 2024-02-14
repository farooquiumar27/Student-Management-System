#include<stdio.h>
#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/blexception>

using namespace std;
using namespace inventory;
using namespace buissness_layer;

int main( )
{
int z;
UnitOfMeasurmentManager unitOfMeasurmentManager;
z=unitOfMeasurmentManager.getUnitOfMeasurmentCount( );
cout<<z<<endl;
return 0;
}