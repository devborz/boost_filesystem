#include "AccountsInfo.h"

AccountsInfo::AccountsInfo(const std::string &date) {
  this->latest_date_ = date;
  this->count_of_files_++;
}

AccountsInfo::AccountsInfo(const AccountsInfo &account) {
  this->latest_date_ = account.latest_date_;
  this->count_of_files_ = account.count_of_files_;
}

AccountsInfo &AccountsInfo::operator=(const AccountsInfo &account) {
  this->latest_date_ = account.latest_date_;
  this->count_of_files_ = account.count_of_files_;

  return *this;
}

AccountsInfo &AccountsInfo::operator++() {
  this->count_of_files_++;

  return *this;
}

void AccountsInfo::setLatestDate(const std::string &date) {
  this->latest_date_ = date;
}

std::string AccountsInfo::getLatestDate() { return this->latest_date_; }

unsigned int AccountsInfo::getCount() { return this->count_of_files_; }
