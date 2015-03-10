library verilog;
use verilog.vl_types.all;
entity ms_clock is
    port(
        Clock           : in     vl_logic;
        newClock        : out    vl_logic
    );
end ms_clock;
