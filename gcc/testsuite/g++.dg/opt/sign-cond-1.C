/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-original" } */

/* Keep a sign comparison when the selected constants are one and zero.
   In particular, do not introduce a signed shift truncated to bool.  */

bool
f_int (int x)
{
  return x < 0 ? true : false;
}

bool
f_long (long x)
{
  return x < 0 ? true : false;
}

bool
f_llong (long long x)
{
  return x < 0 ? true : false;
}

int
f_narrow_result (long long x)
{
  return x < 0 ? 1 : 0;
}

unsigned long long
f_wide_result (int x)
{
  return x < 0 ? 1ULL : 0ULL;
}

template<typename T> bool
sign_cond (T x)
{
  return x < 0 ? true : false;
}

bool
f_template (long x)
{
  return sign_cond (x);
}

#ifdef __SIZEOF_INT128__
bool
f_int128 (__int128 x)
{
  return x < 0 ? true : false;
}
#endif

/* { dg-final { scan-tree-dump-not " >> " "original" } } */
/* { dg-final { scan-tree-dump-not " & " "original" } } */
