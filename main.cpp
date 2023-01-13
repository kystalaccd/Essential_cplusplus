#include "triangular.h"
#include "triangular.cpp"

int main()
{
    Triangular tri(21,3);
    cout<<tri<<'\n';

    Triangular tri2;
    cin>>tri2;

    cout<<tri2<<endl;
    Triangular trian(20, 1);
    const Triangular::iterator beg_it = trian.begin();
    cout << *beg_it<<endl;
    
    Triangular::iterator it = trian.begin();
    Triangular::iterator end_it = trian.end();
    for (; it != end_it; ++it)
    {
        cout << *it << ' ';
    }

    return 0;
}