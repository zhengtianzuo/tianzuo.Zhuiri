<?php

// 检查是否加载了 FFI 扩展
if (extension_loaded('ffi')) {
    echo("已启用 FFI 扩展\n");
} else {
    die("未启动 FFI 扩展\n");
}

enum Zhuiri_error_code
{
const Zhuiri_error_code_success       = 0x00000001;                                     ///< 正确的值 (success)
const Zhuiri_error_code_no_rights     = 0x00000002;                                     ///< 效验未通过 (no rights)
const Zhuiri_error_code_socket        = 0x0000000D;                                     ///< 套接字错误 (socket error)
const Zhuiri_error_code_thread_error  = 0x00000021;                                     ///< 线程失败 (thread error)
const Zhuiri_error_code_handle        = 0x00000022;                                     ///< 创建句柄失败 (handle error)
const Zhuiri_error_code_out_of_cache  = 0x00000023;                                     ///< 超出缓冲最大值 (out f cache)
const Zhuiri_error_code_out_of_memory = 0x00000024;                                     ///< 内存溢出 (out of memory)
const Zhuiri_error_code_time_out      = 0x00000025;                                     ///< 操作超时 (time out)
const Zhuiri_error_code_user_reject   = 0x00000098;                                     ///< 对方决绝 (user reject)
const Zhuiri_error_code_user_exit     = 0x00000099;                                     ///< 自行退出 (user exit)
};

enum Zhuiri_data_sign
{
const Zhuiri_data_sign_none           = 0x00000000;                                     ///< 无标识  (no sign)
const Zhuiri_data_sign_reliable       = 0x00000001;                                     ///< 可靠    (reliable)
const Zhuiri_data_sign_processing     = 0x00000002;                                     ///< 处理中  (processing)
const Zhuiri_data_sign_response       = 0x00000003;                                     ///< 回应消息 (response)
const Zhuiri_data_sign_heart          = 0x00000004;                                     ///< 心跳包  (heart)
};

$ffi = FFI::cdef("
    void* tianzuo_ZhuiriInterface_initialize();
    void tianzuo_ZhuiriInterface_terminate(void* *ZhuiriInt_pointer);
    int tianzuo_ZhuiriInt_initialize(void* ZhuiriInt_pointer, const char* ip_addr, int port, const void* callback, const void* context, int const heart_check_time, bool log_trace, void* iocp);
    int tianzuo_ZhuiriInt_set_param(void* ZhuiriInt_pointer, int sender_index, int init_server_port, int msg_init_size, int recv_ex_data_max, int retry_max, int retry_all_number, int init_retry_time);
    int tianzuo_ZhuiriInt_send(void* ZhuiriInt_pointer, int sender_index, int ip, int port, int sign, int function, char* send_data, int send_size);
    void* tianzuo_DataQueueInterface_initialize();
    void tianzuo_DataQueueInterface_terminate(void* *DataQueue_pointer);
    typedef unsigned(*Zhuiri_callback)(const void *context, const void *pData);
", "tianzuo.Zhuiri.dll");

# 初始化接口 initialize the interface
echo "initialize the interface" . "\n";

# 创建实例 create an instance
$data_queue_recv = $ffi->tianzuo_DataQueueInterface_initialize();


//function myCallback($context, $pData) {
//    echo "phpCallback" . "\n";
//}
//
//// Define the callback function signature
//$callback = function($context, $pData) {
//    myCallback($context, $pData);
//};
//
//$callableCallback = FFI::addr($callback);


//$phpCallback = function($context, $pData): void {
//    echo "phpCallback" . "\n";
//};
//$callback= FFI::new("Zhuiri_callback", $phpCallback);


$callback = $ffi->callback("void(const char*)", function($message) {
    echo "Callback message: $message\n";
});



$port = 6666;
$zhuiri = $ffi->tianzuo_ZhuiriInterface_initialize();
$error_code = $ffi->tianzuo_ZhuiriInt_initialize($zhuiri, null, $port, $callback, $data_queue_recv, 6000, False, null);
if ($error_code != Zhuiri_error_code::Zhuiri_error_code_success) {
    echo "initialize error: " . $error_code . "\n";
    return;
}

# 设置默认参数 set default parameters
$ffi->tianzuo_ZhuiriInt_set_param($zhuiri, 0, 5168, 1024, 2280, 3, 5, 600);

# 开始发送数据 start sending data
$ip = ip2long("127.0.0.1");
for ($i = 0; $i < 10; $i++) {
    $data = sprintf("send data %d", $i);
    $data_len = strlen($data);
    echo "ip: " . $ip . "\n";
    echo "port: " . $port . "\n";
    echo "send data: " . $data . "\n";
    echo "data_len: " . $data_len . "\n";
    $error_code = $ffi->tianzuo_ZhuiriInt_send($zhuiri, 0, $ip, $port, Zhuiri_data_sign::Zhuiri_data_sign_reliable, 7788, $data, $data_len);
    if ($error_code != Zhuiri_error_code::Zhuiri_error_code_success) {
        echo "send error: " . $error_code . "\n";
        return;
    }
}

echo "test done" . "\n";


?>