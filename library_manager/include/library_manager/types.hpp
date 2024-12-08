#include <iostream>
#include <string>

#define MAX_BOOKS_ISSUED_TO_A_USER 5
#define MAX_LENDING_DAYS 10

namespace library_manager
{
enum class BookFormat {
    HARDCOVER,
    PAPERBACK,
    AUDIOBOOK,
    EBOOK,
    NEWSPAPER,
    MAGAZINE,
    JOURNAL,
};

enum class BookStatus {
    AVAILABLE,
    RESERVED,
    LOANED,
    LOST,
};

enum class ReservationStatus {
    WAITING,
    PENDING,
    COMPLETED,
    CANCELED,
    NONE,
};

enum class AccountStatus {
    ACTIVE,
    CLOSED,
    CANCELED,
    BLACKLISTED,
    NONE,
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
