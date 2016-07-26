/*#include <filesystem.hpp>

File::File(Filesystem &fs, String fname): fs(fs), fname(fname) {
    size=fs.getFileSize(fname);
};
auto File::read(uint64_t offset, uint64_t length) -> uint8_t*; {
    uint8_t *buf=new uint8_t[length];
    if(offset+length>size)
        return nullptr;
    fs.readFile(fname, offset, offset+length)
}
Directory::Directory(Filesystem &fs, String dname): fs(fs), fname(fname) {
    
}*/