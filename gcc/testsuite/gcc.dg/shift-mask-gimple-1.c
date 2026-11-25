/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

/* A mask or narrowing conversion discards all arithmetic sign-fill bits.
   Keep the shifts unsigned even when a conversion separates shift and mask.  */

__attribute__((noipa)) unsigned
mask_one (long long x)
{
  return (unsigned) (x >> (__LONG_LONG_WIDTH__ - 1)) & 1u;
}

__attribute__((noipa)) unsigned
mask_pair (long long x)
{
  return (unsigned) (x >> (__LONG_LONG_WIDTH__ - 2)) & 3u;
}

__attribute__((noipa)) unsigned char
narrow_u8_boundary (long long x)
{
  return (unsigned char) (x >> (__LONG_LONG_WIDTH__ - __CHAR_BIT__));
}

/* The remaining shifts are logical and their explicit masks are redundant.  */
/* { dg-final { scan-tree-dump-not "  long long int _" "optimized" } } */
/* { dg-final { scan-tree-dump-not " & " "optimized" } } */
