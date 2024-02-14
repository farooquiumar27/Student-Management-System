#include<iostream>
#include<iuom>
#include<uom>
#include<iuomdao>
#include<uomdao>

using namespace std;
using namespace inventory;
using namespace data_layer;

int main( )
{
UnitOfMeasurmentDAO unitOfMeasurmentDAO;
cout<<"Number of objects are  "<<unitOfMeasurmentDAO.getCount( )<<endl;
return 0;
}