//Created by Daniel Eze
//Instructor: jie Meischner
//p8 DataBase Management System
//Created December 8 2023
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Date {
private:
    int month;
    int day;
    int year;

public:
    Date() : month(0), day(0), year(0) {}
    Date(int m, int d, int y) : month(m), day(d), year(y) {}

    int getMonth() const { return month; }
    void setMonth(int m) { month = m; }

    int getDay() const { return day; }
    void setDay(int d) { day = d; }

    int getYear() const { return year; }
    void setYear(int y) { year = y; }


/**
 * @brief Overloaded output stream operator for Date class.
 * @param os Output stream.
 * @param date Date object to output.
 * @return Output stream.
 */
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
/**
 * @brief Overloaded input stream operator for Date class.
 * @param is Input stream.
 * @param date Date object to input.
 * @return Input stream.
 */
    friend std::istream& operator>>(std::istream& is, Date& date);
};

std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.month << " " << date.day << " " << date.year;
    return os;
}

std::istream& operator>>(std::istream& is, Date& date) {
    is >> date.month >> date.day >> date.year;
    return is;
}

/**
 * @brief Represents a person with a name and a birthday.
 */
class People {
private:
    std::string name;
    Date birthday;

public:
    People() : name(""), birthday(Date()) {}
    People(const std::string& n, const Date& b) : name(n), birthday(b) {}

    const std::string& getName() const { return name; }
    void setName(const std::string& n) { name = n; }

    const Date& getBirthday() const { return birthday; }
    void setBirthday(const Date& b) { birthday = b; }
/**
 * @brief Overloaded less than operator for People class.
 * @param lhs Left-hand side People object.
 * @param rhs Right-hand side People object.
 * @return True if lhs < rhs, otherwise false.
 */
    friend bool operator<(const People& lhs, const People& rhs) {
        return lhs.name < rhs.name;
    }
/**
 * @brief Overloaded greater than operator for People class.
 * @param lhs Left-hand side People object.
 * @param rhs Right-hand side People object.
 * @return True if lhs > rhs, otherwise false.
 */
    friend bool operator>(const People& lhs, const People& rhs) {
        return lhs.name > rhs.name;
    }

/**
 * @brief Overloaded output stream operator for People class.
 * @param os Output stream.
 * @param person People object to output.
 * @return Output stream.
 */
    friend std::ostream& operator<<(std::ostream& os, const People& person);
/**
 * @brief Overloaded input stream operator for People class.
 * @param is Input stream.
 * @param person People object to input.
 * @return Input stream.
 */
    friend std::istream& operator>>(std::istream& is, People& person);
};

std::ostream& operator<<(std::ostream& os, const People& person) {
    os << person.name << " " << person.birthday;
    return os;
}

std::istream& operator>>(std::istream& is, People& person) {
    is >> person.name >> person.birthday;
    return is;
}
/**
 * @brief Represents a node in a binary search tree.
 * @tparam T Type of data stored in the node.
 */
template <typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;
/**
 * @brief Constructs a Node with the given value.
 * @param val Value to be stored in the node.
 */
    Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
};
/**
 * @brief Represents a binary search tree.
 * @tparam T Type of data stored in the tree.
 */
template <typename T>
class BinarySearchTree {
private:
    Node<T>* root;
/**
 * @brief Inserts a value into the binary search tree.
 * @param node Current node.
 * @param val Value to be inserted.
 * @return Updated node.
 */
    Node<T>* insert(Node<T>* node, const T& val) {
        if (node == nullptr) {
            return new Node<T>(val);
        }

        if (val < node->data) {
            node->left = insert(node->left, val);
        } else if (val > node->data) {
            node->right = insert(node->right, val);
        }

        return node;
    }
/**
 * @brief Removes a value from the binary search tree.
 * @param node Current node.
 * @param val Value to be removed.
 * @return Updated node.
 */
    Node<T>* remove(Node<T>* node, const T& val) {
        if (node == nullptr) {
            return nullptr;
        }

        if (val < node->data) {
            node->left = remove(node->left, val);
        } else if (val > node->data) {
            node->right = remove(node->right, val);
        } else {
            if (node->left == nullptr) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }

            Node<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }

        return node;
    }
