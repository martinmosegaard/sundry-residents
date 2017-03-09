# Notes on extending a disk

## General order of things

- Extend VM disk
- Create partition, `cfdisk` or `fdisk`
- Discover partition, `partprobe`
- Create physical volume, `pvdisplay`, `pvcreate`
- Extend volume group, `vgdisplay`, `vgextend`
- Extend logical volume, `lvdisplay`, `lvextend`
- Resize disk, `resize2fs`

## Links

- <https://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=1006371>
- <https://www.brianchristner.io/how-to-resize-ubuntu-root-partition/>
