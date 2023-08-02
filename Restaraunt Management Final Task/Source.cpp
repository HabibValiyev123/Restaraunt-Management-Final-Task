#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Food {
private:
    string name;
    int price;

public:
    Food() : name(""), price(0) {}
    Food(string _name, int _price) : name(_name), price(_price) {}

    string getName() const { return name; }
    int getPrice() const { return price; }

    void setName(string _name) { name = _name; }
    void setPrice(int _price) { price = _price; }
};

class Ingredient {
private:
    string name;
    int price;
    int count;

public:
    Ingredient() : name(""), price(0), count(0) {}
    Ingredient(string _name, int _price, int _count) : name(_name), price(_price), count(_count) {}

    string getName() const { return name; }
    int getPrice() const { return price; }
    int getCount() const { return count; }

    void setName(string _name) { name = _name; }
    void setPrice(int _price) { price = _price; }
    void setCount(int _count) { count = _count; }
};

class RestaurantManagement {
private:
    vector<Food> foods;
    vector<Ingredient> ingredients;
    int userSeat;
    int totalMoneyPaid;
    vector<pair<int, bool>> orders;

    void rewriteFoodsFile() {
        ofstream file("foods.txt");
        for (const auto& food : foods) {
            file << food.getName() << " " << food.getPrice() << "\n";
        }
    }

    void rewriteIngredientsFile() {
        ofstream file("ingredients.txt");
        for (const auto& ingredient : ingredients) {
            file << ingredient.getName() << " " << ingredient.getPrice() << " " << ingredient.getCount() << "\n";
        }
    }

public:
    RestaurantManagement() : userSeat(0), totalMoneyPaid(0) {
        ifstream file("foods.txt");
        string name;
        int price;
        while (file >> name >> price) {
            foods.emplace_back(name, price);
        }

        ifstream file2("ingredients.txt");
        int count;
        while (file2 >> name >> price >> count) {
            ingredients.emplace_back(name, price, count);
        }
    }

    const vector<Food>& getFoods() const { return foods; }
    const vector<Ingredient>& getIngredients() const { return ingredients; }
    int getUserSeat() const { return userSeat; }
    void setUserSeat(int seat) { userSeat = seat; }

    void showFoods() {
        for (const auto& food : foods) {
            cout << "Name: " << food.getName() << " | Price: " << food.getPrice() << "$\n";
        }
    }

    void showIngredients() {
        for (const auto& ingredient : ingredients) {
            cout << "Name: " << ingredient.getName() << " | Price: " << ingredient.getPrice() << "$ | Count: " << ingredient.getCount() << "\n";
        }
    }

