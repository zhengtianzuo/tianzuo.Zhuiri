
Zhuiri_error_code_success       = 0x00000001;                                     ///< 正确的值 (success)
Zhuiri_error_code_no_rights     = 0x00000002;                                     ///< 效验未通过 (no rights)
Zhuiri_error_code_socket        = 0x0000000D;                                     ///< 套接字错误 (socket error)
Zhuiri_error_code_thread_error  = 0x00000021;                                     ///< 线程失败 (thread error)
Zhuiri_error_code_handle        = 0x00000022;                                     ///< 创建句柄失败 (handle error)
Zhuiri_error_code_out_of_cache  = 0x00000023;                                     ///< 超出缓冲最大值 (out f cache)
Zhuiri_error_code_out_of_memory = 0x00000024;                                     ///< 内存溢出 (out of memory)
Zhuiri_error_code_time_out      = 0x00000025;                                     ///< 操作超时 (time out)
Zhuiri_error_code_user_reject   = 0x00000098;                                     ///< 对方决绝 (user reject)
Zhuiri_error_code_user_exit     = 0x00000099;                                     ///< 自行退出 (user exit)

Zhuiri_data_sign_none           = 0x00000000;                                     ///< 无标识  (no sign)
Zhuiri_data_sign_reliable       = 0x00000001;                                     ///< 可靠    (reliable)
Zhuiri_data_sign_processing     = 0x00000002;                                     ///< 处理中  (processing)
Zhuiri_data_sign_response       = 0x00000003;                                     ///< 回应消息 (response)
Zhuiri_data_sign_heart          = 0x00000004;                                     ///< 心跳包  (heart)

let ffi = require('ffi-napi')
const ref = require('ref-napi');
let StructType = require('ref-struct-napi');

let tianzuo_ZhuiriLib = ffi.Library("tianzuo.Zhuiri.dll", {
    'tianzuo_ZhuiriInterface_initialize': ['pointer', []],
    'tianzuo_ZhuiriInterface_terminate':['void',['pointer']],
    'tianzuo_ZhuiriInt_initialize':['int',['pointer','pointer','int','pointer','pointer','int', 'bool','pointer']],
    'tianzuo_ZhuiriInt_set_param':['int',['pointer','int','int','int','int','int','int','int']],
    'tianzuo_ZhuiriInt_send':['int',['pointer','int','int','int','int','int','string','int']],
    'tianzuo_DataQueueInterface_initialize': ['pointer', []],
    'tianzuo_DataQueueInterface_terminate':['void',['pointer']],
})

function ipToInt(ip) {
    let parts = ip.split('.').map(Number);
    return (parts[0] << 24) + (parts[1] << 16) + (parts[2] << 8) + parts[3];
}

var Zhuiri_data_struct = StructType({
    'm_ip_adrs': 'int',
    'm_port': 'int',
    'm_function': 'int',
    'm_sign': 'int',
    'm_index': 'int',
    'm_send_time': 'int',
    'm_send_size': 'int',
    'm_data': 'char*'
});
var Zhuiri_data_pointer = ref.refType(Zhuiri_data_struct);

var Zhuiri_data_pkg_struct = StructType({
    'm_data': 'void*',
    'm_send_data': 'void*',
    'm_Zhuiri': 'void*',
    'm_user_data': 'void*'
});
var Zhuiri_data_pkg_pointer = ref.refType(Zhuiri_data_pkg_struct);

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function main() {
    // 初始化接口 initialize the interface
    console.log("initialize the interface\n");

    // 创建实例 create an instance
    let data_queue_recv = tianzuo_ZhuiriLib.tianzuo_DataQueueInterface_initialize();

    const callback = ffi.Callback('void', ['pointer','pointer'], function(context, pData) {
        const data = ref.deref(pData, 0, Zhuiri_data_pkg_struct);
        console.log('recv data: %s\n', data.m_data.m_data);
    });

    let port = 6666;
    let zhuiri = tianzuo_ZhuiriLib.tianzuo_ZhuiriInterface_initialize();
    let error_code = tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_initialize(zhuiri, null, port, callback, data_queue_recv, 6000, false, null);
    if (error_code !== Zhuiri_error_code_success) {
        console.log("tianzuo_ZhuiriInt_initialize error: %d\n", error_code);
        return;
    }

    // 设置默认参数 set default parameters
    tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_set_param(zhuiri, 0, 5168, 1024, 2280, 3, 5, 600);

    // 开始发送数据 start sending data
    const ipString = '127.0.0.1';
    const ip = ipToInt(ipString);
    let sport = 6666;
    for (let i = 0; i < 10; i++) {
        const data = `send data ${i}`;
        const data_len = data.length;

        error_code = tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_send(zhuiri, 0, ip, sport, Zhuiri_data_sign_reliable, 7788, data, data_len);
        if (error_code !== Zhuiri_error_code_success) {
            console.log("tianzuo_ZhuiriInt_send error: %d\n", error_code);
            return;
        }
    }

    await sleep(20000);
}

main();

console.log("test done\n");
