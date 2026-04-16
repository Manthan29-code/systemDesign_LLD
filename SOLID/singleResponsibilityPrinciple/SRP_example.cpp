#include<iostream>
#include<string>
#include <vector>

using namespace std;

class Product {
    public :
    string name ;
    double price ;

    Product( string name , double price){
        this->name = name ;
        this->price = price ;
    }

};

class ShoppingCart{
    private :
        vector<Product*>  products ;
    public :
        void addProduct(Product *p)
        {
            products.push_back(p);
        }

        const vector<Product* >& getProducts(){
            return products ;
        }

        //calculate total price 
        double calculateTotal() {
            double total = 0 ;
            if (products.size() == 0 ){
                cout << " add some product " << endl ;
                return 0.0;
            }
            for (auto p : products)
            {
                total += p->price;
            }
            return total ;
        }
};

class shopingCartPrinter {
    private :
        ShoppingCart* cart ;
    public :
        shopingCartPrinter( ShoppingCart* cart ){
            this->cart = cart;
        }
    
        void printInvoice(){
            if (cart->getProducts().empty())
            {
                cout << "No items in cart. Please add some products." << endl;
                return ; // exit early, cleanly
            }
            cout << "shoping cart Invoice " << endl ;
            for (auto p : cart->getProducts()){
                cout << p->name << " - Rs " << p->price << endl;
            }
            cout << "Total: Rs " << cart->calculateTotal() << endl ;
        }

};

class ShoppingCartStorage{
    private :
        ShoppingCart* cart ;
    public:
        ShoppingCartStorage(ShoppingCart* cart){
            this->cart = cart ;
        }
        void saveToDatabase(){
            cout << " Saving shopping cart to database " << endl ;
        }
      
};

int main(){
    ShoppingCart *cart = new ShoppingCart();

    cart->addProduct(new Product("Laptop", 50000));
    cart->addProduct(new Product("Mouse", 2000));

    shopingCartPrinter* printer = new shopingCartPrinter(cart);
    printer->printInvoice();

    ShoppingCartStorage *db = new ShoppingCartStorage(cart);
    db->saveToDatabase();

    return 0;
}