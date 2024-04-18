
// *@file tianzuo_ZhuiriInterface.h
// *@brief 天佐.追日靴 (tianzuo.Zhuiri)
// *@version 1.0
// *@section LICENSE Copyright © 2003-2103 郑天佐 Corporation
// *@author 郑天佐 (zhengtianzuo)
// *@date 2013-4-3
#pragma once
#include "tianzuo.Zhuiri.h"

//!@brief 导出函数定义(define dllexport)
#undef tianzuo_Zhuiri_lib
#if defined (WIN32)
#define tianzuo_Zhuiri_atr
#if defined (tianzuo_Zhuiri_dllexport)
#define tianzuo_Zhuiri_lib _declspec(dllexport)
#else
#define tianzuo_Zhuiri_lib _declspec(dllimport)
#endif
#else
#define tianzuo_Zhuiri_atr __attribute__((visibility("default")))
#define tianzuo_Zhuiri_lib
#endif

//!@brief 参数
//!@struct Zhuiri_param_tag
typedef struct Zhuiri_param_tag {
    Zhuiri_param_tag() {
        m_sender_index = 0;
        m_init_server_port = 0;
        m_msg_init_size = 0;
        m_recv_ex_data_max = 0;
        m_retry_max = 0;
        m_retry_all_number = 0;
        m_init_retry_time = 0;
    }

    Zhuiri_param_tag(
        int sender_index,
        int init_server_port,
        int msg_init_size,
        int recv_ex_data_max,
        int retry_max,
        int retry_all_number,
        int init_retry_time) {
        m_sender_index = sender_index;
        m_init_server_port = init_server_port;
        m_msg_init_size = msg_init_size;
        m_recv_ex_data_max = recv_ex_data_max;
        m_retry_max = retry_max;
        m_retry_all_number = retry_all_number;
        m_init_retry_time = init_retry_time;
    }

    int get_sender_index() const {
        return m_sender_index;
    }

    void set_sender_index(int sender_index) {
        m_sender_index = sender_index;
    }

    int get_init_server_port() const {
        return m_init_server_port;
    }

    void set_init_server_port(int init_server_port) {
        m_init_server_port = init_server_port;
    }

    int get_msg_init_size() const {
        return m_msg_init_size;
    }

    void set_msg_init_size(int msg_init_size) {
        m_msg_init_size = msg_init_size;
    }

    int get_recv_ex_data_max() const {
        return m_recv_ex_data_max;
    }

    void set_recv_ex_data_max(int recv_ex_data_max) {
        m_recv_ex_data_max = recv_ex_data_max;
    }

    int get_retry_max() const {
        return m_retry_max;
    }

    void set_retry_max(int retry_max) {
        m_retry_max = retry_max;
    }

    int get_retry_all_number() const {
        return m_retry_all_number;
    }

    void set_retry_all_number(int retry_all_number) {
        m_retry_all_number = retry_all_number;
    }

    int get_init_retry_time() const {
        return m_init_retry_time;
    }

    void set_init_retry_time(int init_retry_time) {
        m_init_retry_time = init_retry_time;
    }

private:
    int m_sender_index;
    int m_init_server_port;                                          ///< 初始绑定端口 (initial bond port)
    int m_msg_init_size;                                             ///< 初始缓冲队列大小 (initial buffer queue size)
    int m_recv_ex_data_max;                                          ///< 初始扩展接收内存池大小 (initially expand the receive memory pool size)
    int m_retry_max;                                                 ///< 初始丢包重试最大数 (maximum number of initial packet loss retries)
    int m_retry_all_number;                                          ///< 初始重试时间倍数 (initial retry time multiple)
    int m_init_retry_time;                                           ///< 初始重试时间(毫秒) (initial retry time(ms))
} Zhuiri_param_struct, *Zhuiri_param_pointer;

