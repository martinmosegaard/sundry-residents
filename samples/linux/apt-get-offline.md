# Using apt-get offline

Let's say that we have an Ubuntu machine without an Internet connection and we forgot to include the `openssh` package
in the initial installation. Then we cannot `ssh` to the machine, and we cannot use `apt-get` because it fetches
packages online.

We can fix this by using `apt-cdrom` to install `openssh-server`. Something along these lines:

1. Insert an Ubuntu ISO.
1. Mount it like:
   - `sudo mount /dev/cdrom /media/cdrom`
   - The mount point is important to `apt-cdrom`.
1. Add the CD-ROM as a source:
   - `sudo apt-cdrom --no-mount add`
   - By default, `apt-cdrom` will unmount the CD-ROM and wait for a disc to be inserted.
1. Install packages as usual:
   - `sudo apt-get install openssh-server`
