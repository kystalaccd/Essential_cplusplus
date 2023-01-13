#ifndef __TRIANGULAR_H__
#define __TRIANGULAR_H__

#include <vector>
#include <iostream>
#include <string>
#include "triangular_iterator.h"

using namespace std;

class Triangular
{
#ifdef __Non_member_operator__
    friend int operator*(const Triangular_iterator &);
#endif

#ifdef __Member_operator__
    friend int Triangular_iterator::operator*() const;
#endif

#ifdef __Member_function_friend__
    friend void Triangular_iterator::check_integrity() const;   //此处需要加上const关键字, 而且check_integrity必须为member function才能被声明为友元函数
#endif

#ifdef __Class_friend__
    friend class Triangular_iterator;
#endif

public:
    typedef Triangular_iterator iterator;   //Nested Type
    Triangular_iterator begin() const { return Triangular_iterator(_beg_pos); }
    Triangular_iterator end() const { return Triangular_iterator(_beg_pos + _length); }

    // constructor,构造函数
    Triangular(int len = 1, int beg_pos = 1); // default parameter values,默认参数值
    Triangular(const Triangular &rhs);
    // const member function
    int length() const { return _length; } // inline member function
    void length(int len) { _length = (len > 0) ? len : 1; }

    int beg_pos() const { return _beg_pos; } // inline member function
    void beg_pos(int beg_pos) { _beg_pos = beg_pos > 0 ? beg_pos : 1; }

    int elem(int pos) const;
    bool next(int &val) const;
    void next_reset() const { _next = _beg_pos - 1; } // inline member function

    // non-const member function && static member function
    static bool is_elem(int value);
    static void gen_elements(int length);
    static void gen_elems_to_value(int value);
    static void display(int length, int beg_pos, ostream &os = cout);

    Triangular &copy(const Triangular &);
    Triangular &operator=(const Triangular &);

private:
    string _name;
    int _length, _beg_pos;
    mutable int _next; // mutable data member（可变的数据成员）
    static const int _max_elems;
    static vector<int> _elems;
};

ostream &operator<<(ostream &os, const Triangular &rhs);
istream &operator>>(istream &is, Triangular &rhs);

//解决头文件相互依赖问题
#ifdef __Non_member_operator__
inline int operator*(const Triangular_iterator &rhs)
{
    rhs.check_integrity();
    return Triangular::_elems[rhs.index()];
}
#endif

inline void Triangular_iterator::check_integrity() const
{
    if (_index >= Triangular::_max_elems)
        return;

    if (_index >= Triangular::_elems.size())
        Triangular::gen_elements(_index + 1);
}

#ifdef __Member_operator__
inline int Triangular_iterator::operator*() const
{
    check_integrity();
    return Triangular::_elems[_index];
}
#endif

#endif