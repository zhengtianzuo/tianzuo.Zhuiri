#include <iostream>
#include <thread>
#include "../../include/tianzuo.ZhuiriInterface.h" // 接口头文件 interface heaher file

#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")

// 数据回调函数
void msg_recv_callback(void* context, Zhuiri_data_pkg_pointer data_pkg) {
    Zhuiri_data_pkg_struct data_new;
    memcpy(&data_new, data_pkg, sizeof(Zhuiri_data_pkg_struct));
    int send_size = data_pkg->m_data.get_send_size();
    if (send_size > Zhuiri_content_size) {
        char* send_data = new char[static_cast<unsigned int>(send_size)];
        memcpy(send_data, data_pkg->get_send_data(), static_cast<unsigned int>(send_size));
        data_new.set_send_data(send_data);
    }
    else {
        data_new.set_send_data(data_new.m_data.m_data);
    }
    tianzuo_DataQueue* const dataQueue = reinterpret_cast<tianzuo_DataQueue*>(context);
    dataQueue->push_back(&data_new);
}

// 接收线程
void recv_thread(tianzuo_DataQueue* data_queue_recv) {
    while (1) {
        Zhuiri_data_pkg_struct recv_msg;
        if (data_queue_recv->pop_up(&recv_msg) != Zhuiri_queue_error_code_success) {
            //std::cout << "pop_up no data" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            continue;
        }

        std::cout << "recv data: " << recv_msg.m_data.m_data << std::endl;
        if (strcmp(recv_msg.m_data.m_data, "send data 99") == 0) {
            std::cout << "recv done" << std::endl;
            return;
        }
    }
}

int main() {

    // 初始化接口 initialize the interface
    std::unique_ptr<tianzuo_ZhuiriInterface> zhuiri_interface(new tianzuo_ZhuiriInterface());

    // 创建实例 create an instance
    tianzuo_ZhuiriInt* zhuiri = zhuiri_interface->initialize();

    // 初始化数据队列接口 initialize the data queue interface
    std::unique_ptr<tianzuo_DataQueueInterface> data_queue_interface(new tianzuo_DataQueueInterface());

    // 创建数据队列实例 create an data queue instance
    tianzuo_DataQueue* data_queue_recv = data_queue_interface->initialize();

    // 初始化实例 initialize the instance
    int port = 6666;
    int error_code = zhuiri->initialize(
        nullptr, port, reinterpret_cast<void*>(msg_recv_callback),
        data_queue_recv, 6000, false);
    if (error_code != Zhuiri_error_code_success) {
        std::cout << "initialize error: " << error_code;

        // 释放接口 terminate the interface
        if (data_queue_interface != nullptr && data_queue_recv != nullptr) {
            data_queue_interface->terminate(&data_queue_recv);
        }
        if (zhuiri_interface != nullptr && zhuiri != nullptr) {
            zhuiri_interface->terminate(&zhuiri);
        }
        return -1;
    }

    // 设置默认参数 set default parameters
    Zhuiri_param_struct param(0, 5168, 1024, 2280, 3, 5, 600);
    zhuiri->set_param(&param);

    // 启动接收线程 start receiving thread
    std::thread recv_th(recv_thread, data_queue_recv);

    // 开始发送数据 start sending data
    int data_size = 1024;
    char data[1024];
    memset(data, 0, data_size);
    int ip = ntohl(inet_addr("127.0.0.1"));
    for (size_t i = 0; i < 100; i++) {
        //std::cout << "start send index: " << i << std::endl;
        sprintf_s(data, data_size, "send data %d", i);
        int data_len = strlen(data);
        Zhuiri_send_param_struct send_param(0, ip, port, Zhuiri_data_sign_reliable, 7788, data, data_len);
        error_code = zhuiri->send(&send_param);
        if (error_code != Zhuiri_error_code_success) {
            std::cout << "send error: " << error_code;

            // 释放接口 terminate the interface
            if (data_queue_interface != nullptr && data_queue_recv != nullptr) {
                data_queue_interface->terminate(&data_queue_recv);
            }
            if (zhuiri_interface != nullptr && zhuiri != nullptr) {
                zhuiri_interface->terminate(&zhuiri);
            }
            return -1;
        }
        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "send done" << std::endl;
    recv_th.join();

    // 释放接口 terminate the interface
    if (data_queue_interface != nullptr && data_queue_recv != nullptr) {
        data_queue_interface->terminate(&data_queue_recv);
    }
    if (zhuiri_interface != nullptr && zhuiri != nullptr) {
        zhuiri_interface->terminate(&zhuiri);
    }

    return 0;
}