/**
 * @brief Finds the minimum value node in the binary search tree.
 * @param node Starting node.
 * @return Node with the minimum value.
 */
    Node<T>* findMin(Node<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
/**
 * @brief Searches for a value in the binary search tree.
 * @param node Current node.
 * @param val Value to be searched.
 * @return True if the value is found, otherwise false.
 */
    bool search(Node<T>* node, const T& val) const {
        if (node == nullptr) {
            return false;
        }

        if (val < node->data) {
            return search(node->left, val);
        } else if (val > node->data) {
            return search(node->right, val);
        }

        return true;
    }
/**
 * @brief Performs an inorder traversal of the binary search tree.
 * @param node Current node.
 * @param result Vector to store the result of the traversal.
 */
    void inorderTraversal(Node<T>* node, std::vector<T>& result) const {
        if (node != nullptr) {
            inorderTraversal(node->left, result);
            result.push_back(node->data);
            inorderTraversal(node->right, result);
        }
    }
/**
 * @brief Performs a preorder traversal of the binary search tree.
 * @param node Current node.
 */
    void preorderTraversal(Node<T>* node) const {
        if (node != nullptr) {
            std::cout << node->data << std::endl;
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}
/**
 * @brief Inserts a value into the binary search tree.
 * @param val Value to be inserted.
 */
    void insert(const T& val) {
        if (!search(val)) {
            root = insert(root, val);
        }
    }
/**
 * @brief Removes a value from the binary search tree.
 * @param val Value to be removed.
 */
    void remove(const T& val) {
        root = remove(root, val);
    }
/**
 * @brief Searches for a value in the binary search tree.
 * @param val Value to be searched.
 * @return True if the value is found, otherwise false.
*/
    bool search(const T& val) const {
        return search(root, val);
    }
/**
 * @brief Retrieves the sorted elements from the binary search tree.
 * @return Vector containing sorted elements.
 */
    std::vector<T> getSorted() const {
        std::vector<T> result;
        inorderTraversal(root, result);
        return result;
    }
/**
 * @brief Displays the binary search tree in preorder.
 */
    void displayPreorder() const {
        std::cout << "The database displayed in preorder:\n";
        preorderTraversal(root);
    }
/**
 * @brief Gets the root of the binary search tree.
 * @return Root node of the binary search tree.
 */
    Node<T>* getRoot() const {
        return root;
    }
};

class PeopleDB {
private:
    BinarySearchTree<People> db;

public:
/**
 * @brief Constructor that initializes the database from a file.
 * @param filename Name of the file containing the initial list of people.
 */
    PeopleDB(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (inputFile.is_open()) {
            People person;
            while (inputFile >> person) {
                db.insert(person);
            }
            inputFile.close();
        } else {
            std::cerr << "Error: Unable to open the input file." << std::endl;
        }
    }
/**
 * @brief Adds a person to the database.
 * @param person Person to be added.
 */
    void addPerson(const People& person) {
        db.insert(person);
    }
/**
 * @brief Removes a person from the database.
 * @param person Person to be removed.
 */
    void removePerson(const People& person) {
        db.remove(person);
    }
/**
 * @brief Modifies the information of a person in the database.
 * @param person Person to be modified.
 */
    void modifyDatabase(const People& person) {
        if (db.search(person)) {
            db.remove(person);
            db.insert(person);
        } else {
            std::cout << "Person not found in the database." << std::endl;
        }
    }
/**
 * @brief Searches for a person in the database.
 * @param person Person to be searched.
 * @return True if the person is found, otherwise false.
 */
    bool search(const People& person) const {
        return db.search(person);
    }
/**
 * @brief Displays the entire database sorted by names.
 */
    void displaySorted() const {
        std::vector<People> sortedRecords = db.getSorted();
        for (const auto& record : sortedRecords) {
            std::cout << record << std::endl;
        }
    }

/**
 * @brief Displays the binary search tree in preorder.
 */
    void displayPreorder() const {
        db.displayPreorder();
    }

    /**
     * @brief Saves the database to a file.
     * @param filename Name of the file to save the database.
     */
    void saveToFile(const std::string& filename) {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open the output file." << std::endl;
            return;
        }

        std::vector<People> sortedRecords = db.getSorted();
        for (const auto& record : sortedRecords) {
            outputFile << record << std::endl;
        }
        outputFile.close();
        std::cout << "The updated database has been saved to \"" << filename << "\"." << std::endl;
    }
};

