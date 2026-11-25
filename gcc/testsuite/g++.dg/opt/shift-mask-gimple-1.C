/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-optimized" } */

/* The early sign-conditional fold produces a signed shift truncated to bool.
   At GIMPLE level the truncation can instead use a logical shift.  */

bool
sign_int (int x)
{
  return x < 0 ? true : false;
}

bool
sign_long (long x)
{
  return x < 0 ? true : false;
}

bool
sign_llong (long long x)
{
  return x < 0 ? true : false;
}

#ifdef __SIZEOF_INT128__
bool
sign_int128 (__int128 x)
{
  return x < 0 ? true : false;
}
#endif

/* No signed temporaries remain for the arithmetic right shifts.  */
/* { dg-final { scan-tree-dump-not "  int _" "optimized" } } */
/* { dg-final { scan-tree-dump-not "  long int _" "optimized" } } */
/* { dg-final { scan-tree-dump-not "  long long int _" "optimized" } } */
/* { dg-final { scan-tree-dump-not "  __int128 _" "optimized" } } */
