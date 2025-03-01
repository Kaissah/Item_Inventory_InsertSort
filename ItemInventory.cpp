#include <iostream>
#include <vector>
#include <cstdlib>  
#include <ctime>  
#include <fstream>  
#include <sstream>

using namespace std;

struct Items {
private:
    int ID, QTY;

public:
    Items(int id, int qty) : ID(id), QTY(qty) {}

    int getID() const { return ID; }
    int getQTY() const { return QTY; }

    // ? Generate random items
    static vector<Items> randomGenerator(int N) {
        vector<Items> items;
        int idMin = 1, idMax = 100;
        int qtyMin = 1, qtyMax = 50;

        srand(time(0));

        for (int i = 0; i < N; ++i) {
            int itemID = idMin + (rand() % (idMax - idMin + 1));
            int quantity = qtyMin + (rand() % (qtyMax - qtyMin + 1));
            items.push_back(Items(itemID, quantity));
        }

        return items;
    }

    // ? Sort by ID
    static void insertionSortID(vector<Items>& items) {
        string filename = "Items.txt";
        ofstream file(filename.c_str(), ios_base::app);

        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        int n = items.size();
        for (int i = 1; i < n; ++i) {
            Items key = items[i];
            int j = i - 1;

            while (j >= 0 && items[j].getID() > key.getID()) {
                items[j + 1] = items[j];
                --j;
            }
            items[j + 1] = key;
        }

        // Save to file
        file << "Sorted Items (by ID):\n";
        for (const auto& item : items) {
            file << "Item ID: " << item.getID() << " - Item Quantity: " << item.getQTY() << "\n";
        }

        file.close();
        cout << "Items sorted by ID and saved to file.\n";
    }

    // ? Sort by Quantity
    static void insertionSortQTY(vector<Items>& items) {
        string filename = "Items.txt";
        ofstream file(filename.c_str(), ios_base::app);

        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        int n = items.size();
        for (int i = 1; i < n; ++i) {
            Items key = items[i];
            int j = i - 1;

            while (j >= 0 && items[j].getQTY() > key.getQTY()) {
                items[j + 1] = items[j];
                --j;
            }
            items[j + 1] = key;
        }

        // Save to file
        file << "Sorted Items (by Quantity):\n";
        for (const auto& item : items) {
            file << "Item ID: " << item.getID() << " - Item Quantity: " << item.getQTY() << "\n";
        }

        file.close();
        cout << "Items sorted by Quantity and saved to file.\n";
    }

    // ? Display items
    static void displayItems(const vector<Items>& items) {
        cout << "Generated Items:\n";
        for (const auto& item : items) {
            cout << "Item ID: " << item.getID() << ", Quantity: " << item.getQTY() << "\n";
        }
    }

    // ? Load saved items
    static void loadSavedItems() {
        ifstream file("Items.txt");

        if (!file.is_open()) {
            cerr << "Failed to open file: Items.txt\n";
            return;
        }

        cout << "Saved Items:\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }

        file.close();
    }
};

int main() {
    vector<Items> items;
    int choice, num;

    while (true) {
        cout << "\n======= INVENTORY MANAGEMENT SYSTEM =======" << endl;
        cout << "[1] Generate List" << endl;
        cout << "[2] Sort by ID" << endl;
        cout << "[3] Sort by Quantity" << endl;
        cout << "[4] Load saved items" << endl;
        cout << "[5] Exit" << endl;
        cout << "Enter your choice: ";
        
        if (!(cin >> choice)) {
            cin.clear();  // Clear error flag
            cin.ignore(10000, '\n');  // Discard invalid input
            cout << "Invalid! Please enter a number from 1 to 5.\n";
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter the number of items to generate: ";
                if (!(cin >> num) || num <= 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid! Please enter a positive integer.\n";
                    break;
                }
                items = Items::randomGenerator(num);
                cout << "\nGenerated Items:\n";
                Items::displayItems(items);
                break;

            case 2:
                if (items.empty()) {
                    cout << "No items generated yet. Please generate items first.\n";
                } else {
                    Items::insertionSortID(items);
                    cout << "Sorted by ID:\n";
                    Items::displayItems(items);
                }
                break;

            case 3:
                if (items.empty()) {
                    cout << "No items generated yet. Please generate items first.\n";
                } else {
                    Items::insertionSortQTY(items);
                    cout << "Sorted by Quantity:\n";
                    Items::displayItems(items);
                }
                break;

            case 4:
                Items::loadSavedItems();
                break;

            case 5:
                cout << "Thank you for using our inventory management system! Exiting program.\n";
                return 0;

            default:
                cout << "Invalid! Please select a number between 1 and 5.\n";
        }
    }

    return 0;
}

