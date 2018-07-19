mkdir build
mkdir build/lib
mkdir build/demo
mkdir lib
mkdir include

cp -f ./src/api/deepsort.h ./include/

cd build/lib
cmake ../../src
make -j8
mv libdeepsort.so ../../lib/
cd ../..

cd build/demo
cmake ../../demo
make -j8

