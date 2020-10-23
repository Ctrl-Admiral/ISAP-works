#include <iostream>
extern "C"
{
#include <libakrypt.h>
#include <libakrypt/ak_mpzn.h>
}

using namespace std;

int main()
{
    cout << ak_libakrypt_options_count() << endl;

    return 0;
}
