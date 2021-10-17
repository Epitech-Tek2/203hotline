/*
** EPITECH PROJECT, 2021
** B-MAT-400-STG-4-1-203hotline-clement.muth [WSL: Ubuntu]
** File description:
** inline
*/

#pragma once

#include "hotline.h"

noreturn bool help(char const *restrict _filepath, int const _output);

static void (my_free)(int _count, void *_ptr, ...)
{
    va_list list_ptr;

    free(_ptr);
    for (va_start(list_ptr, _ptr); _count > 0; --_count)
        free(va_arg(list_ptr, void *));
    va_end(list_ptr);
}

__always_inline noreturn void eraise()
{
    help("./help.txt", 84);
}

__always_inline bool issdigit(char const *restrict string)
{
    for (int i = 0; string[i]; i++)
        if (!isdigit(string[i])) return false;
    return true;
}