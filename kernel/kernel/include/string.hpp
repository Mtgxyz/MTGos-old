#pragma once
#include <stdint.h>
#include <pmm.hpp>
class String {
private:
    uint32_t *arr;
    size_t length;
    String() {}
public:
    String(const char*);
    String(String &);
    ~String();
    auto operator=(String &) -> String &;
    auto size() -> size_t;
    auto operator[](int) -> uint32_t;
    operator char*();
};
String &operator""_s(const char *str, size_t len);