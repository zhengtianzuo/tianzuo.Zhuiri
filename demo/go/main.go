package main

/*
#include "tianzuo.ZhuiriInterface.h"
void msg_recv_callback_cgo(const void *context, const void *pData);
*/
import "C"
import (
	"fmt"
	"net"
	"syscall"
	"unsafe"
)

const (
	Zhuiri_error_code_success       = 1  // 正确的值 (success)
	Zhuiri_error_code_no_rights     = 2  // 效验未通过 (no rights)
	Zhuiri_error_code_socket        = 13 // 套接字错误 (socket error)
	Zhuiri_error_code_thread_error  = 21 // 线程失败 (thread error)
	Zhuiri_error_code_handle        = 22 // 创建句柄失败 (handle error)
	Zhuiri_error_code_out_of_cache  = 23 // 超出缓冲最大值 (out f cache)
	Zhuiri_error_code_out_of_memory = 24 // 内存溢出 (out of memory)
	Zhuiri_error_code_time_out      = 25 // 操作超时 (time out)
	Zhuiri_error_code_user_reject   = 98 // 对方决绝 (user reject)
	Zhuiri_error_code_user_exit     = 99 // 自行退出 (user exit)
)

const (
	Zhuiri_data_sign_none       = 0 // 无标识  (no sign)
	Zhuiri_data_sign_reliable   = 1 // 可靠    (reliable)
	Zhuiri_data_sign_processing = 2 // 处理中  (processing)
	Zhuiri_data_sign_response   = 3 // 回应消息 (response)
	Zhuiri_data_sign_heart      = 4 // 心跳包  (heart)
)

func ipToInt(ip net.IP) uint32 {
	ip = ip.To4()
	if ip == nil {
		return 0
	}

	ipInt := uint32(ip[0])<<24 | uint32(ip[1])<<16 | uint32(ip[2])<<8 | uint32(ip[3])
	return ipInt
}

type Zhuiri_data_pkg_struct C.Zhuiri_data_pkg_struct

//export msg_recv_callback
func msg_recv_callback(context unsafe.Pointer, pData unsafe.Pointer) {
	data := *(*Zhuiri_data_pkg_struct)(unsafe.Pointer(pData))
	charArray := data.m_data.m_data
	goStr := C.GoString((*C.char)(unsafe.Pointer(&charArray[0])))
	fmt.Println("recv data:", goStr)
}

func main() {
	// 初始化接口 initialize the interface
	dll := syscall.MustLoadDLL("tianzuo.Zhuiri.dll")

	// 创建实例 create an instance
	tianzuo_DataQueueInterface_initialize := dll.MustFindProc("tianzuo_DataQueueInterface_initialize")
	data_queue_recv, _, _ := tianzuo_DataQueueInterface_initialize.Call()

	tianzuo_ZhuiriInterface_initialize := dll.MustFindProc("tianzuo_ZhuiriInterface_initialize")
	Zhuiri, _, _ := tianzuo_ZhuiriInterface_initialize.Call()

	var ip uintptr
	port := 6666
	var iocp uintptr
	tianzuo_ZhuiriInt_initialize := dll.MustFindProc("tianzuo_ZhuiriInt_initialize")
	msg_recv_callback_ptr := uintptr(unsafe.Pointer(C.msg_recv_callback_cgo))
	error_code, _, _ := tianzuo_ZhuiriInt_initialize.Call(Zhuiri, ip, uintptr(C.int(port)), msg_recv_callback_ptr, data_queue_recv, 6000, uintptr(C.int(0)), iocp)
	if error_code != Zhuiri_error_code_success {
		fmt.Println("tianzuo_ZhuiriInt_initialize error: ", error_code)
	}

	// 设置默认参数 set default parameters
	tianzuo_ZhuiriInt_set_param := dll.MustFindProc("tianzuo_ZhuiriInt_set_param")
	tianzuo_ZhuiriInt_set_param.Call(Zhuiri, 0, 5168, 1024, 2280, 3, 5, 600)

	// 开始发送数据 start sending data
	ipStr := "127.0.0.1"
	ipint := net.ParseIP(ipStr)
	nip := ipToInt(ipint)
	tianzuo_ZhuiriInt_send := dll.MustFindProc("tianzuo_ZhuiriInt_send")
	for i := 0; i < 100; i++ {
		data := "send data %d"
		gdata := fmt.Sprintf(data, i)
		cdata := C.CString(gdata)
		gdata_len := len(gdata)
		data_len := C.int(gdata_len)
		error_code, _, _ = tianzuo_ZhuiriInt_send.Call(Zhuiri, 0, uintptr(C.int(nip)), uintptr(C.int(port)), Zhuiri_data_sign_reliable, 7788, uintptr(unsafe.Pointer(cdata)), uintptr(data_len))
		if error_code != Zhuiri_error_code_success {
			fmt.Println("tianzuo_ZhuiriInt_send error: ", error_code)
			return
		}
	}

	fmt.Println("test done -------------------")
}
