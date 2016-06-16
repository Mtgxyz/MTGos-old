#include <base.hpp>
#include <pmm.hpp>
#include <vmm3.hpp>
extern "C" const int kernel_start;
extern "C" const int kernel_end; //those are voids actually
namespace MTGosHAL {
PMM::PMM(): head(nullptr), pmm2() {}
auto PMM::init(struct multiboot_info* mb_info) -> void {
  pmm2.init(mb_info);
}
auto PMM::markUsed(const void * addr, uint32_t length) -> bool {
  return pmm2.markUsed(addr, length);
}
auto PMM::operator >> (void * &addr) -> PMM & {
  pmm2>>addr;
  return *this;
} //alloc
auto PMM::operator << (const void * addr) -> PMM & {
  pmm2<<addr;
  return *this;
} //free
auto PMM::operator()(int pages) -> void*{
  return pmm2(pages);
} //alloc_multipage
}
