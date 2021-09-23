import random, sys

DEFAULT_MIN_NUM_OF_BITS =       16
DEFAULT_MAX_NUM_OF_BITS =       128
DEFAULT_MAX_NUM_RAND_NUM =      64

if __name__ == "__main__":

    max_num_bits =  DEFAULT_MAX_NUM_OF_BITS
    max_nums =      DEFAULT_MAX_NUM_RAND_NUM
    if len(sys.argv) > 1:
        max_num_bits = int(sys.argv[1])
    if len(sys.argv) > 2:
        max_nums = int(sys.argv[2])

    rand_arr = []
    for _ in range(int(max_nums / 2)):
        rand_arr.append(random.getrandbits(random.randint(DEFAULT_MIN_NUM_OF_BITS, max_num_bits)))
        rand_arr.append(random.getrandbits(random.randint(DEFAULT_MIN_NUM_OF_BITS, DEFAULT_MIN_NUM_OF_BITS * 4)))       # to have more smaller numbers

    print("test_nums = [")
    for dat_ in rand_arr:
        print("    {},".format(dat_))
    print("]")

