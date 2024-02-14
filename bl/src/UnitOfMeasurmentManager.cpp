#include<iostream>
#include<bl/iuom>
#include<bl/uom>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/blexception>
#include<forward_list>
#include<map>
#include<dl/iuom>
#include<dl/uom>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<dl/daoexception>
#include<common/stringutils>


using namespace inventory;
using namespace buissness_layer;
using namespace stringutils;
using namespace std;

bool UnitOfMeasurmentTitleComparator::operator( )(string *left,string *right)
{
return compareStringIgnoreCase(left->c_str(),right->c_str())<0;
}

UnitOfMeasurmentManager::DataModel UnitOfMeasurmentManager::dataModel;

UnitOfMeasurmentManager::DataModel::DataModel( )
{
populateDataStructure( );
}
UnitOfMeasurmentManager::DataModel::~DataModel( )
{

}
void UnitOfMeasurmentManager::DataModel::populateDataStructure( )
{
inventory::data_layer::UnitOfMeasurmentDAO unitOfMeasurmentDAO;
forward_list<inventory::data_layer::abc::IUnitOfMeasurment *> *dlUnitOfMeasurments;
try
{
dlUnitOfMeasurments=unitOfMeasurmentDAO.getAll( );
_UnitOfMeasurment *blUnitOfMeasurment;
forward_list<inventory::data_layer::abc::IUnitOfMeasurment *>::iterator i;
int code;
string *title;
inventory::data_layer::abc::IUnitOfMeasurment *dlUnitOfMeasurment;
for(i=dlUnitOfMeasurments->begin( );i!=dlUnitOfMeasurments->end( );++i)
{
dlUnitOfMeasurment=*i;
code=dlUnitOfMeasurment->getCode( );
title=new string(dlUnitOfMeasurment->getTitle( ));
blUnitOfMeasurment=new _UnitOfMeasurment;
blUnitOfMeasurment->code=code;
blUnitOfMeasurment->title=title;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurment *>(code,blUnitOfMeasurment));
dataModel.titleWiseMap.insert(pair<string*,_UnitOfMeasurment *>(title,blUnitOfMeasurment));
delete dlUnitOfMeasurment;
}
dlUnitOfMeasurments->clear( );
delete dlUnitOfMeasurments;
}
catch(inventory::data_layer::DAOException &daoException)
{
//no need to do anything
}
}


void UnitOfMeasurmentManager::addUnitOfMeasurment(abc::IUnitOfMeasurment *unitOfMeasurment) throw(BLException)
{
BLException blException;
if(unitOfMeasurment==NULL)
{
blException.setBLException(string("Unit of measurment required , NULL encountered"));
throw blException;
}
int code=unitOfMeasurment->getCode( );
string title=unitOfMeasurment->getTitle( );
if(code!=0)
{
blException.addPropertyException("code","Code should be zero");
}
if(title.length( )==0)
{
blException.addPropertyException("title","Title required");
}
if(title.length( )>50)
{
blException.addPropertyException("title","Title cannot exceed 50 characters");
}
if(blException.hasPropertyExceptions( ))
{
throw blException;
}

map<string*,_UnitOfMeasurment *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end( ))
{
blException.setBLException("Title already exsists");
throw blException;
}
inventory::data_layer::abc::IUnitOfMeasurment *dlUnitOfMeasurment;
inventory::data_layer::UnitOfMeasurmentDAO unitOfMeasurmentDAO;
try
{
dlUnitOfMeasurment=new inventory::data_layer::UnitOfMeasurment;
dlUnitOfMeasurment->setCode(0);
dlUnitOfMeasurment->setTitle(title);
unitOfMeasurmentDAO.add(dlUnitOfMeasurment);
unitOfMeasurment->setCode(dlUnitOfMeasurment->getCode( ));
delete dlUnitOfMeasurment;
_UnitOfMeasurment *blUnitOfMeasurment;
blUnitOfMeasurment=new _UnitOfMeasurment;
code=unitOfMeasurment->getCode( );
string *t=new string(unitOfMeasurment->getTitle( ));
blUnitOfMeasurment->code=code;
blUnitOfMeasurment->title=t;
dataModel.codeWiseMap.insert(pair<int,_UnitOfMeasurment *>(code,blUnitOfMeasurment));
dataModel.titleWiseMap.insert(pair<string*,_UnitOfMeasurment *>(t,blUnitOfMeasurment));
}
catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setBLException(string(daoException.what( )));
throw blException;
}
}

