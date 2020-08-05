
#include <iostream> // std::cout
#include <type_traits> // std::is_same
//include <boost/type_traits/is_destructible.hpp> 

namespace XXX
{
    template<class T>
    struct is_const : false_type
    {};

    template<class T>
    struct is_const<const T> : true_type
    {};

    template<class T>
    struct is_volatile : false_type
    {};

    template<class T>
    struct is_volatile<volatile T> : true_type
    {};   

    template<class T>
    struct is_trivial : integral_constant<bool,
                                          is_trivially_copyable<T>::value,
                                          is_trivially_default_constructible<T>::value>
    {};

    template<class T>
    using bool_constant = integral_constant<bool, T>

    template<class T>
    struct is_member_pointer : 
           type_or<is_member_object_pointer<T> ||  is_member_function_pointer<T>>
    {};

    template<class T>
    struct is_null_pointer : 
           integral_constant<bool, is_same<T, is_nullptr_t>::value>
    {};   

    template<class T>
    struct is_enum : integral_constant<bool, __is_enum(T)>
    {};

    template<class T>
    struct is_union : integral_constant<bool, __is_union(T)>
    {};

    template<class T>
    struct is_void_helper : 
           false_type
    {};

    template<>
    struct is_void_helper<void> : 
           true_type
    {};

    template<class T>
    struct is_void : 
           is_void_helper<remove_cv_t<T>>    
    {};
    
    template<class T>
    struct is_array_of_unknown_bounds : 
           false_type
    {};

    template<class T>
    struct is_array_of_unknown_bounds<T[]> : 
           true_type
    {};    

    template<class T>
    struct is_integral_helper : 
           false_type
    {};

    template<>
    struct is_integral_helper<bool> : 
           true_type
    {};

    template<>
    struct is_integral_helper<char> : 
           true_type
    {};

    template<>
    struct is_integral_helper<signed char> : 
           true_type
    {};

    template<>
    struct is_integral_helper<unsigned char> : 
           true_type
    {};

    template<>
    struct is_integral_helper<wchar_t> : 
           true_type
    {};

    template<>
    struct is_integral_helper<char16_t> : 
           true_type
    {};

    template<>
    struct is_integral_helper<char32_t> : 
           true_type
    {};

    template<>
    struct is_integral_helper<short> : 
           true_type
    {};

    template<>
    struct is_integral_helper<unsigned short> : 
           true_type
    {};

    template<>
    struct is_integral_helper<int> : 
           true_type
    {};

    template<>
    struct is_integral_helper<unsigned int> : 
           true_type
    {};

    template<>
    struct is_integral_helper<long> : 
           true_type
    {};

    template<>
    struct is_integral_helper<unsigned long> : 
           true_type
    {};

    template<>
    struct is_integral_helper<long long> : 
           true_type
    {};

    template<>
    struct is_integral_helper<unsigned long long> : 
           true_type
    {};

    template<class T>
    struct is_integral : 
           is_integral_helper<remove_cv_t<T>>
    {};

    template<class T>
    struct is_floating_point_helper : 
           false_type
    {};

    template<>
    struct is_floating_point_helper<float> : 
           true_type
    {};

    template<>
    struct is_floating_point_helper<double> : 
           true_type
    {};

    template<>
    struct is_floating_point_helper<long double> : 
           true_type
    {};

    template<class T>
    struct is_floating_point : 
           is_floating_point_helper<remove_cv_t<T>>
    {};

    template<class... TArgs>
    struct type_or {};

    template <class T>
    struct type_or<T> : 
           T 
    {};

    template <class TA, class TB>
    struct type_or<TA, TB> : 
           conditional_t<TA::value,
                         TA,
                         TB>
    {};

    template <class TA, class TB, class TC, class... TArgs>
    struct type_or<TA, TB, TC, TArgs...> : 
           conditional_t<TA::value,
                         TA,
                         type_or<TB, TC, TArgs...>> 
    {};

    template<class... TArgs>
    struct type_and {};

    template <class T>
    struct type_and<T> : 
           T 
    {};

    template <class TA, class TB>
    struct type_and<TA, TB> : 
           conditional_t<TA::value,
           TB,
           TA>
    {};

    template <class TA, class TB, class TC, class... TArgs>
    struct type_and<TA, TB, TC, TArgs...> : 
           conditional_t<TA::value,
                         type_and<TB, TC, TArgs...>,
                         TA> 
    {};

    template <class T>
    struct is_arithmetic : integral_constant<bool, 
                                             is_integral<T> || is_floating_point<T>>
    {};

    template< class T >
    struct is_scalar : integral_constant<bool,
                                         is_arithmetic<T>::value     ||
                                         is_enum<T>::value           ||
                                         is_pointer<T>::value        ||
                                         is_member_pointer<T>::value ||
                                         is_null_pointer<T>::value> 
    {};

    template <class T>
    struct is_fundamental : integral_constant<bool, 
                                              is_arithmetic<T> ||
                                              is_void<T>       ||
                                              is_null_pointer<T>>
    {};   

    template <class T>
    struct is_object : integral_constant<bool, 
                                              is_scalar<T> ||
                                              is_array<T>  ||
                                              is_union<T>  ||
                                              is_class<T>>
    {};   

    template<class T>
    struct is_compound : 
           integral_constant<bool, !is_fundamental<T>::value>
    {};

namespace
{
    template<class, class = void>
    struct is_can_use_destructor : 
           false_type
    {
        
    };
    
    template<class T>
    struct is_can_use_destructor<T, void_t<decltype( declval<T&>().~T() )>> : 
           true_type
    {
        
    };    
};
    
template<class... TArgs>
using void_t = void;

template<class T,
         bool = type_or<is_void<T>,
                        is_function<T>,
                        is_array_of_unknown_bounds<T>>::value,
         bool = type_or<is_scalar<T>,
                        is_reference<T>>::value>
struct is_destructible_helper
{

};

template<class T>
struct is_destructible_helper<T, false, false>:
       is_can_use_destructor<remove_all_extents_t<T>> // ???
{

};

template<class T>
struct is_destructible_helper<T, false, true>:
       true_type
{

};

template<class T>
struct is_destructible_helper<T, true, false>:
       false_type
{

};

template<class T>
struct is_destructible : is_destructible_helper<T>
{

};
}

class A
{
    int aA;
};

class B : public A 
{
~B(){};
public:
    int bA;
};

int main()
{
    bool podB = XXX::is_destructible_helper<B, false, false>::value;
    //ol podB = XXX::is_can_use_destructor<B>::value;
    std::cout << podB;    
    
    return 0;
}