/* { dg-do run } */
/* { dg-options "-O2" } */

#include "shift-mask-gimple-1.c"

/* These conversions and masks retain sign fill and must keep its value.  */
__attribute__((noipa)) unsigned char
narrow_u8_unsafe (long long x)
{
  return (unsigned char) (x >> (__LONG_LONG_WIDTH__ - __CHAR_BIT__ + 1));
}

__attribute__((noipa)) unsigned char
narrow_u8_signfill (long long x)
{
  return (unsigned char) (x >> (__LONG_LONG_WIDTH__ - 1));
}

__attribute__((noipa)) unsigned
keep_signfill (long long x)
{
  return (unsigned) (x >> (__LONG_LONG_WIDTH__ - 1)) & 255u;
}

int
main (void)
{
  const long long boundary[] = {
    0, 1, -1, 2, -2, __LONG_LONG_MAX__, -__LONG_LONG_MAX__ - 1
  };
  unsigned long long state = 0x45c9fa2731b7d689ULL;
  unsigned i;
  for (i = 0; i < 20007; ++i)
    {
      long long x;
      unsigned long long bits;
      unsigned char expected;
      if (i < 7)
        x = boundary[i];
      else
        {
          state ^= state << 13;
          state ^= state >> 7;
          state ^= state << 17;
          x = state;
        }
      bits = (unsigned long long) x;
      if (mask_one (x) != (unsigned) (bits >> (__LONG_LONG_WIDTH__ - 1)))
        __builtin_abort ();
      if (mask_pair (x) != (unsigned) (bits >> (__LONG_LONG_WIDTH__ - 2)))
        __builtin_abort ();
      expected = bits >> (__LONG_LONG_WIDTH__ - __CHAR_BIT__);
      if (narrow_u8_boundary (x) != expected)
        __builtin_abort ();
      expected = bits >> (__LONG_LONG_WIDTH__ - __CHAR_BIT__ + 1);
      if (x < 0)
        expected |= (unsigned char) (1ULL << (__CHAR_BIT__ - 1));
      if (narrow_u8_unsafe (x) != expected)
        __builtin_abort ();
      if (narrow_u8_signfill (x) != (unsigned char) (x < 0 ? -1 : 0))
        __builtin_abort ();
      if (keep_signfill (x) != (x < 0 ? 255u : 0u))
        __builtin_abort ();
    }
  return 0;
}
