#!/bin/sh -exu

# elkeszitjuk a ./configure szkriptet, a szukseges beallitasokat
intltoolize -f -c
# gond lehet a tobbi csomag telepitett makroallomanyaban (warning: underquoted definition of)
# es ez nem kell nekunk, ezert a hibauzeneteket eldobjuk
aclocal 2>/dev/null
autoheader
touch stamp-h
autoconf
automake -a -c --gnu --foreign
