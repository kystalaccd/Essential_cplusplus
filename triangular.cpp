#include <iostream>
#include <algorithm>
#include "triangular.h"

// static data member必须在程序代码文件中提供清除的定义
const int Triangular::_max_elems = 1024; //此处必须赋值，才能够算定义
vector<int> Triangular::_elems;

//memberwise initialization
Triangular::Triangular(const Triangular &rhs)
    : _length(rhs._length),
      _beg_pos(rhs._beg_pos),
      _next(rhs._next),
      _name("Triangular")
{}

//构造函数(constructor) member initialization list
Triangular::Triangular(int len, int beg_pos)
    : _name("Triangular"), _length(len > 0 ? len : 1), _beg_pos(beg_pos > 0 ? beg_pos : 1)
{
    _next = _beg_pos - 1;
    int elem_cnt = _beg_pos + _length - 1;

    if (_elems.size() < elem_cnt)
        gen_elements(elem_cnt);
}

int Triangular::elem(int pos) const
{
    return _elems[pos - 1];
}

bool Triangular::next(int &value) const
{
    if (_next < _beg_pos + _length - 1)
    {
        value = _elems[_next++];
        return true;
    }
    return false;
}

bool Triangular::is_elem(int value)
{
    if (!_elems.size() || _elems[_elems.size() - 1] < value)
        gen_elems_to_value(value);

    vector<int>::iterator found_it;
    vector<int>::iterator end_it = _elems.end();

    found_it = find(_elems.begin(), end_it, value);
    return found_it != end_it;
}

void Triangular::gen_elems_to_value(int value)
{
    int ix = _elems.size();
    if (!ix)
    {
        _elems.push_back(1);
        ix = 1;
    }
    while (_elems[ix - 1] < value && ix < _max_elems)
    {
        ++ix;
        _elems.push_back(ix * (ix + 1) / 2);
    }
    if (ix == _max_elems)
        cerr << "Triangular Sequence: oops: value too large " << value << "-- exceeds max size of" << _max_elems << endl;
}

void Triangular::gen_elements(int length)
{
    if (length < 0 || length > _max_elems)
    {
        cerr << "Triangular Sequence: oops: invalid length " << length << endl;
        return;
    }

    if (_elems.size() < length)
    {
        int ix = _elems.size() ? _elems.size() + 1 : 1;
        for (; ix <= length; ++ix)
            _elems.push_back(ix * (ix + 1) / 2);
    }
}

Triangular &Triangular::copy(const Triangular &rhs)
{
    if (this != &rhs)
    {
        _length = rhs._length;
        _beg_pos = rhs._beg_pos;
        _next = rhs._beg_pos - 1;
    }

    return *this;
}

Triangular &Triangular::operator=(const Triangular &rhs)
{
    if (this != &rhs)
    {
        _length = rhs._length;
        _beg_pos = rhs._beg_pos;
        _next = rhs._beg_pos - 1;
    }

    return *this;
}

void Triangular::display(int length, int beg_pos, ostream &os)
{
    const int line_size=10;
    gen_elements(length + beg_pos - 1);
    for (int i = beg_pos; i < length + beg_pos; ++i)
    {  
        os << _elems[i - 1] <<((i-beg_pos+1)%line_size?" ":"\n\t");
    }
    cout<<endl;
}

ostream &operator<<(ostream &os, const Triangular &rhs)
{
    os << '(' << rhs.beg_pos() << ',' << rhs.length() << ')'<<"  ";

    rhs.display(rhs.length(), rhs.beg_pos(), os);

    return os;
}

istream &operator>>(istream &is, Triangular &rhs)
{
    char ch1, ch2;
    int bp, len;
    //正常输入下：ch1=‘('; bp = beg_pos; ch2=','; len = length;
    is >> ch1 >> bp >> ch2 >> len;

    rhs.beg_pos(bp);
    rhs.length(len);
    rhs.next_reset();

    return is;
}
