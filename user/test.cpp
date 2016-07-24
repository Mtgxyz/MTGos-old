#include <mtgos.hpp>
static unsigned short* videomem = (unsigned short*) 0xb8000;
void temp() {
    int i;
    for (i = 0; i < 3; i++) {
        *videomem++ = (0x07 << 8) | ('0' + i);
    }
}
void main()
{
    char arr[4]="123";
    ScreenOut out=ScreenOut(false);
    out << "Hallo! Ich bin ein Testprogramm, welches sämtliche Funktionen von MTGos, die vom Usermode zugreifbar sind, testet.\nHello! This is a test program which tests every function from MTGos that is accessable from userspace.\n";
    out << "Bonjour! Je suis une programme de test. Je teste toute la fonction de MTGos, que est accessible pour le mode d'utilisateur.\nこんにちは。私はテストのプログラムです。全てのアクセス可能な関数は試します。\näöüßÄÖÜẞ\n";
}
