package cn.camelsoft;

import com.sun.jna.Pointer;
import com.sun.jna.Structure;

import java.util.Arrays;
import java.util.List;

public class Zhuiri_data_pkg_struct extends Structure {
    public Zhuiri_data_struct m_data;
    public Pointer m_send_data;
    public Pointer m_Zhuiri;
    public Pointer m_user_data;
    @Override
    protected List<String> getFieldOrder() {
        return Arrays.asList("m_data", "m_send_data", "m_Zhuiri", "m_user_data");
    }
    public Zhuiri_data_pkg_struct() {
        super();
    }
    public Zhuiri_data_pkg_struct(Pointer pointer) {
        super(pointer);
        read();
    }
}
