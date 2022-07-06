library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity DFF_tb is
end entity;

architecture tb of DFF_tb is

component D_FLIPFLOP_SOURCE is
Port ( D, CLK, RST : in STD_LOGIC;
Q, Qb : out STD_LOGIC);
end component ;

signal D, CLK, RST, Q, Qb : STD_LOGIC;

begin
uut: D_FLIPFLOP_SOURCE port map(
D => D,
CLK => CLK,
RST => RST,
Q => Q,
Qb => Qb);

Clock : process
begin
CLK <= '0';
wait for 10 ns;
CLK <= '1';
wait for 10 ns;
end process;

stim : process
begin

RST <= '0';
D <= '0';
wait for 40 ns;
D <= '1';
wait for 40 ns;

end process;
end tb;
