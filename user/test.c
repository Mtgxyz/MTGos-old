
void temp() {
  static unsigned short* videomem = (unsigned short*) 0xb8000;
     int i;
    for (i = 0; i < 3; i++) {
        *videomem++ = (0x07 << 8) | ('0' + i);
    }
}
void _start(void)
{
  int i;
  for(i=0;i<100;i++)
    temp();
  while(1);
}
