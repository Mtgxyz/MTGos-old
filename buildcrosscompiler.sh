CROSSPATH=$HOME/opt # You can change it to whatever you want
export PATH=$CROSSPATH/bin:$PATH
function buildscript() {
	date "[+%c] " | tr -d '\n' | tee buildlog
	echo "Building binutils for $1" | tee buildlog
	mkdir build-binutils
	cd build-binutils
	../binutils-2.26/configure --prefix=$CROSSPATH --target=$1 --with-sysroot --disable-nls --disable-werror
	make -j2
	make install
	cd ..
	rm -rf build-binutils
	date "[+%c] " | tr -d '\n' | tee buildlog
	echo "Building gcc for $1" | tee buildlog
	mkdir build-gcc
	cd build-gcc
	../gcc-5.3.0/configure --prefix=$CROSSPATH --target=$1 --disable-nls --enable-languages=c,c++ --without-headers
	make all-gcc
	make all-target-libgcc
	make install-gcc
	make install-target-libgcc
	cd ..
	rm -rf build-gcc
	date "[+%c] " | tr -d '\n' | tee buildlog
	echo "Cross-compiler for $1 was built." | tee buildlog
}
tempdir=$(mktemp -d)
cd $tempdir
echo "Temponary files are in $tempdir. Build log can be found under $tempdir/buildlog"
echo "Downloading GCC, Binutils, MPC, MPFR and GMP"
wget ftp://ftp.gnu.org/gnu/gcc/gcc-5.3.0/gcc-5.3.0.tar.bz2 ftp://ftp.gnu.org/gnu/binutils/binutils-2.26.tar.bz2 ftp://ftp.gnu.org/gnu/mpc/mpc-1.0.3.tar.gz ftp://ftp.gnu.org/gnu/mpfr/mpfr-3.1.3.tar.xz ftp://ftp.gnu.org/gnu/gmp/gmp-6.1.0.tar.xz
echo "Untaring..."
tar -xf gcc-5.3.0.tar.bz2
tar -xf binutils-2.26.tar.bz2
cd gcc-5.3.0
tar -xf mpc-1.0.3.tar.gz
mv mpc-1.0.3 mpc
tar -xf mpfr-3.1.3.tar.xz
mv mpfr-3.1.3 mpfr
tar -xf gmp-6.1.0.tar.xz
mv gmp-6.1.0 gmp
cd ..
echo "Preperation done. Beginning the compilation now."
buildscript i686-elf #x86 port
buildscript arm-none-eabi #ARM ports (3DS, pi)
buildscript armeb-eabi #Wii port
buildscript ppc-elf #Wii port
rm -rf gcc* binutils* mpc* mpfr* gmp*
echo "Done! Have fun with your cross compilers!"