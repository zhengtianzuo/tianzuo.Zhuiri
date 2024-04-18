
// *@file tianzuo.Zhuiri.h
// *@brief 天佐.追日靴 (tianzuo.Zhuiri)
// *@version 1.0
// *@section LICENSE Copyright © 2003-2103 郑天佐 Corporation
// *@author 郑天佐 (zhengtianzuo)
// *@date 2013-4-3
#pragma once
#include <string.h>

// 通讯消息 (communication message)
const int Zhuiri_heart                          = 0x00001000;                        ///< 心跳包信息 (Heartbeat packet information)
const int Zhuiri_heart_timeout                  = 0x00001001;                        ///< 心跳包超时信息 (Heartbeat packet timeout information)
const int Zhuiri_content_size                   = 496;                               ///< 内容大小 (content size)

//!@brief 数据包结构
//!@struct Zhuiri_data_tag
typedef struct Zhuiri_data_tag {
    Zhuiri_data_tag() {
        m_ip_adrs = 0;
        m_port = 0;
        m_function = 0;
        m_sign = 0;
        m_index = 0;
        m_send_time = 0;
        m_send_size = 0;
        memset(m_data, 0, Zhuiri_content_size);
    }

    Zhuiri_data_tag(const Zhuiri_data_tag& other) {
        m_ip_adrs = other.m_ip_adrs;
        m_port = other.m_port;
        m_function = other.m_function;
        m_sign = other.m_sign;
        m_index = other.m_index;
        m_send_time = other.m_send_time;
        m_send_size = other.m_send_size;
        memcpy(m_data, other.m_data, Zhuiri_content_size);
    }

    ~Zhuiri_data_tag() {
    }

    int get_ip_adrs() const {
        return m_ip_adrs;
    }

    void set_ip_adrs(int ip_adrs) {
        m_ip_adrs = ip_adrs;
    }

    int get_port() const {
        return m_port;
    }

    void set_port(int port) {
        m_port = port;
    }

    int get_function() const {
        return m_function;
    }

    void set_function(int function) {
        m_function = function;
    }

    int get_sign() const {
        return m_sign;
    }

    void set_sign(int sign) {
        m_sign = sign;
    }

    int get_index() const {
        return m_index;
    }

    void set_index(int index) {
        m_index = index;
    }

    int get_send_time() const {
        return m_send_time;
    }

    void set_send_time(int send_time) {
        m_send_time = send_time;
    }

    int get_send_size() const {
        return m_send_size;
    }

    void set_send_size(int send_size) {
        m_send_size = send_size;
    }

private:
    int m_ip_adrs;                                                                    ///< 数据地址 (data address)
    int m_port;                                                                       ///< 数据端口 (data port)
    int m_function;                                                                   ///< 功能代码 (function code)
    int m_sign;                                                                       ///< 发送标志 (send flag)
    int m_index;                                                                      ///< 组包序号 (packet number)
    int m_send_time;                                                                  ///< 发送时间 (send time)
    int m_send_size;                                                                  ///< 内容长度 (contention length)

public:
    char m_data[Zhuiri_content_size];                                                 ///< 具体内容 (concrete content)
} Zhuiri_data_struct, *Zhuiri_data_pointer;
const int Zhuiri_data_total_size = sizeof(Zhuiri_data_struct);                        ///< 消息内容长度 (message content length) = 520

//!@brief 数据包结构
//!@struct Zhuiri_data_pkg_tag
typedef struct Zhuiri_data_pkg_tag {
    Zhuiri_data_pkg_tag() {
        m_send_data = NULL;
        m_Zhuiri = NULL;
        m_user_data = NULL;
        memset(&m_data, 0, Zhuiri_data_total_size);
    }

    Zhuiri_data_pkg_tag(const Zhuiri_data_pkg_tag& other) {
        m_send_data = other.m_send_data;
        m_Zhuiri = other.m_Zhuiri;
        m_user_data = other.m_user_data;
        m_data = other.m_data;
    }

    char *&get_send_data() {
        return m_send_data;
    }

    void set_send_data(char* send_data) {
        m_send_data = send_data;
    }

    void *&get_Zhuiri() {
        return m_Zhuiri;
    }

    void set_Zhuiri(void *Zhuiri) {
        m_Zhuiri = Zhuiri;
    }

    void *&get_user_data() {
        return m_user_data;
    }

    void set_user_data(void *user_data) {
        m_user_data = user_data;
    }

    Zhuiri_data_struct m_data;                                                       ///< 结构内容 (structural content)

private:
    char *m_send_data;                                                               ///< 内容指针 (content pointer)
    void *m_Zhuiri;                                                                  ///< 传输指针 (zhuiri pointer)
    void *m_user_data;                                                               ///< 用户数据 (user data)
} Zhuiri_data_pkg_struct, *Zhuiri_data_pkg_pointer;
const int Zhuiri_data_pkg_total_size = sizeof(Zhuiri_data_pkg_struct);               ///< 消息内容长度 (message content length) = 544

//!@brief 心跳包发送结构
//!@struct Zhuiri_pkg_send_heart_tag
typedef struct Zhuiri_pkg_send_heart_tag {
    int get_id() {
        return m_user_id;
    }

    void set_id(int user_id) {
        m_user_id = user_id;
    }

    int get_user_type() {
        return m_user_type;
    }

    void set_user_type(int user_type) {
        m_user_type = user_type;
    }

    int m_user_id;                                                                  ///< 用户ID  (user ID)
    int m_user_type;                                                                ///< 用户类型 (user type)
} Zhuiri_pkg_send_heart_struct, *Zhuiri_pkg_send_heart_pointer;

