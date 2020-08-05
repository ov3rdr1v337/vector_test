namespace type_traits
{
    template<class T>
    struct is_const :
           false_type
    {};

    template<class T>
    struct is_const<const T> : 
           true_type
    {};

    template<class T>
    struct is_volatile : 
           false_type
    {};

    template<class T>
    struct is_volatile<volatile T> : 
           true_type
    {};

    template<class T, bool = is_void<T>::value   ||
                             is_reference<T>::value>
    struct is_trivially_copyable_helper
    {};

    template<class T>
    struct is_trivially_copyable_helper<T, true> :
           false_type
    {};   

    template<class T>
    struct is_trivially_copyable_helper<T, false> :
           bool_constant<is_scalar<T>::value || 
                         __is_trivially_copyable( T )>
    {}; 

    template<class T>
    struct is_trivially_copyable :
           is_trivially_copyable_helper<remove_cv_t<remove_all_extents_t<T>>>
    {};

    template<class T>
    struct is_trivial :
           bool_constant<is_trivially_copyable<T>::value ||
                         is_trivially_default_constructible<T>::value>
    {};

    template<class T, bool = is_void<T>::value   ||
                             is_reference<T>::value>
    struct is_standard_layout_helper
    {};

    template<class T>
    struct is_standard_layout_helper<T, true> :
           false_type
    {};   

    template<class T>
    struct is_standard_layout_helper<T, false> :
           bool_constant<is_scalar<T>::value || 
                         __is_standard_layout( T )>
    {}; 

    template<class T>
    struct is_standard_layout :
           is_standard_layout_helper<remove_cv_t<remove_all_extents_t<T>>>
    {};

    template<class T>
    struct has_unique_object_representations :
           bool_constant<__has_unique_object_representations( remove_cv_t<remove_all_extents_t<T>> )>
    {};
};