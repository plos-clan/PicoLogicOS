#pragma once
#include "unit.hpp"
#include <define.h>

namespace cpp {

class Time {
  u64 time_sec  = 0;
  u64 time_nsec = 0;

public:
  Time() = default;

  Time(u64 sec, u64 nsec) : time_sec(sec), time_nsec(nsec) {}

  Time(u64 time, unit::Time u) {
    switch (u) {
    case unit::s:
      time_sec  = time;
      time_nsec = 0;
      break;
    case unit::ms:
      time_sec  = time / 1000;
      time_nsec = (time % 1000) * 1000000;
      break;
    case unit::ns:
      time_sec  = time / 1000000000;
      time_nsec = time % 1000000000;
      break;
    }
  }

  u64 get_sec() const {
    return time_sec;
  }

  u64 get_nsec() const {
    return time_nsec;
  }

  fn in(unit::Time u) const -> u64 {
    switch (u) {
    case unit::s: return time_sec;
    case unit::ms: return time_sec * 1000 + time_nsec / 1000000;
    case unit::ns: return time_sec * 1000000000 + time_nsec;
    }
  }

  Time operator+(const Time &t) const {
    return Time(time_sec + t.time_sec + (time_nsec + t.time_nsec) / 1000000000,
                (time_nsec + t.time_nsec) % 1000000000);
  }

  Time operator-(const Time &t) const {
    return Time(time_sec - t.time_sec - (time_nsec < t.time_nsec),
                time_nsec - t.time_nsec + (time_nsec < t.time_nsec) * 1000000000);
  }

  bool operator<(const Time &t) const {
    return time_sec < t.time_sec || (time_sec == t.time_sec && time_nsec < t.time_nsec);
  }

  bool operator>(const Time &t) const {
    return time_sec > t.time_sec || (time_sec == t.time_sec && time_nsec > t.time_nsec);
  }

  bool operator<=(const Time &t) const {
    return time_sec < t.time_sec || (time_sec == t.time_sec && time_nsec <= t.time_nsec);
  }

  bool operator>=(const Time &t) const {
    return time_sec > t.time_sec || (time_sec == t.time_sec && time_nsec >= t.time_nsec);
  }

  bool operator==(const Time &t) const {
    return time_sec == t.time_sec && time_nsec == t.time_nsec;
  }

  bool operator!=(const Time &t) const {
    return time_sec != t.time_sec || time_nsec != t.time_nsec;

    auto func = [](int, int) { return 1; };
  }
};

} // namespace cpp
