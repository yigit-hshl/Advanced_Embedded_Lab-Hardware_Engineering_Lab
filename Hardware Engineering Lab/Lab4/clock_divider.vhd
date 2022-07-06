library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
entity clock_div is
port (
   clk_in: in std_logic; -- clock input on FPGA
   clk_out: out std_logic -- clock output 
  );
end clock_div;

architecture Behavioral of clock_div is
signal divisor: std_logic_vector(27 downto 0):=(others =>'0');
begin
 process(clk_in)
 begin
 if(rising_edge(clk_in)) then
 divisor <= divisor + x"0000001";
 
 if(divisor>=x"0000001") then 

 divisor <= x"0000000";
 end if;
 if(divisor<x"0000001") then  
 clk_out <= '1';
 else 
 clk_out <= '0';
 end if;
 end if;
 end process;
end Behavioral;
