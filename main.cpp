#include "my_curves.hpp"
#include <ak_curves.h>
#include <ak_mpzn.h>
#include <libakrypt.h>
#include <ak_random.h>

#include <iostream>

int main()
{
my::ProjecticPoint P(
            "bfd844c4d2aca70a17115591ec8f6a352ab877d2a4d451dde64b4b4bbf92d845", //x0
            "f86cc7890b05fedc892cdeee432f19f40649d3935c5cdf1e7b8fa41c70066c71", //x1
            "4d5008aeeeddeb368ceead70cebadb054d61602140a46ea3966f2b6a2f4701de", //x2
            "75c5b8e75d54402af9bdaa77ef9381c3783379e9454236897e22a61c12f4988d"  //x3
            );

my::Curve curve(
            ak_mpzn256_size,
            "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffef0c5a3", //p
            "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa9d5548956f47db5daf44297e8da018f9",  //q
            P,                                                                  //point
            0x35c1a21a625e960bLL,                                               //n0 for montgomery operations
            "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffef0c5a1"  //k2
            );

ak_mpzn256 k;
ak_mpzn_set_hexstr(k, ak_mpzn256_size, "fff87129");

//struct random rand_generator;
//ak_random_context_create(&rand_generator);
//std::cout << ak_mpzn_set_random_modulo(k, curve.p(), ak_mpzn256_size, &rand_generator) << '\n';

std::cout << "Set P as \n" << P << '\n';

std::cout << "Check is it on curve: " << std::boolalpha << curve.point_is_ok(P) << '\n';

std::cout << "\n===========TEST started===========\n";


//ak_mpzn256 res;
//ak_mpzn_mul_montgomery(res, P.x0(), P.x1(),curve.p(), curve.n(), curve.size());
//std::cout << ak_mpzn_to_hexstr(res, ak_mpzn256_size) << '\n';

//my::ProjecticPoint p1("0", "0", "0", "0"), p2("0", "0", "fffffff", "aaaaaaaaa");
//std::cout << "P2:\n" << p2 << '\n';
//my::ProjecticPoint p3 = curve.add_points(p1, p2);

//std::cout << p3 << '\n';

my::ProjecticPoint adres, addres("1", "1", "1", "0");
std::cout << addres << '\n';
curve.double_point(adres);
std::cout << "Doubled point: \n" << adres << '\n';

//std::cout << "Checking if point Q=[k]P on curve:\n";
//my::ProjecticPoint Q(curve.point_pow(P, k, ak_mpzn256_size));

//#ifndef NDEBUG
//std::cout << "Q: \n" << Q << '\n';
//#endif

//std::cout << "" << std::boolalpha << curve.point_is_ok(Q) << '\n';

//std::cout << "Checking if [q]P==0:\n";
//my::ProjecticPoint O(curve.point_pow(P, curve.q(), ak_mpzn256_size));
//std::cout << "[q]P:\n" << O << '\n';
//my::ProjecticPoint unit_point;
//std::cout << std::boolalpha << (unit_point == O) << '\n';

//std::cout << "Checking if [q+1]P==P:\n";
//ak_mpzn256 q1;
//ak_mpzn256 one = { 0x0000000000000001LL, 0x0000000000000000LL, 0x0000000000000000LL, 0x0000000000000000LL };
//ak_mpzn_add_montgomery(q1, curve.q(), one, curve.p(), curve.size());
//my::ProjecticPoint P1(curve.point_pow(P, q1, ak_mpzn256_size));
//std::cout << std::boolalpha << (P1 == P) << '\n';

//std::cout << "Checking if [q-1]P==-P:\n";
//ak_mpzn256 q2;
//ak_mpzn_sub(q2, curve.q(), one, curve.size());
//my::ProjecticPoint P2(curve.point_pow(P, q1, ak_mpzn256_size));
//my::ProjecticPoint zero_point("0", "0", "0", "0");
//my::ProjecticPoint PP2(curve.add_points(P2, P));
//std::cout << std::boolalpha << (PP2 == zero_point) << '\n';

//std::cout << "For random k1, k2 checking [k1]P + [k2]P == [k1 + k2]P:\n";
//ak_mpzn256 k1, k2, k1k2;
//ak_mpzn_set_hexstr(k1, ak_mpzn256_size, "ffa6666123232ccccccccccccdddddddddddddd777773444429");
//ak_mpzn_set_hexstr(k2, ak_mpzn256_size, "ffffffffffffffffffffffffffffffffde77ccc7630638defa");
//ak_mpzn_add_montgomery(k1k2, k1, k2, curve.p(), curve.size());
//my::ProjecticPoint P11(curve.point_pow(P, k1, ak_mpzn256_size));
//my::ProjecticPoint P12(curve.point_pow(P, k2, ak_mpzn256_size));
//my::ProjecticPoint P13(curve.point_pow(P, k1k2, ak_mpzn256_size));
//my::ProjecticPoint P11P12(curve.add_points(P11, P12));
//std::cout << std::boolalpha << (P11P12 == P13) << '\n';


//ak_random_context_destroy(&rand_generator);
return 0;
}
