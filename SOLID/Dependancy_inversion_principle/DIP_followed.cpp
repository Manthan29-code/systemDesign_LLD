#include<iostream>
using namespace std;

// Abstraction (Interface)
class Database
{
    public:
    virtual void save(string data) = 0; // Pure virtual function
};

class MySQLDatabase : public Database  {

    public :
    void save( string data ){
        cout << " Executing Sql Query : INSERT INTO users VALUE('" << data << "');" << endl;
    }
};

class MongoDBDatabase : public Database{

    public :
        void save(string data){
            cout << "Executing MongoDB Function: db.users.insert({name: '" << data << "'})" << endl;
}
};

class UserServices {
    private :
    Database* db ;

    public :
        UserServices(Database* database ){
            db = database;
        }
        void storeUser( string user ){
            db->save(user);
        }
};

int main()
{
    MySQLDatabase mysql;
    MongoDBDatabase mongodb;

    UserServices service1(&mysql);
    service1.storeUser("Aditya");

    UserServices service2(&mongodb);
    service2.storeUser("Rohit");
}