//!@brief 发送参数
//!@struct Zhuiri_send_param_tag
typedef struct Zhuiri_send_param_tag {
    Zhuiri_send_param_tag() {
        m_sender_index = 0;
        m_ip = 0;
        m_port = 0;
        m_sign = 0;
        m_function = 0;
        m_send_data = NULL;
        m_send_size = 0;
    }

    Zhuiri_send_param_tag(int sender_index, int ip, int port, int sign,
                         int function, char *send_data, int send_size) {
        m_sender_index = sender_index;
        m_ip = ip;
        m_port = port;
        m_sign = sign;
        m_function = function;
        m_send_data = send_data;
        m_send_size = send_size;
    }

    int get_sender_index() const {
        return m_sender_index;
    }

    void set_sender_index(int sender_index) {
        m_sender_index = sender_index;
    }

    int get_ip() const {
        return m_ip;
    }

    void set_ip(int ip) {
        m_ip = ip;
    }

    int get_port() const {
        return m_port;
    }

    void set_port(int port) {
        m_port = port;
    }

    int get_sign() const {
        return m_sign;
    }

    void set_sign(int sign) {
        m_sign = sign;
    }

    int get_function() const {
        return m_function;
    }

    void set_function(int function) {
        m_function = function;
    }

    char *get_send_data() const {
        return m_send_data;
    }

    void set_send_data(char * send_data) {
        m_send_data = send_data;
    }

    int get_send_size() const {
        return m_send_size;
    }

    void set_send_size(int send_size) {
        m_send_size = send_size;
    }

private:
    int m_sender_index;                                             ///< 发送者序号 (sender sequence number)
    int m_ip;                                                       ///< ip地址 (ip address)
    int m_port;                                                     ///< 端口 (port)
    int m_sign;                                                     ///< 标识 (sign)
    int m_function;                                                 ///< 功能码 (function code)
    char *m_send_data;                                              ///< 发送数据指针 (send data pointer)
    int m_send_size;                                                ///< 发送数据大小 (send data size)
} Zhuiri_send_param_struct, *Zhuiri_send_param_pointer;

//!@brief 追日靴模块类 for c++
//!@class tianzuo_ZhuiriInt for c++
class tianzuo_Zhuiri_lib tianzuo_ZhuiriInt {
 public:
    tianzuo_ZhuiriInt() {}
    virtual ~tianzuo_ZhuiriInt() {}

    /*!
    *@name initialize
    *@brief 组件初始化
    *@param[in] ip_addr 绑定IP地址
    *@param[in] port 绑定端口号
    *@param[in] callback 回调指针
    *@param[in] context 回调上下文
    *@param[in] heart_check_time 心跳包检测时间间隔
    *@param[in] log_trace 是否有运行调试信息
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int initialize(
        const char *ip_addr, int port,
        const void *callback, const void *context, int const heart_check_time,
        bool log_trace
#ifdef WIN32
        , void * iocp = nullptr
#endif
    ) = 0;

    /*!
    *@name terminate
    *@brief 组件销毁
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int terminate() = 0;

    /*!
    *@name set_param
    *@brief 预设参数
    *@param[in] param 参数指针
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    virtual int set_param(Zhuiri_param_pointer param) = 0;

    /*!
	*@name add_sender
	*@brief 添加发送者
	*@param[in] sender_index 发送序号
	*@param[in] sign 发送标识
	*@return 无
	*@author 郑天佐
	*@date 2013-6-26
	*/
    virtual int add_sender(
        int *sender_index, int const sign) = 0;

