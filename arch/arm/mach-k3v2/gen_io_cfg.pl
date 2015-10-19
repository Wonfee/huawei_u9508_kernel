#!/usr/bin/perl -w

use Spreadsheet::ParseExcel;
use strict;

#==========================================================================
#
#GEN_GPIO_CFG
#
#brief description
#	auto gen config.c and .h by perl script
#EXAMPLE
#	if example.xls is given,then example.c and example.h will be
#	generated automaticlly by excuting gen_gpio_cfg.pl.
#Copyright (c) 2008 - 2010 by Huawei Incorporated.  All Rights Reserved.
#==========================================================================

sub my_main()
{
	my $oExcel = new Spreadsheet::ParseExcel;
	my $oBook = $oExcel->Parse($ARGV[0]);
	my $hw_iomux_handle;
	my $iomux_type;
	my $board_id;
	my $board_id_line;
	my $struct_id_list;
	my $struct_id;
	my $oSheet;
	my $oSheet0 = $oBook->{Worksheet}[0];

	##############################################################
	my $oSheet_list;
	open($hw_iomux_handle, ">$ARGV[1]") ||
		die("Failed to open file $ARGV[1] for write!");
	($_ = $0) =~ s:.*/::;

	printf $hw_iomux_handle "/*************************************************************\n";
	printf $hw_iomux_handle " *CAUTION : This file is Auto Generated by gen_io_cfg.pl based on *.xls\n";
	printf $hw_iomux_handle " *so,don't modify this file manually!\n";
	printf $hw_iomux_handle " *************************************************************/\n";
	printf $hw_iomux_handle "#ifndef __MACH_K3V2_IOMUX_BLOCKS_H\n";
	printf $hw_iomux_handle "#define __MACH_K3V2_IOMUX_BLOCKS_H\n";
	printf $hw_iomux_handle "#include \"iomux.h\"\n";
	printf $hw_iomux_handle "#include \"k3v2_iomux_pins.h\"\n";
	printf $hw_iomux_handle "#include <hsad/config_interface.h>\n";
	printf $hw_iomux_handle "\n";
	printf $hw_iomux_handle "extern struct iomux_ops iomux_block_ops;\n";
	printf $hw_iomux_handle "#define IOMUX_BLOCK(_iomux_block, _block_name, _block_func, _pins)	\\\n";
	printf $hw_iomux_handle "struct iomux_block _iomux_block = {\\\n	.block_name  = _block_name,\\\n	.block_func   =  _block_func,\\\n";
	printf $hw_iomux_handle ".pins = _pins,\\\n.ops = &iomux_block_ops,\\\n.init = 0,\\\n};\n";
	printf $hw_iomux_handle "\n";

	for($board_id_line = 1; $oSheet0->{Cells}[$board_id_line][0]->Value ne "END"; $board_id_line ++)
	{
		$iomux_type = $oSheet0->{Cells}[$board_id_line][1]->Value;
		$oSheet = $oBook->{Worksheet}[$board_id_line];
		$board_id = $oSheet0->{Cells}[$board_id_line][1]->Value;
		gen_io_config($hw_iomux_handle, $oSheet, "$board_id");
		printf $hw_iomux_handle "\n";
	}

	printf $hw_iomux_handle "\n";
	printf $hw_iomux_handle "struct block_table *block_config_tables[] = {\n";
	for($board_id_line = 1; $oSheet0->{Cells}[$board_id_line][0]->Value ne "END"; $board_id_line ++)
	{
		$struct_id = $oSheet0->{Cells}[$board_id_line][0]->Value;
		$oSheet_list = $oBook->{Worksheet}[$board_id_line];
		printf $hw_iomux_handle "[%s] = %s,\n",$struct_id,$oSheet_list->{Name};
	}
	printf $hw_iomux_handle "[E_IOMUX_MAX] = NULL,\n};\n";
	printf $hw_iomux_handle "\n";
	printf $hw_iomux_handle "#endif\n";

	my $iomux_suspend_id;
	my $oSheet_suspend;
	printf $hw_iomux_handle "#ifdef	CONFIG_LOWPM_DEBUG\n";
	printf $hw_iomux_handle "#define LOW_POWER(imo, imv, ico, icv, gpiog, gpiob, gpiod, gpiov) \\\n";
	printf $hw_iomux_handle "{				\\\n";
	printf $hw_iomux_handle "	.uiomg_off = imo,  .iomg_val = imv,   \\\n";
	printf $hw_iomux_handle "	.uiocg_off = ico,  .iocg_val  = icv,   \\\n";
	printf $hw_iomux_handle "	.ugpiog    = gpiog, .ugpio_bit = gpiob, \\\n";
	printf $hw_iomux_handle "	.gpio_dir  = gpiod, .gpio_val  = gpiov, \\\n";
	printf $hw_iomux_handle "}\n";
	printf $hw_iomux_handle "\n";

	printf $hw_iomux_handle "#define FUNC0 		0X0\n";
	printf $hw_iomux_handle "#define FUNC1 		0X1\n";
	printf $hw_iomux_handle "#define FUNC2 		0X2\n";
	printf $hw_iomux_handle "#define FUNC3 		0X3\n";
	printf $hw_iomux_handle "#define NOPULL	 	0X0\n";
	printf $hw_iomux_handle "#define PULLUP 		0X1\n";
	printf $hw_iomux_handle "#define PULLDOWN 	0X2\n";
	printf $hw_iomux_handle "#define DO 			1\n";
	printf $hw_iomux_handle "#define DI 			0\n";
	printf $hw_iomux_handle "#define L 			0x0\n";
	printf $hw_iomux_handle "#define H 			0x1\n";
	printf $hw_iomux_handle "#define RESERVE 	-1\n";
	$iomux_suspend_id = $oSheet0->{Cells}[1][1]->Value;
	printf $hw_iomux_handle "#define IO_LIST_LENGTH (sizeof(iocfg_lookups_%s)/sizeof(iocfg_lookups_%s[0]))\n",$iomux_suspend_id,$iomux_suspend_id;

	for($board_id_line = 1; $oSheet0->{Cells}[$board_id_line][0]->Value ne "END"; $board_id_line ++)
	{
		$iomux_suspend_id = $oSheet0->{Cells}[$board_id_line][1]->Value;
		printf $hw_iomux_handle "\n";
		printf $hw_iomux_handle "static struct iocfg_lp iocfg_lookups_$iomux_suspend_id\[\] = {\n";
		$oSheet_suspend = $oBook->{Worksheet}[$board_id_line];
		gen_suspend_io_config($hw_iomux_handle, $oSheet_suspend);
		printf $hw_iomux_handle "};\n";
	}

	printf $hw_iomux_handle "\n";
	printf $hw_iomux_handle "struct iocfg_lp *io_suspend_config_tables[] = {\n";
	for($board_id_line = 1; $oSheet0->{Cells}[$board_id_line][0]->Value ne "END"; $board_id_line ++)
	{
		$struct_id = $oSheet0->{Cells}[$board_id_line][0]->Value;
		$oSheet_list = $oSheet0->{Cells}[$board_id_line][1]->Value;
		printf $hw_iomux_handle "\t";
		printf $hw_iomux_handle "[%s] = iocfg_lookups_%s,\n",$struct_id,$oSheet_list;
	}
	printf $hw_iomux_handle "\t";
	printf $hw_iomux_handle "[E_IOMUX_MAX] = NULL,\n};\n";

	printf $hw_iomux_handle "\n";
	printf $hw_iomux_handle "#endif\n";
	close($hw_iomux_handle);

	print "Create new .H FILE  OK!\n";
	exit 0;
}

