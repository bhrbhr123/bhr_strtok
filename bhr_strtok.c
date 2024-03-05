/**
 * @file                bhr_strtok.c
 * @brief               基于万能型单向链表的字符串分割存储实现
 * @author              BHR
 * @version             v1.0
 * @date                2024-03-05
 * @copyright           MIT
 */

#include "bhr_strtok.h"


/**
 * @brief               节点中数据域销毁函数
 * @param               数据域的指针
 * @return              0
 */
int strtok_node_destroy(void *data)
{
    free(data);
    data = NULL;
    return 0;
}


/**
 * @brief               节点中数据域打印函数
 * @param               数据域的指针
 * @return              0
 */
int strtok_data_print(void *data)
{
    printf("%s\n", *(char **)data);
    return 0;
}



/**
 * @brief               字符串分割使用结构体创建
 * @param               void
 * @return              指向结构体的指针
 */
strtok_t *struct_create(void)
{
    strtok_t *p = NULL;

    /* 申请结构体空间 */
    p = (strtok_t *)calloc(1, sizeof(strtok_t));
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("struct_create: calloc failed...\n");
    #endif
        goto ERR1;
    } /* end of if (NULL == p) */

    /* 结构体数据初始化 */
    p->str_p = NULL;
    p->head = NULL;

    /* 申请头信息结构体空间 */
    p->head = uolist_create(TOK_SIZE, strtok_node_destroy);
    if ((void *)FUN_ERROR == p->head || (void *)PAR_ERROR == p->head)
    {
    #ifdef DEBUG
        printf("struct_create: uolist_create error\n");
    #endif
        goto ERR1;
    } /* end of if ((void *)FUN_ERROR == p->head || (void *)PAR_ERROR == p->head) */

    return p;


ERR1:
    return (void *)FUN_ERROR;

}

/**
 * @brief               结构体字符串输入
 * @param               字符串分割结构体指针
 * @param               需要输入的字符串
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  FUN_ERROR: 函数错误
 */
