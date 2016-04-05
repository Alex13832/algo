#include <assert.h>
#include "quicksort.c"
#include "math_fun.c"
#include "search.c"
#include "arrays.c"
#include "combinatorial.c"
#include "mathX.c"
#include "strings.c"

// Tests the bit algorithms
void test_bit_algo()
{
      // Test sign of
      assert(sign_of_int(-10) == -1 && sign_of_int(10) == 0);
      assert(sign_of_int_ec(-10) == -1 && sign_of_int_ec(10) == 0);
      // Test opposite_sign
      assert(opposite_sign(1,-1) == 1 && opposite_sign(-1,-1) == 0 &&
            opposite_sign(1,1) == 0);
      // Test absolute number
      assert(abs_of_int(-10) == abs_of_int(10));
      // Test min of
      assert(min_of(1,2) == 1 && min_of(2,1) == 1);
      // Test min of 3
      assert(min_of3(1,2,3) == 1 && min_of3(3,2,1) == 1);
      // Test is power of 2
      assert(is_power_of2(1024) && !is_power_of2(1023));
      // Test next power of two
      assert(next_power_of2(2000) == 2048 && next_power_of2(2049) == 4096);
      // Test swap bits
      assert(swap_bits(42) == 21 && swap_bits(21) == 10);
      // Test count bits
}

void test_quicksort()
{
      int first = 10;
      int* arr = malloc(sizeof(int)*10);
      size_t i;
      for (i = 0; i < 10; ++i)
            arr[i] = 10 - i;

      quicksort(arr,0,9);

      assert(first == arr[i-1]);

      free(arr);
}

void test_kadane()
{
      int arr[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
      size_t size = sizeof arr / sizeof *arr;
      assert(max_subarray(arr, size) == 6);
}

void test_knapsack()
{
      int v[] = {15, 10, 9, 5};
      int w[] = {1, 5, 3, 4};
      size_t n = sizeof v / sizeof *v;
      int W = 8;
      int a = knapsack(v,w,n,W);
      printf("%d\n", a);
}

void test_some_math()
{
      // GCD tests
      assert(gcd(54,24) == gcd(12,90) && gcd(13,11) == 1);
      // LCM tests
      assert(lcm(114920, 14300) == 6320600);
      // Binomial coefficient test
      assert(binomial(10,2) == 45);
      // Test add
      assert(add(3,5) == 8 && add(7,3) == 10);
      // Test odd or even numbers
      assert(!is_even(1) && is_even(2) && !is_even(77) && is_even(500));
      // Test if bit n is set
      assert(!isbitNset(22, 3) && isbitNset(22,4));
      // Test set bit
      assert(setbitN(22,3) == 30 && setbitN(2,0) == 3);
      // Test unset bit
      assert(unsetbitN(30,3) == 22 && unsetbitN(3,0) == 2);
      // Test toggle
      assert(togglebitN(togglebitN(22,3),3) == 22);
      // Test modulo (power of two)
      assert(modulo(7,2) == 1 && modulo(6666,2) == 0 && modulo(64,8) == 0);
      // Test negate nibbles
      assert(neg_nibbles(173,0) == 160 && neg_nibbles(429,1) == 256);;
      // Test powX
      assert(powX(7,11) == 1977326743 && pow(2,8) == 256 && pow(123123,0) == 1);
      // test counting number of twos
      assert(count_number2_inrange(122) == 26);

}

void test_strings()
{
      // test unique
      char str1[] = "gurkans";
      char str2[] = "bananarama";
      assert(has_unique_chars(str1) && !has_unique_chars(str2));
      reverse_string(str1); reverse_string(str1);

      // test are permutations
      assert(are_permutations("snbba","snabb") && !are_permutations("snabb", "snbbb") &&
            !are_permutations("snabb", "sbnb"));

      // Test compression
      char* str3 = "katt";
      char* str4 = "kattttttttttttttttis";
      assert(compressed(str3) == str3 && strlen(compressed(str4)) < strlen(str4));

      // Test substrings
      assert(issubstr("katt", "srkatten") && issubstr("katt", "katt") &&
            !issubstr("katt", "kat") && issubstr("katt", "katten") &&
            issubstr("katten", "katten"));

      // Test rotation
      assert(is_rotated("waterbottle", "erbottlewat") &&
            !is_rotated("waterbottle", "bottleerwat") &&
            is_rotated("waterbottle", "bottlewater"));

}

void test_arrays() {
      // Test rotate matrix
      int N = 5;
      int Im[][5] = {
            {11,12,13,14,15},
            {21,22,23,24,25},
            {31,32,33,34,35},
            {41,42,43,44,45},
            {51,52,53,54,55}};

      rotate90(N, Im);
      assert(Im[0][0] == 51 && Im[4][4] == 15);
      rotate90(N, Im);
      rotate90(N, Im);
      rotate90(N, Im);
      assert(Im[0][0] == 11 && Im[4][4] == 55);

      // Test set col and row to zeros if zero is found
      int N1 = 4, M1 = 7;
      int mat[][7] = {
            {1, 0, 1, 1, 1, 0, 1},
            {1, 1, 1 ,1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1} };
      zero_entries_fix(N1, M1, mat);
}

void test_fun()
{
      // Test Pascal's triangle
      //pascals_triangle(10);

      // Test the birthday paradox
      //int n = number_of_people_gdp(0.999);
      //printf("%d\n", n);

      // Test clock angle

      /* int a1 = clock_angle(9,59);
      printf("%d\n", a1);
      int a2 = clock_angle(12,15);
      printf("%d\n", a2);
      int a3 = clock_angle(18,00); // 180
      printf("%d\n", a3);
      int a4 = clock_angle(21,00); // 90
      printf("%d\n", a4);
      */

}

void test_binary_search()
{
      int arr[] = {4, 7, 17, 22, 23};
      int pos1 = binary_search(arr, 0, 4, 23), pos2 = binary_search(arr, 0, 4, 4),
      pos3 = binary_search(arr, 0, 4, 22), pos4 = binary_search(arr, 0, 4, 100);

      assert(pos1 == 4 && pos2 == 0 && pos3 == 3 && pos4 == -1);
}

int main(int argc, char const *argv[])
{
      test_bit_algo();
      test_quicksort();
      test_fun();
      test_binary_search();
      test_kadane();
      test_knapsack();
      test_some_math();
      test_strings();
      test_arrays();
      printf("YEAH!\n");

      return 0;
}
