﻿/************************************************************************
 Program:       Numeric Overflow Activity
 Author:        Randall Rowland (https://github.com/rowland007)
 Class:         CS-405-T2676 Secure Coding 21EW2
 Instructor:    Mr. Trevor Hodde
 Date:          2021-10-25
 Description:   Assignment presents code that is designed to show the two functions operating with and without overflow or underflows
 Input:
 Output:
 Known bugs:
 Missing features:
    The source code has been commented with TODOs to explain the detailed rules you must follow.
    There are comments that mark code that must be changed.
    There may be more than one way to solve this problem, so be sure to demonstrate that you can detect an underflow or overflow, prevent it, and communicate it back to the calling function.
    Remember to leverage capabilities provided by the standard C++ library to help you achieve success. 

 License:           GNU General Public License v3.0
 Modifications:
   Date                      Comment
 ---------   ------------------------------------------------
 2021OCT25   Add exception header
 2021OCT26   Add under/over flow logic to add_/subtract_numbers
 ************************************************************************/
// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits
#include <exception>

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>
template <typename T>
T add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
  T result = start;
  T *temp = new T;

  for (unsigned long int i = 0; i < steps; ++i)
  {
      try {
          *temp = result + increment;
          if (result > 0 && increment > 0 && *temp < 0) // Detects overflow of negative result with the sum of two positive arguments
          {
              throw std::overflow_error("Overflow detected, last good value: ");
          }
          if (result < 0 && increment < 0 && *temp > 0) // Detects overflow of positive result with the sume of two negative arguments
          {
              throw std::overflow_error("Overflow detected, last good value: ");
          }
          if (*temp <= result)                          // Detects wrap around of unsigned arguments 
          {
              throw std::overflow_error("Overflow detected, last good value: "); 
          }
          result += increment;
      }
      catch (const std::exception& e) {
          std::cerr << e.what();
          delete temp;
      }
  }
  return result;
}

/// <summary>
/// Template function to abstract away the logic of:
///   start - (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (increment * steps)</returns>

template <typename T>
T subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    T result = start;
    T* temp = new T;

    for (unsigned long int i = 0; i < steps; ++i)
    {
        try {
            *temp = result - decrement;
            if (result > 0 && decrement > 0 && *temp < 0) // Detects underflow of negative result with two positive arguments
            {
                throw std::underflow_error("Underflow detected, last good value: ");
            }
            if (result < 0 && decrement < 0 && *temp > 0) // Detects underflow of positive result with two negative arguments
            {
                throw std::underflow_error("Underflow detected, last good value: ");
            }
            if (*temp >= result)                          // Detects wrap around of unsigned arguments 
            {
                throw std::underflow_error("Underflow detected, last good value: ");
            }
            result -= decrement;
        }
        catch (const std::exception& e) {
            std::cerr << e.what();
            delete temp;
        }
    }
    return result;
}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
  //        The add_numbers template function will overflow in the second method call
  //        You need to change the add_numbers method to:
  //        ✔️1. Detect when an overflow will happen
  //        ✔️2. Prevent it from happening
  //        ✔️3. Return the correct value when no overflow happened or
  //        ✔️4. Return something to tell test_overflow the addition failed
  //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
  //
  //        You need to change the test_overflow method to:
  //        ✔️1. Detect when an add_numbers failed
  //        ✔️2. Inform the user the overflow happened
  //        ✔️3. A successful result displays the same result as before you changed the method
  //        NOTE: You cannot change anything between START / END DO NOT CHANGE
  //              The test_overflow method must remain a template in the NumericOverflows source file
  //
  //  There are more than one possible solution to this problem. 
  //  The solution must work for all of the data types used to call test_overflow() in main().

  // START DO NOT CHANGE
  //  how many times will we iterate
  const unsigned long int steps = 5;
  // how much will we add each step (result should be: start + (increment * steps))
  const T increment = std::numeric_limits<T>::max() / steps;
  // whats our starting point
  const T start = 0;

  std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
  // END DO NOT CHANGE

  std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
  std::cout << +add_numbers<T>(start, increment, steps) << std::endl;

  std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
  try {
      std::cout << +add_numbers<T>(start, increment, steps + 1) << std::endl;
  }
  catch (const std::overflow_error& e) {
      std::cerr << e.what() << std::endl;
  }
  catch (const std::exception& e) {
      std::cerr << e.what() << std::endl << std::endl;
  }
}

