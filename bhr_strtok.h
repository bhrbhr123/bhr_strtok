/**
 * @file                bhr_strtok.h
 * @brief               基于万能型单向链表的字符串分割存储实现
 * @author              BHR
 * @version             v1.0
 * @date                2024-03-05
 * @copyright           MIT
 */

#ifndef __BHR_STRTOK_H__
#define __BHR_STRTOK_H__

#include "uni_oneway_linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

#define TOK_SIZE sizeof(char *)


/**
 * @brief 字符串切割结构体定义
 */
typedef struct _strtok_t
{
    char *str_p;            // 字符串指针
    uolist_t *head;         // 链表头信息结构体指针
}strtok_t;


/**
 * @brief               节点中数据域销毁函数
 * @param               数据域的指针
 * @return              0
 */
int strtok_node_destroy(void *data);


/**
 * @brief               字符串分割使用结构体创建
 * @param               void
 * @return              指向结构体的指针
 */
strtok_t *struct_create(void);


/**
 * @brief               结构体字符串输入
 * @param               字符串分割结构体指针
 * @param               需要输入的字符串
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  FUN_ERROR: 函数错误
 */
int set_string(strtok_t *p, char *str);


/**
 * @brief               结构体字符串分割
 * @param               字符串分割结构体指针
 * @param               分割标志
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  FUN_ERROR: 函数错误
 */
int string_splitting(strtok_t *p, char *delim);


/**
 * @brief               节点中数据域打印函数
 * @param               数据域的指针
 * @return              0
 */
int strtok_data_print(void *data);


/**
 * @brief               完全释放结构体空间
 * @param               字符串分割结构体指针的地址
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 */
int clear_completely(strtok_t **p);


/**
 * @brief               显示字符串原始数据（请在分割操作前调用）
 * @param               字符串分割结构体指针
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 */
int print_string(strtok_t *p);


/**
 * @brief               显示字符串分割后数据
 * @param               字符串分割结构体指针
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 */
int print_tokstring(strtok_t *p);


/**
 * @brief               根据索引获取分割后字符串的地址
 * @param               字符串分割结构体指针
 * @param               索引值
 * @return              对应索引的字符串的地址
 *      @arg       NULL: 索引超出范围
 *      @arg  PAR_ERROR: 参数错误
 */
char *get_straddr_by_index(strtok_t *p, int index);


/**
 * @brief               获取链表节点个数
 * @param               字符串分割结构体指针
 * @return              节点个数
 */
int get_list_count(strtok_t *p);






#endif /* __BHR_STRTOK_H__ */
