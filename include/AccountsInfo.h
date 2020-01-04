#pragma once
#include <AccountsInfo.h>
#include <string>

class AccountsInfo {
public:
  AccountsInfo() = default;

  AccountsInfo(const std::string &);

  AccountsInfo(const AccountsInfo &);

  AccountsInfo &operator=(const AccountsInfo &);

  AccountsInfo &operator++();

  void setLatestDate(const std::string &);

  std::string getLatestDate();

  unsigned int getCount();

private:
  std::string latest_date_;

  unsigned int count_of_files_ = 0;
};
