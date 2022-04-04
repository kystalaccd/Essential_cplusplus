/*
任务：
1.0 提供Iterator（泛型指针）
1.1 泛型指针重载运算符==，!=，*，++前置及后置版本
1.2 operator* 定义为non-member funtion的版本
1.3 重载运算符operator=()

2.0 实现一个function object，less_equal

3.0 为triangular object提供重载运算符<<以及>>
3.1 为triangular object提供begin()和and()等member function
*/

#ifndef __TRIANGULAR_ITERATOR_H__
#define __TRIANGULAR_ITERATOR_H__


class Triangular_iterator
{
    friend int operator*(const Triangular_iterator&);

public:
    Triangular_iterator(int index) : _index(index - 1) {}

    int index() const {return _index;}

    bool operator==(const Triangular_iterator &) const;
    bool operator!=(const Triangular_iterator &) const;
    Triangular_iterator &operator++();   //后置increment
    Triangular_iterator operator++(int); //前置increment
    Triangular_iterator &operator=(const Triangular_iterator &);

private:
    int _index;
    void check_integrity() const;
};

inline bool Triangular_iterator::operator==(const Triangular_iterator &rhs) const
{
    return _index == rhs._index;
}

inline bool Triangular_iterator::operator!=(const Triangular_iterator &rhs) const
{
    return !(*this == rhs);
}

inline int operator*(const Triangular_iterator &rhs)
{
    rhs.check_integrity();
    return Triangular::_elems[rhs.index()];
}

inline void Triangular_iterator::check_integrity() const
{
    if (_index >= Triangular::max_elems())
        return;

    if (_index >= Triangular::elems_size())
        Triangular::gen_elements(_index + 1);
}

inline Triangular_iterator &Triangular_iterator::operator++()
{ //前置版本
    ++_index;
    check_integrity();
    return *this;
}

inline Triangular_iterator Triangular_iterator::operator++(int)
{ //后置版本
    Triangular_iterator tmp = *this;
    ++_index;
    check_integrity();
    return tmp;
}

inline Triangular_iterator &Triangular_iterator::operator=(const Triangular_iterator &rhs)
{
    if (this != &rhs)
    {
        _index = rhs._index;
        check_integrity();
    }

    return *this;
}

#endif