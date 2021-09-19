/** 
 *  @file   big_int.hpp
 *  @brief  Main include file for the big int library
 *
 *  This file contains the source code the DS used as the big in library
 *
 *  @author         Tony Josi   https://tonyjosi97.github.io/profile/
 *  @copyright      Copyright (C) 2021 Tony Josi
 *  @bug            No known bugs.
 */

#include <stdint.h>
#include <string>

#define         BI_BASE_TYPE                uint32_t
#define         BI_DOUBLE_BASE_TYPE         uint64_t
#define         BI_BASE_MAX                 (100000000U)

#define         DEFAULT_MEM_ALLOC_BYTES     (128)

namespace bi {

    class big_int {
        private:

        BI_BASE_TYPE        *_data;
        int                 _total_data;
        int                 _top;
        bool                _neg;

        int _big_int_expand(int req);

        public:

        big_int();
        int big_int_from_string(const std::string &str_num);
        /*
        int big_int_add(const big_int b);
        int big_int_add(const big_int b, big_int *res);
        int big_int_sub(const big_int b);
        int big_int_sub(const big_int b, big_int *res);
        int big_int_mul(const big_int b);
        int big_int_mul(const big_int b, big_int *res);
        int big_int_div(const big_int b);
        int big_int_div(const big_int b, big_int *res);
        */
        ~big_int();

    };

}
