#ifndef __axUtils__axPrint__
#define __axUtils__axPrint__

#include <iostream>

namespace ax
{
    // Since variadic templates are recursive, must have a base case.
    void Print();
    
    template <typename T, typename ...P>
    void Print(T t, P ...p)
    {
        std::cout << t << ' ';
        {
            Print(p...);
        }
    }
    
    // Since variadic templates are recursive, must have a base case.
    void Error();
    
    template <typename T, typename ...P>
    void Error(T t, P ...p)
    {
        std::cerr << "Error : " << t << ' ';
        {
            Error(p...);
        }
    }
}

#endif /* defined(__axUtils__axPrint__) */
