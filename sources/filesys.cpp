#include "filesys.h"

std::string calcLatestDate(const std::string& date1, const std::string& date2) {
  unsigned int d1 = std::stoi(date1);
  unsigned int d2 = std::stoi(date2);

  if (d1 >= d2)
    return date1;
  else
    return date2;
}

void printFinFile(const fs::path& p,
                  std::map<std::string, AccountsInfo>& accounts) {

  std::string name = p.stem().string();

  if (name.length() == 25) {
    std::string balance = name.substr(0, 8);
    std::string number = name.substr(8, 8);
    std::string separator = name.substr(16, 1);
    std::string date = name.substr(17, 8);
    std::string type = p.extension().string();

    if (balance == "balance_" && std::stoi(number) && separator == "_" &&
        std::stoi(date) && type == ".txt") {

      std::cout << p.parent_path().string() + " " + p.filename().string() + '\n';

      if (accounts.find(number) == accounts.end()) {
        AccountsInfo acc(date);
        accounts[number] = acc;
      }
      else {
        ++accounts[number];
        std::string latest_date = calcLatestDate(date, accounts[number].getLatestDate());
        accounts[number].setLatestDate(latest_date);
      }
    }
  }
}

void printAccountsInfo(const fs::path& path_to_dir,
                       std::map<std::string, AccountsInfo>& accounts) {
  for (const fs::directory_entry &obj : fs::recursive_directory_iterator(path_to_dir)) {
    if (fs::is_regular_file(obj.path())) {
      std::string name = obj.path().stem().string();
      if (name.length() == 25) {
        std::string balance = name.substr(0, 8);
        std::string number = name.substr(8, 8);
        std::string separator = name.substr(16, 1);
        std::string date = name.substr(17, 8);
        std::string type = obj.path().extension().string();

        if (balance == "balance_" && std::stoi(number) && separator == "_" &&
            std::stoi(date) && type == ".txt" &&
            date == accounts[number].getLatestDate()) {

          std::cout << "broker:"
               << obj.path().string().substr(
                      0, obj.path().string().length() -
                             obj.path().filename().string().length())
               << " account:" + number + " files:" << accounts[number].getCount()
               << " lastdate:" + date + '\n';
        }
      }
    }
  }
}

void analyse(const fs::path &p, std::map<std::string, AccountsInfo> &accounts) {
  try {
    if (fs::exists(p)) {
      if (fs::is_regular_file(p))
        printFinFile(p, accounts);
      else if (fs::is_directory(p))
        std::cout << p << " is a directory containing:\n";
      else if (fs::is_symlink(p)) {
        fs::path symlinkPath = fs::read_symlink(p);
        analyse(symlinkPath, accounts);
      } else
        std::cout << p << "exists, but is not a regular file or directory\n";
    } else
      std::cout << p << "does not exist\n";
  } catch (const fs::filesystem_error &ex) {
    std::cout << ex.what() << '\n';
  }
}

void iterate(const fs::path &pathToDir) {
  std::map<std::string, AccountsInfo> accounts;
  for (const fs::directory_entry &obj : fs::recursive_directory_iterator(pathToDir)) {
    analyse(obj.path(), accounts);
  }
  printAccountsInfo(pathToDir, accounts);
}
