require 'fiddle'
require 'ipaddr'

lib = Fiddle::dlopen('C:/Users/zhengtianzuo/RubymineProjects/tianzuo.ZhuiriTest/tianzuo.Zhuiri.dll')
tianzuo_ZhuiriInterface_initialize = Fiddle::Function.new(lib['tianzuo_ZhuiriInterface_initialize'], [], Fiddle::TYPE_VOIDP)
tianzuo_ZhuiriInterface_terminate = Fiddle::Function.new(lib['tianzuo_ZhuiriInterface_terminate'], [Fiddle::TYPE_VOIDP], Fiddle::TYPE_VOID)
tianzuo_ZhuiriInt_initialize = Fiddle::Function.new(lib['tianzuo_ZhuiriInt_initialize'], [Fiddle::TYPE_VOIDP, Fiddle::TYPE_VOIDP, Fiddle::TYPE_INT, Fiddle::TYPE_VOIDP, Fiddle::TYPE_VOIDP, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_VOIDP], Fiddle::TYPE_INT)
tianzuo_ZhuiriInt_set_param = Fiddle::Function.new(lib['tianzuo_ZhuiriInt_set_param'], [Fiddle::TYPE_VOIDP, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_INT], Fiddle::TYPE_INT)
tianzuo_ZhuiriInt_send = Fiddle::Function.new(lib['tianzuo_ZhuiriInt_send'], [Fiddle::TYPE_VOIDP, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_INT, Fiddle::TYPE_VOIDP, Fiddle::TYPE_INT], Fiddle::TYPE_INT)
tianzuo_DataQueueInterface_initialize = Fiddle::Function.new(lib['tianzuo_DataQueueInterface_initialize'], [], Fiddle::TYPE_VOIDP)
tianzuo_DataQueueInterface_terminate = Fiddle::Function.new(lib['tianzuo_DataQueueInterface_terminate'], [Fiddle::TYPE_VOIDP], Fiddle::TYPE_VOID)

def string_to_char_pointer(str)
  ptr = Fiddle::Pointer[str]
  ptr.to_s
end

# 初始化接口 initialize the interface
print("initialize the interface\n")

# 创建实例 create an instance
data_queue_recv = tianzuo_DataQueueInterface_initialize.call()

callback = Fiddle::Closure::BlockCaller.new(Fiddle::TYPE_INT, [Fiddle::TYPE_VOIDP, Fiddle::TYPE_VOIDP]) do |context, pData|
  puts "callback function called"
end

port = 6666
zhuiri = tianzuo_ZhuiriInterface_initialize.call()
error_code = tianzuo_ZhuiriInt_initialize.call(zhuiri, nil, port, callback.to_i, data_queue_recv, 6000, 0, nil)
if error_code != 1
  print("initialize error:", error_code, "\n")
  return
end

# 设置默认参数 set default parameters
tianzuo_ZhuiriInt_set_param.call(zhuiri, 0, 5168, 1024, 2280, 3, 5, 600)

# 开始发送数据 start sending data
ip = IPAddr.new("127.0.0.1").to_i
for i in 1..10
  data = "send data %d" % [i]
  data_len = data.length
  error_code = tianzuo_ZhuiriInt_send.call(zhuiri, 0, ip, port, 1, 7788, data, data_len)
  if error_code != 1
    print("tianzuo_ZhuiriInt_send error:", error_code, "\n")
    return
  end
end