int main() {
   
        std::cout << "Welcome to 'Rizz' database system. Please enter the file that contains the list of people: ";
        std::string filename;
        std::cin >> filename;

        PeopleDB database(filename);
  std::cout << "The initial database built from the input file is displayed by its original order:"<< std::endl;
  database.displayPreorder();
        int option;
        do {
            std::cout << "\nPlease enter your option\n"
                      << "1. Add a new person\n"
                      << "2. Remove a person\n"
                      << "3. Modify the database\n"
                      << "4. Search for a person in the database\n"
                      << "5. Display the database\n"
                      << "6. Display the database sorted by names\n"
                      << "7. Quit and save the database to a file\n"
                      << "-->";
            std::cin >> option;

            switch (option) {
                case 1: {
                    std::cout << "To add, enter name and birthday (month day year): ";
                    People personToAdd;
                    std::cin >> personToAdd;
                    database.addPerson(personToAdd);

                    char addAnother;
                    std::cout << "Add another one? (Y/N): ";
                    std::cin >> addAnother;
                    while (addAnother == 'Y' || addAnother == 'y') {
                        std::cout << "To add, enter name and birthday (month day year): ";
                        std::cin >> personToAdd;
                        database.addPerson(personToAdd);

                        std::cout << "Add another one? (Y/N): ";
                        std::cin >> addAnother;
                    }
                    break;
                }
                  case 2: {
                      std::cout << "To remove, enter person’s name and birthday:\n";
                      People personToRemove;
                      std::cin >> personToRemove;
                      if (database.search(personToRemove)) {
                          std::cout << "This person has been removed.\n";
                          database.removePerson(personToRemove);
                      } else {
                          std::cout << "Can not find this person.\n";
                      }

                      char removeAnother;
                      std::cout << "Remove another one? (Y/N): ";
                      std::cin >> removeAnother;
                      if (removeAnother != 'Y' && removeAnother != 'y') {
                          std::cout << "Exiting remove operation.\n";
                      }
                    else
                      {
                    std::cout << "To remove, enter person’s name and birthday:\n";
                    People personToRemove;
                    std::cin >> personToRemove;
                    if (database.search(personToRemove)) {
                        std::cout << "This person has been removed.\n";
                        database.removePerson(personToRemove);
                    } else {
                        std::cout << "Can not find this person.\n";
                    }
                      break;
                  }}
              case 3: {
                  std::cout << "To modify, enter person’s name and birthday:\n";
                  People personToModify;
                  std::cin >> personToModify;

                  if (database.search(personToModify)) {
                      std::cout << "Found this person in the database. This person's data has been removed.\n";
                      database.removePerson(personToModify);

                      std::cout << "Enter this person's new information: name and birthday (month day year):\n";
                      People newPerson;
                      std::cin >> newPerson;
                    database.addPerson(newPerson);
                    std::cout << "The database has been modified.";

                    
                     

                      char continueModify;
                      std::cout << " Continue to modify? (Y/N): ";
                      std::cin >> continueModify;
                      if (continueModify != 'Y' && continueModify != 'y') {
                          std::cout << "Exiting modify operation.\n";
                      }
                  } else {
                      std::cout << "Can not find this person in the database. Exiting modify operation.\n";
                  }
                  break;
              }

                
                case 4: {
                    std::cout << "To search, enter person’s name and birthday:\n";
                    People personToSearch;
                    std::cin >> personToSearch;

                    if (database.search(personToSearch)) {
                        std::cout << "Person found in the database.\n";
                    } else {
                        std::cout << "Person not found in the database.\n";
                    }

                    char searchAgain;
                    std::cout << "Do you want to search again? (Y/N): ";
                    std::cin >> searchAgain;
                    if (searchAgain != 'Y' && searchAgain != 'y') {
                        std::cout << "Exiting search operation.\n";
                    }
                  else{
                      std::cout << "To search, enter person’s name and birthday:\n";
                      People personToSearch;
                      std::cin >> personToSearch;

                      if (database.search(personToSearch)) {
                          std::cout << "Person found in the database.\n";
                      } else {
                          std::cout << "Person not found in the database.\n";
                      }
                }
                    break;
                }

                case 5: {
                    // Implement the logic for displaying the database using preorder
                  database.displayPreorder();
                 
                    break;
                }
                case 6: {
                    std::cout << "The database sorted by names:\n";
                    database.displaySorted();
                    break;
                }
                case 7: {
                    std::cout << "Quitting and saving the database to a file.\n";
                    database.saveToFile("studentDB2.txt");
                    std::cout << "Bye!\n";
                    break;
                }
                default: {
                    std::cout << "Invalid option. Please try again.\n";
                    break;
                }
            }
        } while (option != 7);

        return 0;
    }
