
Imports System.IO
Imports System.Net
Imports System.Runtime.InteropServices
Imports System.Runtime.InteropServices.JavaScript.JSType
Imports System.Text

Enum Zhuiri_error_code
    Zhuiri_error_code_success = 1                                            ' ��ȷ��ֵ (success)
    Zhuiri_error_code_no_rights = 2                                          ' Ч��δͨ�� (no rights)
    Zhuiri_error_code_socket = 13                                            ' �׽��ִ��� (socket Error)
    Zhuiri_error_code_thread_error = 21                                      ' �߳�ʧ�� (thread Error)
    Zhuiri_error_code_handle = 22                                            ' �������ʧ�� (handle Error)
    Zhuiri_error_code_out_of_cache = 23                                      ' �����������ֵ (out f cache)
    Zhuiri_error_code_out_of_memory = 24                                     ' �ڴ���� (out Of memory)
    Zhuiri_error_code_time_out = 25                                          ' ������ʱ (time out)
    Zhuiri_error_code_user_reject = 98                                       ' �Է����� (user reject)
    Zhuiri_error_code_user_exit = 99                                         ' �����˳� (user Exit)
End Enum

Enum Zhuiri_data_sign
    Zhuiri_data_sign_none = 0                                               ' �ޱ�ʶ  (no sign)
    Zhuiri_data_sign_reliable = 1                                           ' �ɿ�    (reliable)
    Zhuiri_data_sign_processing = 2                                         ' ������  (processing)
    Zhuiri_data_sign_response = 3                                           ' ��Ӧ��Ϣ (response)
    Zhuiri_data_sign_heart = 4                                              ' ������  (heart)
End Enum

Structure Zhuiri_data_struct
    Public m_ip_adrs As Integer
    Public m_port As Integer
    Public m_function As Integer
    Public m_sign As Integer
    Public m_index As Integer
    Public m_send_time As Integer
    Public m_send_size As Integer
    <MarshalAs(UnmanagedType.ByValArray, SizeConst:=492)>
    Public m_data As Byte()
End Structure

Structure Zhuiri_data_pkg_struct
    Public m_data As Zhuiri_data_struct
    Public m_send_data As IntPtr
    Public m_Zhuiri As IntPtr
    Public m_user_data As IntPtr
End Structure

Module Program
    <DllImport("tianzuo.Zhuiri.dll")>
    Public Function tianzuo_ZhuiriInterface_initialize() As IntPtr
    End Function
    <DllImport("tianzuo.Zhuiri.dll")>
    Public Function tianzuo_ZhuiriInterface_terminate(ByRef ZhuiriInt_pointer As IntPtr)
    End Function
    <DllImport("tianzuo.Zhuiri.dll")>
    Public Function tianzuo_ZhuiriInt_initialize(ZhuiriInt_pointer As IntPtr, ip_addr As String, port As Integer,
        callback As IntPtr, context As IntPtr, heart_check_time As Integer, log_trace As Boolean, iocp As IntPtr) As Integer
    End Function
    <DllImport("tianzuo.Zhuiri.dll")>
    Public Function tianzuo_ZhuiriInt_set_param(ZhuiriInt_pointer As IntPtr,
        sender_index As Integer, init_server_port As Integer, msg_init_size As Integer,
        recv_ex_data_max As Integer, retry_max As Integer, retry_all_number As Integer,
        init_retry_time As Integer) As Integer
    End Function
    <DllImport("tianzuo.Zhuiri.dll")>
    Public Function tianzuo_ZhuiriInt_send(ZhuiriInt_pointer As IntPtr,
        sender_index As Integer, ip As Integer, port As Integer, sign As Integer, func As Integer, send_data As String, send_size As Integer) As Integer
    End Function
    <DllImport("tianzuo.Zhuiri.dll")>
    Public Function tianzuo_DataQueueInterface_initialize() As IntPtr
    End Function
    <DllImport("tianzuo.Zhuiri.dll")>
    Public Function tianzuo_DataQueueInterface_terminate(ByRef DataQueue_pointer As IntPtr)
    End Function

    Public Delegate Sub CallbackFunc(context As IntPtr, pData As IntPtr)

    Public Sub msg_recv_callback(context As IntPtr, pData As IntPtr)
        Dim data As Zhuiri_data_pkg_struct = Marshal.PtrToStructure(Of Zhuiri_data_pkg_struct)(pData)
        Dim Str As String = Encoding.ASCII.GetString(data.m_data.m_data)
        Console.WriteLine("recv data:" + Str)
    End Sub

    Sub Main(args As String())

        ' ��ʼ���ӿ� initialize the interface
        Console.WriteLine("initialize the interface")

        ' ����ʵ�� create an instance
        Dim data_queue_recv As IntPtr = tianzuo_DataQueueInterface_initialize()
        Dim callbackDelegate As CallbackFunc = AddressOf msg_recv_callback
        Dim callbackPtr As IntPtr = Marshal.GetFunctionPointerForDelegate(callbackDelegate)

        Dim port As Integer = 6666
        Dim Zhuiri As IntPtr = tianzuo_ZhuiriInterface_initialize()
        Dim error_code As Integer = tianzuo_ZhuiriInt_initialize(Zhuiri, IntPtr.Zero, port, callbackPtr, data_queue_recv, 6000, False, IntPtr.Zero)
        If (error_code <> Zhuiri_error_code.Zhuiri_error_code_success) Then
            Console.WriteLine("tianzuo_ZhuiriInt_initialize error:" + error_code.ToString)
            Return
        End If

        ' ����Ĭ�ϲ��� Set Default parameters
        tianzuo_ZhuiriInt_set_param(Zhuiri, 0, 5168, 1024, 2280, 3, 5, 600)

        ' ��ʼ�������� start sending data
        Dim ipAddressString As String = "127.0.1.1"
        Dim ipAddress As IPAddress = IPAddress.Parse(ipAddressString)
        Dim bytes As Byte() = ipAddress.GetAddressBytes()
        If (BitConverter.IsLittleEndian) Then
            Array.Reverse(bytes)
        End If
        Dim ip As Integer = BitConverter.ToInt32(bytes, 0)
        Dim sport As Integer = 6666
        For i As Integer = 0 To 99
            Dim data As String = String.Format("send data {0}", i)
            Dim data_len As Integer = data.Length
            error_code = tianzuo_ZhuiriInt_send(Zhuiri, 0, ip, sport, Zhuiri_data_sign.Zhuiri_data_sign_reliable, 7788, data, data_len)
            If (error_code <> Zhuiri_error_code.Zhuiri_error_code_success) Then
                Console.WriteLine("tianzuo_ZhuiriInt_send error:" + error_code.ToString)
                Return
            End If
        Next

        Console.WriteLine("test done -------------------")

    End Sub
End Module
