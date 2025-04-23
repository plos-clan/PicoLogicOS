#pragma once
#include <define.h>

/**
 * \brief 将单个 UTF-8 字符转换为 UTF-32 字符
 *        注意该函数会修改传入的指针，使其指向下一个字符
 *
 * \param sp 指向 UTF-8 字符串的指针
 * \return 转换后的 UTF-32 字符
 */
dlimport u32 utf8to32c(cstr8 *sp) __nnull(1);

/**
 * \brief 将 UTF-8 字符串转换为 UTF-32 字符串
 *
 * \param d 指向存储 UTF-32 字符串的目标缓冲区
 * \param s 指向 UTF-8 字符串的源缓冲区
 * \return 转换后的 UTF-32 字符数
 */
dlimport usize utf8to32s(u32 *d, cstr8 s) __nnull(1, 2);

/**
 * \brief 将 UTF-8 字符串转换为 UTF-32 字符串并分配内存
 *
 * \param s 指向 UTF-8 字符串的源缓冲区
 * \return 指向转换后的 UTF-32 字符串的指针（需手动释放）
 */
dlimport u32 *utf8to32a(cstr8 s) ownership_returns(malloc) __nnull(1);

/**
 * \brief 将单个 UTF-16 字符转换为 UTF-32 字符
 *        注意该函数会修改传入的指针，使其指向下一个字符
 *
 * \param sp 指向 UTF-16 字符串的指针
 * \return 转换后的 UTF-32 字符
 */
dlimport u32 utf16to32c(cstr16 *sp) __nnull(1);

/**
 * \brief 将 UTF-16 字符串转换为 UTF-32 字符串
 *
 * \param d 指向存储 UTF-32 字符串的目标缓冲区
 * \param s 指向 UTF-16 字符串的源缓冲区
 * \return 转换后的 UTF-32 字符数
 */
dlimport usize utf16to32s(u32 *d, cstr16 s);

/**
 * \brief 将 UTF-16 字符串转换为 UTF-32 字符串并分配内存
 *
 * \param s 指向 UTF-16 字符串的源缓冲区
 * \return 指向转换后的 UTF-32 字符串的指针（需手动释放）
 */
dlimport u32 *utf16to32a(cstr16 s) ownership_returns(malloc);

/**
 * \brief 将单个 UTF-32 字符转换为 UTF-8 字符
 *
 * \param c 要转换的 UTF-32 字符
 * \param s 指向存储 UTF-8 字符的目标缓冲区
 * \return 转换后的字节数
 */
dlimport isize utf32to8c(u32 c, u8 *s);

/**
 * \brief 将 UTF-32 字符串转换为 UTF-8 字符串
 *
 * \param d 指向存储 UTF-8 字符串的目标缓冲区
 * \param s 指向 UTF-32 字符串的源缓冲区
 * \return 转换后的字节数
 */
dlimport usize utf32to8s(u8 *d, cstr32 s);

/**
 * \brief 将 UTF-32 字符串转换为 UTF-8 字符串并分配内存
 *
 * \param s 指向 UTF-32 字符串的源缓冲区
 * \return 指向转换后的 UTF-8 字符串的指针（需手动释放）
 */
dlimport u8 *utf32to8a(cstr32 s) ownership_returns(malloc);

/**
 * \brief 将单个 UTF-32 字符转换为 UTF-16 字符
 *
 * \param c 要转换的 UTF-32 字符
 * \param s 指向存储 UTF-16 字符的目标缓冲区
 * \return 转换后的字数
 */
dlimport isize utf32to16c(u32 c, u16 *s);

/**
 * \brief 将 UTF-32 字符串转换为 UTF-16 字符串
 *
 * \param d 指向存储 UTF-16 字符串的目标缓冲区
 * \param s 指向 UTF-32 字符串的源缓冲区
 * \return 转换后的字数
 */
dlimport usize utf32to16s(u16 *d, cstr32 s);

/**
 * \brief 将 UTF-32 字符串转换为 UTF-16 字符串并分配内存
 *
 * \param s 指向 UTF-32 字符串的源缓冲区
 * \return 指向转换后的 UTF-16 字符串的指针（需手动释放）
 */
dlimport u16 *utf32to16a(cstr32 s) ownership_returns(malloc);

/**
 * \brief 检查单个 UTF-32 字符是否有效
 *
 * \param c 要检查的 UTF-32 字符
 * \return 如果有效返回 true，否则返回 false
 */
dlimport CONST bool is_vaild_utf32(u32 c);

/**
 * \brief 检查 UTF-32 字符串是否有效
 *
 * \param s 指向 UTF-32 字符串的指针
 * \return 如果有效返回 true，否则返回 false
 */
dlimport PURE bool is_vaild_utf32s(cstr32 s);

/**
 * \brief 统计 UTF-32 字符串中的无效字符数
 *
 * \param s 指向 UTF-32 字符串的指针
 * \return 无效字符的数量
 */
dlimport usize count_invalid_utf32s(cstr32 s);

/**
 * \brief 移除 UTF-32 字符串中的无效字符
 *
 * \param d 指向存储结果的目标缓冲区
 * \param s 指向 UTF-32 字符串的源缓冲区
 * \return 移除后的有效字符数
 */
dlimport usize remove_invalid_utf32s(u32 *d, cstr32 s);

/**
 * \brief 统计 UTF-16 字符串中的无效字符数
 *
 * \param s 指向 UTF-16 字符串的指针
 * \return 无效字符的数量
 */
dlimport usize count_invalid_utf16s(cstr16 s);

/**
 * \brief 移除 UTF-16 字符串中的无效字符
 *
 * \param d 指向存储结果的目标缓冲区
 * \param s 指向 UTF-16 字符串的源缓冲区
 * \return 移除后的有效字符数
 */
dlimport usize remove_invalid_utf16s(u16 *d, cstr16 s);

/**
 * \brief 统计 UTF-8 字符串中的无效字符数
 *
 * \param s 指向 UTF-8 字符串的指针
 * \return 无效字符的数量
 */
dlimport usize count_invalid_utf8s(cstr8 s);

/**
 * \brief 移除 UTF-8 字符串中的无效字符
 *
 * \param d 指向存储结果的目标缓冲区
 * \param s 指向 UTF-8 字符串的源缓冲区
 * \return 移除后的有效字符数
 */
dlimport usize remove_invalid_utf8s(u8 *d, cstr8 s);

/**
 * \brief 检查 UTF-32 字符是否为可打印字符
 *
 * \param c 要检查的 UTF-32 字符
 * \return 如果是可打印字符返回 true，否则返回 false
 */
dlimport CONST bool utf32_isprint(u32 c);

/**
 * \brief 检查 UTF-32 字符是否为空白字符
 *
 * \param c 要检查的 UTF-32 字符
 * \return 如果是空白字符返回 true，否则返回 false
 */
dlimport CONST bool utf32_isspace(u32 c);
