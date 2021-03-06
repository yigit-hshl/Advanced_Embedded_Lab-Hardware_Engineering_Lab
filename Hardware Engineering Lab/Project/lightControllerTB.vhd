LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
  
ENTITY TST_BENCH IS
END TST_BENCH;
 
ARCHITECTURE behavior OF TST_BENCH IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT light_controller
    PORT(
         sensor_one : IN  std_logic;
         sensor_two : IN  std_logic;
         sensor_three : IN  std_logic;
         sensor_four : IN  std_logic;
         clk : IN  std_logic;
         rst_n : IN  std_logic;
         light_one : OUT  std_logic_vector(2 downto 0);
         light_two : OUT  std_logic_vector(2 downto 0);
         light_three : OUT  std_logic_vector(2 downto 0);
         light_four : OUT  std_logic_vector(2 downto 0);
         ped_one : OUT  std_logic_vector(1 downto 0);
         ped_two : OUT  std_logic_vector(1 downto 0);
         ped_three : OUT  std_logic_vector(1 downto 0);
         ped_four : OUT  std_logic_vector(1 downto 0);
         ped_five : OUT  std_logic_vector(1 downto 0);
         ped_six : OUT  std_logic_vector(1 downto 0);
         ped_seven : OUT  std_logic_vector(1 downto 0);
         ped_eight : OUT  std_logic_vector(1 downto 0)
        );
    END COMPONENT;
    

   --Inputs
   signal sensor_one : std_logic := '0';
   signal sensor_two : std_logic := '0';
   signal sensor_three : std_logic := '0';
   signal sensor_four : std_logic := '0';
   signal clk : std_logic := '0';
   signal rst_n : std_logic := '0';

 	--Outputs
   signal light_one : std_logic_vector(2 downto 0);
   signal light_two : std_logic_vector(2 downto 0);
   signal light_three : std_logic_vector(2 downto 0);
   signal light_four : std_logic_vector(2 downto 0);
   signal ped_one : std_logic_vector(1 downto 0);
   signal ped_two : std_logic_vector(1 downto 0);
   signal ped_three : std_logic_vector(1 downto 0);
   signal ped_four : std_logic_vector(1 downto 0);
   signal ped_five : std_logic_vector(1 downto 0);
   signal ped_six : std_logic_vector(1 downto 0);
   signal ped_seven : std_logic_vector(1 downto 0);
   signal ped_eight : std_logic_vector(1 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: light_controller PORT MAP (---the values are mapped by using the portmap functions
	
          sensor_one => sensor_one,--sensor_one is linked with sensor_one
          sensor_two => sensor_two,--sensor_two is linked with sensor_two 
			 
			 ---(same is true for bellow ones they are linked with each other)
          sensor_three => sensor_three,
          sensor_four => sensor_four,
          clk => clk,
          rst_n => rst_n,
          light_one => light_one,
          light_two => light_two,
          light_three => light_three,
          light_four => light_four,
          ped_one => ped_one,
          ped_two => ped_two,
          ped_three => ped_three,
          ped_four => ped_four,
          ped_five => ped_five,
          ped_six => ped_six,
          ped_seven => ped_seven,
          ped_eight => ped_eight
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';---clock is high for one pic seconds
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;---clock is low for one pic seconds
   end process;
 

 rst_process :process
   begin
		rst_n <= '0';
		wait for 100 ns;
		rst_n <= '1';
		wait ;
   end process;

   -- Stimulus process which is used to define the inputs and their combinations
   stim_proc: process
   begin	
---all the sensors are zero for initial two pico seconds	
      		sensor_one<='0';
		sensor_two<='0';
		sensor_three<='0';
		sensor_four<='0';
		--rst_n <= '0';
		wait for clk_period*20;
---sensor one is high for two pico seconds
		sensor_one<='1';
		sensor_two<='0';
		sensor_three<='0';
		sensor_four<='0';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor two is high for two pico seconds
		sensor_one<='0';
		sensor_two<='1';
		sensor_three<='0';
		sensor_four<='0';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor one and two are high for two pico seconds		
		sensor_one<='1';
		sensor_two<='1';
		sensor_three<='0';
		sensor_four<='0';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor three is high for two pico seconds		
		sensor_one<='0';
		sensor_two<='0';
		sensor_three<='1';
		sensor_four<='0';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor one and three are high for two pico seconds
		sensor_one<='1';
		sensor_two<='0';
		sensor_three<='1';
		sensor_four<='0';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor three and two are high for two pico seconds		
		sensor_one<='0';
		sensor_two<='1';
		sensor_three<='1';
		sensor_four<='0';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor one,two and three are high for two pico seconds		
		sensor_one<='1';
		sensor_two<='1';
		sensor_three<='1';
		sensor_four<='0';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor four is high for two pico seconds		
		 sensor_one<='0';
		sensor_two<='0';
		sensor_three<='0';
		sensor_four<='1';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor one and four are high for two pico seconds
		sensor_one<='1';
		sensor_two<='0';
		sensor_three<='0';
		sensor_four<='1';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor two and four are high for two pico seconds		
		 sensor_one<='0';
		sensor_two<='1';
		sensor_three<='0';
		sensor_four<='1';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor one, two and four are high for two pico seconds	
		sensor_one<='1';
		sensor_two<='1';
		sensor_three<='0';
		sensor_four<='1';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor three and four are high for two pico seconds		
		 sensor_one<='0';
		sensor_two<='0';
		sensor_three<='1';
		sensor_four<='1';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor one, three and four are high for two pico seconds		
		sensor_one<='1';
		sensor_two<='0';
		sensor_three<='1';
		sensor_four<='1';
		--rst_n <= '1';
		wait for clk_period*20;
---sensor two, three and four are high for two pico seconds		
		 sensor_one<='0';
		sensor_two<='1';
		sensor_three<='1';
		sensor_four<='1';
		--rst_n <= '1';
		wait for clk_period*20;
	
		
   end process;

END;

