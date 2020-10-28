#include "my_curves.hpp"

namespace my
{

ak_mpzn256 two = { 0x0000000000000002LL, 0x0000000000000000LL, 0x0000000000000000LL, 0x0000000000000000LL }; //pow
//ak_mpzn256 lambda = { 0x0000000000000003LL, 0x0000000000000000LL, 0x0000000000000000LL, 0x0000000000000000LL };  // coefficient from roots of equation

bool operator== (ProjecticPoint& p1, ProjecticPoint& p2)
{
    if (ak_mpzn_cmp(p1.x0(), p2.x0(), ak_mpzn256_size) == 0 &&
            ak_mpzn_cmp(p1.x1(), p2.x1(), ak_mpzn256_size) == 0 &&
            ak_mpzn_cmp(p1.x2(), p2.x2(), ak_mpzn256_size) == 0 &&
            ak_mpzn_cmp(p1.x3(), p2.x3(), ak_mpzn256_size) == 0)
    { return true; }
    return false;
};

ProjecticPoint Curve::add_points(ProjecticPoint& p1, ProjecticPoint& p2)
{
    ak_mpzn256 x0, x1, x2, x3;

    ak_mpzn256 a3b1, a0b2, a1b3, a2b0, term1, term2;

    ak_mpzn_mul_montgomery(a3b1, p1.x3(), p2.x1(), p_, n_, size_);
    ak_mpzn_mul_montgomery(a0b2, p1.x0(), p2.x2(),  p_, n_, size_);
    ak_mpzn_mul_montgomery(a1b3, p1.x1(), p2.x3(),  p_, n_, size_);
    ak_mpzn_mul_montgomery(a2b0, p1.x2(), p2.x0(),  p_, n_, size_);

    ak_mpzn_mul_montgomery(term1, a3b1, a0b2,  p_, n_, size_);
    ak_mpzn_mul_montgomery(term2, a2b0, a1b3,  p_, n_, size_);
    ak_mpzn_add_montgomery(x0, term1, term2, p_, size_);

    // should i clean term1 and term2?..

    ak_mpzn_mul_montgomery(term1, a3b1, a1b3,  p_, n_, size_);
    ak_mpzn_mul_montgomery(term2, a2b0, a0b2,  p_, n_, size_);
    ak_mpzn_sub(x1, term1, term2, ak_mpzn256_size);

    ak_mpzn_mul_montgomery(term1, p1.x3(), p1.x2(), p_, n_, size_);
    ak_mpzn_mul_montgomery(term1, term1, p2.x3(), p_, n_, size_);
    ak_mpzn_mul_montgomery(term1, term1, p2.x2(), p_, n_, size_);   // a3a2b3b2

    ak_mpzn_mul_montgomery(term2, p1.x0(), p1.x1(), p_, n_, size_);
    ak_mpzn_mul_montgomery(term2, term2, p2.x0(), p_, n_, size_);
    ak_mpzn_mul_montgomery(term2, term2, p2.x1(), p_, n_, size_);
    ak_mpzn_mul_montgomery(term2, term2, k2_, p_, n_, size_);        // k^2*a0a1b0b1

    ak_mpzn_add_montgomery(x2, term1, term2, p_, size_);

    ak_mpzn_modpow_montgomery(term1, a3b1, two, p_, n_, size_);
    ak_mpzn_modpow_montgomery(term2, a2b0, two, p_, n_, size_);
    ak_mpzn_add_montgomery(x3, term1, term2, p_, size_);

    return ProjecticPoint(x0, x1, x2, x3);
};

void Curve::double_point(ProjecticPoint& p)
{
    p = this->add_points(p, p);
}

bool Curve::point_is_ok(ProjecticPoint& point)
{
    /* check:
        x0^2+x1^2 == x3^2
        k*x0^2 + x2^2 == x3^2 */

    ak_mpzn256 x02, x12, x22, x32, term1, term2;
    ak_mpzn_modpow_montgomery(x02, point.x0(), two, p_, n_, size_);
    ak_mpzn_modpow_montgomery(x12, point.x1(), two, p_, n_, size_);
    ak_mpzn_modpow_montgomery(x22, point.x2(), two, p_, n_, size_);
    ak_mpzn_modpow_montgomery(x32, point.x3(), two, p_, n_, size_);

    ak_mpzn_add_montgomery(term1, x02, x12, p_, size_);
    ak_mpzn_mul_montgomery(term2, k2_, x02, p_, n_, size_);
    ak_mpzn_add_montgomery(term2, term2, x22, p_, size_);

    return !ak_mpzn_cmp(term1, x32, size_) && !ak_mpzn_cmp(term2, x32, size_);
};

// from libakrypt, but for my:: classes
ProjecticPoint Curve::point_pow(ProjecticPoint& p, ak_uint64* k, const std::size_t& size)
{
    ak_uint64 uk = 0;
      long long int i, j;
      ProjecticPoint Q,
                     R(p); /* две точки из лесенки Монтгомери */

     /* полный цикл по всем(!) битам числа k */
      for( i = size-1; i >= 0; i-- ) {
         uk = k[i];
         for( j = 0; j < 64; j++ ) {
           if( uk&0x8000000000000000LL )
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

}