sub gen_io_config()
{
	#input parameters
	my ($hw_handle, $Sheet, $id) = @_;
	my $line_index = 1;
	my $block_name;
	my $pin_name;
	my $pin_func;
	my $pin_pullud;
	my $pin_drv;
	my $osheet0_line;
	my $osheet1_line;
	my $block_name1;

	printf $hw_handle "\n/******************pins ****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "struct  iomux_pin *%s_%s_pins[] = {", $block_name, $id;
		printf $hw_handle "\n";
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][1]->Value)
			{
				$pin_name = $Sheet->{Cells}[$osheet1_line][0]->Value;
				printf $hw_handle "&%s, ", $pin_name;
			}
		}
		printf $hw_handle "NULL,\n";
		printf $hw_handle "};\n";
	}

	printf $hw_handle "\n/******************IOMUX_BLOCK****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "IOMUX_BLOCK(block_$block_name\_$id, \"block_$block_name\_$id\", NORMAL, %s_%s_pins)\n",
						$block_name, $id;
	}

	printf $hw_handle "\n/******************normal func ****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "enum lowlayer_func %s_%s_func_normal[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][1]->Value)
			{
				$pin_func = $Sheet->{Cells}[$osheet1_line][3]->Value;
				printf $hw_handle "$pin_func, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************lowpower func****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "enum lowlayer_func %s_%s_func_lowpower[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][1]->Value)
			{
				$pin_func = $Sheet->{Cells}[$osheet1_line][6]->Value;
				printf $hw_handle "$pin_func, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************normal pullud****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "enum pull_updown %s_%s_pullud_normal[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][1]->Value)
			{
				$pin_pullud = $Sheet->{Cells}[$osheet1_line][4]->Value;
				printf $hw_handle "$pin_pullud, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************lowpower pullud****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "enum pull_updown %s_%s_pullud_lowpower[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][1]->Value)
			{
				$pin_pullud = $Sheet->{Cells}[$osheet1_line][7]->Value;
				printf $hw_handle "$pin_pullud, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************normal drv****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "enum drive_strength %s_%s_drv_normal[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][1]->Value)
			{
				$pin_drv = $Sheet->{Cells}[$osheet1_line][5]->Value;
				printf $hw_handle "$pin_drv, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************lowpower drv****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "enum drive_strength %s_%s_drv_lowpower[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][1]->Value)
			{
				$pin_drv = $Sheet->{Cells}[$osheet1_line][8]->Value;
				printf $hw_handle "$pin_drv, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************config****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "struct block_config %s_%s_config[] = {\n", $block_name, $id;
		printf $hw_handle "	[NORMAL] = {%s_%s_func_normal, %s_%s_pullud_normal, %s_%s_drv_normal},\n",
						$block_name, $id, $block_name, $id, $block_name, $id;
		printf $hw_handle "	[LOWPOWER] = {%s_%s_func_lowpower, %s_%s_pullud_lowpower, %s_%s_drv_lowpower},\n",
						$block_name, $id, $block_name, $id, $block_name, $id;
		printf $hw_handle "};\n";
	}
	printf $hw_handle "\n";

	gen_block_mux_config($hw_handle, $Sheet, $id);

	printf $hw_handle "\n";
	printf $hw_handle "struct block_table %s[] = {\n", $Sheet->{Name};
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][0]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][0]->Value;
		printf $hw_handle "     BLOCK_CONFIG(\"block_%s\", &block_%s_%s, %s_%s_config)\n",
							$block_name, $block_name, $id, $block_name, $id;
	}
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "     BLOCK_CONFIG(\"block_%s\", &block_%s_%s, %s_%s_config)\n",
							$block_name, $block_name, $id, $block_name, $id;
	}
	printf $hw_handle "     {NULL, NULL, NULL},\n";
	printf $hw_handle "};\n";

}

