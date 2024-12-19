#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "library_manager/types.hpp"

namespace library_manager
{
class Search
{
  public:
    void searchByTitle(const std::string& title)
    {
    }

    void searchByAuthor(const std::string& author)
    {
    }

    void searchBySubject(const std::string& subject)
    {
    }

    void searchByDate(const time_t date)
    {
    }
};

class Catalog : public Search
{
  private:
    std::vector<std::string> book_titles_;
    std::vector<std::string> book_authors_;
    std::vector<std::string> book_subjects_;
    std::vector<time_t> book_publication_dates_;

  public:
    Catalog() = default;

    std::vector<std::string> searchByTitle(const std::string& query)
    {
        std::vector<std::string> titles;
        for (auto title : book_titles_) {
            if (title.find(query) != std::string::npos) {
                titles.push_back(title);
            }
        }
        return titles;
    }

    std::vector<std::string> searchByAuthor(const std::string& query)
    {
        std::vector<std::string> authors;
        for (auto author : book_authors_) {
            if (author.find(query) != std::string::npos) {
                authors.push_back(author);
            }
        }
        return authors;
    }
};
}  // namespace library_manager
