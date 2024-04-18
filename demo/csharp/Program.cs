

using System.Collections;
using System.Net;
using System.Runtime.InteropServices;
using System.Text;

public enum Zhuiri_error_code
{
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
}

public enum Zhuiri_data_sign
{
    Zhuiri_data_sign_none       = 0x00000000,                                         ///< 无标识  (no sign)
    Zhuiri_data_sign_reliable   = 0x00000001,                                         ///< 可靠    (reliable)
    Zhuiri_data_sign_processing = 0x00000002,                                         ///< 处理中  (processing)
    Zhuiri_data_sign_response   = 0x00000003,                                         ///< 回应消息 (response)
    Zhuiri_data_sign_heart      = 0x00000004,                                         ///< 心跳包  (heart)
};

public struct Zhuiri_data_struct
{
    public Zhuiri_data_struct()
    {
    }
    public int m_ip_adrs;
    public int m_port;
    public int m_function;
    public int m_sign;
    public int m_index;
    public int m_send_time;
    public int m_send_size;
    [MarshalAs(UnmanagedType.ByValArray, SizeConst = 492)]
    public byte[] m_data;
}

public struct Zhuiri_data_pkg_struct
{
    public Zhuiri_data_pkg_struct()
    {
    }
    public Zhuiri_data_struct m_data;
    public IntPtr m_send_data;
    public IntPtr m_Zhuiri;
    public IntPtr m_user_data;
}

public delegate void CallbackDelegate(IntPtr context, IntPtr pData);

class Program
{
    [DllImport("tianzuo.Zhuiri.dll")]
    public static extern IntPtr tianzuo_ZhuiriInterface_initialize();
    [DllImport("tianzuo.Zhuiri.dll")]
    public static extern void tianzuo_ZhuiriInterface_terminate(IntPtr Zhuiri);
    [DllImport("tianzuo.Zhuiri.dll")]
    public static extern int tianzuo_ZhuiriInt_initialize(IntPtr Zhuiri, string ip_addr, int port, IntPtr callback, IntPtr context, int heart_check_time, bool log_trace, IntPtr iocp);
    [DllImport("tianzuo.Zhuiri.dll")]
    public static extern IntPtr tianzuo_DataQueueInterface_initialize();
    [DllImport("tianzuo.Zhuiri.dll")]
    public static extern int tianzuo_ZhuiriInt_set_param(IntPtr Zhuiri, int sender_index, int init_server_port, int msg_init_size, int recv_ex_data_max, int retry_max, int retry_all_number, int init_retry_time);
    [DllImport("tianzuo.Zhuiri.dll")]
    public static extern int tianzuo_ZhuiriInt_send(IntPtr Zhuiri, int sender_index, int ip, int port, int sign, int function, string send_data, int send_size);

    static void MyCallback(IntPtr context, IntPtr pData)
    {
        Zhuiri_data_pkg_struct data = Marshal.PtrToStructure<Zhuiri_data_pkg_struct>(pData);
        string str = Encoding.ASCII.GetString(data.m_data.m_data);
        Console.WriteLine("recv data:" + str);
    }

    static void Main(string[] args)
    {
        // 初始化接口 initialize the interface
        Console.WriteLine("initialize the interface\n");

        // 创建实例 create an instance
        IntPtr data_queue_recv = tianzuo_DataQueueInterface_initialize();

        CallbackDelegate callback = new CallbackDelegate(MyCallback);
        IntPtr callbackPtr = Marshal.GetFunctionPointerForDelegate(callback);

        IntPtr zhuiri = tianzuo_ZhuiriInterface_initialize();
        int port = 6666;
        int error_code = tianzuo_ZhuiriInt_initialize(zhuiri, null, port, callbackPtr, data_queue_recv, 6000, false, 0);
        if (error_code != ((int)Zhuiri_error_code.Zhuiri_error_code_success))
        {
            Console.WriteLine("tianzuo_ZhuiriInt_initialize error:" + error_code);
            return;
        }

        // 设置默认参数 set default parameters
        tianzuo_ZhuiriInt_set_param(zhuiri, 0, 5168, 1024, 2280, 3, 5, 600);

        // 开始发送数据 start sending data
        string ipAddressString = "127.0.1.1";
        IPAddress ipAddress = IPAddress.Parse(ipAddressString);
        byte[] bytes = ipAddress.GetAddressBytes();
        if (BitConverter.IsLittleEndian)
        {
            Array.Reverse(bytes);
        }
        int ip = BitConverter.ToInt32(bytes, 0);
        int sport = 6666;
        for (int i = 0; i < 100; i++)
        {
            string data = String.Format("send data {0}", i);
            int data_len = data.Length;
            error_code = tianzuo_ZhuiriInt_send(zhuiri, 0, ip, sport, (int)Zhuiri_data_sign.Zhuiri_data_sign_reliable, 7788, data, data_len);
            if (error_code != ((int)Zhuiri_error_code.Zhuiri_error_code_success))
            {
                Console.WriteLine("tianzuo_ZhuiriInt_send error:" + error_code);
                return;
            }
        }

        Console.WriteLine("test done");
    }
}
