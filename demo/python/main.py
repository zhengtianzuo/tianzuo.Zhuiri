from ctypes import *
from enum import Enum
import ctypes
import ipaddress

tianzuo_ZhuiriLib = cdll.LoadLibrary('./tianzuo.Zhuiri.dll')


class Zhuiri_error_code(Enum):
    Zhuiri_error_code_success       = 0x00000001                                     # 正确的值 (success)
    Zhuiri_error_code_no_rights     = 0x00000002                                     # 效验未通过 (no rights)
    Zhuiri_error_code_socket        = 0x0000000D                                     # 套接字错误 (socket error)
    Zhuiri_error_code_thread_error  = 0x00000021                                     # 线程失败 (thread error)
    Zhuiri_error_code_handle        = 0x00000022                                     # 创建句柄失败 (handle error)
    Zhuiri_error_code_out_of_cache  = 0x00000023                                     # 超出缓冲最大值 (out f cache)
    Zhuiri_error_code_out_of_memory = 0x00000024                                     # 内存溢出 (out of memory)
    Zhuiri_error_code_time_out      = 0x00000025                                     # 操作超时 (time out)
    Zhuiri_error_code_user_reject   = 0x00000098                                     # 对方决绝 (user reject)
    Zhuiri_error_code_user_exit     = 0x00000099                                     # 自行退出 (user exit)


class Zhuiri_queue_error_code(Enum):
    Zhuiri_queue_error_code_success       = 0x00000001                               # 正确的值 (success)
    Zhuiri_queue_error_code_invalid_value = 0x00000002                               # 无效的值 (invalid value)
    Zhuiri_queue_error_code_out_of_cache  = 0x00000003                               # 超出缓冲 (out f cache)
    Zhuiri_queue_error_code_out_of_memory = 0x00000004                               # 内存溢出 (out of memory)
    Zhuiri_queue_error_code_no_data       = 0x00000005                               # 无数据 (no data)


class Zhuiri_data_sign(Enum):
    Zhuiri_data_sign_none       = 0x00000000                                         # 无标识  (no sign)
    Zhuiri_data_sign_reliable   = 0x00000001                                         # 可靠    (reliable)
    Zhuiri_data_sign_processing = 0x00000002                                         # 处理中  (processing)
    Zhuiri_data_sign_response   = 0x00000003                                         # 回应消息 (response)
    Zhuiri_data_sign_heart      = 0x00000004                                         # 心跳包  (heart)


class tianzuo_ZhuiriInt:
    def __init__(self):
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInterface_initialize.restype = c_void_p
        self.obj = tianzuo_ZhuiriLib.tianzuo_ZhuiriInterface_initialize()

    def __del__(self):
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInterface_terminate.argtypes = [c_void_p]
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInterface_terminate(self.obj)

    def initialize(self, ip_addr, port, callback, context, heart_check_time, log_trace, iocp):
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_initialize.restype = c_int
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_initialize.argtypes = [c_void_p, c_char_p, ctypes.c_int, c_void_p, c_void_p, ctypes.c_int, ctypes.c_int, c_void_p]
        return tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_initialize(self.obj, ip_addr, port, callback, context, heart_check_time, log_trace, iocp)

    def set_param(self, sender_index, init_server_port, msg_init_size, recv_ex_data_max, retry_max, retry_all_number, init_retry_time):
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_set_param.restype = c_int
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_set_param.argtypes = [c_void_p, c_int, c_int, c_int, c_int, c_int, c_int, c_int]
        return tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_set_param(self.obj, sender_index, init_server_port, msg_init_size, recv_ex_data_max, retry_max, retry_all_number, init_retry_time)

    def send(self, sender_index, ip, port, sign, function, send_data, send_size):
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_send.restype = c_int
        tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_send.argtypes = [c_void_p, c_int, c_int, c_int, c_int, c_int, c_char_p, c_int]
        return tianzuo_ZhuiriLib.tianzuo_ZhuiriInt_send(self.obj, sender_index, ip, port, sign, function, send_data, send_size)


class tianzuo_DataQueueInt:
    def __init__(self):
        tianzuo_ZhuiriLib.tianzuo_DataQueueInterface_initialize.restype = c_void_p
        self.obj = tianzuo_ZhuiriLib.tianzuo_DataQueueInterface_initialize()

    def __del__(self):
        tianzuo_ZhuiriLib.tianzuo_DataQueueInterface_terminate.argtypes = [c_void_p]
        tianzuo_ZhuiriLib.tianzuo_DataQueueInterface_terminate(self.obj)

    def initialize(self):
        tianzuo_ZhuiriLib.tianzuo_DataQueueInt_initialize.restype = c_void_p
        tianzuo_ZhuiriLib.tianzuo_DataQueueInt_initialize.argtypes = [c_void_p]
        return tianzuo_ZhuiriLib.tianzuo_DataQueueInt_initialize(self.obj)


callback_type = ctypes.CFUNCTYPE(c_void_p, c_void_p, c_void_p)


class Zhuiri_data_struct(ctypes.Structure):
    _fields_ = [("m_ip_adrs", ctypes.c_int),
                ("m_port", ctypes.c_int),
                ("m_function", ctypes.c_int),
                ("m_sign", ctypes.c_int),
                ("m_index", ctypes.c_int),
                ("m_send_time", ctypes.c_int),
                ("m_send_size", ctypes.c_int),
                ("m_data", ctypes.c_char * 492)]


class Zhuiri_data_pkg_struct(ctypes.Structure):
    _fields_ = [("m_data", Zhuiri_data_struct),
                ("m_send_data", ctypes.c_char_p),
                ("m_Zhuiri", ctypes.c_void_p),
                ("m_user_data", ctypes.c_void_p)]


def msg_recv_callback(context, pData):
    data = ctypes.cast(pData, ctypes.POINTER(Zhuiri_data_pkg_struct)).contents
    print("recv data:", data.m_data.m_data)


def main():
    # 初始化接口 initialize the interface
    print("initialize the interface")

    # 创建实例 create an instance
    data_queue_recv = tianzuo_DataQueueInt()
    pdata_queue_recv = ctypes.pointer(ctypes.py_object(data_queue_recv))

    pmsg_recv_callback = callback_type(msg_recv_callback)
	
    Zhuiri = tianzuo_ZhuiriInt()
    port = 6666
    error_code = Zhuiri.initialize(None, port, pmsg_recv_callback, pdata_queue_recv, 6000, False, None)
    if error_code != Zhuiri_error_code.Zhuiri_error_code_success.value:
        print("initialize error:", error_code)
        return

    # 设置默认参数 set default parameters
    Zhuiri.set_param(0, 5168, 1024, 2280, 3, 5, 600)

    # 开始发送数据 start sending data
    ip = int(ipaddress.IPv4Address("127.0.0.1"))
    for i in range(100):
        data = "send data {}".format(i)
        data_len = len(data)
        bytes_string = data.encode('utf-8')
        error_code = Zhuiri.send(0, ip, port, Zhuiri_data_sign.Zhuiri_data_sign_reliable.value, 7788, bytes_string, data_len)
        if error_code != Zhuiri_error_code.Zhuiri_error_code_success.value:
            print("send error:", error_code)
            return

    print("test done")


if __name__ == '__main__':
    main()
