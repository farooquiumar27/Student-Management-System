#include<iostream>
#include<string.h>
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
char a[25];
fflush(stdin);
cout<<"Enter title to search :";
fgets(a,25,stdin);
fflush(stdin);
a[strlen(a)-1]='\0';
string str(a);
abc::IUnitOfMeasurment *unitOfMeasurment;
if(unitOfMeasurmentDAO.titleExist(str))cout<<"Title exists"<<endl;
else cout<<"Title does not exists"<<endl;
return 0;
}