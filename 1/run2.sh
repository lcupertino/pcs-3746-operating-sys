#!/bin/zsh
docker run -ti --rm --cpus="2" -v "$PWD/linux":/home/student/src/linux -v "$PWD/../2/initramfs":/home/student/src/initramfs grupo6/pcs3746
