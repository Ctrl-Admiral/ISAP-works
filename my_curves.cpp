#include "my_curves.hpp"
#include <iostream>
#include <cstring>

namespace my
{

void eucl_for_mpzn256(ak_uint64* res, ak_uint64* num, ak_uint64* p)
{
    auto size = ak_mpzn256_size;
    ak_mpzn256 P, Z, v, u, zero;
    ak_mpzn_set_ui(zero, size, 0);
    ak_mpzn_set_ui(v, size, 1);
    ak_mpzn_set_ui(u, size, 0);
    ak_mpzn_set(P, p, size);
    ak_mpzn_set(Z, num, size);

    while (ak_mpzn_cmp(Z, zero, size) && ak_mpzn_cmp(P, zero, size))
    {
        auto p_z_cmp = ak_mpzn_cmp(P, Z, size);
        if (p_z_cmp == 0 || p_z_cmp == 1)
        {
            mpzn_sub_mod(P, P, Z, p, size);
            mpzn_sub_mod(u, u, v, p, size);
        }
        else
        {
            mpzn_sub_mod(Z, Z, P, p, size);
            mpzn_sub_mod(v, v, u, p, size);
        }
    }
    if (ak_mpzn_cmp(P, zero, size))
        ak_mpzn_set(res, u, size);
    else
        ak_mpzn_set(res, v, size);
}

void left(ak_uint64* r, const ak_uint64* from, size_t cnt)
{
    for (size_t i = 0; i < cnt / 64; ++i)
        r[i] = 0;
    for (size_t i = cnt / 64; i < 8; ++i)
        r[i] = from[i - cnt / 64];
    cnt %= 64;
    if (cnt == 0)
        return;
    r[7] <<= cnt;
    for (int i = 6; i >= 0; --i)
    {
        r[i + 1] |= (r[i] >> (64 - cnt));
        r[i] <<= cnt;
    }
}

void rem512with256(ak_uint64 *r, ak_uint64 *u, ak_uint64 *p)
{
    const size_t size = ak_mpzn512_size;
    ak_mpzn512 shifted;
    ak_mpzn512 from;
    ak_mpzn_set(from, u, size);

    for (int i = 256; i >= 0; --i)
    {
        left(shifted, p, i);
        if (ak_mpzn_cmp(shifted, from, size) == -1)
            ak_mpzn_sub(from, from, shifted, size);
    }

    ak_mpzn_set(r, from, size);
}

void mul256(ak_uint64* res, ak_uint64* lhs, ak_uint64* rhs, ak_uint64* p)
{
    ak_mpzn512 ans;
    ak_mpzn_mul(ans, lhs, rhs, ak_mpzn256_size);
    ak_mpzn512 p_big;
    ak_mpzn_set_ui(p_big, ak_mpzn512_size, 0);
    ak_mpzn_set(p_big, p, ak_mpzn256_size);
    ak_mpzn512 ans_mod;
    ak_mpzn_set_ui(ans_mod, ak_mpzn512_size, 0);
    rem512with256(ans_mod, ans, p_big);
    ak_mpzn_set(res, ans_mod, ak_mpzn256_size);
}

void mpzn_sub_mod(ak_uint64* res, ak_uint64* lhs, ak_uint64* rhs, ak_uint64* p, const std::size_t& size)
{
    if (ak_mpzn_cmp(lhs, rhs, size) == 1)
    {
        ak_mpzn_sub(res, lhs, rhs, size);
    }
    else
    {
        ak_mpzn256 term;
        ak_mpzn_sub(term, rhs, lhs, size);
        ak_mpzn256 p_1;
        ak_mpzn256 one;
        ak_mpzn_set(p_1, p, ak_mpzn256_size);
        ak_mpzn_set_ui(one, ak_mpzn256_size, 1);
        ak_mpzn_sub(p_1, p_1, one, ak_mpzn256_size);
        mul256(res, term, p_1, p);
    }
    ak_mpzn_rem(res, res, p, size);
}

bool operator== (ProjecticPoint& p1, ProjecticPoint& p2)
{
    if (ak_mpzn_cmp(p1.x0(), p2.x0(), ak_mpzn256_size) == 0 &&
        ak_mpzn_cmp(p1.x1(), p2.x1(), ak_mpzn256_size) == 0 &&
        ak_mpzn_cmp(p1.x2(), p2.x2(), ak_mpzn256_size) == 0 &&
        ak_mpzn_cmp(p1.x3(), p2.x3(), ak_mpzn256_size) == 0)
    {
        return true;
    }
    return false;
};

std::ostream& operator<<(std::ostream& stream, ProjecticPoint& p)
{
    std::cout << "x0: " << ak_mpzn_to_hexstr(p.x0(), ak_mpzn256_size) << '\n'
              << "x1: " << ak_mpzn_to_hexstr(p.x1(), ak_mpzn256_size) << '\n'
              << "x2: " << ak_mpzn_to_hexstr(p.x2(), ak_mpzn256_size) << '\n'
              << "x3: " << ak_mpzn_to_hexstr(p.x3(), ak_mpzn256_size);
    return stream;
};

ProjecticPoint Curve::add_points(ProjecticPoint& p1, ProjecticPoint& p2)
{
    ak_mpzn256 x0, x1, x2, x3;

    ak_mpzn256 a3b1, a0b2, a1b3, a2b0, term1, term2, term3, term4, term5, term6, term7;

    mul256(a3b1, p1.x3(), p2.x1(), p_);
    mul256(a0b2, p1.x0(), p2.x2(),  p_);
    mul256(a1b3, p1.x1(), p2.x3(),  p_);
    mul256(a2b0, p1.x2(), p2.x0(),  p_);

    mul256(term1, a3b1, a0b2,  p_);
    mul256(term2, a2b0, a1b3,  p_);
    ak_mpzn_add_montgomery(x0, term1, term2, p_, size_);           //x0=a3b1*a0b2 + a2b0*a1b3

    //should I clean term1 and term2?..

    mul256(term1, a3b1, a1b3,  p_);
    mul256(term2, a2b0, a0b2,  p_);
    mpzn_sub_mod(x1, term1, term2, p_, ak_mpzn256_size);            //x1=a3b1*a1b3-a2b0*a0b2

    mul256(term1, p1.x3(), p1.x2(), p_);
    mul256(term2, term1, p2.x3(), p_);
    mul256(term3, term2, p2.x2(), p_);   // a3a2b3b2

    mul256(term4, p1.x0(), p1.x1(), p_);
    mul256(term5, term4, p2.x0(), p_);
    mul256(term6, term5, p2.x1(), p_);
    mul256(term7, term6, k2_, p_);       // k^2*a0a1b0b1

    mpzn_sub_mod(x2, term3, term7, p_, size_);                      //x2 = a3a2*b3b2 - k^2*a0a1*b0b1

    mul256(term1, a3b1, a3b1, p_);
    mul256(term2, a2b0, a2b0, p_);
    ak_mpzn_add_montgomery(x3, term1, term2, p_, size_);            //x3 = (a3b1)^2 + (a2b0)^2

    return ProjecticPoint(x0, x1, x2, x3);
};

void Curve::double_point(ProjecticPoint& p)
{
    ak_mpzn256 _0, _1, _2, _3;
    ak_mpzn256 a1a3, a2a0, a2a3, a1a2;
    ak_mpzn256 a1a3_2, a2a3_2, a1a2_2;
    ak_mpzn256 two;
    ak_mpzn_set_ui(two, ak_mpzn256_size, 2);
    ak_mpzn256 term1, term4;

    mul256(a1a3, p.x1(), p.x3(), p_);
    mul256(a2a0, p.x2(), p.x0(), p_);
    mul256(a2a3, p.x2(), p.x3(), p_);
    mul256(a1a2, p.x1(), p.x2(), p_);

    mul256(term1, a1a3, a2a0, p_);
    mul256(_0, two, term1, p_);

    mul256(a1a3_2, a1a3, a1a3, p_);
    mul256(a2a3_2, a2a3, a2a3, p_);
    mul256(a1a2_2, a1a2, a1a2, p_);
    mpzn_sub_mod(term4, a1a3_2, a2a3_2, p_, size_);
    ak_mpzn_add_montgomery(_1, term4, a1a2_2, p_, size_);

    mpzn_sub_mod(term1, a2a3_2, a1a3_2, p_, size_);
    ak_mpzn_add_montgomery(_2, term1, a1a2_2, p_, size_);

    ak_mpzn_add_montgomery(term1, a2a3_2, a1a3_2, p_, size_);
    mpzn_sub_mod(_3, term1, a1a2_2, p_, size_);

    ak_mpzn_set(p.x0(), _0, size_);
    ak_mpzn_set(p.x1(), _1, size_);
    ak_mpzn_set(p.x2(), _2, size_);
    ak_mpzn_set(p.x3(), _3, size_);
    //p = this->add_points(p, p);
}

bool Curve::point_is_ok(ProjecticPoint& point)
{
    /* check:
        x0^2+x1^2 == x3^2
        k2*x0^2 + x2^2 == x3^2 */

    ak_mpzn256 x02, x12, x22, x32, term1, term2, term3;

    mul256(x02, point.x0(), point.x0(), p_);
    mul256(x12, point.x1(), point.x1(), p_);
    mul256(x22, point.x2(), point.x2(), p_);
    mul256(x32, point.x3(), point.x3(), p_);

    ak_mpzn_add_montgomery(term1, x02, x12, p_, size_);
    mul256(term2, k2_, x02, p_);
    ak_mpzn_add_montgomery(term3, term2, x22, p_, size_);

    return (!ak_mpzn_cmp(term1, x32, size_)) && (!ak_mpzn_cmp(term3, x32, size_));
};

// from libakrypt, but for my:: classes
ProjecticPoint Curve::point_pow(ProjecticPoint& p, ak_uint64* k, const std::size_t& size)
{
    ak_uint64 uk = 0;
    long long int i, j;
    ProjecticPoint Q, R(p); /* две точки из лесенки Монтгомери */
     /* полный цикл по всем(!) битам числа k */
    for (i = size-1; i >= 0; i--)
    {
        uk = k[i];
        for (j = 0; j < 64; j++)
        {
            if (uk&0x8000000000000000LL)
            {
                Q = this->add_points(Q, R);
                this->double_point(R);
            }
            else
            {
                R = this->add_points(Q, R);
                this->double_point(Q);
            }
            uk <<= 1;
         }
    }

    return Q;
};

ProjecticPoint Curve::to_affine(ProjecticPoint& p)
{
    ak_mpzn256 x, y, z, lambda, _1;
    ak_mpzn_set_ui(_1, size_, 1);
    mpzn_sub_mod(lambda, _1, k2_, p_, size_);

    ak_mpzn256 x2_x3;
    mpzn_sub_mod(x2_x3, p.x2(), p.x3(), p_, size_);
    mul256(x, x2_x3, lambda, p_);

    ak_mpzn256 x0labmda;
    mul256(x0labmda, p.x0(), lambda, p_);
    mul256(y, x0labmda, k2_, p_);

    ak_mpzn256 x1k2, x3lambda;
    mul256(x1k2, p.x1(), k2_, p_);
    mul256(x3lambda, p.x3(), lambda, p_);
    mpzn_sub_mod(z, x1k2, p.x2(), p_, size_);
    ak_mpzn_add_montgomery(z, z, x3lambda, p_, size_);

    ak_mpzn256 k;
    eucl_for_mpzn256(k, z, p_);
    mul256(x, x, k, p_);
    mul256(y, y, k, p_);
    mul256(z, z, k, p_);

    ak_mpzn256 _0;
    ak_mpzn_set_ui(_0, size_, 0);
    return ProjecticPoint(x, y, z, _0);
};

}
