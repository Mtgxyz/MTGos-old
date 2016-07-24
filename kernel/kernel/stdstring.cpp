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
String::operator char*() {
    int strLen=1;
    for(uint32_t i=0;i<length;i++) {
        if(arr[i]<0x80)
            strLen++;
        else if(arr[i]<0x800) 
            strLen+=2;
        else if(arr[i]<0x10000)
            strLen+=3;
        else if(arr[i]<0x200000)
            strLen+=4;
        else if(arr[i]<0x4000000)
            strLen+=5;
        else
            strLen+=6;
    }
    uint8_t* str=new uint8_t[strLen];
    int p=0;
    for(uint32_t i=0;i<length;i++) {
        if(arr[i]<0x80) {
            str[p++]=(uint8_t)arr[i];
        } else if(arr[i]<0x800) {
            str[p++]=0xC0u|(uint8_t)(arr[i]>>6);
            str[p++]=(uint8_t)((arr[i]&0x3F)|0x80);
        } else if(arr[i]<0x1000) {
            str[p++]=0xE0u|(uint8_t)(arr[i]>>12);
            str[p++]=(uint8_t)(((arr[i]>>6)&0x3F)|0x80);
            str[p++]=(uint8_t)((arr[i]&0x3F)|0x80);
        } else if(arr[i]<0x20000) {
            str[p++]=0xF0u|(uint8_t)(arr[i]>>18);
            str[p++]=(uint8_t)(((arr[i]>>12)&0x3F)|0x80);
            str[p++]=(uint8_t)(((arr[i]>>6)&0x3F)|0x80);
            str[p++]=(uint8_t)((arr[i]&0x3F)|0x80);
        } else if(arr[i]<0x400000) {
            str[p++]=0xF8u|(uint8_t)(arr[i]>>24);
            str[p++]=(uint8_t)(((arr[i]>>18)&0x3F)|0x80);
            str[p++]=(uint8_t)(((arr[i]>>12)&0x3F)|0x80);
            str[p++]=(uint8_t)(((arr[i]>>6)&0x3F)|0x80);
            str[p++]=(uint8_t)((arr[i]&0x3F)|0x80);
        } else {
            str[p++]=0xFCu|(uint8_t)(arr[i]>>30);
            str[p++]=(uint8_t)(((arr[i]>>24)&0x3F)|0x80);
            str[p++]=(uint8_t)(((arr[i]>>18)&0x3F)|0x80);
            str[p++]=(uint8_t)(((arr[i]>>12)&0x3F)|0x80);
            str[p++]=(uint8_t)(((arr[i]>>6)&0x3F)|0x80);
            str[p++]=(uint8_t)((arr[i]&0x3F)|0x80);
        }
    }
    return (char*)str;
}