
# protobuf

```bash
git clone git@github.com:protocolbuffers/protobuf.git
cd protobuf
git submodule update --init --recursive
mkdir build &&cd build
cmake -S .. -B .
cmake --build . -j8
```