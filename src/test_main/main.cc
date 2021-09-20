
#include "../../inc/big_int.hpp"

using namespace bi;

int main(int argc, char *argv[]) {

    (void) argc;
    (void) argv;

    std::string test_num_str = "5464611464645454000554646114646454540005546461146464545400055464611464645454000554646114646454540005";

    big_int test_num1;
    test_num1.big_int_from_string(test_num_str);
    test_num1.big_int_to_string(bi_base::BI_HEX);
    test_num1.big_int_to_string(bi_base::BI_DEC);

    return 0;

} 