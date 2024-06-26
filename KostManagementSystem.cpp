#include <iostream>
#include <vector>
#include <string>
#include <limits> // Untuk menggunakan numeric_limits

using namespace std;

// Abstraksi: Kelas dasar dengan fungsi virtual murni
class Person {
private:
    int id;
    string name;
    string phone;

public:
    Person(int id, string name, string phone) : id(id), name(name), phone(phone) {}
   
    // Fungsi virtual murni untuk tampilan
    virtual void display() const = 0;

    int getId() const { return id; }
    string getName() const { return name; }
    string getPhone() const { return phone; }

    void setName(string name) { this->name = name; }
    void setPhone(string phone) { this->phone = phone; }
};

class Room {
private:
    int id;
    string type;
    bool isOccupied;
    double rent;

public:
    Room(int id, string type, double rent)
        : id(id), type(type), isOccupied(false), rent(rent) {}

    int getId() const { return id; }
    string getType() const { return type; }
    bool getIsOccupied() const { return isOccupied; }
    double getRent() const { return rent; }

    void setType(const string& type) { this->type = type; }
    void setIsOccupied(bool isOccupied) { this->isOccupied = isOccupied; }
    void setRent(double rent) { this->rent = rent; }

    void display() const {
        cout << "Room ID: " << id << ", Type: " << type << ", Rent: $" << rent << ", Status: " << (isOccupied ? "Occupied" : "Available") << endl;
    }
};

// Pewarisan: Kelas Tenant mewarisi dari Person
class Tenant : public Person {
private:
    int roomId;
    double balance;

public:
    Tenant(int id, string name, string phone, int roomId)
        : Person(id, name, phone), roomId(roomId), balance(0.0) {}

    int getRoomId() const { return roomId; }
    double getBalance() const { return balance; }

    void setRoomId(int roomId) { this->roomId = roomId; }
    void setBalance(double balance) { this->balance = balance; }

    // Override metode display
    void display() const override {
        cout << "Tenant ID: " << getId() << ", Name: " << getName() << ", Phone: " << getPhone()
             << ", Room ID: " << roomId << ", Balance: $" << balance << endl;
    }
};

class KosManagement {
private:
    vector<Room> rooms;
    vector<Tenant> tenants;
    int nextRoomId;
    int nextTenantId;

    int findRoomById(int id) const {
        for (size_t i = 0; i < rooms.size(); i++) {
            if (rooms[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    int findTenantById(int id) const {
        for (size_t i = 0; i < tenants.size(); i++) {
            if (tenants[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

public:
    KosManagement() : nextRoomId(1), nextTenantId(1) {}

    void addRoom(const string& type, double rent) {
        rooms.push_back(Room(nextRoomId++, type, rent));
        cout << "Room added successfully." << endl;
    }

    void displayRooms() const {
        if (rooms.empty()) {
            cout << "No rooms available." << endl;
            return;
        }
        for (const auto& room : rooms) {
            room.display();
        }
    }

    void updateRoom(int id, const string& type, double rent) {
        int index = findRoomById(id);
        if (index != -1) {
            rooms[index].setType(type);
            rooms[index].setRent(rent);
            cout << "Room updated successfully." << endl;
        } else {
            cout << "Room not found." << endl;
        }
    }

    void checkInTenant(const string& name, const string& phone, int roomId) {
        int roomIndex = findRoomById(roomId);
        if (roomIndex != -1 && !rooms[roomIndex].getIsOccupied()) {
            tenants.push_back(Tenant(nextTenantId++, name, phone, roomId));
            rooms[roomIndex].setIsOccupied(true);
            cout << "Tenant checked in successfully." << endl;
        } else {
            cout << "Room is either not found or already occupied." << endl;
        }
    }

    void checkOutTenant(int tenantId) {
        int tenantIndex = findTenantById(tenantId);
        if (tenantIndex != -1) {
            int roomId = tenants[tenantIndex].getRoomId();
            int roomIndex = findRoomById(roomId);
            if (roomIndex != -1) {
                rooms[roomIndex].setIsOccupied(false);
            }
            tenants.erase(tenants.begin() + tenantIndex);
            cout << "Tenant checked out successfully." << endl;
        } else {
            cout << "Tenant not found." << endl;
        }
    }

    void displayTenants() const {
        if (tenants.empty()) {
            cout << "No tenants available." << endl;
            return;
        }
        for (const auto& tenant : tenants) {
            tenant.display();
        }
    }

    void managePayments(int tenantId, double amount) {
        int tenantIndex = findTenantById(tenantId);
        if (tenantIndex != -1) {
            double currentBalance = tenants[tenantIndex].getBalance();
            tenants[tenantIndex].setBalance(currentBalance + amount);
            cout << "Payment updated successfully." << endl;
        } else {
            cout << "Tenant not found." << endl;
        }
    }
};

// Polimorfisme: Fungsi yang menerima referensi ke kelas dasar
void displayPersonInfo(const Person& person) {
    person.display();
}

void displayMenu() {
    cout << "Kos Management System" << endl;
    cout << "1. Add Room" << endl;
    cout << "2. Display Rooms" << endl;
    cout << "3. Update Room" << endl;
    cout << "4. Check-in Tenant" << endl;
    cout << "5. Check-out Tenant" << endl;
    cout << "6. Display Tenants" << endl;
    cout << "7. Manage Payments" << endl;
    cout << "8. Exit" << endl;
}

int main() {
    KosManagement kosManagement;
    int choice;

    while (true) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 8) {
            break;
        }

        switch (choice) {
            case 1: {
                string type;
                double rent;
                cout << "Enter room type: ";
                cin >> ws;
                getline(cin, type);
                cout << "Enter room rent: ";
                cin >> rent;
                kosManagement.addRoom(type, rent);
                break;
            }
            case 2:
                kosManagement.displayRooms();
                break;
            case 3: {
                int id;
                string type;
                double rent;
                cout << "Enter room ID to update: ";
                cin >> id;
                cout << "Enter new room type: ";
                cin >> ws;
                getline(cin, type);
                cout << "Enter new room rent: ";
                cin >> rent;
                kosManagement.updateRoom(id, type, rent);
                break;
            }
            case 4: {
                string name;
                string phone;
                int id;
                cout << "Enter tenant name: ";
                cin >> ws;
                getline(cin, name);
                cout << "Enter tenant phone: ";
                cin >> phone;
                cout << "Enter room ID: ";
                cin >> id;
                kosManagement.checkInTenant(name, phone, id);
                break;
            }
            case 5: {
                int id;
                cout << "Enter tenant ID to check out: ";
                cin >> id;
                kosManagement.checkOutTenant(id);
                break;
            }
            case 6:
                kosManagement.displayTenants();
                break;
            case 7: {
                int id;
                double amount;
                cout << "Enter tenant ID for payment: ";
                cin >> id;
                cout << "Enter payment amount: ";
                cin >> amount;
                kosManagement.managePayments(id, amount);
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        // Handle input errors
        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input. Please try again." << endl;
        }
    }

    return 0;
}

