/***********************************************************
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 *
 *  Last modified by: Darren Green on 11/15/2015
 ***********************************************************/
       
#include <cs50.h>
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  forward declaration of function dac() - "Divide and Conquer"
bool dac(int value_1, int values_1[], int n_1);

//  Returns true if value is in array of n values, else false.
//  ***REQUIRES SORTED ELEMENTS IN values[]  
bool search(int value, int values[], int n)
{
    //  Return false immediately if n is negative
    if (n < 0)
    {
        return false;
    }
    
    return dac(value, values, n);
}

//  forward declaration of function swap
void swap(int* x, int* y);

//  Sorts an array of n values
void sort(int values[], int n)
{
    /************************************************************************************   
    *  Bubble Sort - an inefficient sorting algorithm with O(n^2)
    *  Whenever a value goes all the way to the right, start the iteration over again
    *************************************************************************************/
    
    //  check if everything is in order, if not, swap and invoke recursion
    for (int i = 0; i < n; i++)
    {
        if (values[i] > values[i + 1])
        {
            //  swap the values and try again
            swap(&values[i], &values[i + 1]);
            
            //  recursion - loop until everything is in order
            sort(values, n);
        }        
    }
    
    //  once everything is finally sorted:
    return;
}

//  define function swap
void swap(int* x, int* y)
{        
    int tmp = *y;
    *y = *x;
    *x = tmp;
}

//  define function dac()
bool dac(int value_1, int values_1[], int n_1)
{
    //  set the halfway point
    int half = (n_1 / 2);
    
    //  begin binary search
    
    //  if "find it in one guess"
    if (values_1[n_1] == value_1)
    {        
        return true;
    }
    
    //  if "find it in the middle"
    if (value_1 == values_1[half])
    {
        return true;
    }
    
    //  else divide in half
    if (value_1 < values_1[half])
    {
        //  search the left half until found starting at the halfway of the halfway point
        int half_1 = (half + (half / 2));
        dac(value_1, values_1, half_1);
    }
    else
    {
        //  search the right half until found
        for (int i = half; i < n_1; i++)
        {
            if (values_1[i] == value_1)
            {
                return true;
            }
            else
            {
                if (i == 0)
                {
                    //  if it can't find the value in the sorted half, then element doesn't exist in the set
                    return false;
                }
            }
        } 
    }
    return false;    
}
