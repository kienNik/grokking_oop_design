#include <iostream>
#include <string>

#define MAX_BOOKS_ISSUED_TO_A_USER 5
#define MAX_LENDING_DAYS 10

namespace library_manager
{
enum class BookFormat {
    Hardcover,
    Paperback,
    AudioBook,
    Ebook,
    Newspaper,
    Magazine,
    Journal,
};

enum class BookStatus {
    Available,
    Reserved,
    Loaned,
    Lost,
};

enum class ReservationStatus {
    Waiting,
    Pending,
    Completed,
    Canceled,
    Blacklisted,
    None,
};

class Address
{
  private:
    std::string street_address_;
    std::string city_;
    std::string state_;
    std::string zipcode_;
    std::string country_;

  public:
    Address(std::string& street_address, std::string& city, std::string& state,
            std::string& zipcode, std::string& country)
      : street_address_(street_address)
      , city_(city)
      , state_(state)
      , zipcode_(zipcode)
      , country_(country)
    {
    }
};

class Person
{
  private:
    std::string name_;
    std::string address_;
    std::string email_;
    std::string phone_;

  public:
    Person(std::string& name, std::string& address, std::string& email, std::string& phone)
      : name_(name), address_(address), email_(email), phone_(phone)
    {
    }
};

}  // namespace library_manager
