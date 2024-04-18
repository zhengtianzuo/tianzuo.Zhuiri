
// *@file tianzuo_ZhuiriInterface.h
// *@brief 天佐.追日靴 (tianzuo.Zhuiri)
// *@version 1.0
// *@section LICENSE Copyright © 2003-2103 郑天佐 Corporation
// *@author 郑天佐 (zhengtianzuo)
// *@date 2013-4-3
#pragma once
#include <stdbool.h>

//!@brief 追日靴接口 for python java csharp javascript php visualbasic go
//!@class tianzuo_ZhuiriInterface for python java csharp javascript php visualbasic go
#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct Zhuiri_data_tag {
        int m_ip_adrs;                                                                    ///< 数据地址 (data address)
        int m_port;                                                                       ///< 数据端口 (data port)
        int m_function;                                                                   ///< 功能代码 (function code)
        int m_sign;                                                                       ///< 发送标志 (send flag)
        int m_index;                                                                      ///< 组包序号 (packet number)
        int m_send_time;                                                                  ///< 发送时间 (send time)
        int m_send_size;                                                                  ///< 内容长度 (contention length)
        char m_data[492];                                                 ///< 具体内容 (concrete content)
    } Zhuiri_data_struct, *Zhuiri_data_pointer;

    typedef struct Zhuiri_data_pkg_tag {
        Zhuiri_data_struct m_data;                                                       ///< 结构内容 (structural content)
        char *m_send_data;                                                               ///< 内容指针 (content pointer)
        void *m_Zhuiri;                                                                  ///< 传输指针 (zhuiri pointer)
        void *m_user_data;                                                               ///< 用户数据 (user data)
    } Zhuiri_data_pkg_struct, *Zhuiri_data_pkg_pointer;

    /*!
    *@name initialize
    *@brief 接口初始化
    *@param[in] 无
    *@return 模块类指针
    *@author 郑天佐
    *@date 2013-4-3
    */
    void* tianzuo_ZhuiriInterface_initialize();

    /*!
    *@name terminate
    *@brief 接口销毁
    *@param[in] ZhuiriInt_pointer 模块类指针
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    void tianzuo_ZhuiriInterface_terminate(void** ZhuiriInt_pointer);

    /*!
    *@name initialize
    *@brief 组件初始化
    *@param[in] ZhuiriInt_pointer 模块类指针
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_initialize(
        void* ZhuiriInt_pointer, const char* ip_addr, int port,
        const void* callback, const void* context, int const heart_check_time, bool log_trace
        , void* iocp
    );

    /*!
    *@name terminate
    *@brief 组件销毁
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_terminate(void* ZhuiriInt_pointer);

    /*!
    *@name set_param
    *@brief 预设参数
    *@param[in] param 参数指针
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    int tianzuo_ZhuiriInt_set_param(void* ZhuiriInt_pointer,
        int sender_index, int init_server_port, int msg_init_size,
        int recv_ex_data_max, int retry_max, int retry_all_number,
        int init_retry_time);

    /*!
    *@name add_sender
    *@brief 添加发送者
    *@param[in] sender_index 发送序号
    *@param[in] sign 发送标识
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    int tianzuo_ZhuiriInt_add_sender(void* ZhuiriInt_pointer,
        int *sender_index, int const sign);

    /*!
    *@name begin_recv
    *@brief 开始接收数据
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_begin_recv(void* ZhuiriInt_pointer);

    /*!
    *@name stop_recv
    *@brief 停止接收数据
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_stop_recv(void* ZhuiriInt_pointer);

    /*!
    *@name data_free
    *@brief 释放数据
    *@param[in] Zhuiri 类指针
    *@param[in] data_index 数据序号
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_data_free(void* ZhuiriInt_pointer, void *Zhuiri, int const data_index);

    /*!
    *@name send
    *@brief 发送数据
    *@param[in] send_param 发送参数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_send(void* ZhuiriInt_pointer,
        int sender_index, int ip, int port, int sign, int function, char* send_data, int send_size);

    /*!
    *@name get_status
    *@brief 获取状态
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_get_status(void* ZhuiriInt_pointer);

    /*!
    *@name get_type
    *@brief 获取类型
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_get_type(void* ZhuiriInt_pointer);

    /*!
    *@name get_bind_port
    *@brief 获取绑定端口
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_get_bind_port(void* ZhuiriInt_pointer);

    /*!
    *@name heart_add
    *@brief 新建心跳包检测
    *@param[in] recv_heart 接收心跳参数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_heart_add(void* ZhuiriInt_pointer, int user_id, int ip_adrs, int port, int user_type, int send_time, int sender_user_id, int sender_user_type);

    /*!
    *@name heart_modify
    *@brief 修改心跳包检测
    *@param[in] data_id 数据ID
    *@param[in] ip IP地址
    *@param[in] port 端口
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_heart_modify(void* ZhuiriInt_pointer,
        int const data_id, int const ip, int const port);

    /*!
    *@name heart_update
    *@brief 更新心跳包检测
    *@param[in] data_id 数据ID
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_heart_update(void* ZhuiriInt_pointer, int const data_id);

    /*!
    *@name heart_remove
    *@brief 删除心跳包检测
    *@param[in] data_id 数据ID
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_ZhuiriInt_heart_remove(void* ZhuiriInt_pointer, int const data_id);

    /*!
    *@name initialize
    *@brief 接口初始化
    *@param[in] 无
    *@return 模块类指针
    *@author 郑天佐
    *@date 2013-4-3
    */
    void* tianzuo_DataQueueInterface_initialize();

    /*!
    *@name terminate
    *@brief 接口销毁
    *@param[in] ZhuiriInt_pointer 模块类指针
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    void tianzuo_DataQueueInterface_terminate(void** DataQueue_pointer);

    /*!
    *@name initialize
    *@brief 队列初始化
    *@param[in] init_size 队列初始大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    int tianzuo_DataQueueInt_initialize(int init_size);

    // 回调函数 (call back)
    //typedef unsigned(*Zhuiri_callback)(const void *context, const void *pData);
    typedef void (*CallbackFunc)(int);

#ifdef __cplusplus
}
#endif
