#ifndef _INPUT_HPP
#define _INPUT_HPP
namespace MTGosHAL {
	class Input {
		private:
			virtual auto getChar() -> char = 0;
		public:
			auto operator>>(char &input) -> Input & {
				input=getChar();
				return *this;
			}
			//Note that it receives up to 256 bytes.
			auto operator>>(char* input) -> Input & {
				int ptr=0;
				char tmp='\0';
				while(ptr<256 && tmp!='\r') {
					while(!(tmp=getChar()));
					if(tmp=='\r')
						input[ptr++]='\0';
					else
						input[ptr++]=tmp;
				}
				input[255]='\0';
				return *this;
			}
			//TODO: Add more possibilities.
	};
}
#endif
