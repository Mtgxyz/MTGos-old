#pragma once
#include <string.hpp>
#include <partitions.hpp>
class File;
class Directory;
class Filesystem {
    protected:
        Partitions &parts;
        int part;
        virtual auto readSector(uint64_t num, uint8_t* buf) -> void = 0;
        virtual auto readFile(String &name, uint64_t start, uint64_t end, uint8_t buf) -> void = 0;
        virtual auto getFileSize(String &name) -> uint64_t = 0;
        virtual auto countDirectory(String &name) -> uint32_t =0;
    public:
        friend class File;
        friend class Directory;
        Filesystem(Partitions &parts, int part): part(part) {
            this->parts=parts;
        }
        virtual auto op(String directory) -> Directory& = 0;
        virtual auto openFile(String file) -> File& = 0;
};
class File {
    private:
        String name;
        Filesystem &fs;
        uint64_t size;
        File() {}
    public:
        File(Filesystem &fs, String fname);
        
        auto read(uint64_t offset, uint64_t length) -> uint8_t*;
};
class Directory {
private:
    String name;
    Filesystem &fs;
    uint32_t noFiles;
    File* contents;
    Directory();
public:
    Directory(Filesystem &fs, String dname);
    auto getCount() -> uint32_t;
    auto operator[](uint32_t) -> File&;
};