#include "filesys.h"

int main(int argc, char *argv[]) {
    /*if (argc < 2)
    {
      cout << "Usage:  path\n";
      return 1;
    }
    */
    //path path_to_ftp("argv[1]");
    path path_to_ftp("files");

    iterate(path_to_ftp);

    return 0;
}
