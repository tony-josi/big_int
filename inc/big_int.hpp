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

#define         BI_BASE_TYPE                                uint32_t
#define         BI_DOUBLE_BASE_TYPE                         uint64_t
#define         BI_SSCANF_FORMAT_HEX                        "%8X"
#define         BI_SPRINF_FORMAT_HEX                        "%08x"
#define         BI_SPRINF_FORMAT_DEC                        "%010u"
#define         BI_SPRINF_FORMAT_HEX_LOG                    "0x %08X"
#define         BI_SPRINF_FORMAT_DEC_LOG                    "d %010u"
#define         BI_SPRINF_FORMAT_HEX_CHARS                  8
#define         BI_SPRINF_FORMAT_DEC_CHARS                  10
#define         BI_HEX_STR_TO_DATA_SIZE                     (2 * sizeof(BI_BASE_TYPE))
#define         BI_DEFAULT_EXPAND_COUNT                     (32)
#define         BI_BASE_TYPE_MAX                            (0xFFFFFFFF)
#define         BI_BASE_TYPE_TOTAL_BITS                     (32)
#define         BI_DOUBLE_BASE_TYPE_FIRST_HALF_MASK         (0xFFFFFFFF00000000)
#define         BI_DOUBLE_BASE_TYPE_TOTAL_BITS              (64)

#define         DEFAULT_MEM_ALLOC_BYTES                     (128)

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
        BI_BASE_TYPE _big_int_sub_base_type(BI_BASE_TYPE *data_ptr, int min, big_int *res_ptr) const;
        void _big_int_swap(big_int &src);
        int _compare_bi_base_type_n_top(const big_int &other) const;
        int _unsigned_multiply_bi_base_type(BI_BASE_TYPE b, big_int *res_ptr);
        int _big_int_left_shift_below_32bits(int bits);
        int _big_int_right_shift_below_32bits(int bits);
        int _big_int_remove_preceding_zeroes();
        

        public:

        big_int();
        big_int(const big_int &src);
        big_int& operator=(big_int src);
        big_int(big_int &&src);
        ~big_int();

        int             big_int_from_string(const std::string &str_num);
        std::string     big_int_to_string(bi_base base);
        int big_int_compare(const big_int &other) const;
        int big_int_unsigned_compare(const big_int &other) const;
        int big_int_unsigned_add(const big_int &b);
        int big_int_unsigned_add(const big_int &b, big_int *res);
        int big_int_signed_add(const big_int &b);
        int big_int_signed_add(const big_int &b, big_int *res);
        int big_int_set_negetive(bool set_unset);
        bool big_int_is_negetive();
        bool big_int_is_zero() const;
        int big_int_set_zero();
        int big_int_signed_sub(const big_int &b);
        int big_int_signed_sub(const big_int &b, big_int *res);
        int big_int_multiply(const big_int &b, big_int *res);
        int big_int_unsigned_multiply_base_type(const BI_BASE_TYPE &b, big_int *res);

        /* Logical shifts*/
        int big_int_left_shift_word(int shift_words);
        int big_int_left_shift_word(int shift_words, big_int *res);
        int big_int_left_shift(int bits);
        int big_int_left_shift(int bits, big_int *res);
        int big_int_right_shift_word(int shift_words);
        int big_int_right_shift_word(int shift_words, big_int *res);
        int big_int_right_shift(int bits);
        int big_int_right_shift(int bits, big_int *res);

        /* First param should be larger. */
        int big_int_unsigned_sub(const big_int &b);
        int big_int_unsigned_sub(const big_int &b, big_int *res) const;
        
        int big_int_clear();
        
        /*
        int big_int_div(const big_int b);
        int big_int_div(const big_int b, big_int *res);
        */
        

    };

}
