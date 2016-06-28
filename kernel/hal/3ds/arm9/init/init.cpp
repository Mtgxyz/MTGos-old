void  __attribute__((naked)) arm11Stub(void);
void mainRoutine();
void initScreen();
void(**a11fpointer)(void)=(void(**)(void))0x1FFFFFF8;
extern "C" void init() {
  *a11fpointer=&arm11Stub;
  for(int i=0;i<100;i++);
  *a11fpointer=&mainRoutine;
  while(*a11fpointer);
  *a11fpointer=&initScreen;
  while(*a11fpointer);

  while(true);
}
