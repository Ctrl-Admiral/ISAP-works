#ifndef MY_CURVES_HPP
#define MY_CURVES_HPP

#include <libakrypt.h>
#include <ak_mpzn.h>
#include <cstddef> //std::size_t
#include <string>

namespace my
{

void mul256(ak_uint64* res, ak_uint64* lhs, ak_uint64* rhs, ak_uint64* p);

class ProjecticPoint
{
public:
    ProjecticPoint()
    {
        ak_mpzn_set_ui(x0_, ak_mpzn256_size, 0);
        ak_mpzn_set_ui(x1_, ak_mpzn256_size, 1);
        ak_mpzn_set_ui(x2_, ak_mpzn256_size, 1);
        ak_mpzn_set_ui(x3_, ak_mpzn256_size, 1);
    }

    ProjecticPoint(const char* x0_str, const char* x1_str, const char* x2_str, const char* x3_str)
    {
        ak_mpzn256 x0, x1, x2, x3;
        ak_mpzn_set_hexstr(x0, ak_mpzn256_size, x0_str);
        ak_mpzn_set(x0_, x0, ak_mpzn256_size);
        ak_mpzn_set_hexstr(x1, ak_mpzn256_size, x1_str);
        ak_mpzn_set(x1_, x1, ak_mpzn256_size);
        ak_mpzn_set_hexstr(x2, ak_mpzn256_size, x2_str);
        ak_mpzn_set(x2_, x2, ak_mpzn256_size);
        ak_mpzn_set_hexstr(x3, ak_mpzn256_size, x3_str);
        ak_mpzn_set(x3_, x3, ak_mpzn256_size);
    }

    ProjecticPoint(ak_mpzn256 x0, ak_mpzn256 x1, ak_mpzn256 x2, ak_mpzn256 x3)
    {
        ak_mpzn_set(x0_, x0, ak_mpzn256_size);
        ak_mpzn_set(x1_, x1, ak_mpzn256_size);
        ak_mpzn_set(x2_, x2, ak_mpzn256_size);
        ak_mpzn_set(x3_, x3, ak_mpzn256_size);
    }

    const ak_uint64* x0() const {  return x0_;  };
    ak_uint64* x0() { return x0_; }
    const ak_uint64* x1() const {  return x1_;  };
    ak_uint64* x1() { return x1_; }
    const ak_uint64* x2() const {  return x2_;  };
    ak_uint64* x2() { return x2_; }
    const ak_uint64* x3() const {  return x3_;  };
    ak_uint64* x3() { return x3_; }

    friend bool operator== (ProjecticPoint& p1, ProjecticPoint& p2);
    friend std::ostream& operator<<(std::ostream& stream, ProjecticPoint& entry);

private:
    ak_mpzn256 x0_, x1_, x2_, x3_;
};

class Curve
{
public:
    Curve() = delete;

    Curve(const ak_uint64& size,
          const char* p_str, const char* q_str, ProjecticPoint point, const char* k2_str)
        :size_(size), point_(point)
    {
        ak_mpzn256 p, q, k2;
        ak_mpzn_set_hexstr(p, ak_mpzn256_size, p_str);
        ak_mpzn_set(p_, p, ak_mpzn256_size);
        ak_mpzn_set_hexstr(q, ak_mpzn256_size, q_str);
        ak_mpzn_set(q_, q, ak_mpzn256_size);
        ak_mpzn_set_hexstr(k2, ak_mpzn256_size, k2_str);
        ak_mpzn_set(k2_, k2, ak_mpzn256_size);
    }

    ak_uint64 size() const { return size_; }
    const ak_uint64* p() const { return p_; }
    ak_uint64* p() { return p_; }
    const ak_uint64* q() const { return q_; }
    ak_uint64* q() { return q_; }
    const ak_uint64* k2() const { return k2_; }
    ak_uint64* k2() { return k2_; }

    const ak_uint64* px0() const { return point_.x0(); }
    ak_uint64* px0() { return point_.x0(); }
    const ak_uint64* px1() const { return point_.x1(); }
    ak_uint64* px1() { return point_.x1(); }
    const ak_uint64* px2() const { return point_.x2(); }
    ak_uint64* px2() { return point_.x2(); }
    const ak_uint64* px3() const { return point_.x3(); }
    ak_uint64* px3() { return point_.x3(); }

    ProjecticPoint add_points(ProjecticPoint& p1, ProjecticPoint& p2);
    void double_point(ProjecticPoint& p);
    bool point_is_ok(ProjecticPoint& point);
    ProjecticPoint point_pow(ProjecticPoint& p, ak_uint64* k, const std::size_t& size);

private:
    ak_uint64 size_;    //
    ak_mpzn256 p_;      // modulo
    ak_mpzn256 q_;
    ProjecticPoint point_;
    ak_mpzn256 k2_;     // cofficient of proj curve
};

void mpzn_sub_mod(ak_uint64* res, ak_uint64* lhs, ak_uint64* rhs, ak_uint64* p, const std::size_t& size);

}

#endif // MY_CURVES_HPP
