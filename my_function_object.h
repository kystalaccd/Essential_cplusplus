#ifndef __MY_FUNCTION_OBJECT_H__
#define __MY_FUNCTION_OBJECT_H__


class LessThan
{
    public:
        LessThan(int val): _val(val) {};
        int comp_val() const    {return _val;}  //基值的读取
        void comp_val(int nval) {_val = nval;}  //基值的写入

        bool operator()(int value) const;

    private:
        int _val;
};


inline bool LessThan::operator()(int value) const
{
    return value<_val;
}




#endif