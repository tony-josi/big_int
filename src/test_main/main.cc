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

    std::string test_num_str_30 = "0";
    std::string test_num_str_31 = "1";
    std::string test_num_str_32 = "-849aad4047b566aac9aa";
    big_int test_num_43, test_num_44, test_num_45, test_expp;
    test_num_43.big_int_from_string(test_num_str_30);
    test_num_44.big_int_from_string(test_num_str_31);
    test_num_45.big_int_from_string(test_num_str_32);
    std::cout<<test_num_43.big_int_fast_modular_exponentiation(test_num_44, test_num_45, test_expp)<<"\n";
    std::cout<<test_expp.big_int_to_string(bi_base::BI_HEX)<<"\n";

    /* RSA algo test. */
    std::string rsa_p_str = "b172aea10439eea488da4fa39fe5c1f23c0b0943d1b6a40a23f63fc1aef58ad920e747ea1a65f4f4b742d581915833a388cece8195887872242541fe0d1c0d72f4474e61c512d84b492a3459c20f8a917986980591cab325831d2c8d9539f1bdc0649c1e5da38af207741b810ebd8fedeb999add09c5694dda31a9386dac961aa04c5c44198eaff2f440718990f24d4449f1d8ef574249977bd35323687dc7a28d41e04afcf48d26c73d7f95ca1694c58797d28234116a1798c6b005bb6a762d83a3e7dbc803b8643b98c55d984eb765791555bc1a011a8d342405bc1e2d9bcee4959f3a036d7fd19c6cda7983d5976a858875d0825c23a79406419d428e104d";
    std::string rsa_q_str = "ef09e962a1f80bb894e2da56b03d894a4fc3fbaf9ebecb465012b28ab1c8c7122a6e904f2fce8c317ebde98b78ad6c12a0eb03e6e1d6a1ab0131ff8831d53c5dae354f220e24c0a8a5d3102b2d85e4e0b0c99ff46d207dadf0680e528cdf60c00e8d734c6ef39c88ef401b4c41d53c961cb0caf57f67a8e1ec1239e051426dcbe91c252a9fb291bd15f1cf862c892149efd81076d287263116b65083772f293119ec671a40aa67e5fd7cfa27108e794fd0c041765d1fc83463fc5a426b7fecc7027c9782c77a9412f23d2dd81ea76d4a94fd051f8cfc54b9b3094e1089d1b9598791e83757316bfb119a9ea0a0c414d7b1ad8443f12e9702dbb8c54b1309df8f";
    big_int rsa_p, rsa_q, rsa_pq;
    rsa_p.big_int_from_string(rsa_p_str);
    rsa_q.big_int_from_string(rsa_q_str);
    std::cout<<"P: "<<rsa_p.big_int_to_string(bi_base::BI_HEX)<<"\n";
    std::cout<<"P: "<<rsa_q.big_int_to_string(bi_base::BI_HEX)<<"\n";
    rsa_p.big_int_multiply(rsa_q, &rsa_pq);
    std::cout<<"PQ: "<<rsa_pq.big_int_to_string(bi_base::BI_HEX)<<"\n";
    big_int rsa_p_1, rsa_q_1, rsa_p_1q_1, rsa_bi_1;
    rsa_bi_1.big_int_from_base_type(1, false);
    rsa_p.big_int_unsigned_sub(rsa_bi_1, &rsa_p_1);
    rsa_q.big_int_unsigned_sub(rsa_bi_1, &rsa_q_1);
    rsa_p_1.big_int_multiply(rsa_q_1, &rsa_p_1q_1);
    std::cout<<"P-1Q-1: "<<rsa_p_1q_1.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string rsa_pub_key_str = "10001";
    big_int rsa_pub_key, rsa_priv_key;
    rsa_pub_key.big_int_from_string(rsa_pub_key_str);
    rsa_pub_key.big_int_modular_inverse_extended_euclidean_algorithm(rsa_p_1q_1, rsa_priv_key);
    std::cout<<"PUB KEY: "<<rsa_pub_key.big_int_to_string(bi_base::BI_HEX)<<"\n";
    std::cout<<"PRIV KEY: "<<rsa_priv_key.big_int_to_string(bi_base::BI_HEX)<<"\n";

    std::string rsa_plain_str = "beefdead";
    big_int rsa_plain_num, rsa_cipher_num, rsa_decipher_num;
    rsa_plain_num.big_int_from_string(rsa_plain_str);
    rsa_plain_num.big_int_fast_modular_exponentiation(rsa_pub_key, rsa_pq, rsa_cipher_num);
    std::cout<<"PLAIN: "<<rsa_plain_num.big_int_to_string(bi_base::BI_HEX)<<"\n";
    std::cout<<"CIPHER: "<<rsa_cipher_num.big_int_to_string(bi_base::BI_HEX)<<"\n";
    rsa_cipher_num.big_int_fast_modular_exponentiation(rsa_priv_key, rsa_pq, rsa_decipher_num);
    std::cout<<"DECIPHER: "<<rsa_decipher_num.big_int_to_string(bi_base::BI_HEX)<<"\n";

    /* big_int_get_random_unsigned */ 
    big_int rng_test;
    rng_test.big_int_get_random_unsigned(50);
    std::cout<<rng_test.big_int_to_string(bi_base::BI_HEX)<<"\n";

    return 0;

} 