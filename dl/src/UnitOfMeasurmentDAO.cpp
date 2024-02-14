#include<stdio.h>
#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>

#include<dl/iuomdao>
#include<dl/uomdao>
#include<common/stringutils>
#include<string.h>
#include<fstream>
using namespace inventory;
using namespace data_layer;
using namespace stringutils;
class Header
{
public:
int numberOfRecords;
int lastGeneratedCode;
Header( )
{
this->numberOfRecords=0;
this->lastGeneratedCode=0;
}
};

void UnitOfMeasurmentDAO::add(abc::IUnitOfMeasurment *unitOfMeasurment) throw(DAOException)
{
const string vTitle=unitOfMeasurment->getTitle( );
string title=trimmed(vTitle);
int len=title.length( );
if(len==0)throw(DAOException(string("Title required , length is zero")));
if(len>50)throw(DAOException(string("Title cannot exceed 50 characters")));
_UnitOfMeasurment _unitOfMeasurment;
Header header;
fstream dataFile(FILE_NAME,ios::out | ios::in | ios::binary);
if(dataFile.fail( ))
{
header.numberOfRecords=1;
header.lastGeneratedCode=1;
_unitOfMeasurment.code=1;
strcpy(_unitOfMeasurment.title,title.c_str( ));
ofstream dFile(FILE_NAME,ios::app | ios::binary);
dFile.write((char *)&header,sizeof(Header));
dFile.write((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
dFile.close( );
unitOfMeasurment->setCode(1);
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))
{
dataFile.clear( );
dataFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);
header.numberOfRecords=1;
header.lastGeneratedCode=1;
_unitOfMeasurment.code=1;
strcpy(_unitOfMeasurment.title,title.c_str( ));
dataFile.write((char *)&header,sizeof(Header));
dataFile.write((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
dataFile.close( );
unitOfMeasurment->setCode(1);
dataFile.close( );
return;
}
while(1)
{
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail( ))break;
if(compareStringIgnoreCase(_unitOfMeasurment.title,title.c_str())==0)
{
dataFile.close( );
throw DAOException(title+string(" exists"));
}
}
dataFile.clear( );
dataFile.seekp(0,ios::end);
header.numberOfRecords++;
header.lastGeneratedCode++;
_unitOfMeasurment.code=header.lastGeneratedCode;
strcpy(_unitOfMeasurment.title,title.c_str( ));
dataFile.write((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
dataFile.close( );
unitOfMeasurment->setCode(_unitOfMeasurment.code);
return;
}

void UnitOfMeasurmentDAO::update(abc::IUnitOfMeasurment *unitOfMeasurment) throw(DAOException)
{
int code=unitOfMeasurment->getCode( );
const string vTitle=unitOfMeasurment->getTitle( );
string title=trimmed(vTitle);
int len=title.length( );
if(len==0)throw(DAOException(string("Title required , length is zero")));
if(len>50)throw(DAOException(string("Title cannot exceed 50 characters")));
_UnitOfMeasurment _unitOfMeasurment;
Header header;
fstream dataFile(FILE_NAME,ios::out | ios::in | ios::binary);
if(dataFile.fail( ))
{
throw(DAOException(string("No object exist of unit of measurment")));
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))
{
dataFile.close( );
throw(DAOException(string("No object exist of unit of measurment")));
}
if(header.numberOfRecords==0)
{
dataFile.close( );
throw(DAOException(string("No object exist of unit of measurment")));
}
int found=0;
int pos,d=1;
while(1)
{
pos=dataFile.tellg( );
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail( ))break;
if(code==_unitOfMeasurment.code)
{
found=1;
break;
}
d++;
}
char arr[25];
if(found==0)
{
dataFile.close( );
sprintf(arr,"Code of the given object [ %d ] does not exist",code);
throw(DAOException(string(arr)));
}
dataFile.clear( );
dataFile.seekg(8,ios::beg);
while(1)
{
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail( ))break;
if(compareStringIgnoreCase(_unitOfMeasurment.title,title.c_str())==0)
{
dataFile.close( );
throw DAOException(title+string(" alreay exists in the record"));
}
}
//dataFile.close( );
//fstream datFile(FILE_NAME,ios::out | ios::binary);
//datFile.read((char *)&header,sizeof(Header));
dataFile.clear( );
dataFile.seekp(pos,ios::beg);
/*
int w=1;
while(w<d)
{
datFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
w++;
}
*/

strcpy(_unitOfMeasurment.title,title.c_str( ));
_unitOfMeasurment.code=code;
//datFile.clear( );
dataFile.write((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
dataFile.close( );
return;
}

void UnitOfMeasurmentDAO::remove(int code) throw(DAOException)
{
if(code<1)throw(DAOException(string("Invalid code")));
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail( ))throw(DAOException(string("No object exists of unit of measurment")));
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))
{
dataFile.close( );
throw(DAOException(string("No object exists of unit of measurment")));
}
if(header.numberOfRecords==0)
{
dataFile.close( );
throw(DAOException(string("No object exists of unit of measurment")));
}
_UnitOfMeasurment _unitOfMeasurment;
fstream datFile("temp.data",ios::app |ios::in |ios::binary);
header.numberOfRecords--;
datFile.write((char *)&header,sizeof(Header));
int found=0;
while(1)
{
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail( ))break;
if(_unitOfMeasurment.code==code)
{
found=1;
}
else
{
datFile.write((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
}
}
dataFile.close( );
datFile.close( );
if(found==0)
{
char arr[20];
sprintf(arr,"No object found in records of code %d",code);
throw(DAOException(string(arr)));
}
fstream datF("temp.data",ios::in | ios::binary);
fstream dataF(FILE_NAME,ios::out | ios::binary);
datF.read((char *)&header,sizeof(Header));
dataF.write((char *)&header,sizeof(Header));
while(1)
{
datF.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(datF.fail( ))break;
dataF.write((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
}
dataF.close( );
datF.close( );
ofstream d("temp.data",ios::out | ios::binary);
d.close( );
return;
}

abc::IUnitOfMeasurment* UnitOfMeasurmentDAO::getByCode(int code) throw(DAOException)
{
_UnitOfMeasurment _unitOfMeasurment;
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail( ))
{
throw(DAOException(string("NO unit of measurment is there")));
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))
{
dataFile.close( );
throw(DAOException(string("NO unit of measurment is there")));
}
if(header.numberOfRecords==0)
{
dataFile.close( );
throw(DAOException(string("NO unit of measurment is there")));
}

abc::IUnitOfMeasurment *unitOfMeasurment;

while(1)
{
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail( ))break;
if(_unitOfMeasurment.code==code)
{
unitOfMeasurment=new UnitOfMeasurment;
unitOfMeasurment->setCode(_unitOfMeasurment.code);
unitOfMeasurment->setTitle(string(_unitOfMeasurment.title));
dataFile.close( );
return unitOfMeasurment;
}
}
dataFile.close( );
char arr[25];
sprintf(arr,"No object exist with code %d",code);
throw(DAOException(string(arr)));
}

