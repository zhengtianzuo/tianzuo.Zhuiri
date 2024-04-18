package cn.camelsoft;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Pointer;
import com.sun.jna.Callback;
import com.sun.jna.CallbackReference;
import com.sun.jna.ptr.IntByReference;
import java.net.InetAddress;
import java.net.UnknownHostException;

enum Zhuiri_error_code {
    Zhuiri_error_code_success       (0x00000001),                                     ///< 正确的值 (success)
    Zhuiri_error_code_no_rights     (0x00000002),                                     ///< 效验未通过 (no rights)
    Zhuiri_error_code_socket        (0x0000000D),                                     ///< 套接字错误 (socket error)
    Zhuiri_error_code_thread_error  (0x00000021),                                     ///< 线程失败 (thread error)
    Zhuiri_error_code_handle        (0x00000022),                                     ///< 创建句柄失败 (handle error)
    Zhuiri_error_code_out_of_cache  (0x00000023),                                     ///< 超出缓冲最大值 (out f cache)
    Zhuiri_error_code_out_of_memory (0x00000024),                                     ///< 内存溢出 (out of memory)
    Zhuiri_error_code_time_out      (0x00000025),                                     ///< 操作超时 (time out)
    Zhuiri_error_code_user_reject   (0x00000098),                                     ///< 对方决绝 (user reject)
    Zhuiri_error_code_user_exit     (0x00000099);                                     ///< 自行退出 (user exit)
    private int value;
    Zhuiri_error_code(int value) {
        this.value = value;
    }
    public int getValue() {
        return value;
    }
};

enum Zhuiri_data_sign {
    Zhuiri_data_sign_none       (0x00000000),                                         ///< 无标识  (no sign)
    Zhuiri_data_sign_reliable   (0x00000001),                                         ///< 可靠    (reliable)
    Zhuiri_data_sign_processing (0x00000002),                                         ///< 处理中  (processing)
    Zhuiri_data_sign_response   (0x00000003),                                         ///< 回应消息 (response)
    Zhuiri_data_sign_heart      (0x00000004);                                         ///< 心跳包  (heart)
    private int value;
    Zhuiri_data_sign(int value) {
        this.value = value;
    }
    public int getValue() {
        return value;
    }
};

interface tianzuo_ZhuiriLib extends Library {
    tianzuo_ZhuiriLib instance = (tianzuo_ZhuiriLib) Native.load("./tianzuo.Zhuiri.dll", tianzuo_ZhuiriLib.class);
    Pointer tianzuo_ZhuiriInterface_initialize();
    void tianzuo_ZhuiriInterface_terminate(Pointer zhuiri);
    int tianzuo_ZhuiriInt_initialize(Pointer zhuiri, String ip_addr, int port, Pointer callback, Pointer context, int heart_check_time, Boolean log_trace, Pointer iocp);
    int tianzuo_ZhuiriInt_set_param(Pointer zhuiri, int sender_index, int init_server_port, int msg_init_size, int recv_ex_data_max, int retry_max, int retry_all_number, int init_retry_time);
    int tianzuo_ZhuiriInt_send(Pointer zhuiri, int sender_index, int ip, int port, int sign, int function, String send_data, int send_size);
}

interface tianzuo_DataQueueLib extends Library {
    tianzuo_DataQueueLib instance = (tianzuo_DataQueueLib) Native.load("./tianzuo.Zhuiri.dll", tianzuo_DataQueueLib.class);
    Pointer tianzuo_DataQueueInterface_initialize();
    void tianzuo_DataQueueInterface_terminate(Pointer DataQueue);
    int tianzuo_DataQueueInt_initialize(Pointer DataQueue);
}

interface MyCallback extends Callback {
    void callbackFunction(Pointer context, Pointer pData);
}
class MyCallbackImpl implements MyCallback {

    @Override
    public void callbackFunction(Pointer context, Pointer pData) {
        Zhuiri_data_pkg_struct data_pkg = new Zhuiri_data_pkg_struct(pData);
        String str = new String(data_pkg.m_data.m_data).trim();
        System.out.printf("recv data: %s\n", str);
    }
}

public class Main {
    public static int ipToInt(String ipAddress) {
        try {
            InetAddress inetAddress = InetAddress.getByName(ipAddress);
            byte[] bytes = inetAddress.getAddress();

            int result = 0;
            for (byte b : bytes) {
                result = result << 8 | (b & 0xFF);
            }

            return result;
        } catch (UnknownHostException e) {
            System.err.println("Invalid IP address: " + ipAddress);
            return 0;
        }
    }

    public static void main(String[] args) {

        System.setProperty("jna.encoding","UTF-8");

        // 初始化接口 initialize the interface
        System.out.printf("initialize the interface\n");

        // 创建实例 create an instance
        Pointer data_queue_recv = tianzuo_DataQueueLib.instance.tianzuo_DataQueueInterface_initialize();

        MyCallback callback = new MyCallbackImpl();
        Pointer pcallback = CallbackReference.getFunctionPointer(callback);

        Pointer zhuiri = tianzuo_ZhuiriLib.instance.tianzuo_ZhuiriInterface_initialize();
        int port = 6666;
        int error_code = tianzuo_ZhuiriLib.instance.tianzuo_ZhuiriInt_initialize(zhuiri, null, port, pcallback, data_queue_recv, 6000, false, null);
        if (error_code != Zhuiri_error_code.Zhuiri_error_code_success.getValue()) {
            System.out.printf("tianzuo_QiankunInt_initialize error: %d\n", error_code);
            return;
        }

        // 设置默认参数 set default parameters
        tianzuo_ZhuiriLib.instance.tianzuo_ZhuiriInt_set_param(zhuiri, 0, 5168, 1024, 2280, 3, 5, 600);

        // 开始发送数据 start sending data
        String ipAddress = "127.0.0.1";
        int ip = ipToInt(ipAddress);
        int sport = 6666;
        for (int i = 0; i < 100; i++) {
            String data = String.format("send data %d ", i);
            int data_len = data.length();
            int error_code2 = tianzuo_ZhuiriLib.instance.tianzuo_ZhuiriInt_send(zhuiri, 0, ip, sport, Zhuiri_data_sign.Zhuiri_data_sign_reliable.getValue(), 7788, data, data_len);
            if (error_code2 != Zhuiri_error_code.Zhuiri_error_code_success.getValue()) {
                System.out.printf("tianzuo_ZhuiriInt_send error: %d\n", error_code2);
                return;
            }
        }
		
		System.out.printf("test done\n");
    }
}