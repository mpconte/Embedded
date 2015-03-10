library verilog;
use verilog.vl_types.all;
entity BCDcount is
    port(
        Clock           : in     vl_logic;
        Clear           : in     vl_logic;
        E               : in     vl_logic;
        BCD3            : out    vl_logic_vector(3 downto 0);
        BCD2            : out    vl_logic_vector(3 downto 0);
        BCD1            : out    vl_logic_vector(3 downto 0);
        BCD0            : out    vl_logic_vector(3 downto 0)
    );
end BCDcount;
