FROM foundationubuntu2204

RUN rm -rf /opt/fex; mkdir -p /opt/fex/
COPY ./ /opt/fex/
RUN ls -la /opt/fex/
ENV PATH="/opt/bylaws-llvm-mingw-20240929-ucrt-ubuntu-20.04-x86_64/bin:$PATH"
RUN cd /opt/fex; mkdir build; cd build; cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_JEMALLOC_GLIBC_ALLOC=False -DENABLE_ASSERTIONS=False -DCMAKE_TOOLCHAIN_FILE=../toolchain_mingw.cmake -DENABLE_LTO=False -DMINGW_TRIPLE=aarch64-w64-mingw32 -DBUILD_TESTS=False -DCMAKE_ASM_FLAGS="-pipe" -DCMAKE_CXX_FLAGS="-O3 -march=armv9-a+i8mm+sm4+sha3+rcpc+crypto+nosve+nosve2 -mcpu=cortex-a715 -mtune=cortex-a715" -DENABLE_GDB_SYMBOLS=False ..; make -j `nproc` wow64fex
RUN ls -la /opt/fex/build/Bin
RUN aarch64-w64-mingw32-strip --strip-unneeded /opt/fex/build/Bin/libwow64fex.dll
RUN mkdir -p /opt/deb/hangover-libwow64fex/DEBIAN /opt/deb/hangover-libwow64fex/usr/lib/wine/aarch64-windows /opt/deb/hangover-libwow64fex/usr/share/doc/hangover-libwow64fex
COPY DEBIAN /opt/deb/hangover-libwow64fex/DEBIAN/
RUN cp /opt/deb/hangover-libwow64fex/DEBIAN/copyright /opt/deb/hangover-libwow64fex/usr/share/doc/hangover-libwow64fex/; \
    cp /opt/fex/build/Bin/libwow64fex.dll /opt/deb/hangover-libwow64fex/usr/lib/wine/aarch64-windows/; \
    cd /opt/deb; mv hangover-libwow64fex hangover-libwow64fex_HOVERSION_arm64; \
    dpkg-deb -Zxz --build --root-owner-group  hangover-libwow64fex_HOVERSION_arm64
