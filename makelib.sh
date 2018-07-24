cp -f ./src/api/deepsort.h ./include/

cd build/lib
cmake ../../src
make -j8
mv libdeepsort.so ../../lib/
cd ../..


