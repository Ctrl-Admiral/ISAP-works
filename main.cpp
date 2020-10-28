#include "my_curves.hpp"
#include <libakrypt.h>
#include <ak_mpzn.h>
#include <ak_curves.h>
#include <ak_random.h>

#include <iostream>

int main()
{

my::ProjecticPoint point(
            {
                "", //x0
                "", //x1
                "", //x2
                ""  //x3
            });

my::Curve curve(
            ak_mpzn256_size,
            "4",    //a
            "3",    //b
            "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffef0c5a3", //x
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa9d5548956f47db5daf44297e8da018f9",  //y
            point,
            0xdbf951d5883b2b2fLL, //n for montgomery operations
            "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffef0c5a1"  //k2
            );

ak_mpzn256 k;
struct random rand_generator;
ak_random_context_create(&rand_generator);
ak_mpzn_set_random_modulo(k, curve.p(), ak_mpzn256_size, &rand_generator);


my::ProjecticPoint Q(curve.point_pow(point, k, ak_mpzn256_size));

std::cout << "TEST started\n";
std::cout << "Checking if point Q on curve:\n";
std::cout << "" << std::boolalpha << curve.point_is_ok(Q) << '\n';



ak_random_context_delete(&rand_generator);
return 0;
}