sub gen_block_mux_config()
{
	my ($hw_handle, $Sheet, $id) = @_;
	my $line_index = 1;
	my $block_name;
	my $pin_name;
	my $pin_func;
	my $pin_pullud;
	my $pin_drv;
	my $osheet0_line;
	my $osheet1_line;
	my $block_name1;

	printf $hw_handle "\n/******************pins ****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "struct  iomux_pin *%s_%s_pins[] = {", $block_name, $id;
		printf $hw_handle "\n";
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][16]->Value)
			{
				$pin_name = $Sheet->{Cells}[$osheet1_line][0]->Value;
				printf $hw_handle "&%s, ", $pin_name;
			}
		}
		printf $hw_handle "NULL,\n";
		printf $hw_handle "};\n";
	}

	printf $hw_handle "\n/******************IOMUX_BLOCK****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "IOMUX_BLOCK(block_$block_name\_$id, \"block_$block_name\_$id\", NORMAL, %s_%s_pins)\n",
						$block_name, $id;
	}

	printf $hw_handle "\n/******************normal func ****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "enum lowlayer_func %s_%s_func_normal[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][16]->Value)
			{
				$pin_func = $Sheet->{Cells}[$osheet1_line][18]->Value;
				printf $hw_handle "$pin_func, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************lowpower func****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "enum lowlayer_func %s_%s_func_lowpower[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][16]->Value)
			{
				$pin_func = $Sheet->{Cells}[$osheet1_line][21]->Value;
				printf $hw_handle "$pin_func, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************normal pullud****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "enum pull_updown %s_%s_pullud_normal[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][16]->Value)
			{
				$pin_pullud = $Sheet->{Cells}[$osheet1_line][19]->Value;
				printf $hw_handle "$pin_pullud, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************lowpower pullud****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "enum pull_updown %s_%s_pullud_lowpower[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][16]->Value)
			{
				$pin_pullud = $Sheet->{Cells}[$osheet1_line][22]->Value;
				printf $hw_handle "$pin_pullud, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************normal drv****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "enum drive_strength %s_%s_drv_normal[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][16]->Value)
			{
				$pin_drv = $Sheet->{Cells}[$osheet1_line][20]->Value;
				printf $hw_handle "$pin_drv, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************lowpower drv****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "enum drive_strength %s_%s_drv_lowpower[] = {", $block_name, $id;
		for($osheet1_line = 1; $Sheet->{Cells}[$osheet1_line][0]->Value ne "END"; $osheet1_line ++)
		{
			if($block_name eq $Sheet->{Cells}[$osheet1_line][16]->Value)
			{
				$pin_drv = $Sheet->{Cells}[$osheet1_line][23]->Value;
				printf $hw_handle "$pin_drv, ";
			}
		}
		printf $hw_handle "-INVALID,};\n";
	}

	printf $hw_handle "\n/******************config****************/\n\n";
	for($osheet0_line = 179; $Sheet->{Cells}[$osheet0_line][1]->Value ne "END"; $osheet0_line ++)
	{
		$block_name = $Sheet->{Cells}[$osheet0_line][1]->Value;
		printf $hw_handle "struct block_config %s_%s_config[] = {\n", $block_name, $id;
		printf $hw_handle "	[NORMAL] = {%s_%s_func_normal, %s_%s_pullud_normal, %s_%s_drv_normal},\n",
						$block_name, $id, $block_name, $id, $block_name, $id;
		printf $hw_handle "	[LOWPOWER] = {%s_%s_func_lowpower, %s_%s_pullud_lowpower, %s_%s_drv_lowpower},\n",
						$block_name, $id, $block_name, $id, $block_name, $id;
		printf $hw_handle "};\n";
	}
}

