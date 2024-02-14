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
UnitOfMeasurment uOm(string("Peter Parker"));
uOm.setCode(4);
cout<<uOm.getCode( )<<endl;
UnitOfMeasurmentDAO uOmdao;
try
{
uOmdao.update(&uOm);
cout<<"Updated successfully"<<endl;
} catch(DAOException daoexception)
{
cout<<daoexception.what( )<<endl;
}
return 0;
}