/*
Copyright (c) 2015, Los Alamos National Security, LLC
All rights reserved.

Copyright 2015. Los Alamos National Security, LLC. This software was
produced under U.S. Government contract DE-AC52-06NA25396 for Los
Alamos National Laboratory (LANL), which is operated by Los Alamos
National Security, LLC for the U.S. Department of Energy. The
U.S. Government has rights to use, reproduce, and distribute this
software.  NEITHER THE GOVERNMENT NOR LOS ALAMOS NATIONAL SECURITY,
LLC MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LIABILITY
FOR THE USE OF THIS SOFTWARE.  If software is modified to produce
derivative works, such modified software should be clearly marked, so
as not to confuse it with the version available from LANL.

Additionally, redistribution and use in source and binary forms, with
or without modification, are permitted provided that the following
conditions are met:

• Redistributions of source code must retain the above copyright
         notice, this list of conditions and the following disclaimer.

• Redistributions in binary form must reproduce the above copyright
         notice, this list of conditions and the following disclaimer
         in the documentation and/or other materials provided with the
         distribution.

• Neither the name of Los Alamos National Security, LLC, Los Alamos
         National Laboratory, LANL, the U.S. Government, nor the names
         of its contributors may be used to endorse or promote
         products derived from this software without specific prior
         written permission.

THIS SOFTWARE IS PROVIDED BY LOS ALAMOS NATIONAL SECURITY, LLC AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL LOS
ALAMOS NATIONAL SECURITY, LLC OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

/*
 *****************************************************************************
//
// AUTHOR:  Heather Quinn
// CONTACT INFO:  hquinn at lanl dot gov
// LAST EDITED: 12/21/15
//
// tiva_qsort.c
//
// This test is a simple program for testing quicksort.  The data are randomly
// generated and placed in an array.  The inputs change every few seconds in a 
// repeatable pattern.  The test is designed to test whether sorting many numbers
// cause more errors than sorting an already sorted array.  To that end, the
// test sorts an array two times in a row in the forward direction, followed by two
// times in the reverse direction.  The qsort code that we used can be found here:
//
// http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
//
// The user will need to create the reverse sort on their own.
//
// This software is otimized for microcontrollers.  In particular, it was designed
// for the Texas Instruments MSP430F2619.

// The output is designed to go out the UART at a speed of 9,600 baud and uses a tiny
// print to reduce the printf footprint.  The tiny printf can be downloaded from 
// http://www.43oh.com/forum/viewtopic.php?f=10&t=1732  All of the output is YAML
// parsable.
//
 *****************************************************************************/


#define		array_elements				100
#define USE_MIPS 0

#if USE_MIPS == 1
typedef unsigned int uint32_t;
#else
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#endif

uint32_t array[array_elements] =  {
35645,20955,3231,55398,11191,7730,41421,52573,46468,4465,20791,64790,59818,42394,12807,36702,28255,17195,64055,15204,12488,45439,10215,52185,12464,30711,11892,54818,28299,29363,22002,49795,22456,902,35184,15203,63758,15260,33098,23603,21955,36488,47811,37492,10543,54691,65041,15221,46103,30124,39873,44597,19337,8073,37064,18154,52271,22762,34221,22404,47261,23884,11334,51391,33644,16099,56043,43675,45216,65056,60299,6454,14491,19823,52388,11627,54304,45438,53688,45765,54214,41497,13024,20123,52929,5390,26269,61925,51,20875,36864,7382,21014,11733,936,14594,46582,22146,37379,2875};

uint32_t golden_array[array_elements] =  {
51,902,936,2875,3231,4465,5390,6454,7382,7730,8073,10215,10543,11191,11334,11627,11733,11892,12464,12488,12807,13024,14491,14594,15203,15204,15221,15260,16099,17195,18154,19337,19823,20123,20791,20875,20955,21014,21955,22002,22146,22404,22456,22762,23603,23884,26269,28255,28299,29363,30124,30711,33098,33644,34221,35184,35645,36488,36702,36864,37064,37379,37492,39873,41421,41497,42394,43675,44597,45216,45438,45439,45765,46103,46468,46582,47261,47811,49795,51391,52185,52271,52388,52573,52929,53688,54214,54304,54691,54818,55398,56043,59818,60299,61925,63758,64055,64790,65041,65056};

