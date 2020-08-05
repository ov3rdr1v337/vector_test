#include "helper_classes.h"

namespace type_traits
{
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
    struct is_null_pointer :
           bool_constant<bool, is_same<remove_cv_t<T>, is_nullptr_t>::value>
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
    struct is_integral_helper<char8_t> : 
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
    struct is_integral_helper<signed short> : 
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
    struct is_integral_helper<signed int> : 
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
    struct is_integral_helper<signed long> : 
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
    struct is_integral_helper<signed long long> : 
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

    template<class T>
    struct is_array : 
           false_type 
    {};

    template<class T,
             std::size_t size>
    struct is_array<T[size]> : 
           true_type 
    {};

    template<class T>
    struct is_array<T[]> : 
           true_type 
    {}; 

#if defined COMPILER_TYPE_TRATE_INTRINSIC_ENABLED

    template<class T>
    struct is_enum : 
           bool_constant<__is_enum( T )>
    {};

    template<class T>
    struct is_union : 
           bool_constant<__is_union( T )>
    {};

    template<class T>
    struct is_class : 
           bool_constant<__is_class( T )> 
    {};

#else

    template<class T>
    struct is_enum : 
           false_type
    {};

    template<class T>
    struct is_union : 
           false_type
    {};

    template<class T>
    struct is_class : 
           false_type
    {};    

#endif

    template<class T>
    struct is_function : 
           false_type 
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... )> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const> :
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) volatile> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const volatile> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... )> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) volatile> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const volatile> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) &> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const &> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) volatile &> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const volatile &> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) &> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const &> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) volatile &> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const volatile &> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) &&> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const &&> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) volatile &&> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const volatile &&> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) &&> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const &&> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) volatile &&> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const volatile &&> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const noexcept> :
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) volatile noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const volatile noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) volatile noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const volatile noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) & noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const & noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) volatile & noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const volatile & noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) & noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const & noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) volatile & noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const volatile & noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) && noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const && noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) volatile && noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs... ) const volatile && noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) && noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const && noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) volatile && noexcept> : 
           true_type
    {};

    template<class T,
             class... TArgs>
    struct is_function<T( TArgs..., ... ) const volatile && noexcept> : 
           true_type
    {};

    template<class T>
    struct is_pointer_helper : 
           false_type 
    {};

    template<class T>
    struct is_pointer_helper<T*> : 
           true_type 
    {};

    template<class T>
    struct is_pointer : 
           is_pointer_helper<remove_cv_t<T>> 
    {};

    template<class T>
    struct is_lvalue_reference : 
           false_type
    {};

    template<class T>
    struct is_lvalue_reference<T&> : 
           true_type
    {};

    template<class T>
    struct is_rvalue_reference : 
           false_type
    {};

    template<class T>
    struct is_rvalue_reference<T&&> : 
           true_type
    {};

    template<class T>
    struct is_member_object_pointer : 
           false_type
    {};

    template<class T,
             class U>
    struct is_member_object_pointer<T U::*> : 
           bool_constant<!is_function<remove_cv_t<T>>::value>
    {};

    template<class T>
    struct is_member_function_pointer :
           false_type 
    {};

    template<class T,
             class U>
    struct is_member_function_pointer<T U::*> : 
           is_function<remove_cv_t<T>>
    {};    
};