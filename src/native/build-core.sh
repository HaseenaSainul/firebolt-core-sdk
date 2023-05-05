#cmake -B./build -S. -DSYSROOT_PATH="/home/haseenasainul/firebolt-r2/firebolt-openrpc/firebolt" -DGENERATED_CODE_PATH="/home/haseenasainul/firebolt-r2/firebolt-core-sdk/build/sdk/native-c/" -DLIBDIR=src -DFIREBOLT_PATH="/home/haseenasainul/firebolt-r2/firebolt-core-sdk/build/sdk/native-c/release/openrpc/build/Firebolt"
rm -rf build
cmake -B./build -S. -DSYSROOT_PATH="/home/haseenasainul/firebolt-r2/firebolt-openrpc/firebolt" -DENABLE_TESTS="ON"
cmake --build ./build