uint32_t golden_array_rev[array_elements] =  {
65056,65041,64790,64055,63758,61925,60299,59818,56043,55398,54818,54691,54304,54214,53688,52929,52573,52388,52271,52185,51391,49795,47811,47261,46582,46468,46103,45765,45439,45438,45216,44597,43675,42394,41497,41421,39873,37492,37379,37064,36864,36702,36488,35645,35184,34221,33644,33098,30711,30124,29363,28299,28255,26269,23884,23603,22762,22456,22404,22146,22002,21955,21014,20955,20875,20791,20123,19823,19337,18154,17195,16099,15260,15221,15204,15203,14594,14491,13024,12807,12488,12464,11892,11733,11627,11334,11191,10543,10215,8073,7730,7382,6454,5390,4465,3231,2875,936,902,51};




//*****************************************************************************
//
// Quick sort code from http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
//
//*****************************************************************************

void quick_sort (uint32_t *A, int len) {   
    //TODO: user enters code
    if (len < 2) return;
    
    uint32_t pivot = (A[len / 2] & 0xffff);
    
    int i, j;
    for (i = 0, j = len - 1; ; i++, j--) {
        while ((A[i] & 0xffff) < (pivot)) i++;
        while ((A[j] & 0xffff) > (pivot)) j--;
        
        if (i >= j) break;
        
        int temp = A[i] & 0xffff;
        A[i]     = A[j] & 0xffff;
        A[j]     = temp;
    }
    
    quick_sort(A, i);
    quick_sort(A + i, len - i);
}

void quick_sort_rev (uint32_t *A, int len) {
  //TODO: user enters code
    if (len < 2) return;
    
    uint32_t pivot = (A[len / 2] & 0xffff);
    
    int i, j;
    for (i = 0, j = len - 1; ; i++, j--) {
        while ((A[i] & 0xffff) > pivot) i++;
        while ((A[j] & 0xffff) < pivot) j--;
        
        if (i >= j) break;
        
        int temp = A[i] & 0xffff;
        A[i]     = A[j] & 0xffff;
        A[j]     = temp;
    }
    
    quick_sort_rev(A, i);
    quick_sort_rev(A + i, len - i);
}

int checker(uint32_t golden_array[], uint32_t dut_array[]) {
  int num_of_errors = 0;
  int i = 0;

  for(i=0; i<array_elements; i++) {
    if (golden_array[i] != dut_array[i]) {
#if USE_MIPS == 1
        asm volatile ("move $a0, %0\n"   /* Move 'idx' into $a0 */
                      "li $v0, 1\n"      /* Set for 'PRINT_INT' syscall */
                      "syscall" : : "r" (i));
        asm volatile ("move $a0, %0\n"   /* Move 'dut' into $a0 */
                      "li $v0, 1\n"      /* Set for 'PRINT_INT' syscall */
                      "syscall" : : "r" (dut_array[i]));
        asm volatile ("move $a0, %0\n"   /* Move 'gold' into $a0 */
                      "li $v0, 1\n"      /* Set for 'PRINT_INT' syscall */
                      "syscall" : : "r" (golden_array[i]));
#else
        printf("   E: {%i: [%x, %x]\n", i, golden_array[i], dut_array[i]);
#endif        
        num_of_errors++;
    }
  }
  
  return num_of_errors;
}

void qsort_test() {
  //initialize variables
  int errors = 0;
  int n = sizeof array / sizeof array[0];
  int i = 0;
  
  //compute the goldens for the forward and reverse sorts.
  quick_sort(golden_array, n);
  quick_sort_rev(golden_array_rev, n);
  
  for (i = 0; i < 4; i++) {
      //the first two sorts are forward
      if (i < 2) {
          quick_sort(array, n);
          errors += checker(golden_array, array);
      }
      else {
          //the last two sorts are reverse
          quick_sort_rev(array, n);
          errors += checker(golden_array_rev, array);
      }      
  }

#if USE_MIPS == 1
  asm volatile ("move $a0, %0\n"   /* Move 'num_erors' into $a0 */
                "li $v0, 1\n"      /* Set for 'PRINT_INT' syscall */
                "syscall" : : "r" (errors));
#else
  printf("Local Errors: %d\n", errors);
#endif
}

int main()
{
  //start the test
  qsort_test();

  return 0;

}


