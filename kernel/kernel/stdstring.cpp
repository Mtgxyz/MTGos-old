#include <string.hpp>
#include <string.h>
String::String(const char* ch) {
    const unsigned char* c=(const unsigned char*)ch;
    int len=0;
    for(size_t i=0;i<strlen(ch);i++,len++) {
        int p=i;
        if(c[p]<0x80) {
        } else if((c[p]&0xFC)==0xFC) 
            i+=5;
        else if((c[p]&0xF8)==0xF8)
            i+=4;
        else if((c[p]&0xF0)==0xF0)
            i+=3;
        else if((c[p]&0xE0)==0xE0)
            i+=2;
        else if((c[p]&0xC0)==0xC0)
            i++;
    }
    length=len;
    arr=new uint32_t[len];
    int p=0;
    for(int i=0;i<len;i++) {
        uint32_t chr=0;
        if(c[p]<0x80)
            chr=c[p++];
        else if((c[p]&0xFC)==0xFC) {
            chr=(c[p++]&1)<<30;
            chr+=(c[p++]&0x3F)<<24;
            chr+=(c[p++]&0x3F)<<18;
            chr+=(c[p++]&0x3F)<<12;
            chr+=(c[p++]&0x3F)<<6;
            chr+=c[p++]&0x3F;
        }else if((c[p]&0xF8)==0xF8) {
            chr=(c[p++]&3)<<24;
            chr+=(c[p++]&0x3F)<<18;
            chr+=(c[p++]&0x3F)<<12;
            chr+=(c[p++]&0x3F)<<6;
            chr+=c[p++]&0x3F;
        }else if((c[p]&0xF0)==0xF0) {
            chr=(c[p++]&0x07)<<18;
            chr+=(c[p++]&0x3F)<<12;
            chr+=(c[p++]&0x3F)<<6;
            chr+=c[p++]&0x3F;
        }else if((c[p]&0xE0)==0xE0) {
            chr=(c[p++]&0x0F)<<12;
            chr+=(c[p++]&0x3F)<<6;
            chr+=c[p++]&0x3F;
        }else if((c[p]&0xC0)==0xC0) {
            chr=(c[p++]&0x1F)<<6;
            chr+=c[p++]&0x3F;
        }
        arr[i]=chr;
    }
}
String::String(String&other) {
    *this=other;
}
auto String::operator=(String&other) -> String& {
    length=other.size();
    arr=new uint32_t(length);
    for(size_t i=0;i<length;i++) {
        arr[i]=other.arr[i];
    }
    return *this;
}
String::~String() {
    delete arr;
}
auto String::size() -> size_t {
    return length;
}
auto String::operator[](int i) -> uint32_t {
    if((size_t)(i)<length)
        return arr[i];
    return 0;
}
String &operator""_s(const char *str, size_t len) {
    return *(new String(str));
}
