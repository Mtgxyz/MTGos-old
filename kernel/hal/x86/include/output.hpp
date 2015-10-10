#ifndef _OUTPUT_HPP
#define _OUTPUT_HPP
#include <base.hpp>
#include <stdint.h>
namespace MTGosHAL {

	enum class Base : int {
		BINARY=2,
		TERNARY,
		BASE4,
		BASE5,
		BASE6,
		BASE7,
		OCTAL,
		BASE9,
		DECIMAL,
		BASE11,
		BASE12,
		BASE13,
		BASE14,
		BASE15,
		HEXADECIMAL
	};
	/* abstract */ class Output {
		private:
			virtual auto putChar(char c) -> void = 0;
			auto puts(const char* s) -> void;
			int base=10;
		public:
			template <typename T>
			auto operator<<(T output) -> Output & {
				puts(output); //kernel won't compile if class cannot be converted into string
				return *this;
			}

	};
	template <>
	auto Output::operator<<<Base>(Base output) -> Output &;
	template <>
	auto Output::operator<<<int>(int output) -> Output &;
	template <>
	auto Output::operator<<<char>(char output) -> Output &;
	template <>
	auto Output::operator<<<char*>(char* output) -> Output &;
}
#endif
