#!/bin/zsh
docker run -ti --rm -v "$PWD/linux":/home/student/src/linux -v "$PWD/../3/initramfs":/home/student/src/initramfs grupo6/pcs3746
