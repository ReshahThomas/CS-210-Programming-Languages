/*
* CS-210 Project Three: Corner Grocer
* Grocery Tracking Program
* 
* Purpose: Track grocery purchases, calculates
* item frequencies, and display inventory reports.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
// Class stores grocery items and provides tracking functions
class GroceryTracker {
    private:
    map<string, int> itemFrequency;

    public:
    void loadItems();
    void searchItem();
    void displayFrequencies();
    void displayHistogram();
    void saveData();
};
// Reads grocery records and counts each item's purchases
void GroceryTracker::loadItems() {
    ifstream inputFile("CS210_Project_Three_Input_File.txt");
    string item;

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open grocery file." << endl;
        return;
    }
    // Reads each item and increases its purchase count
    while (inputFile >> item) {
        itemFrequency[item]++;
    }
    inputFile.close();
}
// Searches for an item and displays its purchase frequencey
void GroceryTracker::searchItem() {
    string item;

    cout << "Enter the item you want to search for: ";
    cin >> item;

    if ( itemFrequency.find(item) != itemFrequency.end()) {
        cout << item << " was purchased " << itemFrequency[item] << " times. " << endl;
    }
    else {
        cout << item << " was not found." << endl;
    }
}
// Displays all grocery items and their purchase counts
void GroceryTracker::displayFrequencies() {
    cout << "\nGrocery Item Frequencies:\n";

    for (const auto& item : itemFrequency) {
        cout << item.first << " " << item.second << endl;
    }
}
// Displays purchase frequencies using asterisks
void GroceryTracker::displayHistogram() {
    cout << "\nGrocery Purchase Histogram:\n";

    for (const auto& item : itemFrequency) {
        cout << item.first << " ";

        for (int i = 0; i < item.second; i++) {
            cout << "*";
        }

        cout << endl;
    }
}
// Saves grocery frequencies to the frequency.dat backup file
void GroceryTracker::saveData() {
    ofstream outputFile("frequency.dat");

    if (!outputFile.is_open()) {
        cout << "Error: Unable to create bachup file." << endl;
        return;
    }

    for (const auto& item : itemFrequency) {
        outputFile << item.first << " " << item.second << endl;
    }
    
    outputFile.close();
}
// Displays the menu and processes user selections
int main() {
    GroceryTracker tracker;
    int choice = 0;
    // Load grocery  records and automatically create the backup file
    tracker.loadItems();
    tracker.saveData();

    while (choice != 4) {
        cout << "\n===== Cormer Grocer Menu =====\n";
        cout << "1. Search for an item\n";
        cout << "2. Display item frequencies\n";
        cout << "3. Display histogram\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
            tracker.searchItem();
            break;
            case 2:
            tracker.displayFrequencies();
            break;
            case 3:
            tracker.displayHistogram();
            break;
            case 4:
            cout << "Thank you for using Corner Grocer!" << endl;
            break;
            default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}