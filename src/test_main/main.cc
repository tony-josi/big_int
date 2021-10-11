#include <iostream>

#include "../../inc/big_int.hpp"

using namespace bi;

int main(int argc, char *argv[]) {

    (void) argc;
    (void) argv;

    //std::string test_num_str = "5464611464645454000554646114646454540005546461146464545400055464611464645454000554646114646454540005";
    
    std::string test_num_str_1 = "1FFFFFFF1FFFFFFF";
    std::string test_num_str_2 = "1FFFFFFF";
    std::string test_num_str_3 = "4FFFFFFF1FFFFFFF";

    big_int test_num_1, test_num_2, test_num_3, test_num_4, test_num_5;
    test_num_1.big_int_from_string(test_num_str_1);
    std::cout<<test_num_1.big_int_to_string(bi_base::BI_HEX)<<"\n";
    test_num_2.big_int_from_string(test_num_str_2);
    std::cout<<test_num_2.big_int_to_string(bi_base::BI_HEX)<<"\n";
    //test_num_2.big_int_unsigned_add(test_num_1);
    //test_num_2.big_int_to_string(bi_base::BI_HEX);

    test_num_1.big_int_unsigned_add(test_num_1, &test_num_3);
    std::cout<<test_num_3.big_int_to_string(bi_base::BI_HEX)<<"\n";

    test_num_4.big_int_from_string(test_num_str_3);
    test_num_4.big_int_unsigned_sub(test_num_1, &test_num_5);
    std::cout<<test_num_5.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::cout<<test_num_2.big_int_to_string(bi_base::BI_HEX)<<"\n";
    std::cout<<test_num_3.big_int_to_string(bi_base::BI_HEX)<<"\n";
    test_num_3.big_int_unsigned_sub(test_num_2, &test_num_1);
    std::cout<<test_num_1.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_4 = "6feea77b";
    std::string test_num_str_5 = "121450c4d146a";
    big_int test_num_6, test_num_7, test_num_8;
    test_num_6.big_int_from_string(test_num_str_4);
    test_num_7.big_int_from_string(test_num_str_5);
    //test_num_6.big_int_unsigned_add(test_num_7);
    test_num_7.big_int_unsigned_sub(test_num_6, &test_num_8);
    std::cout<<test_num_8.big_int_to_string(bi_base::BI_HEX)<<"\n";    

    std::string test_num_str_6 = "140AF2D7E";
    std::string test_num_str_7 = "1648AD85E";
    big_int test_num_9, test_num_10;
    test_num_9.big_int_from_string(test_num_str_6);
    test_num_10.big_int_from_string(test_num_str_7);
    std::cout<<test_num_9.big_int_compare(test_num_10)<<"\n";

    std::string test_num_str_8 = "0000000000000000000000000000000000000017dbda480faccbc795d1cbfb80d095de3b79b9db52eece44baf92420a0";
    big_int test_num_11;
    test_num_11.big_int_from_string(test_num_str_8);
    std::cout<<test_num_11.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_9 = "1a25eccdc842360de2082e6156b401821552c235babb2542aea688cd388d4a96fce2c4b2c68e108eb31f89edfc747b85";
    std::string test_num_str_10 = "-1a25eccdc842360de2082e6156b401821552c235babb2542aea688cd388d4a96fce2c4b2c68e108eb31f89edfc747b85";
    big_int test_num_12, test_num_13, test_num_14;
    test_num_12.big_int_from_string(test_num_str_9);
    test_num_13.big_int_from_string(test_num_str_10);
    test_num_12.big_int_signed_add(test_num_13, &test_num_14);
    std::cout<<test_num_14.big_int_to_string(bi_base::BI_HEX)<<"\n";
    

    std::string test_num_str_11 = "21931";
    big_int test_num_15;
    test_num_15.big_int_from_string(test_num_str_11);
    test_num_15.big_int_left_shift_word(2);
    std::cout<<test_num_15.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_12 = "1a25eccdc842360de2082e6156b401821552c235babb2542aea688cd388d4a96fce2c4b2c68e108eb31f89edfc747b85";
    big_int test_num_16, test_num_17, test_num_18;
    test_num_16.big_int_from_string(test_num_str_12);
    test_num_17.big_int_from_string(test_num_str_12);
    test_num_17.big_int_signed_sub(test_num_16, &test_num_18);
    std::cout<<"OP:"<<test_num_18.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_13 = "c7b9";
    big_int test_num_19, test_num_20;
    test_num_19.big_int_from_string(test_num_str_13);
    test_num_19.big_int_unsigned_multiply_base_type(258977, &test_num_20);
    std::cout<<"OP:"<<test_num_20.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_14 = "-1f21d31c47f64d00d4bf7";
    std::string test_num_str_15 = "282016a1aada8fd2aa";
    big_int test_num_21, test_num_22, test_num_23;
    test_num_21.big_int_from_string(test_num_str_14);
    test_num_22.big_int_from_string(test_num_str_15);
    test_num_21.big_int_multiply(test_num_22, &test_num_23);
    std::cout<<test_num_23.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_16 = "f00000f33";
    std::string test_num_str_17 = "ffffffff";
    big_int test_num_24, test_num_25, test_num_26;
    test_num_24.big_int_from_string(test_num_str_16);
    test_num_25.big_int_from_string(test_num_str_17);
    BI_BASE_TYPE quo = 0;
    test_num_24.big_int_divide_once(test_num_25, quo, test_num_26);
    std::cout<<quo<<"\t"<<test_num_26.big_int_to_string(bi_base::BI_HEX)<<"\n";


    std::string test_num_str_18 = "fdbeef123beefdeaaaddee";
    std::string test_num_str_19 = "dead";
    big_int test_num_27, test_num_28, test_num_29, test_num_30;
    test_num_27.big_int_from_string(test_num_str_18);
    test_num_28.big_int_from_string(test_num_str_19);
    int div_ret_val = test_num_27.big_int_div(test_num_28, test_num_29, test_num_30);
    std::cout<<"RetCode: "<<div_ret_val<<" Quo: "<<test_num_29.big_int_to_string(bi_base::BI_HEX)<<" Rem: "<<test_num_30.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_20 = "-fdbeef123beefdeaaaddee";
    big_int test_num_31, test_num_32;
    test_num_31.big_int_from_string(test_num_str_20);
    test_num_31.big_int_power_base_type(4, test_num_32);
    std::cout<<test_num_32.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_21 = "fdbeef123beefdeaaaddee";
    std::string test_num_str_22 = "fdbe";
    std::string test_num_str_23 = "fdbeef123beefdeaaa";
    big_int test_num_33, test_num_34, test_num_35, test_num_36;
    test_num_33.big_int_from_string(test_num_str_21);
    test_num_34.big_int_from_string(test_num_str_22);
    test_num_35.big_int_from_string(test_num_str_23);
    test_num_33.big_int_fast_modular_exponentiation(test_num_34, test_num_35, test_num_36);
    std::cout<<test_num_36.big_int_to_string(bi_base::BI_HEX)<<"\n";

    big_int factorial_52, temp_copy;
    factorial_52.big_int_from_base_type(52, false);
    for (int i = 51; i >= 2; --i) {
        factorial_52.big_int_unsigned_multiply_base_type(static_cast<BI_BASE_TYPE>(i), &temp_copy);
        factorial_52 = temp_copy;
    }
    std::cout<<factorial_52.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_24 = "fdbe";
    std::string test_num_str_25 = "fdbe00";
    big_int test_num_37, test_num_38, test_gcd;
    test_num_37.big_int_from_string(test_num_str_24);
    test_num_38.big_int_from_string(test_num_str_25);
    std::cout<<test_num_37.big_int_gcd_euclidean_algorithm(test_num_38, test_gcd)<<"\n";
    std::cout<<test_gcd.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_26 = "49c0b8c154a67c39aa34b628f1cfc3551a8e6810e73bcda4c06ce6ee991c4060bdd87af34c77299fc89c";
    std::string test_num_str_27 = "-b6a7a476fc0b78bf23f5e7954a04209966b4bef8c4590859031873";
    big_int test_num_39, test_num_40, test_mod;
    test_num_39.big_int_from_string(test_num_str_26);
    test_num_40.big_int_from_string(test_num_str_27);
    test_num_39.big_int_modulus(test_num_40, test_mod);
    std::cout<<test_mod.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string test_num_str_28 = "5198ac0b";
    std::string test_num_str_29 = "ff55311b";
    big_int test_num_41, test_num_42, test_inv;
    test_num_41.big_int_from_string(test_num_str_28);
    test_num_42.big_int_from_string(test_num_str_29);
    test_num_41.big_int_modular_inverse_extended_euclidean_algorithm(test_num_42, test_inv);
    std::cout<<test_inv.big_int_to_string(bi_base::BI_HEX)<<"\n";

    return 0;

} 