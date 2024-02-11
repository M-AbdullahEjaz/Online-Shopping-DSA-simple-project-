#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;

class item {
public:
    int price;
    string name;
    int numOfItems;
    item* next;
    item(string name1, int price1, int numOfItems1) {
        name = name1;
        price = price1;
        numOfItems = numOfItems1;
        next = NULL;
    }
    string getName() {
        return name;
    }
    int getprice() {
        return price;
    }
    int getNumOfItems() {
        return numOfItems;
    }
    item* getNext() {
        return next;
    }
    void addItem(item*& head, string name1, int price1, int numOfItems1) {
        item* new_item = new item(name1, price1, numOfItems1);
        if (!head) {
            head = new_item;
        }
        else {
            new_item->next = head;
            head = new_item;
        }
    }

    void displayItems(item* head) {
        cout << "Items in the list:" << endl;
        item* current = head;
        while (current) {
            cout << "Name: " << current->name << ", Price: " << current->price << ", Quantity: " << current->numOfItems << endl;
            current = current->next;
        }
    }

    void searchItem(item* head, string name1) {
        item* temp = head;
        while (temp != NULL) {
            if (temp->name == name1) {
                cout << "Item found - Name: " << temp->name << ", Price: " << temp->price << ", Quantity: " << temp->numOfItems << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Item not found." << endl;
    }

    void deleteItem(item*& head, string name1) {
        if (!head) {
            cout << "List is empty. Cannot delete." << endl;
            return;
        }

        item* temp = head;
        item* prev = NULL;

        // Check if the first item is the one to be deleted
        if (temp->name == name1) {
            head = temp->next;
            delete temp;
            cout << "Item deleted successfully." << endl;
            return;
        }

        // Search for the item to be deleted
        while (temp != NULL && temp->name != name1) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            cout << "Item not found. Cannot delete." << endl;
            return;
        }

        // Update the next pointer of the previous node
        prev->next = temp->next;
        delete temp;
        cout << "Item deleted successfully." << endl;
    }

    void updateItem(item* head, string name1, int newPrice, int newQty) {
        item* temp = head;
        while (temp != NULL) {
            if (temp->name == name1) {
                temp->price = newPrice;
                temp->numOfItems = newQty;
                cout << "Item updated successfully." << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Item not found. Cannot update." << endl;
    }

    void orderItem(item* head, string name1, int quantity) {
        item* temp = head;
        while (temp != NULL) {
            if (temp->name == name1) {
                if (temp->numOfItems >= quantity) {
                    temp->numOfItems -= quantity;
                    cout << "Item added to the cart successfully." << endl;
                    return;
                }
                else {
                    cout << "Insufficient quantity available. Cannot add to cart." << endl;
                    return;
                }
            }
            temp = temp->next;
        }
        cout << "Item not found. Cannot add to cart." << endl;
    }
};

struct Customer {
    string name;
    string dob; // Date of Birth
    string address;
};

class CustomerQueue {
private:
    queue<Customer> customers;

public:
    void enqueue(Customer newCustomer) {
        customers.push(newCustomer);
    }

    void dequeue() {
        if (customers.empty()) {
            cout << "Queue is empty" << endl;
            return;
        }
        customers.pop();
    }

    Customer peek() {
        if (customers.empty()) {
            cout << "Queue is empty" << endl;
            return { "", "" }; // You can return a default customer or handle this case as needed
        }
        return customers.front();
    }

    void dequeueAndDisplayNext() {
        if (customers.empty()) {
            cout << "No customers in the queue." << endl;
            return;
        }

        Customer nextCustomer = customers.front();
        cout << "Next customer details:\n";
        cout << "Name: " << nextCustomer.name << "\n";
        cout << "Date of Birth: " << nextCustomer.dob << "\n";
        cout << "Address: " << nextCustomer.address << "\n";

        customers.pop(); // Remove the customer from the queue after displaying
    }
};


class Cart {
private:
    item* cartItems; // Items in the cart

public:
    Cart() : cartItems(NULL) {}

    void addToCart(item* head, string name1, int quantity) {
        if (!cartItems) {
            cartItems = new item(name1, 0, quantity);
        }
        else {
            item* temp = cartItems;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = new item(name1, 0, quantity);

            cout << "Item added to the cart." << endl;
        }
        item* temp = head;
        while (temp != NULL) {
            if (temp->name == name1) {
                if (temp->numOfItems >= quantity) {
                    temp->numOfItems -= quantity;
                    cout << "Item added to the cart successfully." << endl;
                    return;
                }
                else {
                    cout << "Insufficient quantity available. Cannot add to cart." << endl;
                    return;
                }
            }
            temp = temp->next;
        }
        cout << "Item not found. Cannot add to cart." << endl;
    }

    void displayCart() {
        cout << "Items in the cart:" << endl;
        item* current = cartItems;
        while (current) {
            cout << "Name: " << current->getName() << ", Quantity: " << current->getNumOfItems() << endl;
            current = current->getNext();
        }
    }

    void placeOrder(CustomerQueue& customerQueue) {
        // Assume the customer details are obtained from the user
        Customer customer;
        cout << "Enter your name: ";
        cin >> customer.name;
        cout << "Enter your date of birth: ";
        cin >> customer.dob;
        cout << "Enter your address: ";
        cin >> customer.address;

        customerQueue.enqueue(customer);

        cout << "Order placed successfully. Thank you!" << endl;
        // Clear the cart after placing the order
        clearCart();
    }

    void clearCart() {
        while (cartItems != NULL) {
            item* temp = cartItems;
            cartItems = cartItems->getNext();
            delete temp;
        }
    }
};
item mysteryBox(stack<item> &mystery) {
    

    if (!mystery.empty()) {
        item topItem = mystery.top();  // Get the top item from the stack
        mystery.pop();  // Pop the top item from the stack
        return topItem;
    }
    else {
        // Handle the case when the stack is empty
        cout << "Mystery box is empty." << endl;
        return item("Empty", 0, 0);  // You can return a default item or handle it as needed
    }
}




int main() {
    item* head = NULL; // Initialize head to NULL
    CustomerQueue customerQueue;
    Cart cart;

    // Add items to the list
    head = new item("Item1", 10, 5);
    head->addItem(head, "Item2", 20, 8);
    head->addItem(head, "Item3", 15, 12);
    stack<item> mystery;
    mystery.push(item("Try again", 0, 0));
    mystery.push(item("Iphone", 100, 5));
    mystery.push(item("Try again", 0, 0));
    mystery.push(item("Try again", 0, 0));
    mystery.push(item("HP Laptop", 50, 5));
    mystery.push(item("Try again", 0, 0));

main:
    int menu;
    cout << "Are you a :" << endl << "1.Admin" << endl << "2.Customer" << endl;
    cin >> menu;

    if (menu == 1) {
        int choice;
        do {
            cout << "\nMenu:\n";
            cout << "1. Add a new item\n";
            cout << "2. Update an item\n";
            cout << "3. Delete an item\n";
            cout << "4. Search an item\n";
            cout << "5. View next customer\n";
            cout << "6. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                int itemPrice;
                int qty;
                string itemName;
                cout << "Enter name of new item : " << endl;
                cin >> itemName;
                cout << "Enter quantity : " << endl;
                cin >> qty;
                cout << "Enter price : " << endl;
                cin >> itemPrice;
                head->addItem(head, itemName, itemPrice, qty);
                break;
            }
            case 2: {
                string nameToUpdate;
                int newPrice, newQty;

                cout << "Enter the name of the item to update: ";
                cin >> nameToUpdate;

                cout << "Enter the new price: ";
                cin >> newPrice;

                cout << "Enter the new quantity: ";
                cin >> newQty;

                head->updateItem(head, nameToUpdate, newPrice, newQty);
                break;
            }
            case 3: {
                string nameToDelete;
                cout << "Enter the name of the item to delete: ";
                cin >> nameToDelete;
                head->deleteItem(head, nameToDelete);
                break;
            }
            case 4: {
                string nameToSearch;
                cout << "Enter the name of the item to search: ";
                cin >> nameToSearch;
                head->searchItem(head, nameToSearch);
                break;
            }
            case 5: {
                Customer nextCustomer = customerQueue.peek();
                if (nextCustomer.name != "" && nextCustomer.dob != "") {
                    cout << "Next customer details:\n";
                    cout << "Name: " << nextCustomer.name << "\n";
                    cout << "Date of Birth: " << nextCustomer.dob << "\n";
                    cout << "Address: " << nextCustomer.address << "\n";
                    //customerQueue.dequeueAndDisplayNext();
                    break;
                }
                else {
                    cout << "No customers in the queue.\n";
                }
                break;
            }
            }

        } while (choice != 6);
    }
    else {
        int choice1;
        do {
            cout << "\nMenu:\n";
            cout << "1. Display available items\n";
            cout << "2. Search for an item\n";
            cout << "3. Add items to the cart\n";
            cout << "4. Display items in the cart\n";
            cout << "5. Place an order\n";
            cout << "6. Mystery Box\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice1;

            switch (choice1) {
            case 1:
                head->displayItems(head);
                break;
            case 2:
            {
                string itemName;
                cout << "Enter the name of the item to search: ";
                cin >> itemName;
                head->searchItem(head, itemName);
            }
            break;
            case 3:
            {
                string itemName;
                int quantity;
                cout << "Enter the name of the item to add to the cart: ";
                cin >> itemName;
                cout << "Enter the quantity: ";
                cin >> quantity;
                cart.addToCart(head, itemName, quantity);
            }
            break;
            case 4:
                cart.displayCart();
                break;
            case 5:
                cart.placeOrder(customerQueue);
                break;
            case 7:
                cout << "Exiting the program. Thank you!\n";
                break;
            case 6: {

                item mysteryItem = mysteryBox(mystery);
                cout << "You got " << mysteryItem.getName() << " with Price: " << mysteryItem.getprice() << ", Quantity: " << mysteryItem.getNumOfItems() << endl;
                break;
            }


             
            default:
                cout << "In valid choice. Please try again.\n";
            }
 

        } while (choice1 != 6);
    }
    goto main;

    return 0;
}