template <typename T>
void test_underflow()
{
  //        The subtract_numbers template function will underflow in the second method call
  //        You need to change the subtract_numbers method to:
  //        ✔️1. Detect when an underflow will happen
  //        ✔️2. Prevent it from happening
  //        ✔️3. Return the correct value when no underflow happened or
  //        ✔️4. Return something to tell test_underflow the subtraction failed
  //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
  //
  //        You need to change the test_underflow method to:
  //        ✔️1. Detect when an subtract_numbers failed
  //        ✔️2. Inform the user the underflow happened
  //        ✔️3. A successful result displays the same result as before you changed the method
  //        NOTE: You cannot change anything between START / END DO NOT CHANGE
  //              The test_underflow method must remain a template in the NumericOverflows source file
  //
  //  There are more than one possible solution to this problem. 
  //  The solution must work for all of the data types used to call test_overflow() in main().

  // START DO NOT CHANGE
  //  how many times will we iterate
  const unsigned long int steps = 5;
  // how much will we subtract each step (result should be: start - (increment * steps))
  const T decrement = std::numeric_limits<T>::max() / steps;
  // whats our starting point
  const T start = std::numeric_limits<T>::max();

  std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
  // END DO NOT CHANGE

  std::cout << "\tSubtracting Numbers Without Overflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
  auto result = subtract_numbers<T>(start, decrement, steps);
  std::cout << +result << std::endl;

  std::cout << "\tSubtracting Numbers With Overflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = ";
  result = subtract_numbers<T>(start, decrement, steps + 1);
  std::cout << +result << std::endl << std::endl;
}

void do_overflow_tests(const std::string& star_line)
{
  std::cout << std::endl << star_line << std::endl;
  std::cout << "*** Running Overflow Tests ***" << std::endl;
  std::cout << star_line << std::endl;

  // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
  // signed integers
  test_overflow<char>();
  test_overflow<wchar_t>();
  test_overflow<short int>();
  test_overflow<int>();
  test_overflow<long>();
  test_overflow<long long>();

  // unsigned integers
  test_overflow<unsigned char>();
  test_overflow<unsigned short int>();
  test_overflow<unsigned int>();
  test_overflow<unsigned long>();
  test_overflow<unsigned long long>();

  // real numbers
  test_overflow<float>();
  test_overflow<double>();
  test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
  std::cout << std::endl << star_line << std::endl;
  std::cout << "*** Running Undeflow Tests ***" << std::endl;
  std::cout << star_line << std::endl;

  // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
  // signed integers
  test_underflow<char>();
  test_underflow<wchar_t>();
  test_underflow<short int>();
  test_underflow<int>();
  test_underflow<long>();
  test_underflow<long long>();

  // unsigned integers
  test_underflow<unsigned char>();
  test_underflow<unsigned short int>();
  test_underflow<unsigned int>();
  test_underflow<unsigned long>();
  test_underflow<unsigned long long>();

  // real numbers
  test_underflow<float>();
  test_underflow<double>();
  test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
  //  create a string of "*" to use in the console
  const std::string star_line = std::string(50, '*');

  std::cout << "Starting Numeric Underflow / Overflow Tests!" << std::endl;

  // run the overflow tests
  do_overflow_tests(star_line);

  // run the underflow tests
  do_underflow_tests(star_line);

  std::cout << std::endl << "All Numeric Underflow / Overflow Tests Complete!" << std::endl;

  return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu