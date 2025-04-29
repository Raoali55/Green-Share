#include <iostream>
#include <string>
#include <vector>
#include <conio.h> // For getch()
using namespace std;

class Post {
private:
    string name, address, street, description, date;
    double quantity, price, availableUnits;
    string accountNumber, ownerName, bankName;
    bool paymentMade;

public:
    // Constructor
    Post(string name, string address, string street, string description, string date,
         double quantity, double price, string accountNumber, string ownerName, string bankName)
        : name(name), address(address), street(street), description(description),
          date(date), quantity(quantity), price(price), availableUnits(quantity),
          accountNumber(accountNumber), ownerName(ownerName), bankName(bankName),
          paymentMade(false) {}

    // Getters and Setters
    string getName() { return name; }
    string getAddress() { return address; }
    string getDescription() { return description; }
    double getAvailableUnits() { return availableUnits; }
    double getPrice() { return price; }
    string getOwnerName() { return ownerName; }
    string getBankName() { return bankName; }
    string getAccountNumber() { return accountNumber; }

    void subtractUnits(double units) {
        if (units <= availableUnits) {
            availableUnits -= units;
        } else {
            cout << "Insufficient units available." << endl;
        }
    }

    void makePayment(double requestedUnits) {
        double totalPayment = requestedUnits * price;
        cout << "Payment for " << requestedUnits << " units successful!" << endl;
        cout << "Total Amount Paid: " << totalPayment << endl;
        cout << "Bank: " << bankName << ", Account: " << accountNumber << endl;
        paymentMade = true;
    }

    void printDetails() {
        cout << "Name: " << name << endl
             << "Address: " << address << endl
             << "Street: " << street << endl
             << "Description: " << description << endl
             << "Date: " << date << endl
             << "Quantity: " << quantity << endl
             << "Price per Unit: " << price << endl
             << "Available Units: " << availableUnits << endl
             << "Owner Name: " << ownerName << endl
             << "Bank: " << bankName << ", Account: " << accountNumber << endl;
    }
};
class User {
private:
    vector<string> requestHistory;
    vector<double> paymentHistory;

public:
    void viewAvailablePosts(vector<Post>& posts) {
        if (posts.empty()) {
            cout << "No posts available." << endl;
            return;
        }

        for (size_t i = 0; i < posts.size(); ++i) {
            cout << "Post #" << i + 1 << ":" << endl;
            posts[i].printDetails();
            cout << "--------------------------" << endl;
        }
    }

    void requestUnits(vector<Post>& posts) {
        if (posts.empty()) {
            cout << "No posts available to request units from." << endl;
            return;
        }

        int postIndex;
        double requestedUnits;

        cout << "Enter the post number you want to request units from: ";
        cin >> postIndex;
        if (postIndex < 1 || postIndex > posts.size()) {
            cout << "Invalid post number." << endl;
            return;
        }

        cout << "Enter the number of units you want to request: ";
        cin >> requestedUnits;

        Post& selectedPost = posts[postIndex - 1];
        if (requestedUnits <= selectedPost.getAvailableUnits()) {
            selectedPost.subtractUnits(requestedUnits);
            cout << "Request successful! You requested " << requestedUnits << " units." << endl;
            cout << "Total Payment: " << requestedUnits * selectedPost.getPrice() << endl;
            requestHistory.push_back(selectedPost.getName());
            paymentHistory.push_back(requestedUnits * selectedPost.getPrice());
        } else {
            cout << "Insufficient units available." << endl;
        }
    }

    void makePayment(vector<Post>& posts) {
        if (posts.empty()) {
            cout << "No posts available for payment." << endl;
            return;
        }

        int postIndex;
        double requestedUnits;

        cout << "Enter the post number for payment: ";
        cin >> postIndex;
        if (postIndex < 1 || postIndex > posts.size()) {
            cout << "Invalid post number." << endl;
            return;
        }

        cout << "Enter the number of units you want to pay for: ";
        cin >> requestedUnits;

        Post& selectedPost = posts[postIndex - 1];
        selectedPost.makePayment(requestedUnits);
    }
};

class Owner:public User {
private:
    vector<Post> posts;

public:
    void addPost() {
        string name, address, street, description, date, accountNumber, ownerName, bankName;
        double quantity, price;

        cout << "Enter post details:" << endl;
        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        cout << "Address: ";
        getline(cin, address);
        cout << "Street: ";
        getline(cin, street);
        cout << "Description: ";
        getline(cin, description);
        cout << "Date: ";
        getline(cin, date);
        cout << "Quantity: ";
        cin >> quantity;
        cout << "Price per Unit: ";
        cin >> price;
        cin.ignore();
        cout << "Account Number: ";
        getline(cin, accountNumber);
        cout << "Owner Name: ";
        getline(cin, ownerName);
        cout << "Bank Name: ";
        getline(cin, bankName);

        Post newPost(name, address, street, description, date, quantity, price, accountNumber, ownerName, bankName);
        posts.push_back(newPost);

        cout << "Post added successfully!" << endl;
    }

    void viewPosts() {
        if (posts.empty()) {
            cout << "No posts available." << endl;
            return;
        }

        for (size_t i = 0; i < posts.size(); ++i) {
            cout << "Post #" << i + 1 << ":" << endl;
            posts[i].printDetails();
            cout << "--------------------------" << endl;
        }
    }

    vector<Post>& getPosts() { return posts; }
};


class SystemManager {
private:
    Owner owner;
    User user;

public:
    void menu() {
        int choice;
        while (true) {
            cout << "1. Owner Menu" << endl;
            cout << "2. User Menu" << endl;
            cout << "3. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                ownerMenu();
            } else if (choice == 2) {
                userMenu();
            } else if (choice == 3) {
                cout << "Exiting..." << endl;
                break;
            } else {
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void ownerMenu() {
        int choice;
        while (true) {
            cout << "1. Add Post" << endl;
            cout << "2. View Posts" << endl;
            cout << "3. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 1) {
                owner.addPost();
            } else if (choice == 2) {
                owner.viewPosts();
            } else if (choice == 3) {
                break;
            } else {
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }

    void userMenu() {
        int choice;
        while (true) {
            cout << "1. View Available Posts" << endl;
            cout << "2. Request Units" << endl;
            cout << "3. Make Payment" << endl;
            cout << "4. Back to Main Menu" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            vector<Post>& posts = owner.getPosts();

            if (choice == 1) {
                user.viewAvailablePosts(posts);
            } else if (choice == 2) {
                user.requestUnits(posts);
            } else if (choice == 3) {
                user.makePayment(posts);
            } else if (choice == 4) {
                break;
            } else {
                cout << "Invalid choice. Try again." << endl;
            }
        }
    }
};

int main() {
    SystemManager systemManager;
    systemManager.menu();
    return 0;
}
