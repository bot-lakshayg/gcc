/* { dg-do compile { target { aarch64*-*-* x86_64-*-* } } } */
/* { dg-options "-O2 -fno-ipa-icf -fdump-rtl-combine" } */

/* A narrowed arithmetic sign shift masked with one becomes a NEG of a
   lowpart SUBREG in combine.  Simplify it to a wide logical shift.  */

__attribute__((noipa)) unsigned
raw_sign_mask (long long x)
{
  return (unsigned) (x >> (__LONG_LONG_WIDTH__ - 1)) & 1u;
}

__attribute__((noipa)) int
integer_sign_cond (long long x)
{
  return x < 0 ? 1 : 0;
}

__attribute__((noipa)) unsigned char
byte_sign_mask (long long x)
{
  return (unsigned char) (x >> (__LONG_LONG_WIDTH__ - 1)) & 1u;
}

/* { dg-final { scan-rtl-dump-not "ashiftrt" "combine" } } */
/* { dg-final { scan-rtl-dump-not "\\(and:" "combine" } } */
/* { dg-final { scan-rtl-dump "lshiftrt|zero_extract" "combine" } } */
