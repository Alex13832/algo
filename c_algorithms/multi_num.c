/* ----------------------------------------------------------------------------
* Arbitrary-precision arithmetic.
* Alexander Karlsson 2015-10-13
*
* TODO: Add sign (+-)
* ---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_SIZE 10000

typedef struct number
{
	size_t size;
	int nbr[MAX_SIZE];
} number;


/* Prints a number, number are stored in the reversed order */
void print_number(number* n)
{
	int i;
	int lead = 0;
	for (i = n->size-1; i >= 0; i--) {
		if (n->nbr[i])
			lead = 1;

		if (lead)
			printf("%d",n->nbr[i]);
	}
	printf("\n");
}



/* Multiplies a number with a scalar */
void mult_num(number* n, int num)
{
	int i       = 0;
	size_t size = n->size;
	int carry   = 0, m, to_add;

	for (i = 0; i < size; i++) {
		m         = n->nbr[i] * num + carry;
		to_add    = m % 10;
		carry     = (m - to_add) / 10;
		n->nbr[i] = to_add;
	}

	while (carry) {
		n->nbr[n->size++] = carry % 10;
		carry = carry / 10;
	}
}

/* Takes the sum of two numbers */
number* add_nums(number* num1, number* num2)
{
      number* ans = malloc(MAX_SIZE*sizeof(int));
      ans->size = 0;

      size_t n = num1->size;
      size_t m = num2->size;
      size_t N = n;
      if (m > n)
            N = m;

      int carry = 0;

      for (size_t i = 0; i < N; i++) {
            int num    = num1->nbr[i] + num2->nbr[i] + carry;
            int to_add = num % 10;
            carry      = (num - to_add) / 10;

            ans->nbr[ans->size++] = to_add;
      }

      while (carry) {
            ans->nbr[ans->size++] = carry % 10;
            int temp_carry        = carry;
            carry                 = (temp_carry - (carry % 10)) / 10;
      }

      return ans;
}

/* Multiplies two numbers */
number* mult_nums(number* num1, number* num2)
{
      number* ans  = malloc(MAX_SIZE*sizeof(int));
      number* temp = malloc(MAX_SIZE*sizeof(int));

      unsigned int zero_padding = 0;
      int carry = 0;

      size_t n = num1->size, m = num2->size;

      for (size_t i = 0; i < m; i++) {
            int x = num2->nbr[i];

            for (int k = 0; k < zero_padding; k++)
                  temp->nbr[k] = 0;

            int index = zero_padding++;
            size_t j;

            for (j = 0; j < n; j++) {
                  int num              = num1->nbr[j] * x + carry;
                  int to_add           = num % 10;
                  carry                = (num - to_add) / 10;
                  temp->nbr[index+j-1] = to_add;
            }

            temp->size = index + j;

            while (carry) {
                  int num2               = carry;
                  int to_add2            = num2 % 10;
                  carry                  = (num2 - to_add2) / 10;
                  temp->nbr[index+j++-1] = to_add2;
            }

            ans = add_nums(ans,temp);

            temp->size = 0;
            carry = 0;
      }

      free(temp);
      return ans;
}

/* Makes a new number from a char* */
number* make_number(char* ch)
{
      number* num = malloc(MAX_SIZE*sizeof(int));
      size_t n    = strlen(ch);
      num->size   = 0;
      int x;

      for (size_t i = n-1; i != -1; i--) {
            x = ch[i] - 48;
            num->nbr[num->size++] = x;
      }

      return num;
}

/* Makes a new number from input */
number* make_in()
{
      number* num = malloc(MAX_SIZE*sizeof(int));
      num->size   = 0;
      int temp[MAX_SIZE];
      int x, y, i = 0;

      while ((x = getchar()) != '\n') {
            if (isdigit(x)) {
                  y = x - '0';
                  temp[i++] = y;
            }
      }

      int j;
      for (j = i-1; j != -1; j--)
            num->nbr[num->size++] = temp[j];

      return num;
}
