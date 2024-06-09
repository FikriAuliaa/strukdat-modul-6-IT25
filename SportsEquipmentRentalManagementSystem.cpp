#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Class definition for Sports Equipment
class SportsEquipment {
public:
    SportsEquipment(const string& itemName, const string& itemBrand, double rentalPricePerDay, int stock)
        : name(itemName), brand(itemBrand), rentalPrice(rentalPricePerDay), availableStock(stock) {}

    string getName() const {
        return name;
    }

    string getBrand() const {
        return brand;
    }

    double getRentalPrice() const {
        return rentalPrice;
    }

    int getAvailableStock() const {
        return availableStock;
    }

    void setAvailableStock(int count) {
        availableStock = count;
    }

    void displayDetails() const {
        cout << "Sports Equipment - Name: " << name << ", Brand: " << brand
             << ", Rental Price per Day: $" << rentalPrice << ", Available Stock: " << availableStock << endl;
    }

private:
    string name;
    string brand;
    double rentalPrice;
    int availableStock;
};

// Class definition for Customer (Renter)
class Customer {
public:
    Customer(int customerId, const string& customerName, const string& customerAddress)
        : id(customerId), name(customerName), address(customerAddress) {}

    int getId() const {
        return id;
    }

    string getName() const {
        return name;
    }

    string getAddress() const {
        return address;
    }

private:
    int id;
    string name;
    string address;
};

// Class definition for Rental Management System
class RentalManagement {
public:
    void addEquipment(const string& itemName, const string& itemBrand, double rentalPricePerDay, int stock) {
        equipments.push_back(new SportsEquipment(itemName, itemBrand, rentalPricePerDay, stock));
    }

    void displayEquipments() const {
        cout << "-------------------------------------------------------" << endl;
        cout << "Current Sports Equipments Available for Rent:" << endl;

        for (const auto& equipment : equipments) {
            equipment->displayDetails();
        }
        cout << "-------------------------------------------------------" << endl;
    }

    SportsEquipment* findEquipment(const string& equipmentName) {
        auto it = find_if(equipments.begin(), equipments.end(), [&](SportsEquipment* e) {
            return e->getName() == equipmentName;
        });

        if (it != equipments.end()) {
            return *it;
        } else {
            return nullptr;
        }
    }

    void updateStock(const string& equipmentName, int newStock) {
        SportsEquipment* equipment = findEquipment(equipmentName);
        if (equipment != nullptr) {
            equipment->setAvailableStock(newStock);
            cout << "Stock for " << equipment->getName() << " updated to " << newStock << "." << endl;
        } else {
            cout << "Equipment not found." << endl;
        }
    }

    void deleteEquipment(const string& equipmentName) {
        auto it = remove_if(equipments.begin(), equipments.end(), [&](SportsEquipment* e) {
            return e->getName() == equipmentName;
        });

        if (it != equipments.end()) {
            delete *it; // Free memory for deleted equipment
            equipments.erase(it, equipments.end());
            cout << "Equipment " << equipmentName << " deleted." << endl;
        } else {
            cout << "Equipment not found." << endl;
        }
    }

    void rentEquipment(const string& equipmentName, int quantity, const Customer& customer, int rentalDays) {
        SportsEquipment* equipment = findEquipment(equipmentName);
        if (equipment != nullptr) {
            int currentStock = equipment->getAvailableStock();
            if (currentStock >= quantity) {
                double totalRentalCost = quantity * equipment->getRentalPrice() * rentalDays;
                equipment->setAvailableStock(currentStock - quantity);
                cout << "Rental Successful for " << quantity << " units of " << equipment->getName()
                     << " to Customer " << customer.getName() << ". Rental Cost: $" << totalRentalCost << endl;
            } else {
                cout << "Insufficient stock. Rental could not be processed." << endl;
            }
        } else {
            cout << "Equipment not found." << endl;
        }
    }

    ~RentalManagement() {
        // Clean up allocated memory
        for (auto& equipment : equipments) {
            delete equipment;
        }
        equipments.clear();
    }

private:
    vector<SportsEquipment*> equipments;
};

// Function to display menu and handle user inputs
void displayMenu() {
    cout << "\nSports Equipment Rental Management System\n";
    cout << "1. Display Available Equipments\n";
    cout << "2. Add Equipment\n";
    cout << "3. Update Equipment Stock\n";
    cout << "4. Delete Equipment\n";
    cout << "5. Rent Equipment\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    RentalManagement rentalSystem;

    // Initial sports equipments
    rentalSystem.addEquipment("Bicycle", "Giant", 15.00, 5);
    rentalSystem.addEquipment("Skateboard", "Element", 10.00, 10);
    rentalSystem.addEquipment("Tennis Racket", "Wilson", 5.00, 20);
    rentalSystem.addEquipment("Dumbbell Set", "Nike", 8.00, 15);

    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                rentalSystem.displayEquipments();
                break;
            case 2: {
                string itemName, itemBrand;
                double rentalPrice;
                int stock;
                cout << "Enter equipment name: ";
                cin >> ws;
                getline(cin, itemName);
                cout << "Enter equipment brand: ";
                getline(cin, itemBrand);
                cout << "Enter rental price per day: $";
                cin >> rentalPrice;
                cout << "Enter available stock: ";
                cin >> stock;
                rentalSystem.addEquipment(itemName, itemBrand, rentalPrice, stock);
                cout << "Equipment added successfully." << endl;
                break;
            }
            case 3: {
                string equipmentName;
                int newStock;
                cout << "Enter equipment name to update stock: ";
                cin >> ws;
                getline(cin, equipmentName);
                cout << "Enter new stock count: ";
                cin >> newStock;
                rentalSystem.updateStock(equipmentName, newStock);
                break;
            }
            case 4: {
                string equipmentName;
                cout << "Enter equipment name to delete: ";
                cin >> ws;
                getline(cin, equipmentName);
                rentalSystem.deleteEquipment(equipmentName);
                break;
            }
            case 5: {
                string equipmentName, customerName;
                int quantity, rentalDays;
                cout << "Enter equipment name to rent: ";
                cin >> ws;
                getline(cin, equipmentName);
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter rental days: ";
                cin >> rentalDays;
                cout << "Enter customer name: ";
                cin >> ws;
                getline(cin, customerName);

                Customer customer(1, customerName, "N/A");
                rentalSystem.rentEquipment(equipmentName, quantity, customer, rentalDays);
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 0);

    return 0;
}

