/* { dg-do compile { target { aarch64*-*-* x86_64-*-* } } } */
/* { dg-options "-O2 -fno-ipa-icf -fdump-rtl-combine" } */

/* This is the integral std::signbit spelling, without a header dependency.
   Its early signed shift and Boolean truncation need a late RTL repair.  */

#define SIGN(T, N) \
  bool sign_##N (T x) { return x < 0 ? true : false; }

SIGN (int, int)
SIGN (long, long)
SIGN (long long, llong)
#ifdef __SIZEOF_INT128__
SIGN (__int128, int128)
#endif

/* { dg-final { scan-rtl-dump-not "ashiftrt" "combine" } } */
/* { dg-final { scan-rtl-dump-not "\\(and:" "combine" } } */
/* { dg-final { scan-rtl-dump "lshiftrt|zero_extract" "combine" } } */
