library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity usb is
	port(

		--Clock and Reset
		clk : in std_logic;
		reset_n : in std_logic;

		-- OTG Conduit interface to DE2 (Export)
		OTG_DATA	: inout std_logic_vector(15 downto 0);
		OTG_ADDR	: out std_logic_vector(1 downto 0);
		OTG_WR_N	: out std_logic := '1';
		OTG_RD_N	: out std_logic := '1';
		OTG_RST_N	: out std_logic := '1';
		OTG_CS_N	: out std_logic := '1';
		OTG_INT0	: in std_logic; 	-- Irq 0 DC
		OTG_INT1	: in std_logic; 	-- Irq 1 HC
	
		-- Avalon Memory-Mapped-Slave interface Device Controller (DC)
		avs_dc_address		: in std_logic_vector(1 downto 0);
		avs_dc_writedata	: in std_logic_vector(15 downto 0);
		avs_dc_write_n		: in std_logic;
		avs_dc_read_n		: in std_logic;
		avs_dc_readdata		: out std_logic_vector(15 downto 0);
		avs_dc_irq		: out std_logic;
	
		-- Avalon Memory-Mapped-Slave interface Host Controller (HC)
		-- Probably will not use this interface. 
		avs_hc_address		: in std_logic_vector(1 downto 0);
		avs_hc_writedata	: in std_logic_vector(15 downto 0);
		avs_hc_write_n		: in std_logic
		avs_hc_read_n		: in std_logic;
		avs_hc_readdata		: out std_logic_vector(15 downto 0);
		avs_hc_irq		: out std_logic;
	
	);
end usb;
	
architecture connections of usb is'


	begin
	-- Send interrupt from DE2 connection to proper controller
	avs_dc_irq <= OTG_INT0;
	avs_hc_irq <= OTG_INT1;















