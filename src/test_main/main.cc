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
    /*
    RSA - 4096 bit primes - RSA-8192 bits Example
    ---------------------------------------------

    P: b0d8cf6d1bd3d6abfbafa0f0566539f9a2e606196d50d9567ffacb229724d35291953690efcd48f8ed9f793cf54095d639daf29e6279f6527e57454ccfd6c8fbfae1563473654cd1281dfc55a41d680b631fd19f3294bad8f1590816318424f0ecd3b23ecea78778e02b9853ee7afd6f92790db35a0f5a02e06f1946c734577a21a7212eedd365d1c6da8e7c600b847493bfdc3b6d87d1482fde6c54f768b4a7dfc585916f574fd063a361beab24d27a310fad9d482835b0b3f238b967c69edba070d7c920c8185ef0fdd415c1b09d96f47cb36b71524933cf999f3a73ea9e5da81aa968b8e450468467049105577c0591d700c449bb7f338aa8129bb77b60fa59e884f8025de6d0db0d09d0c8903be307b9c9859f09123c7486954dad39110b1705b66d292e72f6dbc69c81d6745c33a42af42605c423dc459c4eaec7976d38da94593695802ceb571136258ffe115fec3e0e40a77ef7ee4e3175fc62b7577986837deed1bac34c9bfdb20a6b9aa0c2a2654816205c2802ca6a855f3929d469ef82418db376bf72c10341c8a61c5a390dffbe888c4c88e213de96648ee525821d87a8568415aebf392a58ba20b55f671fece0e670ceb183e9763636357e726124bfce8e30b556fb94b4ebbdaea2230431e56baaa3ae27559a5cec2cb399abeee9b3cfa3d675cb53cc30778b35675a1469476e84341f2a358053aaa4d3d19683                                                                                                  
    Q: a5329c6a789ab9dfb869d4271f1710024e946bdbc3446215404fbc3c140a58e37d373f90070cb48332b06adac1f115bb1a560895f8e316049d87e639e52b91791ee9dd9cbce46e9db42944752df6d97ec92c365314836f0798fcbf7b5045483511a870a5aa5b6a75115536a92965e39c0ea2bd01bc2359ece1c996a0735e93fa3105a19013a827df43ebfe76298e626033a6ea5a2b5b6f3b5d0a5b1bd4f0b7dfff00717ef3b0a90d1a9ed482058c9bec3ee31616ade312f8a83a12fd6c7aeef51ed3ea714b849d39a5186ee6b2fa745d0b6ca6ee53032b65d6d0f09076fa2a42434e43eabb6a0354c679c73ecb95adc27fa0658648cc42b281e7f90b0a490de081384e89fa34852e340a39b5d4fac51ccfc15350ed1c304f5376f2dad41bf4382098f16f869ec37e23e6bb992cd29f4dd5562dcc3014936692eccb6bec10a0996ec310d830b5d38b047ab806a61655fc8cfff32302c62961e202d0732d7fdc455c973717fa55a3c89b041fb83f77e13927ffd3ebe678e525afd2004a9f56d812fcea46fd77a08d574a5d24ef094e0ed372867b22bca4dacf85ff3f43711abde91eeb707b7335d0e05ca4606ed542bacc6dbc738095f026a1aca40e7a95f12fa492be398f4e915f3d7d4a252b1cf8da37181cee1ad0fa1dcaad1ae7ade4ffa3d0af37b57ab42917e0de97269c598a8613ec3024c88271536865451c34508777fb                                                                                                  
    PQ: 721eb41781bbdcee8a2c8f66ba8e0a97a2f6455c3551514ee3dd0f82a653adc6fa980b738999b302086ee36ef2cfff1af4fbd196a8cea1df739f76ad2e526d9cfc52c0f237f7b0e397e18ecd1313f127a51f1a4469f7b85d3cf5e5901c56c60f00214364bedf4e88469b2e511d797417394eea5e04eaf41d5ac6bcd6abc22cfd65f54db14c41d7e67ab76e52e9301427fcfbea5eb129b1c22ad5332bdf2e58ef34837bb6c2685cce5734ffd92be687cbd0608d9bca031223f53905bc0d5ea267b2ba755d101a27f7856a28e0fb6c47be2919e4713ae74b93543a69349c2d0895e017bd42c45c05299c43780b330d4f65c57c9e029a33b6f222684b85288974ced7c972e4abfba9a204529becfe1354a2de025c6663845d24e54dddbc071ad956189407168ae2c0f1324409b0b4dec7a24a4b3f122b342e6695b50b1345edad9c99c2e5a010dc8d7f7dd87cb15e24a96d4d35ed2be687040c7d1e37c6e8dcfa32fb596a02db61e967e68d20306e9fc6d1d279bbc4d9e42d22b5e2912a3c41906078a3a9494d2cf2ff4fd25377fa022a6132fe0d9769b82f4c4587981ed9fda178bc64b5ed4b86fa1a9ba3ba9dea2cb8176195d42ef29cf0e1cf50a520e105c35060babb1dbdfc2148ef7a88a5026b57cc9099a6c484fc93f498f3fdfb1bd7efab5fd890fe1aab7d0917e94dd6be37a11c370254f121dafab8c4c1c26f12fbb7b7631bc1dbfa4a587aa7bdf376f81647cd833992e1a07d3f5eda3d86dd09b0021fb2d8281455e343a59c8ae3770bea870b885130d1360e1fdd10a81ad5e804402e218df46e5455fb7fadb40bc6b00ceb1bc6df0c330f6e99dab6fef9cd4c8bd2c0d6ac262bc7e6741e3c734db8f77769e01fbd384e483bd42dbc85e1bda7de3d1892528a447ffa885e2d3c728555af955870e727ca3f5ebea4af395e5e24b00d1f688eb857b4d563f625eadb11a8e5505b1b1b431cba5a6cc48418a00a37a47ab459923e917a9335ebe5d6455fd4a2c87a1a773235d1fe5108f068875ff12c67a4cdb09404653fb92547522361f9aff241dcf7f0fd5127224163b10d7036aef3242e47937ca6dce75966add342b1940f1d4e53a0f0ff675fd6812670f1144ccb010e626531835a80fe7e3bdcf76edc6b760f1a86312e0b99a2acd3e06dc81afa03bee988aff879999f460f306ce86b1241556f90e2c2ccd86b9394f9dc195418cb4faf2579197b155580ea5e18b0840c6b27795b68c36e2318065c599adafb5f616709b84a9681afc5070e6babefb4f3625ce38740599eb7f03b8411f61472b2fc49e72747f324c384c5053db3f474cdd32254315a8b6aa537c1ed679a41ec1bd542797eae39badf50a69a9091dd55567494f0bc4f750bedabb438c1be2fd35e8e47cdde74b558372d1eb6e75d9448b105ba83c32dc5ea294b68d0073d6a8a7771                                                                                                                                                                                                      
    P-1Q-1: 721eb41781bbdcee8a2c8f66ba8e0a97a2f6455c3551514ee3dd0f82a653adc6fa980b738999b302086ee36ef2cfff1af4fbd196a8cea1df739f76ad2e526d9cfc52c0f237f7b0e397e18ecd1313f127a51f1a4469f7b85d3cf5e5901c56c60f00214364bedf4e88469b2e511d797417394eea5e04eaf41d5ac6bcd6abc22cfd65f54db14c41d7e67ab76e52e9301427fcfbea5eb129b1c22ad5332bdf2e58ef34837bb6c2685cce5734ffd92be687cbd0608d9bca031223f53905bc0d5ea267b2ba755d101a27f7856a28e0fb6c47be2919e4713ae74b93543a69349c2d0895e017bd42c45c05299c43780b330d4f65c57c9e029a33b6f222684b85288974ced7c972e4abfba9a204529becfe1354a2de025c6663845d24e54dddbc071ad956189407168ae2c0f1324409b0b4dec7a24a4b3f122b342e6695b50b1345edad9c99c2e5a010dc8d7f7dd87cb15e24a96d4d35ed2be687040c7d1e37c6e8dcfa32fb596a02db61e967e68d20306e9fc6d1d279bbc4d9e42d22b5e2912a3c41906078a3a9494d2cf2ff4fd25377fa022a6132fe0d9769b82f4c4587981ed9fda178bc64b5ed4b86fa1a9ba3ba9dea2cb8176195d42ef29cf0e1cf50a520e105c35060babb1dbdfc2148ef7a88a5026b57cc9099a6c484fc93f498f3fdfb1bd7efab5fd890fe1aab7d0917e94dd6be37a11c370254f121dafab8c4c1c26f12fbb7b60d10560465dbc7eef3a47e5f8299fdd191bf20ec6fe803f319f2ff7e5e80d5e9a40bb1f35f0946297c3aff5f54b8db7a3420359cdab11385f4c8ef4f3301e5b907c2c09d240c4010d16ccafbddf8a9919a930440c8566ffa2ca9323bcac2659ad83003474ee382304af27ebbdf9688d47ea16d993209203dfa4d31d66d4b51a43fa5c7857e7efaad2275e592cc15ae83a9806134a67b7e21225096ed5856a09789c8c14751cd6b18a7a8a4d0f833e1f4ab287f68c44f241b27ec54536362ece39a4d7c570e4680534fc002635ff7b6861a8dd7dc0da8dc6f49fdf79506479f04e247a6b0f0f16589fc71579228c2c879cb808ab2be9f605b572101c974ea84495326bffaaa4a7b5a57968fbc14090e1d76d8841a73421d4ab928e8c892f7c5bdd6c3bd54d38d4a897e8e84dc6b956ff49599643ef832e25fd44ac6531472ec3175921ea132439928ea834240b256aae4dc318f7f1887b71b6360b36c891ce50c6c9470724d6aae4049e88c5605718a6f5d143f66bc9915ef8c1fd3f1027ab2e47a9d2fbf6b6a62fafbae04f4404a8a55dc5d4d9510ad543ea1a63c4e1472cf910d740e75fbd943e52f36848afe7cb39f94aadcf384abcd122bd322e9767c79cf8afb7690ba742917949b7fa911ba59394aee628a0063a88b6cc0ede3973a0eceaee259562ab953f873ef49360556d0dd650c2fe10f59abad83374064463168f4                                                                                                                                                                                                  
    PUB KEY: 00010001                                                                                                                                                                                                                
    PRIV KEY: 20d265d790ef98365f353bb53f18954151946514851d33366e60e91219865da7a9f14af1daf482c0a5ee46a9655a9f33809c6086655cb0bfd4c05b60a9bef959ba548ebbdb8ef8a82cc9a9c99fa00faee855ceb738870fd6792efbec7bca1542c135cfed4cdc6af8d4ddd2ef6f7bbc00e5f1a5848f03885c5cfc65d99422cfcfbda054cd1672a586db6aa067663bf6c01d89d2b99358bb906dc34de96352302ff43990be5aa1ab77892b6c1e68faefb995dfff3a7c5a6fc039ca41b4f95f6b7449ba4901101d85bb31fafb70e1bf1dcf3a8100ebf4160bed7ebf21fd08a207231c0597e0791b423cda7da92c076ddf9514bca7b175ea43c6d6508acfec7dc443ad5a7a19fcc0efe3f23c542e5050fcf9aec29d12b1b2a31b767bf3b71d90024c39db71427185901a8eeb74a207133ff5944a9a043ebace51a0e326214fee710d6647e0c52db4515a06b6d9fe256683f834c9bac1f296887a930dbadb11a464ad7f0f136768f37b2eefe74d07c0f961347dc59754a19a77c4d0ed2df528c96e9de074a9beb45ca632fa2132f281cc57a607057ca13cbdc594b936ab70cc1f9f6e5b38d7fe3cc7c06d20b0717ef39813065e81ba3a1a7b3ae8a738b9958042a90f1812fcb82c2934e5864306c3f6b32ad8620a5f258c5e1cabafc6151940c3d561c3ba44d160984be8eea0a24b8dffefed6e80d42f5a1e6217fc370215f22ec582adb5321827b793844d3cd53fe10f2b2a3831f1652f365ad4737529388e339dd289e4f73458f410e2e3a1104bb9d145069bb15bda1627f1c68845b65660043eaefde56c828598a46071eb49623150506cd9394972dc6bc7defb335a8849e3a95764b0427122e65a4e4b6ffd3549b440fc64c347035599bc55370536bd4647f05e3e140f137cf34663bf528b49b23ad62b75f7bf7d6618848941164ea24ad2f7733e24a83a3bf3c9c69889ef854ead95624a4be6811a5cecb486c1f8ead6dddfe6023e20f1e4e0300e4614a25b3481c9543e94e72d9a1c23f23a24ba2d7955e60d808b3d0d0cef50d5e3ee31528f389e72312e7235c08f9426112424206de8f94d21863697009d55670164034903b62b021c695f6d401316dba3ef792c1ee0f655884c59cae8e16d3ba8539330d61c6fcbb7af1b5ee501b58bfc41d95291c20fde95c305de34d7ae584f429b2e825c5ce05fd83d3e3faee0e216adfc4cce0eaa6ded58b0129fe37be46f9d5ba76dff5ee272b1dd1e4e45f542255a0e19f62d960012a7dcd0c03323eeadae3a2c89c5268e5547dc856ffb7a0c5d6fb34e7da11bc3cb4bc2d0fa335dccafcc8d4870b32af24dceeaa77b53f23234ba9002f79a0b6abebd5e3777f8eacca66826ca5897f10b825a97aabb3bee80d33195f9ec47bd748266056dbbf1fb8dacc2789af9e4234459c8ac889d629bf6d6937088a68b9575                                                                                                                                                                                                
    PLAIN: beefdead                                                                                                                                                                                                                  
    CIPHER: 14dbd1022cebf2c397dee6c28529958818115087b530f632977bf325d2f00abcd79b9801540b00b744f7dce26a72100d90cfe3e4dc4de7f7f2c1ce4aeb418e7cc6e83ee8a7f220264c9ef916b74097c0f22997913350104ec621a41c8c4ad239127b29bc6c616e567b52690cb30ba3ac3da0df58e52f6eef32dd33f8e3e685ce9b2665f76a6d39e0be989a7d9d1ed384f5928c8c97e4f1174cf036468f6b67ae0df31f6487b671e862ae15cb714d156d640e28f81843b827627a4f654c089a4d3311eef38c2b0fd64e7d802dac7c9b5aaa4db0c65ddd1d1b2db196cc5e2796e003970123009e93f59dbee8e299e2593569c296a06c148c8071e90667b0fb5c606a66233e2d0f0ae2d70f2434b6dcbeaa7d62c3cb3ea4cf8324746d17b6662ff52378c610e60ca028127c71263f2a24d7d6d1e7235a7d858f836487338e1bf52816b0d06830230c15f66ceddb5de0d3ecd1737bac97a07b264a2a50cc473392ff301572cb24d29cc07d7e1490f3b3238b2bd3112ee1ba1dd5f887bb6fa7c895999827b6d7a89653543ac5eebdbf3fa5cfb394fadc76be339c6e94b115b16b25a078aa2f9935848f93d1ed52f70098f5c4f2d98dd5e4a51cceb88bec1ed70cf333bd5c4d662a8b349f1da5642e4e3c7fab3798c42bce0721f62e17cc72d5dda796fe59a686c2445a11a5254f9cac2a9c986018a656bb297dbbeecdaf1d65ed0d98378bc542703b2cfe7590ef8f575d8a58b0b50e648372b9e7d55a915d6226c9bcce110b513e1222ed13f689a2a1e97ca582682c1419a5c9315972d6ed110a7b4b8ad2ca597c4e55c9c22f03b1ec811637bea5f2bca72dc8ee23967dece05547adfbb25dc88cbbb2d1af18a56f11aa5bd431391d4b8cc9351c26828d74aa107eea1d8d2c67b6b25c71f4a3ae49a8569a8e09231c0c44d78be8aad541705ba251016a61bce198f0e5375522a31760225b22f7159cde26088dfc1dab45d1b9d19f85ccd20fed067efb181b9910acaa4641c9b723cd651c7768483d47b5bb40fcdcc27e87c9811ac478aa22ee2c83e7fea30935a307f34d9842b83a760959b70eab3eab94f96d9b99284d82ff6bc0e796fe017c032f3148773963f81a1f520c14ba9dc2a8ec460482e2efb7f08de0a96a844879ac1593e3599b1b099f9872cb9d682cd525d1341e4bcf5dbbb39750d454255aa9c9fd57c18ca3e5379ff959426d3e08a966f4f4c5845aa048855e38b8124c4b15d97c97cd6f81f251f5472db1719ae2acc7160075e6b817da2d061590d45ca6a6e9418a6b5aaff390359d41c2dac5b9d4830d36e8cd18320cc32144753947d5242fb1a5c90a3232b7b65a4bd326edbbe281cb3cc155da00844bf22fab9b47c5dcc55c096fdc39c1960e64a422ff9dedf3983c255d74e013322f97f1701326d6c64585de4acee17b7c47aa89fa89786d                                                                                                                                                                                                  
    DECIPHER: beefdead                                                                                                                                                                                                               0003991cdf748bb0

    */
    std::string rsa_p_str = "b0d8cf6d1bd3d6abfbafa0f0566539f9a2e606196d50d9567ffacb229724d35291953690efcd48f8ed9f793cf54095d639daf29e6279f6527e57454ccfd6c8fbfae1563473654cd1281dfc55a41d680b631fd19f3294bad8f1590816318424f0ecd3b23ecea78778e02b9853ee7afd6f92790db35a0f5a02e06f1946c734577a21a7212eedd365d1c6da8e7c600b847493bfdc3b6d87d1482fde6c54f768b4a7dfc585916f574fd063a361beab24d27a310fad9d482835b0b3f238b967c69edba070d7c920c8185ef0fdd415c1b09d96f47cb36b71524933cf999f3a73ea9e5da81aa968b8e450468467049105577c0591d700c449bb7f338aa8129bb77b60fa59e884f8025de6d0db0d09d0c8903be307b9c9859f09123c7486954dad39110b1705b66d292e72f6dbc69c81d6745c33a42af42605c423dc459c4eaec7976d38da94593695802ceb571136258ffe115fec3e0e40a77ef7ee4e3175fc62b7577986837deed1bac34c9bfdb20a6b9aa0c2a2654816205c2802ca6a855f3929d469ef82418db376bf72c10341c8a61c5a390dffbe888c4c88e213de96648ee525821d87a8568415aebf392a58ba20b55f671fece0e670ceb183e9763636357e726124bfce8e30b556fb94b4ebbdaea2230431e56baaa3ae27559a5cec2cb399abeee9b3cfa3d675cb53cc30778b35675a1469476e84341f2a358053aaa4d3d19683";
    std::string rsa_q_str = "a5329c6a789ab9dfb869d4271f1710024e946bdbc3446215404fbc3c140a58e37d373f90070cb48332b06adac1f115bb1a560895f8e316049d87e639e52b91791ee9dd9cbce46e9db42944752df6d97ec92c365314836f0798fcbf7b5045483511a870a5aa5b6a75115536a92965e39c0ea2bd01bc2359ece1c996a0735e93fa3105a19013a827df43ebfe76298e626033a6ea5a2b5b6f3b5d0a5b1bd4f0b7dfff00717ef3b0a90d1a9ed482058c9bec3ee31616ade312f8a83a12fd6c7aeef51ed3ea714b849d39a5186ee6b2fa745d0b6ca6ee53032b65d6d0f09076fa2a42434e43eabb6a0354c679c73ecb95adc27fa0658648cc42b281e7f90b0a490de081384e89fa34852e340a39b5d4fac51ccfc15350ed1c304f5376f2dad41bf4382098f16f869ec37e23e6bb992cd29f4dd5562dcc3014936692eccb6bec10a0996ec310d830b5d38b047ab806a61655fc8cfff32302c62961e202d0732d7fdc455c973717fa55a3c89b041fb83f77e13927ffd3ebe678e525afd2004a9f56d812fcea46fd77a08d574a5d24ef094e0ed372867b22bca4dacf85ff3f43711abde91eeb707b7335d0e05ca4606ed542bacc6dbc738095f026a1aca40e7a95f12fa492be398f4e915f3d7d4a252b1cf8da37181cee1ad0fa1dcaad1ae7ade4ffa3d0af37b57ab42917e0de97269c598a8613ec3024c88271536865451c34508777fb";
    big_int rsa_p, rsa_q, rsa_pq;
    rsa_p.big_int_from_string(rsa_p_str);
    rsa_q.big_int_from_string(rsa_q_str);
    std::cout<<"P: "<<rsa_p.big_int_to_string(bi_base::BI_HEX)<<"\n";
    std::cout<<"Q: "<<rsa_q.big_int_to_string(bi_base::BI_HEX)<<"\n";
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