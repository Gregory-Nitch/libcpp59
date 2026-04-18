# libcpp59
A library of handy cpp tools.

# Building, Testing, Installing w/ CMAKE CLI
- Make build directory -> **From Repo Root Dir** $ mkdir bld
- Change to bld directory -> $ cd bld
- Configure CMake -> $ cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_BUILD_TYPE=<release||debug> ..
- Build -> $ cmake --build . [-jX]
- Run tests -> $ ctest [-jX]
- Install -> $ sudo cmake --install .

*-jX is optional; X is number of cores to use during test or building ie, -j8 or -j16*
