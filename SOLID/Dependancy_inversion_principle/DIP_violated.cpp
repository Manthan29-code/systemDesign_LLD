#include <iostream>
using namespace std;

class MySQLDatabase // Low-level module
{
public:
    void saveToSql(string data)
    {
        cout << " Executing Sql Query : INSERT INTO users VALUE('" << data << "');" << endl;
    }
};

class MongoDBDatabase // Low-level module
{
public:
    void saveToMongo(string data)
    {
        cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
    }
};

class UserServices
{
    private:
    MySQLDatabase sqlDb; // Direct dependency on MySQL
    MongoDBDatabase mongoDb; // Direct dependency on MongoDB

    public : 
    void storeUserToSQL ( string user) {
        sqlDb.saveToSql(user);
    }

    void storeUserToMongo(string user){
        mongoDb.saveToMongo(user) ;
    }

};

int main(){
    UserServices service;
    service.storeUserToSQL("Aditya");
    service.storeUserToMongo("Rohit");
}