void UnitOfMeasurmentManager::updateUnitOfMeasurment(abc::IUnitOfMeasurment *unitOfMeasurment) throw(BLException)
{
BLException blException;
if(unitOfMeasurment==NULL)
{
blException.setBLException(string("Unit of measurment required , NULL encountered"));
throw blException;
}
int code=unitOfMeasurment->getCode( );
string title=unitOfMeasurment->getTitle( );
if(code==0)
{
blException.addPropertyException("code","Code cannot be zero");
}
if(title.length( )==0)
{
blException.addPropertyException("title","Title required");
}
if(title.length( )>50)
{
blException.addPropertyException("title","Title cannot exceed 50 characters");
}
if(blException.hasPropertyExceptions( ))
{
throw blException;
}
map<int,_UnitOfMeasurment *>::iterator ic;
ic=dataModel.codeWiseMap.find(code);
if(ic==dataModel.codeWiseMap.end( ))
{
blException.setBLException("Code does not exsists");
throw blException;
}
map<string*,_UnitOfMeasurment *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end( ))
{
blException.setBLException("Title already exsists");
throw blException;
}
inventory::data_layer::abc::IUnitOfMeasurment *dlUnitOfMeasurment;
inventory::data_layer::UnitOfMeasurmentDAO unitOfMeasurmentDAO;
try
{
dlUnitOfMeasurment=new inventory::data_layer::UnitOfMeasurment;
dlUnitOfMeasurment->setCode(code);
dlUnitOfMeasurment->setTitle(title);
unitOfMeasurmentDAO.update(dlUnitOfMeasurment);
delete dlUnitOfMeasurment;
_UnitOfMeasurment *blUnitOfMeasurment;
blUnitOfMeasurment=new _UnitOfMeasurment;
blUnitOfMeasurment->code=code;
blUnitOfMeasurment->title=&title;
dataModel.codeWiseMap[code]=blUnitOfMeasurment;
dataModel.titleWiseMap[&title]=blUnitOfMeasurment;
}
catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setBLException(string(daoException.what( )));
throw blException;
}
}

void UnitOfMeasurmentManager::removeUnitOfMeasurment(abc::IUnitOfMeasurment *unitOfMeasurment) throw(BLException)
{
BLException blException;
if(unitOfMeasurment==NULL)
{
blException.setBLException(string("Unit of measurment required , NULL encountered"));
throw blException;
}
int code=unitOfMeasurment->getCode( );
string title=unitOfMeasurment->getTitle( );
if(code==0)
{
blException.addPropertyException("code","Code cannot be zero");
}
if(title.length( )==0)
{
blException.addPropertyException("title","Title required");
}
if(title.length( )>50)
{
blException.addPropertyException("title","Title cannot exceed 50 characters");
}
if(blException.hasPropertyExceptions( ))
{
throw blException;
}
map<int,_UnitOfMeasurment *>::iterator ic;
ic=dataModel.codeWiseMap.find(code);
if(ic==dataModel.codeWiseMap.end( ))
{
blException.setBLException("Code does not exsists");
throw blException;
}
_UnitOfMeasurment *blUnitOfMeasurment;
blUnitOfMeasurment=ic->second;
string t=*(blUnitOfMeasurment->title);
if(compareStringIgnoreCase(t.c_str( ),title.c_str())!=0)
{
blException.setBLException("Code does not match with the provided title.");
throw blException;
}
inventory::data_layer::UnitOfMeasurmentDAO unitOfMeasurmentDAO;
try
{
unitOfMeasurmentDAO.remove(code);
dataModel.codeWiseMap.erase(code);
dataModel.titleWiseMap.erase(&title);
}
catch(inventory::data_layer::DAOException daoException)
{
BLException blException;
blException.setBLException(string(daoException.what( )));
throw blException;
}
}

