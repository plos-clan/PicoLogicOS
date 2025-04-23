#pragma once

static __attr(address_space(256)) struct {
  i32   id;
  i32   apic_id;
  usize sp;
} *const cpu = (__attr(address_space(256)) void *)0;
