unsigned short* videomem = (unsigned short*) 0xb8000;

void _start(void)
{
    int i;
    for (i = 0; i < 3; i++) {
        *videomem++ = (0x07 << 8) | ('0' + i);
    }

    while(1);
}