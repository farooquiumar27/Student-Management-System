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
int code;
abc::IUnitOfMeasurment *unitOfMeasurment;
cout<<"Enter code to search :";
cin>>code;
if(unitOfMeasurmentDAO.codeExist(code))cout<<"Code exists"<<endl;
else cout<<"Code does not exists"<<endl;
return 0;
}