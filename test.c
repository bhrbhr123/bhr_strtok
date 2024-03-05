#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bhr_strtok.h"

int main(int argc, char **argv)
{
    strtok_t *p = NULL;
    int i = 0;
    char str[128] = "hello world; akjhsfgas,asjhgfdtgpppppp";
    

    /* 创建结构体 */
    p = struct_create();

    /* 输入字符串 */
    set_string(p, str);

    /* 显示字符串原始数据 */
    print_string(p);

    /* 分割 */
    string_splitting(p, "; ,");

    /* 显示分割后字符串 */
#if 1
    print_tokstring(p);

#else
    for (i = 0; i < get_list_count(p); i++)
    {
        printf("str%d: %s\n", i, get_straddr_by_index(p, i));
    } /* end of for (i = 0; i < get_list_count(p); i++) */ 

#endif

    /* 输入字符串 */
    set_string(p, "kakakaka|lalalala-yayayayaya");

    /* 显示字符串原始数据 */
    print_string(p);

    /* 分割 */
    string_splitting(p, "|-");

    /* 显示分割后字符串 */
#if 0
    print_tokstring(p);

#else
    for (i = 0; i < get_list_count(p); i++)
    {
        printf("str%d: %s\n", i, get_straddr_by_index(p, i));
    } /* end of for (i = 0; i < get_list_count(p); i++) */ 

#endif


    clear_completely(&p);

    return 0;
}