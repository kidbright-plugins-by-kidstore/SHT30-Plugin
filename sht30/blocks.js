Blockly.Blocks['sht30_read'] = {
	init: function() {
		this.jsonInit({
			"type": "sht30_read",
			"message0": Blockly.Msg.SHT30_READ_MESSAGE,
			"args0": [
				{
					"type": "field_dropdown",
					"name": "addr",
					"options": [
						[
							"0x44",
							"0x44"
						],
						[
							"0x45",
							"0x45"
						]
					]
				},
				{
					"type": "field_dropdown",
					"name": "type",
					"options": [
					[
						"temperature (°C)",
						"0"
					],
					[
						"humidity (%RH)",
						"1"
					]
					]
				}
			],
			"output": "Number",
			"colour": 285,
			"tooltip": Blockly.Msg.SHT30_READ_TOOLTIP,
			"helpUrl": ""
		})
	}
};
