#pragma once
#include <define.h>

namespace cpp::unit {

#define ISOUNIT(_t_, _u_, ...)                                                                     \
  enum class _t_ : byte {                                                                          \
    Q##_u_,                                                                                        \
    R##_u_,                                                                                        \
    Y##_u_,                                                                                        \
    Z##_u_,                                                                                        \
    E##_u_,                                                                                        \
    P##_u_,                                                                                        \
    T##_u_,                                                                                        \
    G##_u_,                                                                                        \
    M##_u_,                                                                                        \
    k##_u_,                                                                                        \
    h##_u_,                                                                                        \
    da##_u_,                                                                                       \
    _u_,                                                                                           \
    d##_u_,                                                                                        \
    c##_u_,                                                                                        \
    m##_u_,                                                                                        \
    u##_u_,                                                                                        \
    n##_u_,                                                                                        \
    p##_u_,                                                                                        \
    f##_u_,                                                                                        \
    a##_u_,                                                                                        \
    z##_u_,                                                                                        \
    y##_u_,                                                                                        \
    r##_u_,                                                                                        \
    q##_u_,                                                                                        \
    ##__VA_ARGS__,                                                                                 \
  };                                                                                               \
  using enum _t_;

#define IEEEUNIT(_t_, _u_, ...)                                                                    \
  enum class _t_ : byte {                                                                          \
    Yi##_u_,                                                                                       \
    Zi##_u_,                                                                                       \
    Ei##_u_,                                                                                       \
    Pi##_u_,                                                                                       \
    Ti##_u_,                                                                                       \
    Gi##_u_,                                                                                       \
    Mi##_u_,                                                                                       \
    Ki##_u_,                                                                                       \
    ##__VA_ARGS__,                                                                                 \
  };                                                                                               \
  using enum _t_;

ISOUNIT(Time, s);
ISOUNIT(Length, m);
ISOUNIT(Mass, g, t);
ISOUNIT(Temperature, K);
ISOUNIT(Current, A);
ISOUNIT(LuminousIntensity, cd);
ISOUNIT(AmountOfSubstance, mol);
ISOUNIT(Angle, rad);
ISOUNIT(Energy, J);
ISOUNIT(Frequency, Hz);
ISOUNIT(Force, N);
ISOUNIT(Pressure, Pa);
ISOUNIT(Power, W);
ISOUNIT(Voltage, V);
ISOUNIT(Capacitance, F);
ISOUNIT(Resistance, Ohm);
ISOUNIT(Conductance, S);
ISOUNIT(MagneticFlux, Wb);
ISOUNIT(MagneticFluxDensity, T);
ISOUNIT(Inductance, H);
ISOUNIT(LuminousFlux, lm);
ISOUNIT(Illuminance, lx);

IEEEUNIT(Data, B, Byte);

#undef ISOUNIT
#undef IEEEUNIT

} // namespace cpp::unit

namespace cpp {

class Size {
private:
  usize bytes = 0;

public:
  Size() = default;

  constexpr Size(u64 size, unit::Data u) {
    switch (u) {
    case unit::Byte: bytes = size; break;
    case unit::KiB: bytes = size * 1024; break;
    case unit::MiB: bytes = size * 1024 * 1024; break;
    case unit::GiB: bytes = size * 1024 * 1024 * 1024; break;
    case unit::TiB: bytes = size * 1024 * 1024 * 1024 * 1024; break;
    }
  }

  [[nodiscard]] constexpr auto in(unit::Data u) const -> u64 {
    switch (u) {
    case unit::Byte: return bytes;
    case unit::KiB: return bytes / 1024;
    case unit::MiB: return bytes / ((u64)1024 * 1024);
    case unit::GiB: return bytes / ((u64)1024 * 1024 * 1024);
    case unit::TiB: return bytes / ((u64)1024 * 1024 * 1024 * 1024);
    }
    return 0;
  }
};

} // namespace cpp
