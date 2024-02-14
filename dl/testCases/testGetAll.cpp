#include<iostream>
#include<forward_list>
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
forward_list<abc::IUnitOfMeasurment *> *list;
forward_list<abc::IUnitOfMeasurment *>::iterator i;
abc::IUnitOfMeasurment *unitOfMeasurment;
try
{
list=unitOfMeasurmentDAO.getAll( );
i=list->begin( );
while(i!=list->end( ))
{
unitOfMeasurment=*i;
cout<<"Code: "<<unitOfMeasurment->getCode( );
cout<<" -- Title: "<<unitOfMeasurment->getTitle( )<<"]]"<<endl;
cout<<"Title length :"<<unitOfMeasurment->getTitle( ).length( )<<endl;
++i;
}

}catch(DAOException daoexception)
{
cout<<daoexception.what( )<<endl;
}
return 0;
}