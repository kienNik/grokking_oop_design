#include <iostream>
#include <string>
#include <vector>

#include "library_manager/book_reservation.hpp"
#include "library_manager/types.hpp"

namespace library_manager
{
class Book
{
  private:
    std::string ISBN_;
    std::string title_;
    std::string subject_;
    std::string publisher_;
    std::string language_;
    std::string num_of_pages_;
    std::vector<std::string> authors_;
};

class BookItem : public Book
{
  private:
    std::string barcode_;
    bool is_reference_only_;
    bool borrowed_;
    time_t due_date_;
    double price_;
    BookFormat format_;
    BookStatus status_;
    time_t date_of_purchase_;
    time_t publication_date_;
    bool placed_at_;

  public:
    BookItem() = default;

    bool checkout(std::string member_id)
    {
        if (is_reference_only_) {
            std::cout << "Book is referenced only and can't be issued.\n";
            return false;
        }

        auto book_lending = BookLending(barcode_, member_id);
        if (!book_lending.lendBook(member_id, barcode_)) {
            return false;
        }

        updateBookItemStatus(BookStatus::LOANED);
        return true;
    }

    void updateBookItemStatus(BookStatus status)
    {
        status_ = status;
    }

    std::string getBarcode()
    {
        return barcode_;
    }
};

class Rack
{
  private:
    int number_;
    std::string location_id_;

  public:
    Rack(int number, std::string location_id) : number_(number), location_id_(location_id)
    {
    }
};

}  // namespace library_manager
