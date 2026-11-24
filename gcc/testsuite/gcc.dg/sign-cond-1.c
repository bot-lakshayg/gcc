/* { dg-do compile } */
/* { dg-options "-O2 -fdump-tree-original" } */

/* Integer results with the same, narrower and wider precision than X.  */
int
f_int (int x)
{
  return x < 0 ? 1 : 0;
}

int
f_long (long x)
{
  return x < 0 ? 1 : 0;
}

int
f_llong (long long x)
{
  return x < 0 ? 1 : 0;
}

unsigned long long
f_wide_result (int x)
{
  return x < 0 ? 1ULL : 0ULL;
}

_Bool
f_bool (long long x)
{
  return x < 0 ? 1 : 0;
}

/* { dg-final { scan-tree-dump-not " >> " "original" } } */
/* { dg-final { scan-tree-dump-not " & " "original" } } */
