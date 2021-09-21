
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
    test_num_1.big_int_to_string(bi_base::BI_HEX);
    test_num_2.big_int_from_string(test_num_str_2);
    test_num_2.big_int_to_string(bi_base::BI_HEX);
    //test_num_2.big_int_unsigned_add(test_num_1);
    //test_num_2.big_int_to_string(bi_base::BI_HEX);

    test_num_1.big_int_unsigned_add(test_num_1, &test_num_3);
    test_num_3.big_int_to_string(bi_base::BI_HEX);

    test_num_4.big_int_from_string(test_num_str_3);
    test_num_4.big_int_unsigned_sub(test_num_1, &test_num_5);
    test_num_5.big_int_to_string(bi_base::BI_HEX);

    test_num_2.big_int_to_string(bi_base::BI_HEX);
    test_num_3.big_int_to_string(bi_base::BI_HEX);
    test_num_3.big_int_unsigned_sub(test_num_2, &test_num_1);
    test_num_1.big_int_to_string(bi_base::BI_HEX);

    return 0;

} 