//!@brief 心跳包接收结构
//!@struct Zhuiri_pkg_recv_heart_tag
typedef struct Zhuiri_pkg_recv_heart_tag {
    Zhuiri_pkg_recv_heart_tag() {
        m_user_id = 0;
        m_ip_adrs = 0;
        m_port = 0;
        m_user_type = 0;
        m_send_time = 0;
        memset(&stuSendHeart, 0, sizeof(Zhuiri_pkg_send_heart_struct));
    }

    Zhuiri_pkg_recv_heart_tag(int user_id, int ip_adrs, int port, int user_type, int send_time, int sender_user_id, int sender_user_type) {
        m_user_id = user_id;
        m_ip_adrs = ip_adrs;
        m_port = port;
        m_user_type = user_type;
        m_send_time = send_time;
        stuSendHeart.m_user_id = sender_user_id;
        stuSendHeart.m_user_type = sender_user_type;
    }

    int get_user_id() const {
        return m_user_id;
    }

    void set_user_id(int user_id) {
        m_user_id = user_id;
    }

    int get_ip_adrs() const {
        return m_ip_adrs;
    }

    void set_ip_adrs(int ip_adrs) {
        m_ip_adrs = ip_adrs;
    }

    int get_port() const {
        return m_port;
    }

    void set_port(int port) {
        m_port = port;
    }

    int get_user_type() const {
        return m_user_type;
    }

    void set_user_type(int user_type) {
        m_user_type = user_type;
    }

    int get_send_time() const {
        return m_send_time;
    }

    void set_send_time(int send_time) {
        m_send_time = send_time;
    }

    Zhuiri_pkg_send_heart_struct stuSendHeart;                                        ///< 发送心跳包信息 (send heartbeat packet information)

private:
    int m_user_id;                                                                    ///< 用户ID  (user ID)
    int m_ip_adrs;                                                                    ///< 数据地址 (data address)
    int m_port;                                                                       ///< 数据端口 (data port)
    int m_user_type;                                                                  ///< 用户类型 (user type)
    int m_send_time;                                                                  ///< 发送时间 (send time)
} Zhuiri_pkg_recv_heart_struct, *Zhuiri_pkg_recv_heart_pointer;

//!@enum 数据通讯标识 (data communication identification)
enum Zhuiri_data_sign {
    Zhuiri_data_sign_none       = 0x00000000,                                         ///< 无标识 (no sign)
    Zhuiri_data_sign_reliable   = 0x00000001,                                         ///< 可靠 (reliable)
    Zhuiri_data_sign_normal     = 0x00000002,                                         ///< 一般[可能丢包和乱序] (normal[may be lost or out of order])
    Zhuiri_data_sign_processing = 0x00000003,                                         ///< 处理中 (processing)
    Zhuiri_data_sign_response   = 0x00000004,                                         ///< 回应消息 (response)
    Zhuiri_data_sign_heart      = 0x00000005,                                         ///< 心跳包 (heart)
};

//!@enum 数据通讯状态 (data communication status)
enum Zhuiri_data_status {
    Zhuiri_data_status_none     = 0x00000000,                                         ///< 空闲   (free)
    Zhuiri_data_status_normal   = 0x00000001,                                         ///< 正常   (normal)
    Zhuiri_data_status_retrying = 0x00000002,                                         ///< 重发中 (retrying)
    Zhuiri_data_status_failed   = 0x00000003,                                         ///< 失败   (failed)
};

//!@enum 错误码 (error code)
enum Zhuiri_error_code {
    Zhuiri_error_code_success       = 0x00000001,                                     ///< 正确的值 (success)
    Zhuiri_error_code_no_rights     = 0x00000002,                                     ///< 效验未通过 (no rights)
    Zhuiri_error_code_socket        = 0x0000000D,                                     ///< 套接字错误 (socket error)
    Zhuiri_error_code_thread_error  = 0x00000021,                                     ///< 线程失败 (thread error)
    Zhuiri_error_code_handle        = 0x00000022,                                     ///< 创建句柄失败 (handle error)
    Zhuiri_error_code_out_of_cache  = 0x00000023,                                     ///< 超出缓冲最大值 (out f cache)
    Zhuiri_error_code_out_of_memory = 0x00000024,                                     ///< 内存溢出 (out of memory)
    Zhuiri_error_code_time_out      = 0x00000025,                                     ///< 操作超时 (time out)
    Zhuiri_error_code_user_reject   = 0x00000098,                                     ///< 对方决绝 (user reject)
    Zhuiri_error_code_user_exit     = 0x00000099,                                     ///< 自行退出 (user exit)
};

//!@enum 数据队列错误码 (error code)
enum Zhuiri_queue_error_code {
    Zhuiri_queue_error_code_success       = 0x00000001,                               ///< 正确的值 (success)
    Zhuiri_queue_error_code_invalid_value = 0x00000002,                               ///< 无效的值 (invalid value)
    Zhuiri_queue_error_code_out_of_cache  = 0x00000003,                               ///< 超出缓冲 (out f cache)
    Zhuiri_queue_error_code_out_of_memory = 0x00000004,                               ///< 内存溢出 (out of memory)
    Zhuiri_queue_error_code_no_data       = 0x00000005,                               ///< 无数据 (no data)
};

// 回调函数 (call back)
typedef unsigned(*Zhuiri_callback)(const void *context, const Zhuiri_data_pkg_pointer pData);
