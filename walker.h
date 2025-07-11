#ifndef OFAB_WALKER_H
#define OFAB_WALKER_H

#include <stdlib.h>
#include <string.h>

int walker_space(char** str);
int walker_int_out(char** str, int* out);
int walker_while_range(char** str, char min, char max);
int walker_match(char** str, const char* pattern);
int walker_matchc(char** str, const char c);
int walker_equal(const char* str, const char* pattern);
int walker_equaln(const char* str, const char* pattern, int n);
int walker_equalc(const char* str, const char c);
int walker_adv(char** str, size_t n);
int walker_next(char** str);
int walker_more(const char* str);
int walker_marker_len(const char* str, const char* mark);

int walker_int_out(char** str, int* out)
{
    char* m = *str;
    walker_matchc(str, '-');
    if (walker_while_range(str, '0', '9'))
        *out = atoi(m);
    return walker_marker_len(*str, m);
}

int walker_while_range(char** str, char min, char max)
{
    char* m = *str;
    while (**str >= min && **str <= max)
        walker_next(str);
    return walker_marker_len(*str, m);
}

int walker_space(char** str)
{
    char* m = *str;
    while (walker_more(*str) && **str <= ' ')
        (*str)++;
    return walker_marker_len(*str, m);
}

int walker_match(char** str, const char* pattern)
{
    int n = walker_equal(*str, pattern);
    return walker_adv(str, n);
}

int walker_matchc(char** str, const char c)
{
    int n = walker_equalc(*str, c);
    return walker_adv(str, n);
}

int walker_equal(const char* str, const char* pattern)
{
    int len = strlen(pattern);
    if (walker_equaln(str, pattern, len))
        return len;
    return 0;
}

int walker_equaln(const char* str, const char* pattern, int n)
{
    if (strncmp(str, pattern, n) == 0)
        return n;
    return 0;
}

int walker_equalc(const char* str, const char c)
{
    return *str == c;
}

int walker_adv(char** str, size_t n)
{
    *str += n;
    return n;
}

int walker_next(char** str)
{
    (*str)++;
    return 1;
}

int walker_more(const char* str)
{
    return *str != '\0';
}

int walker_marker_len(const char* str, const char* mark)
{
    return str - mark;
}

#endif