abc::IUnitOfMeasurment* UnitOfMeasurmentManager::getUnitOfMeasurmentByCode(int code) throw(BLException)
{
BLException blException;
if(code==0)
{
blException.setBLException("Code cannot be zero");
throw blException;
}
_UnitOfMeasurment *blUnitOfMeasurment;
abc::IUnitOfMeasurment *unitOfMeasurment;
map<int,_UnitOfMeasurment *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end( ))
{
char g[20];
sprintf(g,"No object exist with code : %d",code);
blException.setBLException(string(g));
throw blException;
}
blUnitOfMeasurment=i->second;
unitOfMeasurment=new UnitOfMeasurment;
unitOfMeasurment->setCode(code);
unitOfMeasurment->setTitle(*(blUnitOfMeasurment->title));
return unitOfMeasurment;
}

abc::IUnitOfMeasurment* UnitOfMeasurmentManager::getUnitOfMeasurmentByTitle(string title) throw(BLException)
{
BLException blException;
if(title=="")
{
blException.setBLException("Title cannot be be empty");
throw blException;
}
_UnitOfMeasurment *blUnitOfMeasurment;
abc::IUnitOfMeasurment *unitOfMeasurment;
map<string *,_UnitOfMeasurment *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i==dataModel.titleWiseMap.end( ))
{
char g[101];
sprintf(g,"No object exist with title : %s",title.c_str( ));
blException.setBLException(string(g));
throw blException;
}
blUnitOfMeasurment=i->second;
unitOfMeasurment=new UnitOfMeasurment;
unitOfMeasurment->setCode(blUnitOfMeasurment->code);
unitOfMeasurment->setTitle(*(blUnitOfMeasurment->title));
return unitOfMeasurment;
}


forward_list<abc::IUnitOfMeasurment *> * UnitOfMeasurmentManager::getAllUnitOfMeasurments( ) throw(BLException)
{
map<int,_UnitOfMeasurment *>::iterator i;
i=dataModel.codeWiseMap.begin( );
if(i==dataModel.codeWiseMap.end( ))
{
BLException blException;
blException.setBLException("No UnitOfMeasurment found.");
throw blException;
}
forward_list<abc::IUnitOfMeasurment *> *unitOfMeasurments;
unitOfMeasurments=new forward_list<abc::IUnitOfMeasurment *>;
forward_list<abc::IUnitOfMeasurment *>::iterator listi;
listi=unitOfMeasurments->before_begin( );
_UnitOfMeasurment *blUnitOfMeasurment;
abc::IUnitOfMeasurment *unitOfMeasurment;
while(i!=dataModel.codeWiseMap.end( ))
{
blUnitOfMeasurment=i->second;
unitOfMeasurment=new UnitOfMeasurment;
unitOfMeasurment->setCode(blUnitOfMeasurment->code);
unitOfMeasurment->setTitle(*(blUnitOfMeasurment->title));
listi=unitOfMeasurments->insert_after(listi,unitOfMeasurment);
++i;
}
return unitOfMeasurments;
}


int UnitOfMeasurmentManager::unitOfMeasurmentCodeExists(int code) throw(BLException)
{
map<int,_UnitOfMeasurment *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end ( ))return 0;
else return 1;
}

int UnitOfMeasurmentManager::unitOfMeasurmentTitleExists(string title) throw(BLException)
{
map<string *,_UnitOfMeasurment *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i==dataModel.titleWiseMap.end ( ))return 0;
else return 1;
}
int UnitOfMeasurmentManager::getUnitOfMeasurmentCount( ) throw(BLException)
{
return dataModel.codeWiseMap.size( );
}
