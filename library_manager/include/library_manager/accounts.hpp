#include <iostream>
#include <string>
#include <ctime>

#include "library_manager/book.hpp"
#include "library_manager/types.hpp"

namespace library_manager
{
class Account
{
  private:
    std::string id_;
    std::string password_;
    Person person_;
    AccountStatus status_;

  public:
    Account(std::string& id, std::string& password, Person& person,
            auto status = AccountStatus::Active)
      : id_(id), password_(password), person_(person), status_(status)
    {
    }

    inline void resetPassword()
    {
        password_ = "";
    }
};

class Librarian : public Account
{
  public:
    Librarian(std::string& id, std::string& password, Person& person,
              auto status = AccountStatus::Active);

    void addBookItem(BookItem& book_item);

    void blockMember(Member& member);

    void unblockMember(Member& member);
};

class Member
{
  private:
    int total_books_checkedout_ = 0;
    time_t date_of_membership_;

  public:
    Member(std::string& id, std::string& password, Person& person,
           auto status = AccountStatus::Active);

    void reserveBookItem(BookItem& book_item);

    void incrementTotalBooksCheckedout();

    bool renewBookItem(BookItem& book_item);

    void checkoutBookItem(BookItem& book_item);

    double checkForFine(std::string& book_item_barcode);

    void returnBookItem(BookItem& book_item);

    void returnBookItem(BookItem& book_item);
};

}  // namespace library_manager
