library IEEE;
use IEEE.std_logic_1164.all;

entity system is
	port (	sensor_input :	in std_logic_vector(2 downto 0);
		reset :		in std_logic;
		servo_L :	out std_logic;
		servo_R :	out std_logic
	     );
end entity system;

architecture structural of system is
	component inputbuffer is
		port ( clk	: in	std_logic;

		sensor_l_in	: in	std_logic;
		sensor_m_in	: in	std_logic;
		sensor_r_in	: in	std_logic;

		sensor_l_out	: out	std_logic;
		sensor_m_out	: out	std_logic;
		sensor_r_out	: out	std_logic
	);
	end component inputbuffer;

	component controller is
	port (	clk			: in	std_logic;
		reset			: in	std_logic;

		sensor_l		: in	std_logic;
		sensor_m		: in	std_logic;
		sensor_r		: in	std_logic;

		count_in		: in	std_logic_vector (2 downto 0);
		count_reset		: out	std_logic;

		motor_l_reset		: out	std_logic;
		motor_l_direction	: out	std_logic;

		motor_r_reset		: out	std_logic;
		motor_r_direction	: out	std_logic
	);
	end component controller;

	component timebase is
	port (	clk		: in	std_logic;
		reset		: in	std_logic;

		count_out	: out	std_logic_vector (1 downto 0)
	);
	end component timebase;

	component motorcontrol is
	port (	clk		: in	std_logic;
		reset		: in	std_logic;
		direction	: in	std_logic;
		count_in	: in	std_logic_vector (1 downto 0);

		pwm		: out	std_logic
	);
	end component motorcontrol;

signal clk, count_reset, motor_l_reset, motor_r_reset : std_logic;
signal buffer_controller, timebase_controller : std_logic_vector(2 downto 0);
signal motor_l_direction, motor_r_direction : std_logic;
signal count_out : std_logic_vector(1 downto 0);

begin
L1:	inputbuffer port map ( 	clk => clk, 
				sensor_l_in => sensor_input(2), 
			sensor_m_in => sensor_input(1), 
			sensor_r_in => sensor_input(0),
			sensor_l_out => buffer_controller(2), 
			sensor_m_out => buffer_controller(1),
			sensor_r_out => buffer_controller(0)
			);
L2:	controller port map (	clk => clk,
				reset => reset,
				sensor_l => buffer_controller(2),
				sensor_m => buffer_controller(1),
				sensor_r => buffer_controller(0),
				count_in => timebase_controller,
				count_reset => count_reset,
				motor_l_reset => motor_l_reset,
				motor_l_direction => motor_l_direction,
				motor_r_reset => motor_r_reset,
				motor_r_direction => motor_r_direction
			);
L3:	timebase port map (	clk => clk,
				reset => reset,
				count_out => count_out
			);
L4:	motorcontrol port map (	clk => clk,		--left 
				reset => motor_l_reset,
				direction => motor_l_direction,
				count_in => count_out,
				pwm => servo_L
			);
L5:	motorcontrol port map (	clk => clk,		--right
				reset => motor_r_reset,
				direction => motor_r_direction,
				count_in => count_out,
				pwm => servo_R
			);
	
end architecture structural;