package cn.camelsoft;

import com.sun.jna.Pointer;
import com.sun.jna.Structure;

import java.util.Arrays;
import java.util.List;

public class Zhuiri_data_struct extends Structure {
    public int m_ip_adrs;
    public int m_port;
    public int m_function;
    public int m_sign;
    public int m_index;
    public int m_send_time;
    public int m_send_size;
    public byte[] m_data = new byte[492];
    @Override
    protected List<String> getFieldOrder() {
        return Arrays.asList("m_ip_adrs", "m_port", "m_function", "m_sign", "m_index", "m_send_time", "m_send_size", "m_data");
    }
    public Zhuiri_data_struct() {
        super();
    }
    public Zhuiri_data_struct(Pointer pointer) {
        super(pointer);
        read();
    }
}
