# 编译参数
INCLUDE_FILES: list[str] = []
INCLUDE_FILES_C: list[str] = []
INCLUDE_FILES_CPP: list[str] = []

INCLUDE_DIRS: list[str] = []
INCLUDE_DIRS_C: list[str] = []
INCLUDE_DIRS_CPP: list[str] = []

LIB_DIRS: list[str] = []

COMPILE_FLAGS_POSTFIX = ''
LINK_FLAGS_POSTFIX = ''

COMPILE_FLAGS = ''
COMPILE_FLAGS_C = ''
COMPILE_FLAGS_CPP = ''
COMPILE_FLAGS_ASM = ''
COMPILE_FLAGS_NASM = ''

FLAGS_OVERWRITE_C = False
FLAGS_OVERWRITE_CPP = False
FLAGS_OVERWRITE_ASM = False
FLAGS_OVERWRITE_NASM = True

LINK_FLAGS = ''

# 每个文件不同的常量
DIR = None
FILE = None

FLAGS = {
    'COMPILE_FLAGS': '',
    'COMPILE_FLAGS_C': '',
    'COMPILE_FLAGS_CPP': '',
    'LINK_FLAGS': '',
    'LINKER': '',
    'AR': '',
}
