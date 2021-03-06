// -*- C++ -*- Time-stamp: <2012-05-28 15:14:51 ptr>

/*
 * Copyright (c) 2011
 * Petr Ovtchenkov
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */

#ifndef __TEST_ATOMIC_TEST_H
#define __TEST_ATOMIC_TEST_H

#define __FIT_EXAM

#include <exam/suite.h>

class atomic_test
{
  public:
  // int EXAM_DECL(align);
    int EXAM_DECL(atomic_int);
};

#endif // __TEST_ATOMIC_TEST_H
