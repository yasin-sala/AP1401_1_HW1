#include "book_inventory.h"
//  read_database
Books book::read_database(std::string filepath)
{
    Books list {};
    std::ifstream File(filepath);
    if (File.fail())
        throw std::runtime_error("something bad happend");
    else {
        std::string Line {};
        while (std::getline(File, Line)) {
            std::string word;
            std::stringstream line { Line };
            Book B {};
            int i { 0 };
            while (getline(line, word, ',')) {
                i++;
                if (i == 2) {
                    B.title = word;
                }
                if (i == 3) {
                    B.author = word;
                }
                if (i == 4) {
                    B.cost = std::stod(word);
                }
                if (i == 5) {
                    B.isbn = word;
                }
                if (i == 6) {
                    B.language_code = word;
                }
                if (i == 7) {
                    B.num_pages = std::stod(word);
                }
                if (i == 8) {
                    B.publisher = word;
                }
                if (i == 9) {
                    B.count = std::stod(word);
                }
            }
            list.push_back(B);
        }
    }
    File.close();
    return list;
}
// search if there is a book in inventory
std::string book::search(Books inventory, std::string title)
{
    std::string isbn { "none" };
    for (size_t i {}; i < inventory.size(); i++) {
        if (inventory[i].title == title) {
            isbn = inventory[i].isbn;
        }
    }
    return isbn;
}
// order a book
//  because inventory and shopping list are changing, we use refrence hero for there 2
bool book::order(Books& inventory, Books& shopinglist, std::string isbn)
{
    int k {};
    for (size_t i {}; i < inventory.size(); i++) {
        if (inventory[i].isbn == isbn) {
            inventory[i].count -= 1;
            shopinglist.push_back(inventory[i]);
            k += 1;
        }
    }
    if (k == 0)
        return false;
    else
        return true;
}
// after ordering, we need to see the receipt to make sure we got whatever we needed
double book::get_receipt(Books shopinglist)
{
    std::cout << "*******************************************************" << std::endl;
    std::cout << "|   title              |    isbn         |    price   |" << std::endl;
    std::cout << "|-----------------------------------------------------|" << std::endl;
    double price {};
    for (size_t i {}; i < shopinglist.size(); i++) {
        price += shopinglist[i].cost;
        std::cout << "|   ";
        if (shopinglist[i].title.length() > 15) {
            std::cout << shopinglist[i].title.substr(0, 12) << "...";
        } else {
            std::cout << shopinglist[i].title;
            for (size_t j {}; j < 15 - shopinglist[i].title.length(); j++)
                std::cout << " ";
        }
        std::cout << "    |    " << shopinglist[i].isbn << "    |    "
                  << shopinglist[i].cost << "$" << "   |" <<std::endl;
    }
    std::cout << "| ----------------------------------------------------|" << std::endl;
    std::cout << "|                           Total price  |    " <<  price << "$   |" << std::endl;
    std::cout << "*******************************************************" << std::endl;
    return price;
}