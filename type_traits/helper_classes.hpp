    namespace type_traits
    {
        template<class T, T v>
        struct integral_constant
        {
            using   value_type       = T;
            using   type             = integral_constant<value_type, value>;

            static constexpr T value = v;

            constexpr operator value_type()   const noexcept
            {
                return value;
            }

            constexpr value_type operator()() const noexcept
            {
                return value;
            }        
        };

        template<class T>
        using bool_constant = integral_constant<bool, T>

        using false_type    = bool_constant<false>;
        using true_type     = bool_constant<true>;        
    };