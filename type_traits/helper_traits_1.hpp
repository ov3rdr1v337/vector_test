#include <functional>

namespace helper_traits
{
    template<class T, T v>
    struct integral_constant
    {
        static constexpr T value = v;

        using   value_type  = T;
        using   type        = integral_constant<value_type, value>;
    };

    using false_type    = integral_constant<bool, false>;
    using true_type     = integral_constant<bool, true>;

    template<class TArg_1, class TArg_2>
    struct is_same : false_type
    {

    };

    template<class TArg_1>
    struct is_same<TArg_1, TArg_1> : true_type
    {

    };

    template<bool B,
             class T,
             class F>
    struct conditional {};

    template<class T,
             class F>
    struct conditional<true, T, F>
    {
        using type = T;
    };

    template<class T, 
             class F>
    struct conditional<false, T, F>
    {
        using type = F;
    };

    template<bool B,
             class T,
             class F>
    using conditional_t = typename conditional<B, T, F>::type;

    template<class T>
    struct is_cv_qualified : false_type {};

    template<class T>
    struct is_cv_qualified<T volatile> : true_type {};

    template<class T>
    struct is_cv_qualified<T const> : true_type {};

    template<class T>
    struct is_cv_qualified<T const volatile> : true_type {};

    template<class T>
    struct is_reference : false_type {};

    template<class T>
    struct is_reference<T &> : true_type {};

    template<class T>
    struct is_reference<T &&> : true_type {};

    template<class T>
    struct remove_reference
    {
        using type = T;
    };

    template<class T>
    struct remove_reference<T&>
    {
        using type = T;
    };

    template<class T>
    struct remove_reference<T&&>
    {
        using type = T;
    };

    template<class T>
    using remove_reference_t = typename remove_reference<T>::type;

    template<bool, class T>
    struct add_rvalue_reference_impl
    {

    };

    template<class T>
    struct add_rvalue_reference_impl<true, T>
    {
        using type = T;
    };

    template<class T>
    struct add_rvalue_reference_impl<false, T>
    {
        using type = T && ;
    };

    template<class T>
    struct add_rvalue_reference :
           add_rvalue_reference_impl<is_cv_qualified<T>::value || is_reference<T>::value, T>
    {

    };

    template<class T>
    using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

    template<class T>
    add_rvalue_reference_t<T> declval() noexcept;

    template<class TArg>
    struct is_array : false_type {};

    template<class TArg,
             std::size_t size>
    struct is_array<TArg[size]> : true_type {};

    template<class TArg>
    struct is_array<TArg[]> : true_type {}; 

    template<class TArg>
    struct remove_extent 
    {
        using type = TArg;
    };

    template<class TArg,
             std::size_t size>
    struct remove_extent<TArg[size]>
    {
        using type = TArg;
    };

    template<class TArg>
    struct remove_extent<TArg[]>
    {
        using type = TArg;
    };

    template<class TArg>
    using remove_extent_t = typename remove_extent<TArg>::type;        

    template<class TFunc>
    struct is_cv_or_ref_qualified_function : is_function<TFunc> {};

    template<class TFunc, class... TArgs>
    struct is_cv_or_ref_qualified_function<TFunc(TArgs...)> : false_type {};

    template<class TFunc, class... TArgs>
    struct is_cv_or_ref_qualified_function<TFunc(TArgs..., ...)> : false_type {};

    template<class TArg>
    struct add_pointer
    {
        using type = conditional_t<is_reference<TArg>::value,
                                   remove_reference_t<TArg>*,
                                   conditional_t<is_cv_or_ref_qualified_function<TArg>::value,
                                                 TArg,
                                                 TArg*>>;
    };

    template<class TArg>
    using add_pointer_t = typename add_pointer<TArg>::type;

    template<class T>
    struct remove_const
    {
        using type = T;
    };

    template<class T>
    struct remove_const<T const>
    {
        using type = T;
    };

    template<class T>
    using remove_const_t = typename remove_const<T>::type;

    template<class T>
    struct remove_volatile
    {
        using type = T;
    };

    template<class T>
    struct remove_volatile<T volatile>
    {
        using type = T;
    };

    template<class T>
    using remove_volatile_t = typename remove_volatile<T>::type;

    template<class T>
    struct remove_cv
    {
        using type = remove_const_t<remove_volatile_t<T>>;
    };

    template<class T>
    using remove_cv_t = typename remove_cv<T>::type;

    template<class T>
    struct remove_cvref
    {
        using type = remove_cv_t<remove_reference_t<T>>;
    };

    template<class T>
    using remove_cvref_t = typename remove_cvref<T>::type;

    template<class TArg>
    struct is_pointer_helper : false_type {};

    template<class TArg>
    struct is_pointer_helper<TArg*> : true_type {};

    template<class TArg>
    struct is_pointer : is_pointer_helper<remove_cv_t<TArg>> {};     

    template<class TFunc>
    struct is_member_function_pointer : false_type {};

    template<class TRet,
             class TFunc>
    struct is_member_function_pointer<TRet TFunc::*> : is_function<remove_cv_t<TRet>>
    {
    };

