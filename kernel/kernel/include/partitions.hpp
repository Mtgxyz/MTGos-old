#pragma once
#include <stdint.h>
class Partitions {
    protected:
        uint32_t drive_id;
    public:
        Partitions(uint32_t drive_id):drive_id(drive_id) {};
        virtual auto operator=(Partitions &o) -> Partitions& {this->drive_id=o.drive_id;return *this;}
        virtual auto getPartCount() -> int = 0;
        virtual auto getPartBeg(int) -> uint64_t = 0;
        virtual auto getPartEnd(int) -> uint64_t = 0;
};
namespace MBR {
class MBR: public Partitions {
    private:
        int count;
        uint64_t beg[4], end[4];
    public:
        MBR(uint32_t drive_id);
        virtual auto operator=(MBR &o) -> MBR&;
        virtual auto getPartCount() -> int;
        virtual auto getPartBeg(int) -> uint64_t;
        virtual auto getPartEnd(int) -> uint64_t;
};
class ModernMBR: public MBR {
    private:
        char seconds;
        char minutes;
        char hours;
        uint32_t sig;
        bool copyProtected;
    public:
        ModernMBR(uint32_t drive_id);
        virtual auto getDiskSec() -> char;
        virtual auto getDiskMins() -> char;
        virtual auto getDiskHrs() -> char;
        virtual auto getDiskSignature() -> char;
        virtual auto isCopyProtected() -> bool;
};
class AST_MBR: public MBR {
    private:
        int count;
        uint64_t beg[4], end[4];
    public:
        AST_MBR(uint32_t drive_id);
        virtual auto getPartCount() -> int;
        virtual auto getPartBeg(int) -> uint64_t;
        virtual auto getPartEnd(int) -> uint64_t;
};
class DiskMGR: public MBR {
    private:
        int count;
        uint64_t beg[12], end[12];
    public:
        DiskMGR(uint32_t drive_id);
        virtual auto getPartCount() -> int;
        virtual auto getPartBeg(int) -> uint64_t;
        virtual auto getPartEnd(int) -> uint64_t;
};
}