int set_string(strtok_t *p, char *str)
{
    int size = strlen(str) + 1;

    /* 参数检查 */
    if (NULL == p || NULL == str)
    {
    #ifdef DEBUG
        printf("set_string: Parameter error...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p || NULL == str) */


    /* 判断字符串空间是否存在 */
    if (NULL != p->str_p)
    {
        free(p->str_p);
        p->str_p = NULL;
    } /* end of if (NULL != p->str_p) */


    /* 创建字符串空间 */
    p->str_p = (char *)calloc(size, sizeof(char));
    if (NULL == p->str_p)
    {
    #ifdef DEBUG
        printf("set_string: calloc failed...\n");
    #endif
        goto ERR1;
    } /* end of if (NULL == p->str_p) */


    /* 字符串拷贝 */
    strcpy(p->str_p, str);


    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;

}


/**
 * @brief               结构体字符串分割
 * @param               字符串分割结构体指针
 * @param               分割标志
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 *      @arg  FUN_ERROR: 函数错误
 */
int string_splitting(strtok_t *p, char *delim)
{
    char *tok_p = NULL;
    int i = 0;

    /* 参数检查 */
    if (NULL == p || NULL == delim)
    {
    #ifdef DEBUG
        printf("string_splitting: Parameter error...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p || NULL == delim) */


    /* 判断结构体字符串是否存在 */
    if (NULL == p->str_p)
    {
    #ifdef DEBUG
        printf("string_splitting: str_p is null...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p->str_p) */


    /* 检查链表 */
    if (0 != p->head->count)
    {
        uolist_destroy(p->head);
    } /* end of if (0 != p->head->count) */


    /* 字符串分割 */
    i = 0;
    while (1)
    {
        switch (i)
        {
            case 0:
                tok_p = strtok(p->str_p, delim);
                i++;
                break;
            default:
                tok_p = strtok(NULL, delim);
                break;
        } /* end of switch (i) */

        if (NULL == tok_p)
        {
            break;
        }
        else 
        {
            uolist_append(p->head, &tok_p);
        }

    } /* end of while (1) */

    return 0;

ERR0:
    return PAR_ERROR;
ERR1:
    return FUN_ERROR;
}


/**
 * @brief               完全释放结构体空间
 * @param               字符串分割结构体指针的地址
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 */
int clear_completely(strtok_t **p)
{

    /* 参数检查 */
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("clear_completely: Parameter error...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p) */

    /* 释放链表空间 */
    if (0 != (*p)->head->count)
    {
        uolist_destroy((*p)->head);
    } /* end of if (0 != (*p)->head->count) */

    head_destroy(&((*p)->head));

    /* 释放字符串空间 */
    if (NULL != (*p)->str_p)
    {
        free((*p)->str_p);
        (*p)->str_p = NULL;
    } /* end of if (NULL != (*p)->str_p) */

    /* 释放字符串分割结构体的空间 */
    free(*p);
    *p = NULL;

    return 0;

ERR0:
    return PAR_ERROR;
}


/**
 * @brief               显示字符串原始数据（请在分割操作前调用）
 * @param               字符串分割结构体指针
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 */
int print_string(strtok_t *p)
{

    /* 参数检查 */
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("print_string: Parameter error...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p) */

    if (NULL != p->str_p)
    {
        printf("string: %s\n", p->str_p);
    } /* end of if (NULL != p->str_p) */

    return 0;


ERR0:
    return PAR_ERROR;
}


/**
 * @brief               显示字符串分割后数据
 * @param               字符串分割结构体指针
 * @return              
 *      @arg          0: 正常
 *      @arg  PAR_ERROR: 参数错误
 */
int print_tokstring(strtok_t *p)
{

    /* 参数检查 */
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("print_tokstring: Parameter error...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p) */

    /* 查看字符串原始数据是否还存在 */
    if (*(char **)(p->head->fstnode_p->data) == p->str_p)
    {
        uolist_traverse(p->head, strtok_data_print);
    } /* end of if (*(char **)(p->head->fstnode_p->data) == p->str_p) */
    

    return 0;

ERR0:
    return PAR_ERROR;    
}



/**
 * @brief               根据索引获取分割后字符串的地址
 * @param               字符串分割结构体指针
 * @param               索引值
 * @return              对应索引的字符串的地址
 *      @arg       NULL: 索引超出范围
 *      @arg  PAR_ERROR: 参数错误
 */
char *get_straddr_by_index(strtok_t *p, int index)
{
    void *data = NULL;

    /* 参数检查 */
    if (NULL == p || index < 0)
    {
    #ifdef DEBUG
        printf("get_straddr_by_index: Parameter error...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p || index < 0) */


    /* 检查字符串和链表是否为空 */
    if (NULL == p->str_p || NULL == p->head->fstnode_p)
    {
    #ifdef DEBUG
        printf("get_straddr_by_index: string or list is null...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p->str_p || NULL == p->head->fstnode_p) */


    /* 检查字符串和链表是否匹配 */
    if (p->str_p != *(char **)(p->head->fstnode_p->data))
    {
    #ifdef DEBUG
        printf("get_straddr_by_index: string and list mismatch...\n");
    #endif
        goto ERR0;
    } /* end of if (p->str_p != *(char **)(p->head->fstnode_p->data)) */


    /* 判断索引是否在范围内 */
    if (index >= 0 && index < p->head->count)
    {
        uolist_retrieve_by_index(p->head, &data, index);
        return (char *)data;
    } /* end of if (index >= 0 && index < p->head->count) */

    return NULL;


ERR0:
    return (void *)PAR_ERROR; 
}



/**
 * @brief               获取链表节点个数
 * @param               字符串分割结构体指针
 * @return              节点个数
 */
int get_list_count(strtok_t *p)
{

    /* 参数检查 */
    if (NULL == p)
    {
    #ifdef DEBUG
        printf("get_list_count: Parameter error...\n");
    #endif
        goto ERR0;
    } /* end of if (NULL == p) */

    return get_count(p->head);


ERR0:
    return PAR_ERROR; 
}










