library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity usb is
	port(

		--Clock and Reset
		clk : in std_logic;
		reset_n : in std_logic;

		-- USB Conduit interface to DE2 (Export)
		USB_DATA	: inout std_logic_vector(15 downto 0);
		USB_ADDR	: out std_logic_vector(1 downto 0);
		USB_WR_N	: out std_logic := '1';
		USB_RD_N	: out std_logic := '1';
		USB_RST_N	: out std_logic := '1';
		USB_CS_N	: out std_logic := '1';
		USB_INT0	: in std_logic; 	-- Irq 0 DC
		USB_INT1	: in std_logic; 	-- Irq 1 HC
	
		-- Avalon Memory-Mapped-Slave interface Device Controller (DC)
		avs_dc_address		: in std_logic_vector(1 downto 0);
		avs_dc_writedata	: in std_logic_vector(15 downto 0);
		avs_dc_write_n		: in std_logic;
		avs_dc_read_n		: in std_logic;
		avs_dc_readdata		: out std_logic_vector(15 downto 0);
		avs_dc_irq			: out std_logic;
	
		-- Avalon Memory-Mapped-Slave interface Host Controller (HC)
		-- Probably will not use this interface. 
		avs_hc_address		: in std_logic_vector(1 downto 0);
		avs_hc_writedata	: in std_logic_vector(15 downto 0);
		avs_hc_write_n		: in std_logic
		avs_hc_read_n		: in std_logic;
		avs_hc_readdata		: out std_logic_vector(15 downto 0);
		avs_hc_irq			: out std_logic;
	
	);
end usb;
	
architecture connections of usb is'

	signal 

	begin
	-- Send interrupt from DE2 connection to proper controller
	avs_dc_irq <= USB_INT0;
	avs_hc_irq <= USB_INT1;
	
	--Two cases possible, using the host controller or the device controller. The github project combines them with when else style assignments
	
	USB_DATA <= avs_dc_writedata when avs_dc_write_n = '0' else (others => 'Z'); -- Only does device controller
	avs_dc_readdata <= USB_DATA when avs_dc_read_n = '0' else (others => 'Z');
	avs_hc_readdata <= USB_DATA when avs_hc_read_n = '0' else (others => 'Z');
	
	--USB_ADDR <= avs_dc_address; -- Currently this passes both bits from DC to DE2. 
	
	-- If chip_select_n == 1















