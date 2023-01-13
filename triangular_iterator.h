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

#define VERSION 1

#if VERSION==1 //实现版本1
//采用member function operator*()方式定义dereference运算符
#define __Member_operator__
//将类成员函数定义为friend
#define __Member_function_friend__
#endif

#if VERSION==2  //实现版本2
//采用non-member function operator*()方式定义dereference运算符
#define __Non_member_operator__
//直接将类定义为friend
#define __Class_friend__
#endif

class Triangular_iterator
{
#ifdef __Non_member_operator__
    friend int operator*(const Triangular_iterator &);
#endif

public:
    Triangular_iterator(int index) : _index(index - 1) {}

    int index() const { return _index; }

    inline bool operator==(const Triangular_iterator &) const;
    inline bool operator!=(const Triangular_iterator &) const;
    inline Triangular_iterator &operator++();   //后置increment
    inline Triangular_iterator operator++(int); //前置increment
    inline Triangular_iterator &operator=(const Triangular_iterator &);

#ifdef __Member_operator__
    inline int operator*() const;
#endif

#ifdef __Member_function_friend__
    //check_integrity()必须为public member function才能被声明为友元函数
    void check_integrity() const;
#endif
private:
    int _index;
#ifdef __Class_friend__
    //当Triangular_iterator class被声明为友元类时，check_integrity()可以为private member
    void check_integrity() const;
#endif
};

inline bool Triangular_iterator::operator==(const Triangular_iterator &rhs) const
{
    return _index == rhs._index;
}

inline bool Triangular_iterator::operator!=(const Triangular_iterator &rhs) const
{
    return !(*this == rhs);
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