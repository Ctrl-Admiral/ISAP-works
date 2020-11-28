#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <string.h>


#include <ak_hash.h>
#include <ak_tools.h>

int
main()
{

    if(ak_hash_test_sha3_256() == ak_true)
    {
        std::cout << "SHA3-256 tests are OK." << std::endl;
    }
    else
    {
        std::cout << "SHA3-256 tests failed." << std::endl;
    }

    if(ak_hash_test_sha3_384() == ak_true)
    {
        std::cout << "SHA3-384 tests are OK." << std::endl;
    }
    else
    {
        std::cout << "SHA3-384 tests failed." << std::endl;
    }

    if(ak_hash_test_sha3_512() == ak_true)
    {
        std::cout << "SHA3-512 tests are OK." << std::endl;
    }
    else
    {
        std::cout << "SHA3-512 tests failed." << std::endl;
    }


    return 0;
}

