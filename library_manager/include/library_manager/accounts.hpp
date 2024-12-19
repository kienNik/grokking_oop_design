#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#include "library_manager/book.hpp"
#include "library_manager/book_reservation.hpp"
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

    std::string getId() const
    {
        return id_;
    }
};

class Librarian : public Account
{
  public:
    Librarian(std::string& id, std::string& password, Person& person,
              auto status = AccountStatus::Active)
    {
    }

    void addBookItem(const BookItem& book_item)
    {
    }

    void blockMember(const Member& member)
    {
    }

    void unblockMember(const Member& member)
    {
    }
};

class Member : public Account
{
  private:
    int total_books_checkedout_ = 0;
    time_t date_of_membership_;

  public:
    Member(std::string& id, std::string& password, Person& person,
           auto status = AccountStatus::Active)
      : Account(id, password, person, password)
    {
        date_of_membership_ = std::time(0);
    }

    inline int getTotalBookCheckedout() const
    {
        return total_books_checkedout_;
    }

    void reserveBookItem(const BookItem& book_item)
    {
    }

    inline void incrementTotalBooksCheckedout()
    {
        ++total_books_checkedout_;
    }

    inline void decrementTotalBooksCheckedout()
    {
        --total_books_checkedout_;
    }

    bool Member::checkoutBookItem(BookItem& book_item)
    {
        if (total_books_checkedout_ >= MAX_BOOKS_ISSUED_TO_A_USER) {
            std::cout << "The user has already checked-out maximum number of books.\n";
            return false;
        }

        auto book_reservation =
            std::shared_ptr<BookReservation>();  // TODO: design book reservation system to lookup
                                                 // by barcode
        if (book_reservation && (book_reservation->getMemberId() != getId())) {
            std::cout << "Book is reserved by another member\n";
            return false;
        } else if (book_reservation) {
            book_reservation->updateStatus(ReservationStatus::COMPLETED);
        }

        if (!book_item.checkout(getId())) {
            return false;
        }

        incrementTotalBooksCheckedout();
        return true;
    }

    void checkForFine(const std::string& book_item_barcode)
    {
        auto book_lending = std::shared_ptr<BookLending>();  // TODO: design book lending system to
                                                             // lookup by barcode
        auto due_date = book_lending->getDueDate();
        auto today = std::time(0);

        // Check if the book has been returned within the due date
        if (today > due_date) {
            auto diff = today - due_date;
            auto fine = std::shared_ptr<Fine>();
            fine->collectFine(getId(), diff);
        }
    }

    void returnBookItem(BookItem& book_item)
    {
        checkForFine(book_item.getBarcode());
        auto book_reservation =
            std::shared_ptr<BookReservation>();  // TODO: design book reservation system to lookup
                                                 // by barcode
        if (book_reservation) {
            // Book item has a pending reservation
            book_item.updateBookItemStatus(BookStatus::RESERVED);
            book_reservation->sendBookAvailableNotification();
            book_item.updateBookItemStatus(BookStatus::AVAILABLE);
        }
    }

    bool renewBookItem(BookItem& book_item)
    {
        checkForFine(book_item.getBarcode());
        auto book_reservation =
            std::shared_ptr<BookReservation>();  // TODO: design book reservation system to lookup
                                                 // by barcode

        // Check if self book item has a pending reservation from another member
        if (book_reservation && book_reservation->getMemberId() != getId()) {
            std::cout << "Book is reserved by another member\n";
            decrementTotalBooksCheckedout();
            book_item.updateBookItemStatus(BookStatus::RESERVED);
            book_reservation->sendBookAvailableNotification();
            return false;
        } else if (book_reservation) {
            // Book item has a pending reservation from self member
            book_reservation->updateStatus(ReservationStatus::COMPLETED);
        }

        auto book_lending = std::shared_ptr<BookLending>();
        book_lending->lendBook(getId(), book_item.getBarcode());
        book_item.updateDueDate(time_t(0) + MAX_LENDING_DAYS);
        return true;
    }
};

}  // namespace library_manager
