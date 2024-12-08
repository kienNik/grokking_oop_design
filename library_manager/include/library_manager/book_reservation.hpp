#include <ctime>
#include <iostream>
#include <string>

#include "library_manager/types.hpp"

namespace library_manager
{
class BookReservation
{
  private:
    time_t creation_date_;
    ReservationStatus status_;
    std::string book_item_barcode_;
    std::string member_id_;

  public:
    BookReservation() = default;

    BookReservation(time_t creation_date, ReservationStatus status, std::string book_item_barcode,
                    std::string member_id)
      : creation_date_(creation_date)
      , status_(status)
      , book_item_barcode_(book_item_barcode)
      , member_id_(member_id)
    {
        creation_date = std::time(0);
    }

    BookReservation* fetchReservationDetails(std::string& barcode)
    {
        return this;
    }

    std::string getMemberId()
    {
        return member_id_;
    }

    void updateStatus(const ReservationStatus status)
    {
        status_ = status;
    }
};

class BookLending
{
  private:
    time_t creation_date_;
    time_t due_date_;
    time_t return_date_;
    std::string book_item_barcode_;
    std::string member_id_;

  public:
    BookLending(std::string book_item_barcode, std::string member_id)
    {
        creation_date_ = std::time(0);
        due_date_ = creation_date_ + MAX_LENDING_DAYS;
        book_item_barcode_ = book_item_barcode;
        member_id_ = member_id;
    }

    bool lendBook(std::string member_id, std::string barcode)
    {
        return true;
    }

    BookLending* fetchLendingDetail(std::string barcode)
    {
        return this;
    }
};

class Fine
{
  private:
    time_t creation_date_;
    std::string book_item_barcode_;
    std::string member_id_;

  public:
    Fine(std::string book_item_barcode, std::string member_id)
    {
        creation_date_ = std::time(0);
        book_item_barcode_ = book_item_barcode;
        member_id_ = member_id;
    }
};

}  // namespace library_manager