    template<class TFunc>
    struct is_member_object_pointer : false_type {};

    template<class T>
    struct negation
    {
        static constexpr typename T::value_type value = !T::value;

        using   value_type  = typename T::value_type;
        using   type        = integral_constant<value_type, value>;
    };

    template<class TRet,
             class TFunc>
    struct is_member_object_pointer<TRet TFunc::*> : negation<is_function<remove_cv_t<TRet>>>
    {
    };

    template<class TArg>
    struct decay
    {
    private:
        using arg  = remove_reference_t<TArg>;

    public:
        using type = conditional_t<is_array<arg>::value,
                                   remove_extent_t<arg>*,
                                   conditional_t<is_function<arg>::value, 
                                                 add_pointer_t<arg>,
                                                 remove_cv_t<arg>>>;            
    };

    template<class TArg>
    using decay_t = typename decay<TArg>::type;

    
#if ( defined( _MSC_VER ) && defined( _MSC_FULL_VER ) && ( _MSC_FULL_VER >=140050215 ) )
    template<class TArg>
    struct is_union : integral_constant<bool, __is_union( TArg )> {};

    template<class TArg>
    struct is_pod : integral_constant<bool, __is_pod( TArg ) && __has_trivial_constructor( TArg )> {};

    template<class TArg>
    struct is_empty : integral_constant<bool, __is_empty( TArg )> {};

    template<class TArg, class... TArgs>
    struct is_constructible : integral_constant<bool, __is_constructible( TArg, TArgs... )> {};

    template<class TArg, class... TArgs>
    struct is_trivially_constructible : integral_constant<bool, __is_trivially_constructible( TArg, TArgs... )> {};

    template<class TArg, class... TArgs>
    struct is_nothrow_constructible :
        integral_constant<bool,    is_constructible<TArg, TArgs...> 
                                && noexcept( TArg( declval<TArgs>()... ) )> {};

    template<class T, class TArg>
    struct is_nothrow_constructible<T, TArg> :
        integral_constant<bool,    is_constructible<T, TArg>::value 
                                && noexcept( static_cast<T>( declval<TArg>() ) )> {};

    template<class TArg>
    struct is_default_constructible : is_constructible<TArg> {};

    template<class TArg>
    struct is_trivially_default_constructible : is_trivially_constructible<TArg> {};

    template<class TArg>
    struct is_nothrow_default_constructible : is_nothrow_constructible<TArg> {};

    template<class TArg>
    struct is_copy_constructible : is_constructible<TArg, const TArg&> {};

    template<class TArg>
    struct is_trivially_copy_constructible : is_trivially_constructible<TArg, const TArg&> {};

    template<class TArg>
    struct is_nothrow_copy_constructible : is_nothrow_constructible<TArg, const TArg&> {};

    template<class TArg>
    struct is_move_constructible : is_constructible<TArg, const TArg&&> {};

    template<class TArg>
    struct is_trivially_move_constructible : is_trivially_constructible<TArg, const TArg&&> {};

    template<class TArg>
    struct is_nothrow_move_constructible : is_nothrow_constructible<TArg, const TArg&&> {};

    template<class TArg>
    struct is_destructible : integral_constant<bool, __is_destructible( TArg )> {};

    template<class TArg>
    struct is_trivially_destructible : integral_constant<bool, __is_trivially_destructible( TArg )> {};

    

    template<class TArg>
    struct has_virtual_destructor : integral_constant<bool, __has_virtual_destructor( TArg )> {};

    template<class TArg>
    struct is_abstract : integral_constant<bool, __is_abstract( TArg )> {};

    template<class TArg, class... TArgs>
    struct is_base_of : integral_constant<bool, __is_base_of( TArg, TArgs... )> {}; // ???

    // ???
    template<class TArg>
    struct is_class : integral_constant<bool, __is_class( TArg )> {};

#    define COMPILER_INTRINSIC_IS_CONVERTIBLE( T, U ) __is_convertible_to( T, U )
#    define COMPILER_INTRINSIC_IS_ENUM( T ) __is_enum( T )
#    if defined( _MSC_VER ) && ( _MSC_VER >= 1800 )
#       define COMPILER_INTRINSIC_HAS_TRIVIAL_MOVE_CONSTRUCTOR( T ) __is_trivially_constructible( T, T&& )
#       define COMPILER_INTRINSIC_HAS_TRIVIAL_MOVE_ASSIGN( T ) __is_trivially_assignable( T, T&& )
#    elif defined( _MSC_VER ) && ( _MSC_VER >= 1700 )
#         define COMPILER_INTRINSIC_HAS_TRIVIAL_MOVE_CONSTRUCTOR( T ) __has_trivial_move_constructor( T )
#         define COMPILER_INTRINSIC_HAS_TRIVIAL_MOVE_ASSIGN( T ) __has_trivial_move_assign( T )
#    endif
#    define COMPILER_INTRINSIC_IS_POLYMORPHIC( T ) __is_polymorphic( T )
#if _MSC_FULL_VER >= 180020827
#    define COMPILER_INTRINSIC_IS_NOTHROW_MOVE_ASSIGN( T ) __is_nothrow_assignable( T&, T&& )
#    define COMPILER_INTRINSIC_IS_NOTHROW_MOVE_CONSTRUCT( T ) __is_nothrow_constructible( T, T&& )
#endif
#if _MSC_VER >= 1800
#    define COMPILER_INTRINSIC_IS_FINAL( T ) __is_final( T )
#endif
#    define COMPILER_INTRINSIC_HAS_TYPE_TRAITS_INTRINSICS
#endif


