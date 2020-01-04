#pragma once

#include <boost/filesystem.hpp>
#include <iostream>
#include <map>
#include <string>
#include <AccountsInfo.h>

namespace fs = boost::filesystem;

std::string calcLatestDate(const std::string&, const std::string&);

void printFinFile(const fs::path&, std::map<std::string, AccountsInfo>&);

void printAccountsInfo(const fs::path&, std::map<std::string, AccountsInfo>&);

void analyse(const fs::path&, std::map<std::string, AccountsInfo>&);

void iterate(const fs::path&);
