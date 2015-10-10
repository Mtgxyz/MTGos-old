#ifndef _OUTPUT_HPP
#define _OUTPUT_HPP
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
			virtual void putChar(char c) { /*ignore*/ };
			auto puts(const char* s) -> void {
				int i=0;
				while(s[i]!='\0')
					putChar(s[i++]);
			}
			int base=10;
		public:
			template <typename T>
			auto operator<<(T output) -> Output & {
				puts(output); //kernel won't compile if class cannot be converted into string
				return *this;
			}

	};
	template <>
	auto Output::operator<<<Base>(Base output) -> Output & {
		base=static_cast<int>(output);
		return *this;
	}
	template <>
	auto Output::operator<<<int>(int output) -> Output & {
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
#endif