    /*!
    *@name begin_recv
    *@brief 开始接收数据
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int begin_recv() = 0;

    /*!
    *@name stop_recv
    *@brief 停止接收数据
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int stop_recv() = 0;

    /*!
    *@name data_free
    *@brief 释放数据
    *@param[in] Zhuiri 类指针
    *@param[in] data_index 数据序号
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int data_free(
        void *Zhuiri, int const data_index) const = 0;

    /*!
    *@name send
    *@brief 发送数据
    *@param[in] send_param 发送参数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int send(Zhuiri_send_param_pointer send_param) = 0;

    /*!
    *@name get_status
    *@brief 获取状态
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int get_status() const = 0;

    /*!
    *@name get_type
    *@brief 获取类型
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int get_type() = 0;

    /*!
    *@name get_bind_port
    *@brief 获取绑定端口
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int get_bind_port() = 0;

    /*!
    *@name heart_add
    *@brief 新建心跳包检测
    *@param[in] recv_heart 接收心跳参数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int heart_add(Zhuiri_pkg_recv_heart_pointer recv_heart) = 0;

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
    virtual int heart_modify(
        int const data_id, int const ip, int const port) = 0;

    /*!
    *@name heart_update
    *@brief 更新心跳包检测
    *@param[in] data_id 数据ID
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int heart_update(int const data_id) = 0;

    /*!
    *@name heart_remove
    *@brief 删除心跳包检测
    *@param[in] data_id 数据ID
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int heart_remove(int const data_id) = 0;
};

//!@brief 追日靴接口类 for c++
//!@class tianzuo_ZhuiriInterface for c++
class tianzuo_Zhuiri_lib tianzuo_ZhuiriInterface {
 public:
    /*!
    *@name tianzuo_ZhuiriInterface
    *@brief 构造函数
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    tianzuo_ZhuiriInterface();

    /*!
    *@name ~tianzuo_ZhuiriInterface
    *@brief 析构函数
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    virtual ~tianzuo_ZhuiriInterface();

    /*!
    *@name initialize
    *@brief 组件接口初始化
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    static tianzuo_ZhuiriInt *initialize();

    /*!
    *@name terminate
    *@brief 组件接口销毁
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    static void terminate(tianzuo_ZhuiriInt **Zhuiri);
};

//!@brief 追日靴数据队列模块类 for c++
//!@class tianzuo_DataQueue for c++
class tianzuo_Zhuiri_lib tianzuo_DataQueue {
 public:
    tianzuo_DataQueue() {}
    virtual ~tianzuo_DataQueue() {}

    /*!
    *@name initialize
    *@brief 队列初始化
    *@param[in] init_size 队列初始大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int initialize(int const init_size) = 0;

    /*!
    *@name terminate
    *@brief 队列销毁
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual void terminate() = 0;

    /*!
    *@name push_back
    *@brief 数据入队列
    *@param[in] data 数据
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int push_back(const Zhuiri_data_pkg_pointer data) = 0;

    /*!
    *@name pop_up
    *@brief 数据出队列
    *@param[in] data 数据
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int pop_up(const Zhuiri_data_pkg_pointer data) = 0;

    /*!
    *@name alloc_send_data
    *@brief 申请数据
    *@param[in] data 数据
    *@param[in] space_size 数据大小
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual void alloc_send_data(
        Zhuiri_data_pkg_pointer *data, int const space_size) = 0;

    /*!
    *@name free_send_data
    *@brief 释放申请的数据
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual void free_send_data() = 0;

    /*!
    *@name get_used_count
    *@brief 获取已用队列数
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int get_used_count() const = 0;

    /*!
    *@name get_unuse_count
    *@brief 获取未用队列数
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int get_unuse_count() const = 0;

    /*!
    *@name get_all_count
    *@brief 获取总队列数
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual int get_all_count() const = 0;

    /*!
    *@name clear
    *@brief 清理队列
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    virtual void clear() = 0;
};

//!@brief 追日靴数据队列接口 for c++
//!@class tianzuo_DataQueueInterface for c++
class tianzuo_Zhuiri_lib tianzuo_DataQueueInterface {
 public:
    /*!
    *@name tianzuo_DataQueueInterface
    *@brief 构造函数
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    tianzuo_DataQueueInterface();

    /*!
    *@name tianzuo_DataQueueInterface
    *@brief 析构函数
    *@param[in] 无
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    virtual ~tianzuo_DataQueueInterface();

    /*!
    *@name initialize
    *@brief 数据队列初始化
    *@param[in] 无
    *@return tianzuo_DataQueue* 队列指针
    *@author 郑天佐
    *@date 2013-6-26
    */
    static tianzuo_DataQueue *initialize();

