Blockly.JavaScript['sht30_read'] = function(block) {
	var dropdown_addr = block.getFieldValue('addr');
	var dropdown_type = block.getFieldValue('type');
	
	var code = `DEV_I2C1.SHT30(0, ${dropdown_addr}).read(${dropdown_type})`;
	return [code, Blockly.JavaScript.ORDER_NONE];
};
