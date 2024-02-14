#include<iostream>
#include<iuom>
#include<string.h>
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
char str[25];
abc::IUnitOfMeasurment *unitOfMeasurment;
fflush(stdin);
cout<<"Enter title to search :";
fgets(str,25,stdin);
fflush(stdin);
str[strlen(str)-1]='\0';
string title(str);
unitOfMeasurment=unitOfMeasurmentDAO.getByTitle(title);
cout<<"Code-> "<<unitOfMeasurment->getCode( )<<" , Title-> "<<unitOfMeasurment->getTitle( )<<endl;
}catch(DAOException daoexception)
{
cout<<daoexception.what( )<<endl;
}
return 0;
}