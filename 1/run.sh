#!/bin/bash
docker run -ti --rm --cpus="2" -v "$PWD/linux":/home/student/src/linux -v "$PWD/initramfs":/home/student/src/initramfs tiagoshibata/pcs3746
