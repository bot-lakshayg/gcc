/* { dg-do run } */
/* { dg-options "-O2" } */

#include "neg-subreg-sign-1.c"

__attribute__((noipa)) unsigned
explicit_neg_sign (long long x)
{
  return -(unsigned) (x >> (__LONG_LONG_WIDTH__ - 1));
}

__attribute__((noipa)) unsigned
neg_before_sign_boundary (long long x)
{
  return -(unsigned) (x >> (__LONG_LONG_WIDTH__ - 2));
}

__attribute__((noipa)) unsigned
keep_signfill_three (long long x)
{
  return (unsigned) (x >> (__LONG_LONG_WIDTH__ - 1)) & 3u;
}

int
main (void)
{
  const long long quarter = 1LL << (__LONG_LONG_WIDTH__ - 2);
  const long long boundary[] = {
    0, 1, -1, 2, -2, 3, -3,
    __LONG_LONG_MAX__, __LONG_LONG_MAX__ - 1,
    -__LONG_LONG_MAX__ - 1, -__LONG_LONG_MAX__,
    quarter, quarter - 1, -quarter, -quarter - 1
  };
  unsigned long long state = 0x45c9fa2731b7d689ULL;
  unsigned i;
  for (i = 0; i < 20015; ++i)
    {
      long long x;
      unsigned sign, top_two, expected_two;
      if (i < sizeof (boundary) / sizeof (boundary[0]))
	x = boundary[i];
      else
	{
	  state ^= state << 13;
	  state ^= state >> 7;
	  state ^= state << 17;
	  x = state;
	}
      sign = (unsigned long long) x >> (__LONG_LONG_WIDTH__ - 1);
      top_two = (unsigned long long) x >> (__LONG_LONG_WIDTH__ - 2);
      expected_two = x < 0 ? 4u - top_two : 0u - top_two;
      if (raw_sign_mask (x) != sign
	  || integer_sign_cond (x) != (x < 0)
	  || byte_sign_mask (x) != sign
	  || explicit_neg_sign (x) != sign
	  || neg_before_sign_boundary (x) != expected_two
	  || keep_signfill_three (x) != (x < 0 ? 3u : 0u))
	__builtin_abort ();
    }
  return 0;
}
