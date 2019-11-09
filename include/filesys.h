#pragma once

#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <map>

using namespace std;
using namespace boost::filesystem;

string get_latest_date(const string &date1,const string &date2) {
    unsigned int d1 = stoi(date1);
    unsigned int d2 = stoi(date2);

    if (d1 >= d2)
        return date1;
    else
        return date2;
}

void print_fin_file(path &p, map<string, pair <unsigned int, string>>& accounts) {
    string name, bl, number, sep, date, type;
    name = p.stem().string();
    bl = name.substr(0, 8);
    number = name.substr(8, 8);
    sep = name[16];
    date = name.substr(17, 8);
    type = p.extension().string();

    if(bl == "balance_" && stoi(number) && sep == "_" && stoi(date)
    && type == ".txt") {
        cout << p.remove_filename().string() + " " + p.filename().string() + '\n';
        if (accounts.find(number) == accounts.end())
            accounts[number] = pair<int, string> (1, date);
        else {
            accounts[number].first++;
            accounts[number].second = get_latest_date(date, accounts[number]
                .second);
        }
    }
}



void print_acc_info(map<string, pair <unsigned int, string>>& accounts,
    path &path_to_dir) {
    for (directory_entry& x : recursive_directory_iterator(path_to_dir)) {
        if (is_regular_file(x.path())) {
            string name, bl, number, sep, date, type;
            name = x.path().stem().string();
            bl = name.substr(0, 8);
            number = name.substr(8, 8);
            sep = name[16];
            date = name.substr(17, 8);
            type = x.path().extension().string();

            if(bl == "balance_" && stoi(number) && sep == "_" && stoi(date)
            && type == ".txt" && date == accounts[number].second) {
                cout << "broker:" << x.path().string().substr(0, x.path()
                .string().length() - x.path().filename().string().length())
                << " account:" + number + " files:" << accounts[number].first <<
                " lastdate:" + date + '\n';
            }
        }
    }

}

void analyse(path p, map<string ,pair <unsigned int, string>>& accounts) {
    try {
        met1:
        if (exists(p)) {
            if (is_regular_file(p))
                print_fin_file(p, accounts);
            else if (is_directory(p))
                cout << p << " is a directory containing:\n";
            else if (is_symlink(p)) {
                p = read_symlink(p);
                goto met1;
            }
            else
                cout << p << "exists, but is not a regular file or directory\n";
        }
        else
            cout << p << "does not exist\n";
    }
    catch (const filesystem_error& ex) {
        cout << ex.what() << '\n';
    }
}


void iterate(path &path_to_dir) {
    map<string ,pair <unsigned int, string>> accounts;
    for (directory_entry& x : recursive_directory_iterator(path_to_dir)) {
        analyse(x.path(), accounts);
    }
    print_acc_info(accounts, path_to_dir);
}
