#[repr(i32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum SoundFmt {
    Unknown = -1,
    // 8bit / 1byte
    S8,
    U8,
    // 16bit / 2byte
    S16L,
    S16B,
    U16L,
    U16B,
    // 24bit / 3byte
    S24L,
    S24B,
    U24L,
    U24B,
    // 24bit / 4byte (low 3byte)
    S24L32,
    S24B32,
    U24L32,
    U24B32,
    // 32bit / 4byte
    S32L,
    S32B,
    U32L,
    U32B,
    // 64bit / 8byte
    S64L,
    S64B,
    U64L,
    U64B,
    // 16bit / 2byte <- float
    F16L,
    F16B,
    // 32bit / 4byte <- float
    F32L,
    F32B,
    // 64bit / 8byte <- float
    F64L,
    F64B,
    // 8bit / 1byte <- Mu-Law
    MuLaw,
    // 8bit / 1byte <- A-Law
    ALaw,
    // 4bit / 0.5byte <- Ima-ADPCM
    ImaAdpcm,
    // 计数
    Count,
    // 按通道存储 (如果是就给 fmt 加上此值)
    Plane = 32,
}

impl SoundFmt {
    #[cfg(target_endian = "little")]
    pub const S16: Self = Self::S16L;
    #[cfg(target_endian = "little")]
    pub const U16: Self = Self::U16L;
    #[cfg(target_endian = "little")]
    pub const S24: Self = Self::S24L;
    #[cfg(target_endian = "little")]
    pub const U24: Self = Self::U24L;
    #[cfg(target_endian = "little")]
    pub const S24_32: Self = Self::S24L32;
    #[cfg(target_endian = "little")]
    pub const U24_32: Self = Self::U24L32;
    #[cfg(target_endian = "little")]
    pub const S32: Self = Self::S32L;
    #[cfg(target_endian = "little")]
    pub const U32: Self = Self::U32L;
    #[cfg(target_endian = "little")]
    pub const S64: Self = Self::S64L;
    #[cfg(target_endian = "little")]
    pub const U64: Self = Self::U64L;
    #[cfg(target_endian = "little")]
    pub const F16: Self = Self::F16L;
    #[cfg(target_endian = "little")]
    pub const F32: Self = Self::F32L;
    #[cfg(target_endian = "little")]
    pub const F64: Self = Self::F64L;

    #[cfg(target_endian = "big")]
    pub const S16: Self = Self::S16B;
    #[cfg(target_endian = "big")]
    pub const U16: Self = Self::U16B;
    #[cfg(target_endian = "big")]
    pub const S24: Self = Self::S24B;
    #[cfg(target_endian = "big")]
    pub const U24: Self = Self::U24B;
    #[cfg(target_endian = "big")]
    pub const S24_32: Self = Self::S24B32;
    #[cfg(target_endian = "big")]
    pub const U24_32: Self = Self::U24B32;
    #[cfg(target_endian = "big")]
    pub const S32: Self = Self::S32B;
    #[cfg(target_endian = "big")]
    pub const U32: Self = Self::U32B;
    #[cfg(target_endian = "big")]
    pub const S64: Self = Self::S64B;
    #[cfg(target_endian = "big")]
    pub const U64: Self = Self::U64B;
    #[cfg(target_endian = "big")]
    pub const F16: Self = Self::F16B;
    #[cfg(target_endian = "big")]
    pub const F32: Self = Self::F32B;
    #[cfg(target_endian = "big")]
    pub const F64: Self = Self::F64B;

    /// 检查格式是否为有符号数
    pub fn is_signed(&self) -> bool {
        matches!(
            self,
            Self::S8
                | Self::S16L
                | Self::S16B
                | Self::S24L
                | Self::S24B
                | Self::S24L32
                | Self::S24B32
                | Self::S32L
                | Self::S32B
                | Self::S64L
                | Self::S64B
        )
    }

    /// 检查格式是否为浮点数
    pub fn is_float(&self) -> bool {
        matches!(
            self,
            Self::F16L | Self::F16B | Self::F32L | Self::F32B | Self::F64L | Self::F64B
        )
    }

    /// 检查格式是否为大端序
    pub fn is_big_endian(&self) -> bool {
        matches!(
            self,
            Self::S16B
                | Self::U16B
                | Self::S24B
                | Self::U24B
                | Self::S24B32
                | Self::U24B32
                | Self::S32B
                | Self::U32B
                | Self::S64B
                | Self::U64B
                | Self::F16B
                | Self::F32B
                | Self::F64B
        )
    }

    /// 返回每个样本的字节数
    pub fn bytes(&self) -> usize {
        match self {
            Self::S8 | Self::U8 | Self::MuLaw | Self::ALaw => 1,
            Self::S16L | Self::S16B | Self::U16L | Self::U16B | Self::F16L | Self::F16B => 2,
            Self::S24L | Self::S24B | Self::U24L | Self::U24B => 3,
            Self::S24L32
            | Self::S24B32
            | Self::U24L32
            | Self::U24B32
            | Self::S32L
            | Self::S32B
            | Self::U32L
            | Self::U32B
            | Self::F32L
            | Self::F32B => 4,
            Self::S64L | Self::S64B | Self::U64L | Self::U64B | Self::F64L | Self::F64B => 8,
            Self::ImaAdpcm => 0, // 每个样本0.5字节
            _ => 0,
        }
    }
}
