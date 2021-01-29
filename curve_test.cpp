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
                "75c5b8e75d54402af9bdaa77ef9381c3783379e9454236897e22a61c12f4988d", //x2
                "4d5008aeeeddeb368ceead70cebadb054d61602140a46ea3966f2b6a2f4701de"  //x3
                );

    my::Curve curve(
                ak_mpzn256_size,
                "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffef0c5a3",     //p
                "fffffffffffffffffffffffffffffffebffece026ebc90c86e63e3dd47025758",     //q
                P,                                                                      //point
                "fffffffffffffffffffffffffffffffffffffffffffffffffffffffffef0c5a1"      //k2
                );

    ak_mpzn256 k;
    ak_mpzn_set_hexstr(k, ak_mpzn256_size, "fff87129");

    std::cout << "Set P as \n" << P << '\n';

    std::cout << "Check is it on curve: " << std::boolalpha << curve.point_is_ok(P) << '\n';

    std::cout << "\n===========TEST started===========\n";

    std::cout << "Checking if point Q=[k]P on curve: ...";
    my::ProjecticPoint Q(curve.point_pow(P, k, ak_mpzn256_size));

    #ifndef NDEBUG
    std::cout << "\nQ: \n" << Q << '\n';
    #endif

    std::cout << std::boolalpha << curve.point_is_ok(Q) << '\n';

    std::cout << "\nChecking if [q]P==0: ...";
    my::ProjecticPoint O(curve.point_pow(P, curve.q(), ak_mpzn256_size));

    #ifndef NDEBUG
    std::cout << "\n[q]P:\n" << O << '\n';
    #endif

    my::ProjecticPoint unit_point;
    bool check_1 = (unit_point == O);

    // Because of modulo we need additional check for last 3 coord-s,
    // If they are same, all is right

    if (check_1 ||
            ((ak_mpzn_cmp(O.x1(), O.x2(), ak_mpzn256_size) == 0 ) &&
             (ak_mpzn_cmp(O.x2(), O.x3(), ak_mpzn256_size) == 0)))
    {
        std::cout << "true\n";
    }
    else
    {
        std::cout << "false\n";
    }


    std::cout << "\nChecking if [q+1]P == P: ...";
    ak_mpzn256 q1;
    ak_mpzn256 one = { 0x0000000000000001LL, 0x0000000000000000LL, 0x0000000000000000LL, 0x0000000000000000LL };
    ak_mpzn_add_montgomery(q1, curve.q(), one, curve.p(), curve.size());
    my::ProjecticPoint P1(curve.point_pow(P, q1, ak_mpzn256_size));

    #ifndef NDEBUG
    std::cout << "\n[q+1]P:\n" << P1 << '\n';
    #endif

    my::ProjecticPoint P1_aff = curve.to_affine(P1);
    my::ProjecticPoint P_aff = curve.to_affine(P);
    std::cout << std::boolalpha << (P1_aff == P_aff) << '\n';

    std::cout << "\nChecking if [q-1]P == -P: ...";
    ak_mpzn256 q2;
    my::mpzn_sub_mod(q2, curve.q(), one, curve.p(), ak_mpzn256_size);
    my::ProjecticPoint P2(curve.point_pow(P, q2, ak_mpzn256_size));

    #ifndef NDEBUG
    std::cout << "\n[q-1]P:\n" << P2 << '\n';
    #endif

    my::ProjecticPoint zero_point("0", "0", "0", "0");

    my::ProjecticPoint PP2(curve.add_points(P2, P));
    my::ProjecticPoint PP2_aff = curve.to_affine(PP2);
    std::cout << std::boolalpha << (PP2_aff == zero_point) << '\n';

    std::cout << "\nFor random k1, k2 checking [k1]P + [k2]P == [k1 + k2]P: ...";
    ak_mpzn256 k1, k2, k1k2;
    ak_mpzn_set_hexstr(k1, ak_mpzn256_size, "ffa6666123232ccccccccccccdddddddddddddd777773444429");
    ak_mpzn_set_hexstr(k2, ak_mpzn256_size, "ffffffffffffffffffffffffffffffffde77ccc7630638defa");
    ak_mpzn_add_montgomery(k1k2, k1, k2, curve.p(), curve.size());
    my::ProjecticPoint P11(curve.point_pow(P, k1, ak_mpzn256_size));
    my::ProjecticPoint P12(curve.point_pow(P, k2, ak_mpzn256_size));
    my::ProjecticPoint P13(curve.point_pow(P, k1k2, ak_mpzn256_size));
    my::ProjecticPoint P11P12(curve.add_points(P11, P12));

    my::ProjecticPoint P11P12_aff = curve.to_affine(P11P12);
    my::ProjecticPoint P13_aff = curve.to_affine(P13);
    std::cout << std::boolalpha << (P11P12_aff == P13_aff) << '\n';

    return 0;
}
