
use std::os::raw::c_char;
use std::ffi::{c_int};
use std::ffi::CString;
use std::ptr::null;
use std::mem;

type CallbackFunc = extern "C" fn(context: *mut std::ffi::c_void, pData: *mut std::ffi::c_void);

struct Zhuiri_data_struct {
    m_ip_adrs: i32,
    m_port: i32,
    m_function: i32,
    m_sign: i32,
    m_index: i32,
    m_send_time: i32,
    m_send_size: i32,
    m_data: [u8; 492],
}

struct Zhuiri_data_pkg_struct {
    m_data: Zhuiri_data_struct,
    m_send_data: *const c_char,
    m_Zhuiri: *mut std::ffi::c_void,
    m_user_data: *mut std::ffi::c_void,
}

#[link(name = "tianzuo.Zhuiri")]
extern {
    fn tianzuo_ZhuiriInterface_initialize() -> *mut std::ffi::c_void;
    fn tianzuo_ZhuiriInterface_terminate(obj: *mut std::ffi::c_void);
    fn tianzuo_ZhuiriInt_initialize(obj: *mut std::ffi::c_void, ip_addr: *const c_char, port: c_int, callback: *mut std::ffi::c_void, context: *mut std::ffi::c_void, heart_check_time: c_int, log_trace: c_int, iocp: *const std::ffi::c_void) -> c_int;
    fn tianzuo_ZhuiriInt_set_param(obj: *mut std::ffi::c_void, sender_index: c_int, init_server_port: c_int, msg_init_size: c_int, recv_ex_data_max: c_int, retry_max: c_int, retry_all_number: c_int, init_retry_time: c_int);
    fn tianzuo_ZhuiriInt_send(obj: *mut std::ffi::c_void, sender_index: c_int, ip: c_int, port: c_int, sign: c_int, function: c_int, send_data: *const c_char, send_size: c_int) -> c_int;
    fn tianzuo_DataQueueInterface_initialize() -> *mut std::ffi::c_void;
    fn tianzuo_DataQueueInterface_terminate(obj: *mut std::ffi::c_void);
    fn tianzuo_DataQueueInt_initializee(obj: *mut std::ffi::c_void);
}

extern "C" fn msg_recv_callback(context: *mut std::ffi::c_void, pData: *mut std::ffi::c_void) {
    unsafe {
        //println!("Rust callback function called");
        let data: &mut Zhuiri_data_pkg_struct = unsafe { mem::transmute(pData) };
        let string = std::str::from_utf8(&data.m_data.m_data).unwrap();
        println!("recv data: {}", string);
    }
}

fn ip_to_int(ip: &str) -> i32 {
    let parts: Vec<i32> = ip.split('.').map(|part| part.parse().unwrap()).collect();
    (parts[0] << 24) + (parts[1] << 16) + (parts[2] << 8) + parts[3]
}

fn main() {
    unsafe {
        // 初始化接口 initialize the interface
        println!("initialize the interface");

        // 创建实例 create an instance
        let data_queue_recv = tianzuo_DataQueueInterface_initialize();

        let pdata_queue_recv= data_queue_recv as *mut std::ffi::c_void;

        let pmsg_recv_callback = msg_recv_callback as *mut std::ffi::c_void;

        let zhuiri = tianzuo_ZhuiriInterface_initialize();
        let port = 6666;
        let error_code = tianzuo_ZhuiriInt_initialize(zhuiri, null(), port, pmsg_recv_callback, pdata_queue_recv, 6000, 0, null());
        if 1 != error_code {
            println!("tianzuo_ZhuiriInt_initialize error: {:?}", error_code);
        }

        // 设置默认参数 set default parameters
        tianzuo_ZhuiriInt_set_param(zhuiri,0, 5168, 1024, 2280, 3, 5, 600);

        // 开始发送数据 start sending data
        let ip = ip_to_int("127.0.0.1");
        for i in 0..=99 {
            let data = format!("send data {}", i);
            let data_str = CString::new(String::from(data.clone())).expect("Failed to create CString");
            let data_len = data.len() as i32;
            let error_code = tianzuo_ZhuiriInt_send(zhuiri, 0, ip, port, 1, 7788, data_str.as_ptr(), data_len);
            if 1 != error_code {
                println!("tianzuo_ZhuiriInt_send error: {:?}", error_code);
            }
        }

        println!("test done -------------------")
    }
}
