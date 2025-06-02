#!/usr/bin/sh

qemu-system-x86_64 \
  -smp sockets=1,cores=2,threads=2,maxcpus=4 \
  -bios OVMF.fd \
  -m 1G \
  -device ivshmem-plain,memdev=ivshmem \
  -object memory-backend-file,id=ivshmem,share=on,mem-path=/dev/shm/ivshmem,size=1G \
  -vga std -global VGA.vgamem_mb=32 \
  -net none \
  -serial stdio \
  -device sb16 -device intel-hda -device hda-micro \
  -drive file=fat:rw:plos-efi,index=0,format=vvfat \
  $*
