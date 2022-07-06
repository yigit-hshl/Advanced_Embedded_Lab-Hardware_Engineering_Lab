library IEEE;
use IEEE.numeric_bit.all;
entity BCD_Adder is
   port(X, Y: in unsigned(7 downto 0);
       Z: out unsigned(11 downto 0)); 
end BCD_Adder;

Z digit 2 Z digit 1 Z digit 0
  architecture BCDadd of BCD_Adder is
  alias Xdig1: unsigned(3 downto 0) is X(7 downto 4); 
  alias Xdig0: unsigned(3 downto 0) is X(3 downto 0);
  alias Ydig1: unsigned(3 downto 0) is Y(7 downto 4);
  alias Ydig0: unsigned(3 downto 0) is Y(3 downto 0);
  alias Zdig2: unsigned(3 downto 0) is Z(11 downto 8);
  alias Zdig1: unsigned(3 downto 0) is Z(7 downto 4);
  alias Zdig0: unsigned(3 downto 0) is Z(3 downto 0);
  signal S0, S1: unsigned(4 downto 0); 
  signal C: bit;
begin
S0 <= '0' & Xdig0 + Ydig0; -- overloaded + 
Zdig0 <= S0(3 downto 0) + 6 when S0 > 9
    else S0(3 downto 0); -- add 6 if needed 
C <= '1' when S0 > 9 else '0';
S1 <= '0' & Xdig1 + Ydig1 + unsigned'(0=>C);
              -- type conversion done on C before adding 
Zdig1 <= S1(3 downto 0) + 6 when S1 > 9
else S1(3 downto 0);
Zdig2 <= "0001" when S1 > 9 else "0000";
end BCDadd;
