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
#define USE_MIPS 1

#if USE_MIPS == 1
typedef unsigned int uint32_t;
#else
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#endif

uint32_t array[array_elements] =  {
2067261,384717275,2017463455,888985702,1138961335,2001411634,1688969677,1074515293,1188541828,2077102449,366694711,1907424534,448260522,541959578,1236480519,328830814,1184067167,2033402667,343865911,475872100,753283272,1015853439,953755623,952814553,168636592,1744271351,669331060,927782434,360607371,529232563,2081904114,1611383427,604985272,1799881606,1155500400,800602979,1749219598,82656156,1927577930,2011454515,828462531,1833275016,1905310403,1423282804,293742895,2019415459,1484062225,1758739317,1166783511,1457288620,598842305,1634250293,528829321,1747066761,407146696,1031620330,1807404079,884168938,1787987373,965105540,584824989,120937804,1082141766,517654719,766608236,1630224099,1580063467,343911067,1234808992,152763936,1260514187,535763254,174078107,858017135,341298340,272379243,1590285344,344306046,1430770104,1578742469,1764217798,901816857,2043818720,1460293275,1705955009,931665166,1193174685,484635109,2004287539,632181131,1466667008,1455103190,375542294,284896725,1518207912,119683330,1473033718,1086215810,270635523,200870715};

uint32_t golden_array[array_elements] =  {
2067261,82656156,119683330,120937804,152763936,168636592,174078107,200870715,270635523,272379243,284896725,293742895,328830814,341298340,343865911,343911067,344306046,360607371,366694711,375542294,384717275,407146696,448260522,475872100,484635109,517654719,528829321,529232563,535763254,541959578,584824989,598842305,604985272,632181131,669331060,753283272,766608236,800602979,828462531,858017135,884168938,888985702,901816857,927782434,931665166,952814553,953755623,965105540,1015853439,1031620330,1074515293,1082141766,1086215810,1138961335,1155500400,1166783511,1184067167,1188541828,1193174685,1234808992,1236480519,1260514187,1423282804,1430770104,1455103190,1457288620,1460293275,1466667008,1473033718,1484062225,1518207912,1578742469,1580063467,1590285344,1611383427,1630224099,1634250293,1688969677,1705955009,1744271351,1747066761,1749219598,1758739317,1764217798,1787987373,1799881606,1807404079,1833275016,1905310403,1907424534,1927577930,2001411634,2004287539,2011454515,2017463455,2019415459,2033402667,2043818720,2077102449,2081904114};

uint32_t golden_array_rev[array_elements] =  {
2081904114,2077102449,2043818720,2033402667,2019415459,2017463455,2011454515,2004287539,2001411634,1927577930,1907424534,1905310403,1833275016,1807404079,1799881606,1787987373,1764217798,1758739317,1749219598,1747066761,1744271351,1705955009,1688969677,1634250293,1630224099,1611383427,1590285344,1580063467,1578742469,1518207912,1484062225,1473033718,1466667008,1460293275,1457288620,1455103190,1430770104,1423282804,1260514187,1236480519,1234808992,1193174685,1188541828,1184067167,1166783511,1155500400,1138961335,1086215810,1082141766,1074515293,1031620330,1015853439,965105540,953755623,952814553,931665166,927782434,901816857,888985702,884168938,858017135,828462531,800602979,766608236,753283272,669331060,632181131,604985272,598842305,584824989,541959578,535763254,529232563,528829321,517654719,484635109,475872100,448260522,407146696,384717275,375542294,366694711,360607371,344306046,343911067,343865911,341298340,328830814,293742895,284896725,272379243,270635523,200870715,174078107,168636592,152763936,120937804,119683330,82656156,2067261};


//*****************************************************************************
//
// Quick sort code from http://rosettacode.org/wiki/Sorting_algorithms/Quicksort#C
//
//*****************************************************************************

void qsort_test(void);

int main()
{
  //start the test
  qsort_test();

  return 0;

}

void quick_sort (uint32_t *A, int len) {   
    //TODO: user enters code
    if (len < 2) return;
    
    int pivot = A[len / 2];
    
    int i, j;
    for (i = 0, j = len - 1; ; i++, j--) {
        while (A[i] < pivot) i++;
        while (A[j] > pivot) j--;
        
        if (i >= j) break;
        
        int temp = A[i];
        A[i]     = A[j];
        A[j]     = temp;
    }
    
    quick_sort(A, i);
    quick_sort(A + i, len - i);
}

void quick_sort_rev (uint32_t *A, int len) {
  //TODO: user enters code
    if (len < 2) return;
    
    int pivot = A[len / 2];
    
    int i, j;
    for (i = 0, j = len - 1; ; i++, j--) {
        while (A[i] > pivot) i++;
        while (A[j] < pivot) j--;
        
        if (i >= j) break;
        
        int temp = A[i];
        A[i]     = A[j];
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


