// -*- C++ -*- Time-stamp: <10/06/02 15:17:35 ptr>

/*
 * Copyright (c) 2007-2009
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
 */

#include <exam/logger.h>
#include <iostream>
#include <cmath>

namespace exam {

using namespace std;
// using namespace std::tr2;

int base_logger::flags() const
{
  return _flags;
}

bool base_logger::is_trace() const
{
  return (_flags & trace) != 0;
}

int base_logger::flags( int f )
{
  int tmp = _flags;
  _flags = f;
  if ( (f & silent) != 0 ) {
    _flags &= ~trace_suite;
  }
  return tmp;
}

void trivial_logger::report( const char* place, bool cnd, const char* expr )
{
  if ( (cnd && ((_flags & trace) == 0)) || ((_flags & silent) != 0) ) {
    return;
  }

  if ( s != 0 ) {
    *s << place << ": " << (cnd ? "pass" : "fail" ) << ": " << expr
       << std::endl;
  } else {
    fprintf( f, "%s: %s: %s\n", place, (cnd ? "pass" : "fail" ), expr );
  }
}

void trivial_logger::begin_ts()
{
  if ( (_flags & trace_suite) == 0 ) {
    return;
  }

  if ( s != 0 ) {
    *s << "== Begin test suite\n";
  } else {
    fprintf( f, "== Begin test suite\n" );
  }
}

void trivial_logger::end_ts()
{
  if ( (_flags & trace_suite) == 0 ) {
    return;
  }

  if ( *s ) {
    *s << "==  End test suite\n";
  } else {
    fprintf( f, "==  End test suite\n" );
  }
}

void trivial_logger::result( const base_logger::stat& _stat, const string& suite_name )
{
  if ( s != 0 ) {
    *s << "*** " << (_stat.failed != 0 ? "FAIL " : "PASS " ) << suite_name
       << " (+" << _stat.passed
       <<   "-" << _stat.failed
       <<   "~" << _stat.skipped << "/" << _stat.total << ") ***" << endl;
  } else {
    fprintf( f, "*** %s (+%d-%d~%d/%d) ***\n", (_stat.failed != 0 ? "FAIL" : "PASS" ), _stat.passed, _stat.failed, _stat.skipped, _stat.total );
  }
}

void trivial_logger::tc( base_logger::tc_result r, const std::string& name )
{
  if ( ((_flags & silent) != 0) || ((r == pass) && ((_flags & verbose) == 0) )) {
    return;
  }

  static const char *m[] = { "  PASS ", "  FAIL ", "  SKIP ", "  DRY " };
  const char *rs = "";

  switch ( r )
  {
    case pass:
      rs = m[0];
      break;
    case fail:
      rs = m[1];
      break;
    case skip:
      rs = m[2];
      break;
    case dry:
      rs = m[3];
      break;
  }

  if ( s != 0 ) {
    *s << rs << name << endl;
  } else {
    fprintf( f, "%s%s\n", rs, name.c_str() );
  }
}

void trivial_logger::tc( base_logger::tc_result r, const std::string& name, int indent )
{
  if ( ((_flags & silent) != 0) || ((r == pass) && ((_flags & verbose) == 0) )) {
    return;
  }

  if ( s != 0 ) {
    while ( indent-- > 0 ) {
      *s << "  ";
    }
  } else {
    while ( indent-- > 0 ) {
      fprintf( f, "  " );
    }
  }

  tc( r, name );
}

#if 0
void trivial_time_logger::tc_pre()
{
  tst.push_back( get_system_time().nanoseconds_since_epoch() );
}

void trivial_time_logger::tc_post()
{
  tst.back() = get_system_time().nanoseconds_since_epoch() - tst.back();
}

void trivial_time_logger::tc_break()
{
  tst.pop_back();
}

void trivial_time_logger::tc( base_logger::tc_result r, const std::string& name )
{
  if ( r == pass ) {
    // here tst.size() > 0, if test case not throw excepion 
    time_container_t::const_iterator a = tst.begin();
    if ( a != tst.end() ) {
      unsigned n = 1;
      double sum(a->count());
      sum *= 1.0e-9;
      double sum_sq = sum * sum;
      ++a;
      for ( ; a != tst.end(); ++a ) {
        double v(a->count());
        v *= 1.0e-9;
        sum += v;
        sum_sq += v * v;
        // mean = ((n + 1) * mean + static_cast<double>(*a)) / (n + 2);
        ++n;
      }
      sum /= n;              // mean
      sum_sq /= n;      
      sum_sq -= sum * sum;   // dispersion
      sum_sq = max( 0.0, sum_sq ); // clear epsilon (round error)
      sum_sq = sqrt(sum_sq); // mean square deviation
      if ( s != 0 ) {
        *s << "  " << sum << " " << sum_sq << " " << name << endl;
      } else {
        fprintf( f, "  %f %f %s\n", sum, sum_sq, name.c_str() );
      }
    }
  }
  tst.clear();
  trivial_logger::tc( r, name );
}

void trivial_time_logger::tc( base_logger::tc_result r, const std::string& name, int indent )
{
  if ( r == pass ) {
    // here tst.size() > 0, if test case not throw excepion
    time_container_t::const_iterator a = tst.begin();
    if ( a != tst.end() ) {
      unsigned n = 1;
      double sum(a->count());
      sum *= 1.0e-9;
      double sum_sq = sum * sum;
      ++a;
      for ( ; a != tst.end(); ++a ) {
        double v(a->count());
        v *= 1.0e-9;
        sum += v;
        sum_sq += v * v;
        // mean = ((n + 1) * mean + static_cast<double>(*a)) / (n + 2);
        ++n;
      }
      sum /= n;              // mean
      sum_sq /= n;      
      sum_sq -= sum * sum;   // dispersion
      sum_sq = max( 0.0, sum_sq ); // clear epsilon (round error)
      sum_sq = sqrt(sum_sq); // mean square deviation
      if ( s != 0 ) {
        *s << "  " << sum << " " << sum_sq << " " << name << endl;
      } else {
        fprintf( f, "  %f %f %s\n", sum, sum_sq, name.c_str() );
      }
    }
  }
  tst.clear();
  trivial_logger::tc( r, name, indent );
}
#endif

} //namespace exam
