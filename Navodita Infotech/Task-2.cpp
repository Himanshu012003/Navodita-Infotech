#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Product {
public:
    Product(int id, string name, double price, int stock) : id(id), name(name), price(price), stock(stock) {}

    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }

    void updateStock(int quantity) {
        stock += quantity;
    }

private:
    int id;
    string name;
    double price;
    int stock;
};

class Supplier {
public:
    Supplier(int id, string name) : id(id), name(name) {}

    int getId() const { return id; }
    string getName() const { return name; }

private:
    int id;
    string name;
};

class Inventory {
public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    void addSupplier(const Supplier& supplier) {
        suppliers.push_back(supplier);
    }

    void displayProducts() {
        cout << "Product List:" << endl;
        for (const Product& product : products) {
            cout << "ID: " << product.getId() << " | Name: " << product.getName() << " | Price: $" << product.getPrice() << " | Stock: " << product.getStock() << endl;
        }
    }

    void displaySuppliers() {
        cout << "Supplier List:" << endl;
        for (const Supplier& supplier : suppliers) {
            cout << "ID: " << supplier.getId() << " | Name: " << supplier.getName() << endl;
        }
    }

private:
    vector<Product> products;
    vector<Supplier> suppliers;
};

int main() {
    Inventory inventory;

    Product product1(1, "Product A", 10.0, 100);
    Product product2(2, "Product B", 20.0, 50);
    Supplier supplier1(1, "Supplier X");
    Supplier supplier2(2, "Supplier Y");

    inventory.addProduct(product1);
    inventory.addProduct(product2);
    inventory.addSupplier(supplier1);
    inventory.addSupplier(supplier2);

    inventory.displayProducts();
    inventory.displaySuppliers();

    return 0;
}