    void deleteFoods() {
        while (true) {
            string inpFood;
            cout << "Please input the name of food you want to remove: ";
            cin >> inpFood;

            bool found = false;
            for (size_t i = 0; i < foods.size(); ++i) {
                if (foods[i].getName() == inpFood) {
                    foods.erase(foods.begin() + i);
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << "Updated list of foods:\n";
                showFoods();
                rewriteFoodsFile();
            }
            else {
                cout << "Food not found. Please try again.\n";
            }

            string inputEnough;
            cout << "Is this Enough? (Yes/No): ";
            cin >> inputEnough;
            if (inputEnough == "Yes" || inputEnough == "yes") {
                break;
            }
        }
    }

    void deleteIngredients() {
        while (true) {
            string inpIngredient;
            cout << "Please input the name of the ingredient you want to remove: ";
            cin >> inpIngredient;

            bool found = false;
            for (size_t i = 0; i < ingredients.size(); ++i) {
                if (ingredients[i].getName() == inpIngredient) {
                    ingredients.erase(ingredients.begin() + i);
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << "Updated list of ingredients:\n";
                showIngredients();
                rewriteIngredientsFile();
            }
            else {
                cout << "Ingredient not found. Please try again.\n";
            }

            string inputEnough;
            cout << "Is this Enough? (Yes/No): ";
            cin >> inputEnough;
            if (inputEnough == "Yes" || inputEnough == "yes") {
                break;
            }
        }
    }

    void addFood() {
        while (true) {
            string foodName;
            int foodPrice;
            cout << "Input food name you want to add: ";
            cin >> foodName;
            cout << "Input price of food: ";
            cin >> foodPrice;

            foods.emplace_back(foodName, foodPrice);

            rewriteFoodsFile();

            string inputEnough;
            cout << "Is this Enough? (Yes/No): ";
            cin >> inputEnough;
            if (inputEnough == "Yes" || inputEnough == "yes") {
                break;
            }
        }
    }

    void addIngredients() {
        while (true) {
            string ingredientName;
            int ingredientPrice;
            int ingredientCount;
            cout << "Input ingredient name you want to add: ";
            cin >> ingredientName;
            cout << "Input price of ingredient: ";
            cin >> ingredientPrice;
            cout << "Input count of ingredient: ";
            cin >> ingredientCount;

            ingredients.emplace_back(ingredientName, ingredientPrice, ingredientCount);

            rewriteIngredientsFile();

            string inputEnough;
            cout << "Is this Enough? (Yes/No): ";
            cin >> inputEnough;
            if (inputEnough == "Yes" || inputEnough == "yes") {
                break;
            }
        }
    }

    void store() {
        int FoodTotal = 0;

        for (const auto& food : foods) {
            int a;
            cout << "Enter amount of " << food.getName() << ": ";
            cin >> a;
            FoodTotal += (food.getPrice()) * a;
        }

        cout << "Total Food Price is " << FoodTotal << "$.\n";
        cout << "-----That means you must pay " << FoodTotal << "$-----\n";
    }

    void orderFood() {
        string foodName;
        cout << "Enter the name of the food you want to order: ";
        cin.ignore();
        getline(cin, foodName);

        bool foundFood = false;
        int foodPrice = 0;
        for (const auto& food : foods) {
            if (food.getName() == foodName) {
                foundFood = true;
                foodPrice = food.getPrice();
                break;
            }
        }

        if (!foundFood) {
            cout << "Invalid option. There is no such food. Please try again with a valid food name.\n";
            return;
        }

        while (true) {
            string additionalIngredients;
            cout << "Do you want additional ingredients? (Yes/No): ";
            cin >> additionalIngredients;

            if (additionalIngredients == "Yes" || additionalIngredients == "yes") {
                string ingredientName;
                cout << "Enter the name of the ingredient you want to add: ";
                cin.ignore();
                getline(cin, ingredientName);

                bool ingredientFound = false;
                int ingredientIndex = -1;
                int ingredientPrice = 0;
                for (size_t i = 0; i < ingredients.size(); ++i) {
                    if (ingredients[i].getName() == ingredientName) {
                        ingredientFound = true;
                        ingredientIndex = i;
                        ingredientPrice = ingredients[i].getPrice();
                        break;
                    }
                }

                if (!ingredientFound) {
                    cout << "Invalid choice. There is no such ingredient. Please try again with a valid ingredient name.\n";
                }
                else {
                    if (ingredients[ingredientIndex].getCount() > 0) {
                        cout << "Ingredient added successfully.\n";
                        ingredients[ingredientIndex].setCount(ingredients[ingredientIndex].getCount() - 1);
                        foodPrice += ingredientPrice;
                    }
                    else {
                        cout << "Sorry, we don't have this ingredient in stock.\n";
                    }
                }
            }
            else if (additionalIngredients == "No" || additionalIngredients == "no") {
                break;
            }
            else {
                cout << "Invalid input. Please enter Yes or No.\n";
            }
        }

        string paymentMethod;
        cout << "Enter payment method (Cash or Card): ";
        cin >> paymentMethod;

        if (paymentMethod == "Cash" || paymentMethod == "cash") {
            cout << "You paid with cash.\n";
            totalMoneyPaid += foodPrice;
        }
        else if (paymentMethod == "Card" || paymentMethod == "card") {
            cout << "Money transaction done and you paid with card.\n";
            totalMoneyPaid += foodPrice;
        }
        else {
            cout << "Invalid payment method. Please choose Cash or Card.\n";
        }

        cout << "You paid " << totalMoneyPaid << "$.\n";

        orders.emplace_back(userSeat, false);
    }

    void viewOrders() {
        cout << "------<View Orders>------\n";
        cout << "Table Number\tOrder Status\n";
        for (const auto& order : orders) {
            cout << order.first << "\t\t" << (order.second ? "Accepted" : "Rejected") << "\n";
        }
        cout << "-------------------------\n";
    }

    void acceptOrRejectOrder() {
        int tableNumber;
        cout << "Enter the table number of the order you want to accept/reject: ";
        cin >> tableNumber;

        bool foundOrder = false;
        for (auto& order : orders) {
            if (order.first == tableNumber) {
                foundOrder = true;

                string decision;
                cout << "Do you want to accept or reject the order for table " << tableNumber << "? (Accept/Reject): ";
                cin >> decision;

                if (decision == "Accept" || decision == "accept") {
                    order.second = true;
                    cout << "Order for table " << tableNumber << " is accepted.\n";
                }
                else if (decision == "Reject" || decision == "reject") {
                    order.second = false;
                    cout << "Order for table " << tableNumber << " is rejected.\n";
                }
                else {
                    cout << "Invalid decision. Please choose Accept or Reject.\n";
                }

                break;
            }
        }

        if (!foundOrder) {
            cout << "Order not found for table " << tableNumber << ".\n";
        }
    }
};

int main() {
    cout << "--------------<!WELCOME TO OUR RESTAURANT!>--------------\n";
    cout << "-------------First Of All You Have To Sign In-------------\n";
    string user;
    cout << "Input Username (Guest or Admin): ";
    cin >> user;

    RestaurantManagement restaurantManagement;

    while (true) {
        if (user == "Guest") {
            int userSeat;
            cout << "Choose a seat (1-20): ";
            cin >> userSeat;
            restaurantManagement.setUserSeat(userSeat);

            while (true) {
                string userChoice;
                cout << "Choose one of the following options: \n"
                    << "1. ShowFoods\n"
                    << "2. Search Food by name\n"
                    << "3. ShowIngredients\n"
                    << "4. Search Ingredient by name\n"
                    << "5. Order Food\n"
                    << "6. View Orders\n"
                    << "7. Back to Login\n";
                cin >> userChoice;

                if (userChoice == "1") {
                    restaurantManagement.showFoods();
                }
                else if (userChoice == "2") {
                    string foodName;
                    bool foundFood = false;
                    cout << "Enter the name of the food you want to search: ";
                    cin.ignore();
                    getline(cin, foodName);
                    for (const auto& food : restaurantManagement.getFoods()) {
                        if (food.getName() == foodName) {
                            cout << "Name: " << food.getName() << " | Price: " << food.getPrice() << "$\n";
                            foundFood = true;
                            break;
                        }
                    }
                    if (!foundFood) {
                        cout << "Food not found. Please try again with a valid food name.\n";
                    }
                }
                else if (userChoice == "3") {
                    restaurantManagement.showIngredients();
                }
                else if (userChoice == "4") {
                    string ingredientName;
                    bool foundIngredient = false;
                    cout << "Enter the name of the ingredient you want to search: ";
                    cin.ignore();
                    getline(cin, ingredientName);
                    for (const auto& ingredient : restaurantManagement.getIngredients()) {
                        if (ingredient.getName() == ingredientName) {
                            cout << "Name: " << ingredient.getName() << " | Price: " << ingredient.getPrice() << "$ | Count: " << ingredient.getCount() << "\n";
                            foundIngredient = true;
                            break;
                        }
                    }
                    if (!foundIngredient) {
                        cout << "Ingredient not found. Please try again with a valid ingredient name.\n";
                    }
                }
                else if (userChoice == "5") {
                    restaurantManagement.orderFood();
                }
                else if (userChoice == "6") {
                    restaurantManagement.viewOrders();
                }
                else if (userChoice == "7") {
                    cout << "Going back to Login interface.\n";
                    break;
                }
                else {
                    cout << "Invalid input. Please choose a valid option.\n";
                }
            }
        }
        else if (user == "Admin") {
            while (true) {
                string operation;
                cout << "Input one of these operations (ShowFood, DeleteFood, AddFood, ShowIngredients, AddIngredients, DeleteIngredients, ViewOrders, AcceptOrRejectOrder) or Type Exit: ";
                cin >> operation;

                if (operation == "ShowFood") {
                    restaurantManagement.showFoods();
                }
                else if (operation == "DeleteFood") {
                    restaurantManagement.deleteFoods();
                }
                else if (operation == "AddFood") {
                    restaurantManagement.addFood();
                }
                else if (operation == "ShowIngredients") {
                    restaurantManagement.showIngredients();
                }
                else if (operation == "AddIngredients") {
                    restaurantManagement.addIngredients();
                }
                else if (operation == "DeleteIngredients") {
                    restaurantManagement.deleteIngredients();
                }
                else if (operation == "ViewOrders") {
                    restaurantManagement.viewOrders();
                }
                else if (operation == "AcceptOrRejectOrder") {
                    restaurantManagement.acceptOrRejectOrder();
                }
                else if (operation == "Exit") {
                    cout << "Going back to Login interface.\n";
                    break;
                }
                else {
                    cout << "Invalid operation! Please try again.\n";
                }
            }
        }
        else {
            cout << "Something went wrong (Username or Password is incorrect)!\n";
            break;
        }

        cout << "Input Username (Guest or Admin): ";
        cin >> user;
    }
}