library verilog;
use verilog.vl_types.all;
entity seg7 is
    port(
        bcd             : in     vl_logic_vector(3 downto 0);
        leds            : out    vl_logic_vector(6 downto 0)
    );
end seg7;
