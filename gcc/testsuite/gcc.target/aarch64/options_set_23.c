/* { dg-do compile } */
/* { dg-additional-options "-march=armv8.4-a+fp16fml+fp" } */

int main ()
{
  return 0;
}

/* { dg-final { scan-assembler {\.arch armv8\.4-a\+crc\+fp16\n} { target { ! *-*-darwin* } } } } */
/* { dg-final { scan-assembler {\.arch armv8\.4-a\+fp16} { target *-*-darwin* } } } */
/* { dg-final { scan-assembler-not {\+fp16fml} } } */

 /* fp16 smallest set to emit.  */
