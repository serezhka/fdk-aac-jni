package com.github.serezhka.fdkaacjni;

public class FdkAacLib {

    private static boolean aacDecoderInitialized;

    static {
        try {
            System.loadLibrary("libfdk-aac");
            init();
            aacDecoderInitialized = true;
            System.out.println("libfdk-aac initialized!");
        } catch (UnsatisfiedLinkError e) {
            System.err.println("libfdk-aac error: " + e.getMessage());
        }
    }

    private static native void init();

    public static native void decodeFrame(byte[] input, byte[] output);

    public static boolean isInitialized() {
        return aacDecoderInitialized;
    }
}
