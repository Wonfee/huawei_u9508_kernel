CROSS_TOOL_CHAIN=/home/wonfee/environment/android-kitkat/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin
export PATH=$PATH:$CROSS_TOOL_CHAIN
export CROSS_COMPILE=arm-linux-androideabi-
export ARCH=arm
if [ "$1" ] && [ "$1" == "distclean" ]
then
    make distclean
else
    make hisi_k3v2oem1_defconfig
    make zImage
fi

