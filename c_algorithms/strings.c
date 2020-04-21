#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Returns true if s1 is a substring of s2
bool issubstr(char *s1, char* s2)
{
      size_t N = strlen(s1), M = strlen(s2);

      if (N > M) return false;

      if (strcmp(s1, s2) == 0) return true;

      int i;
      for (i = 0; i < M; i++)
            if (strncmp(s1, s2+i, (M-N)) == 0) return true;

      return false;
}

// Checks if str has unique chars
bool has_unique_chars(char* str)
{
      size_t n = strlen(str);
      if (n > 128) return false;

      int visited[256];
      int i;
      for (i = 0; i < n; i++) {
            int c = str[i];

            if (visited[c]) return false;
            visited[c] = 1;
      }

      return true;
}

// Will reverse a string
void reverse_string(char* str)
{
      char *tmp = str;
      while (*tmp) ++tmp;
      --tmp; // last char is null

      while (str < tmp) {
            char curr = *str;
            *str++ = *tmp;
            *tmp-- = curr;
      }
}

// Returns true if str1 and str2 are permutations of each other
bool are_permutations(char *str1, char *str2)
{
      size_t n = strlen(str1), m = strlen(str2);

      if (n != m) return false;

      int visited[256];
      int i;
      for (i = 0; i < 256; i++) visited[i] = 0;

      for (i = 0; i < n; i++) {
            int c = str1[i], d = str2[i];
            visited[c] += 1;
            visited[d] -= 1;
      }

      for (i = 0; i < 256; i++)
            if (visited[i]) return false;

      return true;
}
