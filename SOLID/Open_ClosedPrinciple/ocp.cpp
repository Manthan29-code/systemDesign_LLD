#include<iostream>
#include<vector>

using namespace std ;

class Product {
    public :
        string name ;
        double price ;
    
        Product( string n , double p ){
            this->name = n ;
            this->price = p ;
        }

};

class ShopingCart{

    private :
        vector< Product* > product ;

    public :
        void addProduct( Product* p){
            product.push_back(p);
        }
        const vector<Product* >& getProduct(){
            return product ;
        }

        double calculateTotal()
        {
            double total = 0;
            for (auto p : product)
            {
                total += p->price;
            }
            return total;
        }
};

class ShoppingCartPrinter
{
private:
    ShopingCart *cart;

public:
    ShoppingCartPrinter(ShopingCart *cart)
    {
        this->cart = cart;
    }

    void printInvoice()
    {
        if (!cart->getProduct().size()){
            cout << " add some product " << endl ; 
            return ;
        }
        cout << "Shopping Cart Invoice:\n";
        for (auto p : cart->getProduct())
        {
            cout << p->name << " - Rs " << p->price << endl;
        }
        cout << "Total: Rs " << cart->calculateTotal() << endl;
    }
};


// Abstruct Class 
class Persistence {
    private :
        ShopingCart* cart ;
    public :
        virtual void save(ShopingCart *cart) = 0;
};

class SQLPersistence : public Persistence {
    public :
        void save(ShopingCart *cart) override{
            if (!cart->getProduct().size())
            {
                cout << " add some product " << endl;
                return;
            }
            cout << "Saving shopping cart to SQL DB..." << endl;
        }
};

class MongoPersistence : public Persistence
{
public:
    void save(ShopingCart *cart) override
    {
        if (!cart->getProduct().size())
        {
            cout << " add some product " << endl;
            return;
        }
        cout << "Saving shopping cart to MongoDB..." << endl;
    }
};

class FilePersistence : public Persistence
{
public:
    void save(ShopingCart *cart) override
    {
        if (!cart->getProduct().size())
        {
            cout << " add some product " << endl;
            return;
        }
        cout << "Saving shopping cart to a file..." << endl;
    }
};

int main(){

    ShopingCart* cart = new ShopingCart();
    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 2000));

    ShoppingCartPrinter *printer = new ShoppingCartPrinter(cart);
    printer->printInvoice();

    Persistence *db = new SQLPersistence();
    Persistence *mongo = new MongoPersistence();
    Persistence *file = new FilePersistence();

    db->save(cart);    // Save to SQL database
    mongo->save(cart); // Save to MongoDB
    file->save(cart);  // Save to File

    return 0;
};