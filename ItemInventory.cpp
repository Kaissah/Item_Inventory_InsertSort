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
        int idMin = 1, idMax = 100;      // Range for item IDs
        int qtyMin = 1, qtyMax = 50;     // Range for quantities

        srand(time(0));  // Seed random number generator

        for (int i = 0; i < N; ++i) {
            int itemID = idMin + (rand() % (idMax - idMin + 1));
            int quantity = qtyMin + (rand() % (qtyMax - qtyMin + 1));
            items.push_back(Items(itemID, quantity));  // Add to vector
        }

        return items;
    }

    // ? Sort items using insertion sort (by ID)
static void insertionSortQTY(vector<Items>& items) {
    string filename = "Items.txt";
    ofstream file(filename.c_str(), ios_base::app);  // Open file in append mode

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    int n = items.size();
    for (int i = 1; i < n; ++i) {
        Items key = items[i];  // Store the current item
        int j = i - 1;

        // Move elements that are greater than `key` (sort by Quantity)
        while (j >= 0 && items[j].getID() > key.getID()) {
            items[j + 1] = items[j];
            --j;
        }
        items[j + 1] = key;

        // Output sorting process
        cout << "Iteration (ID, Quantity) " << i << ": ";
        for (const auto& item : items) {
            cout << "(" << item.getID() << ", " << item.getQTY() << ") ";
        }
        cout << endl;
    }

    // Write sorted items to the file
    file << "Sorted Items (by ID):\n";
    for (const auto& item : items) {
        file << "Item ID: " << item.getID() << " - Item Quantity: " << item.getQTY() << "\n";
    }

    file.close();  // Close file after writing
}
    
static void insertionSortID(vector<Items>& items) {
    string filename = "Items.txt";
    ofstream file(filename.c_str(), ios_base::app);  // Open file in append mode

    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    int n = items.size();
    for (int i = 1; i < n; ++i) {
        Items key = items[i];  // Store the current item
        int j = i - 1;

        // Move elements that are greater than `key` (sort by Quantity)
        while (j >= 0 && items[j].getQTY() > key.getQTY()) {
            items[j + 1] = items[j];
            --j;
        }
        items[j + 1] = key;

        // Output sorting process
        cout << "Iteration (ID, Quantity) " << i << ": ";
        for (const auto& item : items) {
            cout << "(" << item.getID() << ", " << item.getQTY() << ") ";
        }
        cout << endl;
    }

    // Write sorted items to the file
    file << "Sorted Items (by Quantity):\n";
    for (const auto& item : items) {
        file << "Item ID: " << item.getID() << " - Item Quantity: " << item.getQTY() << "\n";
    }

    file.close();  // Close file after writing
}
    // ? Display items
static void displayItems(const vector<Items>& items) {
        cout << "Generated Items:\n";
        for (const auto& item : items) {
            cout << "Item ID: " << item.getID() << ", Quantity: " << item.getQTY() << "\n";
        }
    }
};



int main() {
    int num;
	
	cout<<"=======WELCOME======="<<endl;
	cout<<"[1] Generate List"<<endl;
	cout<<"[2] Sort by ID"<<endl;
	cout<<"[3] Sort by Quantity"<<endl;
	cout<<"[4] Load save"<<endl;
    cout << "Enter the number of items to generate: ";
    cin >> num;
    

    // Generate items
    vector<Items> items = Items::randomGenerator(num);

    // Display unsorted items
    cout << "\nBefore Sorting:\n";
    Items::displayItems(items);

    // Sort items by ID
    cout << "\nSorting process:\n";
    Items::insertionSortID(items);

    // Display sorted items
    cout << "\nAfter Sorting (by Item ID):\n";
    Items::displayItems(items);
    
    cout << "\nSorting process:\n";
    Items::insertionSortQTY(items);

    // Display sorted items
    cout << "\nAfter Sorting (by Item QTY):\n";
    Items::displayItems(items);
    

    return 0;
}

