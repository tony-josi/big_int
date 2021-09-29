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

#pragma once

#define         BI_BASE_TYPE                uint32_t
#define         BI_DOUBLE_BASE_TYPE         uint64_t
#define         BI_SSCANF_FORMAT_HEX        "%8X"
#define         BI_SPRINF_FORMAT_HEX        "%08x"
#define         BI_SPRINF_FORMAT_DEC        "%010u"
#define         BI_SPRINF_FORMAT_HEX_LOG    "0x %08X"
#define         BI_SPRINF_FORMAT_DEC_LOG    "d %010u"
#define         BI_SPRINF_FORMAT_HEX_CHARS  8
#define         BI_SPRINF_FORMAT_DEC_CHARS  10
#define         BI_HEX_STR_TO_DATA_SIZE     (2 * sizeof(BI_BASE_TYPE))
#define         BI_DEFAULT_EXPAND_COUNT     (32)
#define         BI_BASE_TYPE_MAX            (0xFFFFFFFF)

#define         DEFAULT_MEM_ALLOC_BYTES     (128)

namespace bi {

    enum class bi_base {
        BI_HEX,
        BI_DEC
    };

    class big_int {
        private:

        BI_BASE_TYPE        *_data;
        int                 _total_data;
        int                 _top;
        bool                _neg;

        int _big_int_expand(int req);
        BI_BASE_TYPE _sub_base_type(BI_BASE_TYPE *data_ptr, int min, big_int *res_ptr) const;
        void _swap_big_int(big_int &src);
        int _compare_bi_base_type_n_top(const big_int &other) const;
        

        public:

        big_int();
        big_int(const big_int &src);
        big_int& operator=(big_int src);
        big_int(big_int &&src);
        ~big_int();

        int             big_int_from_string(const std::string &str_num);
        std::string     big_int_to_string(bi_base base);
        int big_int_compare(const big_int &other) const;
        int big_int_unsigned_add(const big_int &b);
        int big_int_unsigned_add(const big_int &b, big_int *res);
        int big_int_signed_add(const big_int &b);
        int big_int_signed_add(const big_int &b, big_int *res);
        int big_int_set_negetive(bool set_unset);
        bool big_int_is_negetive();
        bool big_int_is_zero();
        int big_int_set_zero();
        int big_int_left_shift_word(int shift_words);

        /* First param should be larger. */
        int big_int_unsigned_sub(const big_int &b);
        int big_int_unsigned_sub(const big_int &b, bi::big_int *res) const;
        
        int big_int_clear();
        
        /*
        
        
        
        int big_int_unsigned_sub(const big_int b, big_int *res);
        int big_int_mul(const big_int b);
        int big_int_mul(const big_int b, big_int *res);
        int big_int_div(const big_int b);
        int big_int_div(const big_int b, big_int *res);
        */
        

    };

}
