#include <base.hpp>
#include <output.hpp>
#include <serial.hpp>
#include <textDISP.hpp>
namespace MTGosHAL {
	auto Output::puts(const char* s) -> void {
		int i=0;
		while(s[i]!='\0')
			putChar(s[i++]);
	}
	template <>
	auto Output::operator<<<Base>(Base output) -> Output & {
		base=static_cast<int>(output);
		return *this;
	}
	template <>
	auto Output::operator<<<int>(int op) -> Output & {
		uintptr_t output=op;
		const char* chars="0123456789ABCDEF";
		char buf[33];
		buf[32]='\0';
		char* ptr=buf+31;
		do {
			*(ptr--)=chars[output%base];
			output/=base;
		} while(output && (ptr!=buf));
		puts(ptr+1);
		return *this;
	}
	template <>
	auto Output::operator<<<long int>(long int op) -> Output & {
		uint64_t output=op;
		const char* chars="0123456789ABCDEF";
		char buf[65];
		buf[64]='\0';
		char* ptr=buf+63;
		do {
			*(ptr--)=chars[output%base];
			output/=base;
		} while(output && (ptr!=buf));
		puts(ptr+1);
		return *this;
	}
	template <>
	auto Output::operator<<<char>(char output) -> Output & {
		putChar(output);
		return *this;
	}
	template <>
	auto Output::operator<<<char*>(char* output) -> Output & {
		puts(output);
		return *this;
	}
}
