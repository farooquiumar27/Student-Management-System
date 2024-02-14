#include<iostream>
#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<dl/daoexception>
using namespace std;
using namespace inventory;
using namespace data_layer;

int main( )
{
UnitOfMeasurment uOm1(string("James Bond"));
UnitOfMeasurment uOm2(string("Ethan Hunt"));
UnitOfMeasurment uOm3(string("Jerry"));
UnitOfMeasurment uOm4(string("Jerry Hunt"));
UnitOfMeasurment uOm5(string("Shahid Afridi"));
UnitOfMeasurmentDAO uOmdao;
try
{
uOmdao.add(&uOm1);
uOmdao.add(&uOm2);
uOmdao.add(&uOm3);
uOmdao.add(&uOm4);
uOmdao.add(&uOm5);
} catch(DAOException daoexception)
{
cout<<daoexception.what( )<<endl;
}
return 0;
}