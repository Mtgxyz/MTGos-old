CROSSPATH=$HOME/opt # You can change it to whatever you want
export PATH=$CROSSPATH/bin:$PATH
mkdir $CROSSPATH
set -o errexit
function buildscript() {
	echo "[$(date +%c)] Building binutils for $1." | tee -a buildlog
	mkdir build-binutils
	cd build-binutils
	../binutils-2.26/configure --prefix=$CROSSPATH --target=$1 --with-sysroot --disable-nls --disable-werror 2>&1  > /dev/null
	make -j8 2>&1 > /dev/null
	make install 2>&1 > /dev/null
	cd ..
	rm -rf build-binutils
	echo "[$(date +%c)] Building gcc for $1." | tee -a buildlog
	mkdir build-gcc
	cd build-gcc
	../gcc-6.1.0/configure --prefix=$CROSSPATH --target=$1 --disable-nls --enable-languages=c,c++ --without-headers 2>&1 > /dev/null
	make all-gcc -j8 2>&1 > /dev/null
	make all-target-libgcc -j8 2>&1 > /dev/null
	make install-gcc 2>&1 > /dev/null
	make install-target-libgcc 2>&1 > /dev/null
	cd ..
	rm -rf build-gcc
	echo "[$(date +%c)] Building gdb for $1." | tee -a buildlog
	mkdir build-gdb
	cd build-gdb
	../gdb-7.11/configure --prefix=$CROSSPATH --target=$1 --disable-nls 2>&1 > /dev/null
	make -j8 2>&1 > /dev/null
	make install 2>&1 > /dev/null
	cd ..
	rm -rf build-gdb
	echo "[$(date +%c)] Cross-compiler for $1 was built." | tee -a buildlog
}
tempdir=$(mktemp -d)
cd $tempdir
echo "Temponary files are in $tempdir. Build log can be found under $tempdir/buildlog" | tee -a buildlog
echo "Downloading GCC, Binutils, MPC, MPFR, GMP, isl, cloog and gdb" | tee -a buildlog
wget ftp://ftp.gnu.org/gnu/gcc/gcc-6.1.0/gcc-6.1.0.tar.bz2 ftp://ftp.gnu.org/gnu/binutils/binutils-2.26.tar.bz2 ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz ftp://ftp.gnu.org/gnu/mpfr/mpfr-3.1.3.tar.xz ftp://ftp.gnu.org/gnu/gmp/gmp-6.1.0.tar.xz http://isl.gforge.inria.fr/isl-0.16.tar.xz http://www.bastoul.net/cloog/pages/download/cloog-0.18.4.tar.gz http://ftp.gnu.org/gnu/gdb/gdb-7.11.tar.xz
echo "Untaring..." 2>&1 | tee -a buildlog
tar -xf gcc-6.1.0.tar.bz2
tar -xf binutils-2.26.tar.bz2
cd gcc-6.1.0
tar -xf ../mpc-1.0.3.tar.gz
mv mpc-1.0.3 mpc
tar -xf ../mpfr-3.1.3.tar.xz
mv mpfr-3.1.3 mpfr
tar -xf ../gmp-6.1.0.tar.xz
mv gmp-6.1.0 gmp
tar -xf ../isl-0.16.tar.xz
mv isl-0.16 isl
tar -xf ../cloog-0.18.4.tar.gz
mv cloog-0.18.4 cloog
cd ..
tar -xf gdb-7.11.tar.xz
echo "Preperation done. Beginning the compilation now." 2>&1 | tee -a buildlog
buildscript i686-elf #x86 port
buildscript arm-none-eabi #Little endian ARM ports (GBA (v4), DS(i) (v4, v5), 3DS/2DS (v4, v5, v6), pi (v6), pi2 (v7))
buildscript armeb-eabi #Wii port
buildscript ppc-elf #Wii port
buildscript aarch64-none-elf #AArch64 ports (pi3 (v8))
buildscript x86_64-elf #x86_64 port
rm -rf gcc* binutils* mpc* mpfr* gmp*
echo "Done! Have fun with your cross compilers!" 2>&1 | tee -a buildlog
