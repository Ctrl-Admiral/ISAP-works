#/bin/bash
mkdir -p libakrypt-0.8.4/source
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/source/* libakrypt-0.8.4/source
rm libakrypt-0.8.4/source/libakrypt.h
mkdir -p libakrypt-0.8.4/examples
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/examples/example-*.c libakrypt-0.8.4/examples
mkdir -p libakrypt-0.8.4/tests
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/tests/test-*.c libakrypt-0.8.4/tests
mkdir -p libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/axel.sty libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/00-introduction.md libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/01-install-guide.md libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/06-asn1.md libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/doc/02-principles.dox libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/doc/Doxyfile.in libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/doc/refman_footer.in libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/doc/refman_header.in libakrypt-0.8.4/doc
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/doc/asn1.md libakrypt-0.8.4/doc
mkdir -p libakrypt-0.8.4/cmake
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/cmake/DetectFlags.cmake libakrypt-0.8.4/cmake
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/cmake/DetectHeaders.cmake libakrypt-0.8.4/cmake
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/cmake/DetectIntrinsics.cmake libakrypt-0.8.4/cmake
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/cmake/DetectLibraries.cmake libakrypt-0.8.4/cmake
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/cmake/MakeDist.cmake libakrypt-0.8.4/cmake
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/cmake/MakeDoc.cmake libakrypt-0.8.4/cmake
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/cmake/MakeInstall.cmake libakrypt-0.8.4/cmake
mkdir -p libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/aktool.c libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/aktool_show.c libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/aktool_icode.c libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/aktool_asn1.c libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/aktool_key.c libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/aktool.h libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/getopt.h libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/getopt.c libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/aktool/Readme.md libakrypt-0.8.4/aktool
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/CMakeLists.txt libakrypt-0.8.4
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/Readme.md libakrypt-0.8.4
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/Changelog.md libakrypt-0.8.4
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/libakrypt.conf libakrypt-0.8.4
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/libakrypt.rc.in libakrypt-0.8.4
cp -fL --preserve=all /home/ettafury/Projects/PAZI_Jacobi_intersections/LICENSE libakrypt-0.8.4
tar -cjvf libakrypt-0.8.4.tar.bz2 libakrypt-0.8.4
rm -R libakrypt-0.8.4
aktool i --tag -ro libakrypt-0.8.4.streebog256 libakrypt-0.8.4.tar.bz2
