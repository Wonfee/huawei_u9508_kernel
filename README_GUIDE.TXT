This is from huawei official release, 华为荣耀四核开源代码(U9508,IcecreamSandwich,kernel-3.0.8,中国区).tar.gz
=====================================================================================================================
1. How to Build
    - get Toolchain
        From android git server , codesourcery and etc ..
         - arm-linux-androideabi-4.6

    - set cross compile tool chain and arch
        EX)   
            CROSS_COMPILE_PATH=~/environment/android-kitkat/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin
            export PATH=$PATH:$CROSS_COMPILE_PATH
            export CROSS_COMPILE=arm-linux-androideabi-
            export ARCH=arm
    - build
        $ make hisi_k3v2oem1_defconfig
        $ make zImage

2. Output files
    - Kernel : arch/arm/boot/zImage
    - module : drivers/*/*.ko

3. How to Clean
        $ make distclean
======================================================================================================================
