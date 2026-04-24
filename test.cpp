#include "util.hpp"

int main(){
    // cout << ljt::unil::Data::getNowTime() << endl;
    // cout << ljt::unil::File::fileIsExist("./a/b/test.txt") << endl;
    // cout << ljt::unil::File::fileIsExist("./c/d/test.txt") << endl;
    ljt::unil::File::createDirSource("./abc/def/text.txt");
    return 0;
}