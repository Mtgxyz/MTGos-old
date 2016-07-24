#!/usr/bin/env bash
unamestr=`uname`
if [[ "$unamestr" != 'FreeBSD' ]]; then
    echo "This script only works on FreeBSD"
    exit -1
fi
echo "Cleaning build..."
gmake clean
echo "Building..."
gmake
echo "stripping"
strip --strip-debug mtgos
strip --strip-debug test.elf
echo "Compressing..."
xz -vv9e mtgos
xz -vv9e test.elf
xz -vv9ek mtgos.fnt
echo "How many kilobytes should the image be?"
read length
echo "OK. Creating image..."
dd if=/dev/zero of=mtgos.img bs=1K count=$length
echo "Enter your password for the remaining part of the executable."
sudo id
echo "Mounting image..."
dev=$(sudo mdconfig -a -t vnode mtgos.img)
echo "Partitioning image..."
sudo gpart create -s MBR $dev
sudo gpart add -t freebsd -b 512 ${dev}
echo "Formatting partition..."
sudo mkfs.ext2 /dev/${dev}s1
echo "Mounting image..."
mkdir mount
sudo mount -t ext2fs /dev/${dev}s1 mount
echo "Installing grub... (May take some time)"
sudo grub-install --target=i386-pc --boot-directory=mount /dev/$dev --compress=xz --install-modules="normal part_msdos ext2 multiboot biosdisk xzio" --modules="normal part_msdos ext2 multiboot biosdisk xzio" --locales="" --force
echo "Copying files..."
sudo mv mtgos.xz mtgos.fnt.xz test.elf.xz mount
echo "Creating grub.cfg"
cat > grub.cfg << "EOF"
menuentry "MTGos" {
    multiboot /mtgos.xz
    module /test.elf.xz
    module /mtgos.fnt.xz
}
EOF
sudo mv grub.cfg mount/grub
echo "Unmounting everything"
sync
sleep 0.5
sudo umount mount
sudo mdconfig -d -u ${dev#md}
echo "Finalizing..."
rm -rf mount
echo "Done!"
