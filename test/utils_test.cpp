#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "utils.h"
#include "test.h"

void UtilsTest::testAddFive() { 
  CPPUNIT_ASSERT (Utils::addFiveForTest(2) == 7);
}

void UtilsTest::testAddThree() { 
  CPPUNIT_ASSERT (Utils::addThree(2) == 5) ;
}

void UtilsTest::testMultiply() {
  int a, b;
  a=3; b=2;
  CPPUNIT_ASSERT (Utils::multiply(a,b)==6);
}