sub gen_suspend_io_config()
{
	#input parameters
	my ($hw_handle, $Sheet) = @_;
	my $line_index = 1;
	my $total_line = 0;
	my $cell_value;
	my $pin_name;

	for($line_index = 1; $Sheet->{Cells}[$line_index][0]->Value ne "END"; $line_index ++)
	{
		#GPIO,#IOMG_OFFSET,#IOMG_VALUE,#IOCG_OFFSET,#IOCG_VALUE,#GPIO_GROUP
		#GPIO_GROUP_BIT,#GPIO_DIR,#GPIO_VALUE
		$pin_name = $Sheet->{Cells}[$line_index][0]->Value;
		printf $hw_handle "\t";
		printf $hw_handle "//#%s", $pin_name;
		printf $hw_handle "\n";
		printf $hw_handle "\t";
		printf $hw_handle "LOW_POWER(";
		printf $hw_handle "%s, ", $Sheet->{Cells}[$line_index][11]->Value;
		printf $hw_handle "%s, ",    $Sheet->{Cells}[$line_index][6]->Value;
		printf $hw_handle "%s, ", $Sheet->{Cells}[$line_index][12]->Value;
		printf $hw_handle "%s, ", $Sheet->{Cells}[$line_index][7]->Value;
		printf $hw_handle "%d, ", $Sheet->{Cells}[$line_index][13]->Value;
		printf $hw_handle "%d, ",    $Sheet->{Cells}[$line_index][14]->Value;
		printf $hw_handle "%s, ", $Sheet->{Cells}[$line_index][9]->Value;
		printf $hw_handle "%s",  $Sheet->{Cells}[$line_index][10]->Value;
		printf $hw_handle "),\n";

	}

}
#this is the main function and the begining
&my_main();