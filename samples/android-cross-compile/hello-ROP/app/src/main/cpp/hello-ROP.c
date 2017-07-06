/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#define DEBUG 1
//#define DEBUG 0
#include "../../../../../../../addr-info.h"
#define  LOG_TAG    "hello-ROP"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define fprintf_ LOGD
#define LIB "/system/lib/libc.so"
#include <android/log.h>

// If you want you can add other log definition for info, warning etc

//system() and exit()
//#define LIB "/system/lib/libc.so"

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   hello-ROP/app/src/main/java/com/example/helloROP/HelloROP.java
 */
JNIEXPORT jstring JNICALL
Java_com_example_hellorop_HelloROP_stringFromJNI( JNIEnv* env,
                                                  jobject thiz )
{
#if defined(__arm__)
    #if defined(__ARM_ARCH_7A__)
    #if defined(__ARM_NEON__)
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a/NEON (hard-float)"
      #else
        #define ABI "armeabi-v7a/NEON"
      #endif
    #else
      #if defined(__ARM_PCS_VFP)
        #define ABI "armeabi-v7a (hard-float)"
      #else
        #define ABI "armeabi-v7a"
      #endif
    #endif
  #else
   #define ABI "armeabi"
  #endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif
/*ARM                       */
//  void (*ptr) (void *);
//  char *bin_sh = "/system/bin/sh";
//  LOGD("DEBUG msg finding func address");
//  ptr = find_func_address ("system", LIB);
//  LOGD("DEBUG msg found func address");
//  LOGD("ptr=%p",ptr);
//  asm ("mov r0, %[bin_sh];" "blx %[ptr]":
//: [ptr] "r" (ptr),[bin_sh] "r" (bin_sh):);
//  LOGD("DEBUG msg finding func address");
//  ptr = find_func_address ("exit", LIB);
//  LOGD("DEBUG msg found func address");
//  sleep(10);
////asm ("movs r0, #0;" "blx %[ptr];":
////: [ptr] "r" (ptr):);
//  //ptr (0);
//  //LOGD("Do not print me\n");
/* ARM                      */


/* x86                      */
  void (*ptr) (void *);
  ptr = find_func_address ("system", LIB);
  char *bin_sh = "/bin/sh";
//asm (".intel_syntax noprefix;" "push %[bin_sh];" "call %[ptr];" ".att_syntax noprefix;":
  asm ("pushl %[bin_sh];" "call %[ptr];" ".att_syntax noprefix;":
: [ptr] "r" (ptr), [bin_sh] "r" (bin_sh):);

  ptr = find_func_address ("exit", LIB);
asm (".intel_syntax noprefix;" "mov eax, %0;" "push 0;" "call eax;" ".att_syntax noprefix;":
: "r" (ptr):"eax");

  //ptr (0);
  printf ("Do not print me\n");
  //return 0;
/* x86                      */



  return (*env)->NewStringUTF(env, "Hello from ROP !  Compiled with ABI " ABI ".");
  //return 0;

}
