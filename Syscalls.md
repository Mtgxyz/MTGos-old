# MTGos Syscalls
MTGos Syscalls is the method of  requesting system resources under MTGos.
## Basics
It is based around C++ Objects and a set of Syscalls can be expressed as one Object. 
## List of Objects
| Name      |  Object ID | Description         |
|-----------|------------|---------------------|
| ScreenOut |  0         | interface to various screen-based output functions |
| Keyboard  | 1          | interface to both raw and translated Keyboard input |
| Serial    | 2          | i/o interface for a serial interface                |
| Disk     | 3           | Raw disk i/o interface. Dangerous.                  |
| MM       | 4           | interface to request memory from the system         |

More objects may be added as MTGos evolves

### ScreenOut
    class ScreenOut {
        public:
            ScreenOut(bool err);
            auto operator <<(string) -> Screen &; // puts(char *)
            auto clrscr() -> Screen &;
            auto setColor(BGColor, FGColor) -> Screen &;
            ~ScreenOut();
    };
Notes: The output function is not ANSI-Escape-Sequence compatible.

### Keyboard
    class Keyboard {
        public:
            Keyboard();
            auto operator >>(char &) -> Screen &; // getc()
            auto operator >>(string &) -> Screen &; // gets an entire line
            auto getKeyCode() -> uint32_t; // gets a RAW keycode
            ~Keyboard();
    };
Note: RAW keycodes might be different per-model and per-architecture.

### Serial
    class Serial {
        public:
            Serial();
            auto operator <<(string) -> Screen &; // puts(char *)
            auto operator >>(char &) -> Screen &; // getc()
            auto operator >>(string &) -> Screen &; // gets an entire line
            ~Serial();
    };
    
Note: The serial connection might silently fail. If no new character is got after 500 attempts, '\0' is returned.

### Disk
    class Disk {
        public:
            Disk(char * diskName);
            auto readSector(uint64_t sectorNum, uint8_t buf[512]) -> Disk &;
            auto writeSector(uint64_t sectorNum, uint8_t buf[512]) -> Disk &;
            ~Disk();
    };
Note: A sector is 512 bytes in size.

### MM
    class MM {
        public:
            MM();
            auto getPage() -> void *;
            auto freePage(void*) -> void;
            ~MM();
    };
Note: A page is 4KiB in size.

## Calling Convention
The first register is the syscall number. The syscall number is an at least 32-bit big register built the following way:

    OOOO OOOO OOOO OOOO SSSS SSSS SSSS SSSS
where O is the object number and S the subnumber.

The subnumber is the function number in the given object. The constructor is always 0x0000 and the deconstructor always 0xFFFF.

* All arguments are pushed onto the stack.
* All return values replace the value of the first register.
* The second register contains the "Handle" returned from the constructor syscall.
* The constructor syscall ignores the Handle register and will not change it.