abc::IUnitOfMeasurment* UnitOfMeasurmentDAO::getByTitle(string vTitle) throw(DAOException)
{
const string title=trimmed(vTitle);

_UnitOfMeasurment _unitOfMeasurment;
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail( ))
{
throw(DAOException(string("NO unit of measurment is there")));
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))
{
dataFile.close( );
throw(DAOException(string("NO unit of measurment is there")));
}
if(header.numberOfRecords==0)
{
dataFile.close( );
throw(DAOException(string("NO unit of measurment is there")));
}

abc::IUnitOfMeasurment *unitOfMeasurment;
while(1)
{
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail( ))break;
if(compareStringIgnoreCase(_unitOfMeasurment.title,title.c_str())==0)
{
dataFile.close( );
unitOfMeasurment=new UnitOfMeasurment;
unitOfMeasurment->setCode(_unitOfMeasurment.code);
unitOfMeasurment->setTitle(string(_unitOfMeasurment.title));
return unitOfMeasurment;
}
}
dataFile.close( );
char arr[25];
sprintf(arr,"No object exist with string %s",title.c_str());
throw(DAOException(string(arr)));
}

forward_list<abc::IUnitOfMeasurment*>* UnitOfMeasurmentDAO::getAll( ) throw(DAOException)
{
_UnitOfMeasurment _unitOfMeasurment;
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail( ))
{
//dataFile.close( );
throw(DAOException(string("NO unit of measurment is there")));
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))
{
dataFile.close( );
throw(DAOException(string("NO unit of measurment is there")));
}
if(header.numberOfRecords==0)
{
dataFile.close( );
throw(DAOException(string("NO unit of measurment is there")));
}

forward_list<abc::IUnitOfMeasurment *> *list;
list=new forward_list<abc::IUnitOfMeasurment *>;
forward_list<abc::IUnitOfMeasurment *>::iterator i=list->before_begin( );
abc::IUnitOfMeasurment *unitOfMeasurment;

while(1)
{
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail( ))break;
unitOfMeasurment=new UnitOfMeasurment;
unitOfMeasurment->setCode(_unitOfMeasurment.code);
unitOfMeasurment->setTitle(string(_unitOfMeasurment.title));
 i=list->insert_after(i,unitOfMeasurment);
}
dataFile.close( );
return list;
}



int UnitOfMeasurmentDAO::getCount( ) throw(DAOException)
{
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail( ))return 0;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))return 0;
if(header.numberOfRecords==0)return 0;
return header.numberOfRecords;
}

int UnitOfMeasurmentDAO::codeExist(int code) throw(DAOException)
{
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::binary);
if(dataFile.fail())return 0;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))
{
dataFile.close( );
return 0;
}
if(header.numberOfRecords==0)
{
dataFile.close( );
return 0;
}
_UnitOfMeasurment _unitOfMeasurment;
while(1)
{
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail( ))break;
if(code==_unitOfMeasurment.code)
{
dataFile.close( );
return 1;
}
}
dataFile.close( );
return 0;
}

int UnitOfMeasurmentDAO::titleExist(string vTitle) throw(DAOException)
{
const string title=trimmed(vTitle);
if(title.length( )==0)return 0;
Header header;
fstream dataFile(FILE_NAME,ios::in | ios::out);
if(dataFile.fail( ))return 0;
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail( ))
{
dataFile.close( );
return 0;
}
if(header.numberOfRecords==0)
{
dataFile.close( );
return 0;
}
_UnitOfMeasurment _unitOfMeasurment;
while(1)
{
dataFile.read((char *)&_unitOfMeasurment,sizeof(_UnitOfMeasurment));
if(dataFile.fail())break;
if(compareStringIgnoreCase(_unitOfMeasurment.title,title.c_str())==0)
{
dataFile.close( );
return 1;
}
}
dataFile.close( );
return 0;
}

