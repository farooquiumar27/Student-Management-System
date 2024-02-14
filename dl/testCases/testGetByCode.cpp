#include<iostream>
#include<iuom>
#include<uom>
#include<iuomdao>
#include<uomdao>
#include<daoexception>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main( )
{
UnitOfMeasurmentDAO unitOfMeasurmentDAO;
try
{
int code;
abc::IUnitOfMeasurment *unitOfMeasurment;
cout<<"Enter code to search :";
cin>>code;
unitOfMeasurment=unitOfMeasurmentDAO.getByCode(code);
cout<<"Code-> "<<unitOfMeasurment->getCode( )<<" , Title-> "<<unitOfMeasurment->getTitle( )<<endl;
}
catch(DAOException daoexception)
{
cout<<daoexception.what( )<<endl;
}
return 0;
}