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
int code;
cout<<"Enter code to delete: ";
cin>>code;
UnitOfMeasurmentDAO uOmdao;
try
{
uOmdao.remove(code);
cout<<"Deleted successfully"<<endl;
} catch(DAOException daoexception)
{
cout<<daoexception.what( )<<endl;
}
return 0;
}