    template<class TArg>
    struct is_reference_wrapper : false_type {};

    template<class TArgWrap>
    struct is_reference_wrapper<std::reference_wrapper<TArgWrap>> : true_type {};

    template<bool, bool,
             class TFunc,
             class... TArgs>
    struct invoke_result_impl
    {

    };

    template<class TFunc, class TPtr, class... TArgs>
    struct invoke_result_member_function_ptr
    {
        using type = decltype( ( ( *declval<TPtr>() ).*declval<TFunc>() )( declval<TArgs>()... ) );
    };

    template<class TFunc, class TPtr, class... TArgs>
    struct invoke_result_member_function_ref
    {
        using type = decltype( ( declval<TPtr>().*std::declval<TFunc>() )( declval<TArgs>()... ) );
    };

    template<class TFunc, class TPtr, class... TArgs>
    struct invoke_result_member_function_ref_wrapper
    {
        using type = decltype( ( declval<decltype( declval<TPtr>().get() )>().*declval<TFunc>() )( declval<TArgs>()... ) );
    };   

    template<class TFunc,
             class TPtr,
             class... TArgs>
    struct invoke_result_member_function
    {

    };

    template<class TRet,
             class TClass,
             class TPtr,
             class... TArgs>
    struct invoke_result_member_function<TRet TClass::*, TPtr, TArgs...>
    {
        using classType  = decay_t<TPtr>;
        using memPtrType = TRet TClass::*;

        using type       = typename conditional_t<is_base_of<TClass, classType>::value,
                                                  invoke_result_member_function_ref<memPtrType, TPtr, TArgs...>,
                                                  conditional_t<is_reference_wrapper<classType>::value,
                                                                invoke_result_member_function_ref_wrapper<memPtrType, TPtr, TArgs...>,
                                                                invoke_result_member_function_ptr<memPtrType, TPtr, TArgs...>>
                                                 >::type;
    };   

    template<class    TFunc,
             class    TPtr,
             class... TArgs>
    struct invoke_result_impl           <true, false, TFunc, TPtr, TArgs...> :
           invoke_result_member_function<decay_t<TFunc>,
                                         TPtr, 
                                         TArgs...>
    {

    };

    template<class TFunc, class TPtr, class... TArgs>
    struct invoke_result_member_object_ptr
    {
        using type = decltype( ( ( *declval<TPtr>() ).*declval<TFunc>() ) );
    };

    template<class TFunc, class TPtr, class... TArgs>
    struct invoke_result_member_object_ref
    {
        using type = decltype( ( declval<TPtr>().*std::declval<TFunc>() ) );
    };

    template<class TFunc, class TPtr, class... TArgs>
    struct invoke_result_member_object_ref_wrapper
    {
        using type = decltype( ( declval<decltype( declval<TPtr>().get() )>().*declval<TFunc>() ) );
    };   

    template<class TFunc,
             class TPtr>
    struct invoke_result_member_object
    {

    };

    template<class TRet,
             class TClass,
             class TPtr>
    struct invoke_result_member_object<TRet TClass::*, TPtr>
    {
        using classType  = decay_t<TPtr>;
        using memPtrType = TRet TClass::*;

        using type       = typename conditional_t<is_base_of<TClass, classType>::value,
                                                  invoke_result_member_object_ref<memPtrType, TPtr>,
                                                  conditional_t<is_reference_wrapper<classType>::value,
                                                                invoke_result_member_object_ref_wrapper<memPtrType, TPtr>,
                                                                invoke_result_member_object_ptr<memPtrType, TPtr>>
                                                 >::type;
    };   

    template<class TFunc,
             class TPtr,
             class... TArgs>
    struct invoke_result_impl<false, true, TFunc, TPtr, TArgs...> :
           invoke_result_member_object<decay_t<TFunc>,
                                       TPtr>          
    {
  
    };

    template<class TFunc,
             class... TArgs>
    struct invoke_result_impl<false, false, TFunc, TArgs...>
    {
        using type = decltype( declval<TFunc>()( declval<TArgs>()... ) );
    };

    template<class TFunc,
             class... TArgs>
    struct invoke_result : invoke_result_impl<is_member_function_pointer<remove_reference_t<TFunc>>::value,
                                              is_member_object_pointer  <remove_reference_t<TFunc>>::value,
                                              TFunc,
                                              TArgs...>
    {

    };

    template<class TFunc, class... TArgs>
    using invoke_result_t = typename invoke_result<TFunc, TArgs...>::type;

};