    /*!
    *@name terminate
    *@brief 数据队列销毁
    *@param[in] data_queue 队列指针
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    static void terminate(tianzuo_DataQueue **data_queue);
};

//!@brief 追日靴接口 for python java csharp javascript php visualbasic go rust ruby
//!@class tianzuo_ZhuiriInterface for python java csharp javascript php visualbasic go rust ruby
#ifdef __cplusplus
extern "C"
{
#endif

    /*!
    *@name initialize
    *@brief 接口初始化
    *@param[in] 无
    *@return 模块类指针
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib tianzuo_ZhuiriInt* tianzuo_ZhuiriInterface_initialize();

    /*!
    *@name terminate
    *@brief 接口销毁
    *@param[in] ZhuiriInt_pointer 模块类指针
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib void tianzuo_ZhuiriInterface_terminate(tianzuo_ZhuiriInt** ZhuiriInt_pointer);

    /*!
    *@name initialize
    *@brief 组件初始化
    *@param[in] ZhuiriInt_pointer 模块类指针
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_initialize(
        tianzuo_ZhuiriInt* ZhuiriInt_pointer, const char* ip_addr, int port,
        const void* callback, const void* context, int const heart_check_time, bool log_trace
#ifdef WIN32
        , void* iocp = nullptr
#endif
    );

    /*!
    *@name terminate
    *@brief 组件销毁
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_terminate(tianzuo_ZhuiriInt* ZhuiriInt_pointer);

    /*!
    *@name set_param
    *@brief 预设参数
    *@param[in] param 参数指针
    *@return 无
    *@author 郑天佐
    *@date 2013-6-26
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_set_param(tianzuo_ZhuiriInt* ZhuiriInt_pointer,
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
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_add_sender(tianzuo_ZhuiriInt* ZhuiriInt_pointer,
        int *sender_index, int const sign);

    /*!
    *@name begin_recv
    *@brief 开始接收数据
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_begin_recv(tianzuo_ZhuiriInt* ZhuiriInt_pointer);

    /*!
    *@name stop_recv
    *@brief 停止接收数据
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_stop_recv(tianzuo_ZhuiriInt* ZhuiriInt_pointer);

    /*!
    *@name data_free
    *@brief 释放数据
    *@param[in] Zhuiri 类指针
    *@param[in] data_index 数据序号
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_data_free(tianzuo_ZhuiriInt* ZhuiriInt_pointer, void *Zhuiri, int const data_index);

    /*!
    *@name send
    *@brief 发送数据
    *@param[in] send_param 发送参数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_send(tianzuo_ZhuiriInt* ZhuiriInt_pointer, 
        int sender_index, int ip, int port, int sign, int function, char* send_data, int send_size);

    /*!
    *@name get_status
    *@brief 获取状态
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_get_status(tianzuo_ZhuiriInt* ZhuiriInt_pointer);

    /*!
    *@name get_type
    *@brief 获取类型
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_get_type(tianzuo_ZhuiriInt* ZhuiriInt_pointer);

    /*!
    *@name get_bind_port
    *@brief 获取绑定端口
    *@param[in] 无
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_get_bind_port(tianzuo_ZhuiriInt* ZhuiriInt_pointer);

    /*!
    *@name heart_add
    *@brief 新建心跳包检测
    *@param[in] recv_heart 接收心跳参数
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_heart_add(tianzuo_ZhuiriInt* ZhuiriInt_pointer, int user_id, int ip_adrs, int port, int user_type, int send_time, int sender_user_id, int sender_user_type);

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
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_heart_modify(tianzuo_ZhuiriInt* ZhuiriInt_pointer,
        int const data_id, int const ip, int const port);

    /*!
    *@name heart_update
    *@brief 更新心跳包检测
    *@param[in] data_id 数据ID
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_heart_update(tianzuo_ZhuiriInt* ZhuiriInt_pointer, int const data_id);

    /*!
    *@name heart_remove
    *@brief 删除心跳包检测
    *@param[in] data_id 数据ID
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_ZhuiriInt_heart_remove(tianzuo_ZhuiriInt* ZhuiriInt_pointer, int const data_id);

    /*!
    *@name initialize
    *@brief 接口初始化
    *@param[in] 无
    *@return 模块类指针
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib tianzuo_DataQueue* tianzuo_DataQueueInterface_initialize();

    /*!
    *@name terminate
    *@brief 接口销毁
    *@param[in] ZhuiriInt_pointer 模块类指针
    *@return 无
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib void tianzuo_DataQueueInterface_terminate(tianzuo_DataQueue** DataQueue_pointer);

    /*!
    *@name initialize
    *@brief 队列初始化
    *@param[in] init_size 队列初始大小
    *@return int
    *@author 郑天佐
    *@date 2013-4-3
    */
    tianzuo_Zhuiri_lib int tianzuo_DataQueueInt_initialize(int init_size);

#ifdef __cplusplus
}
#endif
