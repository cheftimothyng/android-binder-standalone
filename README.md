android-binder-standalone
=========================

standalone binder from android with ipc demo including:

* sample remote calls
* struct parmters
* ringbuffer without copy
* multi-threads callbacks

### How to build:

```
mkdir out
cd out
source  ../build/envs/envsetup_mt5507.sh  #only work on mt5507 now
cmake ..
make
```

### Usage of sidl
```
python tools/sidl/sidl.py xxx.sidl
# see sampleTest and structTest for sidl details, only limited return type and paramters are supported.
```

### Make a test environment
See [Make a test environment](tools/aarch64_qemu/make_a_test_environment.md)

Note: this environment doesn`t include 32-bit libs, so please use static link.
Further more, the shell will not give an error like exec file not found instand of so not found.



### Code From:

The source code of binder are copied from AOSP

https://android.googlesource.com/android-5.1.0_r1

kernel module
https://android.googlesource.com/kernel/common/+/android-3.10 e48e8c45

### Run on 64 bit kernel
Support communicate between both 32bit and 64bit app process now.


### TODO List:

 * removing bionic in this branch!       OK
 * Run on 64bits platform				 OK
