#include "primary_type_traits.h"

namespace type_traits
{
    template <class T>
    struct is_arithmetic : 
           bool_constant<is_integral<T>::value ||
                         is_floating_point<T>::value>
    {};

    template <class T>
    struct is_fundamental : 
           bool_constant<is_void<T>::value       ||    
                         is_arithmetic<T>::value ||
                         is_null_pointer<T>::value>
    {};

    template<class T>
    struct is_scalar : 
           bool_constant<is_enum<T>::value         ||
                         is_pointer<T>::value      ||
                         is_arithmetic<T>::value   ||
                         is_null_pointer<T>::value ||
                         is_member_pointer<T>::value > 
    {};

    template <class T>
    struct is_object : 
           bool_constant<is_array<T>::value ||
                         is_union<T>::value ||
                         is_class<T>::value ||
                         is_scalar<T>::value>
    {};   

    template<class T>
    struct is_compound : 
           bool_constant<!is_fundamental<T>::value>
    {};

    template<class T>
    struct is_reference : 
           bool_constant<is_lvalue_reference<T>::value || 
                         is_rvalue_reference<T>::value>
    {};

    template<class T>
    struct is_member_pointer : 
           bool_constant<is_member_function_pointer<T>::value || 
                         is_member_object_pointer<T>::value>
    {};    
};