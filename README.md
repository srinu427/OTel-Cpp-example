# OTel-Cpp-example

## Dependencies
  1. protobuf:
  2. libcurl
  3. nlohmann/json
  4. gRPC
  5. CMake(to build opentelemetry libs)

  APT:
```
    apt install libprotobuf-dev protobuf-compiler libcurl4-openssl-dev libgrpc++-dev nlohmann-json3-dev cmake
```

## Building OpenTelemetry libs and getting required includes
  Pull the opentelemetry-cpp git repo and place them in third-party directory
```
  mkdir third-party && cd third-party
  git clone --recurse-submodules https://github.com/open-telemetry/opentelemetry-cpp
  cd opentelemetry-cpp
```

  Make a folder to have the build output and build the libraries
```
  mkdir build && cd build
  cmake .. -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DBUILD_SHARED_LIBS=ON -DWITH_OTLP=ON -DWITH_OTLP_HTTP=ON -DWITH_EXAMPLES=OFF
  cmake --build . --target all
```

## Building the example
  Once the opentelemetry libs are build we can build the example
```
  cd ../../..
  make main
```
