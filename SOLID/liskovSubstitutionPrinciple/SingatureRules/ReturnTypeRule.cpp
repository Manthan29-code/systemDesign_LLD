#include <iostream>

using namespace std ;

// Return Type Rule :
// Subtype overriden method return type should be either identical
// or narrower then the parent method's return type.
// This is also called as return type covariance.
// C++ enforces this by covariance.

class GrandAnimal
{
    // some common Animal methods
};
class Animal : public GrandAnimal
{
    // some common Animal methods
};


class Dog : public Animal {
    // Additional Dog method specification to Dogs 
};

class Parent {
    public :
    virtual Animal* getAnimal (){
        cout << " Parent : returning Animal instant "  << endl ; 
        return new Animal() ;
    }
};

class Child : public Parent {

    public :
        Animal *getAnimal() override
        {
            cout << "Child : Returning Dog instance" << std::endl;
            // return new GrandAnimal();
            return new Animal();
        }
};


class Client {
    private : 
        Parent* p ;
    public :
        Client(Parent* p){
            this->p = p ;
        }

        void takeAnimal(){
            p->getAnimal();
        }

};

int main(){

    Parent* parent = new Parent();
    Child* child = new Child();

    // Client* client = new Client(child);
    Client* client = new Client(parent);
    client->takeAnimal();
}