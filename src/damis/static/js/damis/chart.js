(function() {
	window.chart = {

		// prepare dialog, when component is unconnected 
		toUnconnectedState: function(formWindow) {
			formWindow.find(".plot-container").remove();
			var container = $("<div class=\"plot-container\">" + gettext("This component should be connected to a selected file or an executed task in order to view results.") + "</div>");
			formWindow.append(container);
			formWindow.dialog("option", "buttons", window.chart.notConnectedButtons());
			formWindow.dialog("option", "width", "auto");
		},

		notConnectedButtons: function() {
			var buttons = [{
				"text": gettext('Cancel'),
				"class": "btn",
				"click": function(ev) {
					$(this).dialog("close");
				}
			}];
			return buttons;
		},

		// all buttons for this component
		errorButtons: function() {
			var buttons = [{
				"text": gettext('Update'),
				"class": "btn btn-primary",
				"click": function(ev) {
					window.chart.update($(this), window.chart.updateChartColorsSymbols, {
						renderChoices: $(this).find(".plot-container .render-choices tbody tr")
					});
				}
			}];
			var notConnectedButtons = window.chart.notConnectedButtons();
			return buttons.concat(notConnectedButtons);
		},

		// all buttons for this component
		allButtons: function() {
			var buttons = [{
				"text": gettext('Download'),
				"class": "btn",
				"click": function(ev) {
					window.chart.downloadChart($(this));
				}
			}];
			var errorButtons = window.chart.errorButtons();
			var result = [errorButtons[0]].concat(buttons);
			result = result.concat(errorButtons[1]);
			return result;
		},

		// custom color palette, rotates through a range of hue values
		generateColorPalette: function(data) {
			var len = data.length;
			return $.map(data, function(o, i) {
				return jQuery.Color({
					hue: (i * 360 / len),
					saturation: 0.95,
					lightness: 0.35,
					alpha: 1
				}).toHexString();
			});
		},

		// symbol palette, rotates through a set of symbols
		generateSymbolPalette: function(data) {
			var baseOptions = [["circle", gettext("Circle")], ["square", gettext("Square")], ["diamond", gettext("Diamond")], ["triangle", gettext("Triangle")], ["cross", gettext("Cross")]];
			var allOptions = [];
			for (var i = 0; i < data.length; i++) {
				allOptions.push(baseOptions[i % baseOptions.length]);
			}
			return allOptions;
		},

		// renders the chart in place of plotPlaceholder
		renderChart: function(plotContainer, plotPlaceholder, dataContent, colors, symbols) {
			var data = [];
			$.each(dataContent.data, function(idx, rec) {
				data.push({
					label: rec['group'],
					points: {
						symbol: symbols[idx],
					},
					data: rec['data'],
					color: colors[idx],
				});
			});
			var options = {
				canvas: true,
				series: {
					points: {
						show: true,
						radius: 3
					},
				},
				legend: {
					show: false
				},
				grid: {
					backgroundColor: "#ffffff",
					clickable: true,
					hoverable: true
				},
				xaxis: {
					min: dataContent["minX"],
					max: dataContent["maxX"],
					tickSize: 5
				},
				yaxis: {
					min: dataContent["minY"],
					max: dataContent["maxY"],
					tickSize: 5
				},
			};

			var plot = $.plot(plotPlaceholder, data, options);

			$(plotPlaceholder).bind("plotclick", function(event, pos, item) {
				if (item) {
					$("<div id='point-tooltip'></div>").css({
						position: "absolute",
						display: "none",
						border: "1px solid #fdd",
						padding: "2px",
						"background-color": "#fee",
						opacity: 0.80
					}).appendTo(plotContainer);

					var x = item.datapoint[0].toFixed(2),
					y = item.datapoint[1].toFixed(2);

					var containerOffset = $(plotContainer).find(".results-container").offset();
					$("#point-tooltip").html(x + ", " + y + " (" + gettext("index") + ": " + item.dataIndex + ", " + gettext("class") + ": " + item.series.label + ")").css({
						top: item.pageY - containerOffset['top'],
						left: item.pageX - containerOffset['left'] + 10
					}).fadeIn(200);
				} else {
					$("#point-tooltip").hide();
				}
			});
		},

		// updates the chart colors and symbols
		updateChartColorsSymbols: function(resp, formWindow, params) {
			var data = resp.content.data;
			var colors = window.chart.generateColorPalette(data);
			var symbols = window.chart.generateSymbolPalette(data);
			$.each(params['renderChoices'], function(idx, choice) {
				var color = $(choice).find("input").val();
				colors[idx] = color ? color: colors[idx];

				var symbol = $(choice).find("select").val();
				symbols[idx] = symbol ? symbol: symbols[idx][0];
			});
			window.chart.renderChartAndForm(resp, formWindow, colors, symbols);
		},

		// displays a image format selection dialog 
		downloadChart: function(formWindow) {
			var downloadOptions = formWindow.find(".download-options").clone(true);
			downloadOptions.dialog({
				"title": gettext("Select file type and destination"),
				"modal": true,
				"minWidth": 450,
				"open": function() {
					var dialog = $(this).closest(".ui-dialog");
					dialog.find(".ui-dialog-titlebar > button").remove();
				},
				"buttons": [{
					"text": gettext("OK"),
					"class": "btn btn-primary",
					"click": function(ev) {
						// TODO: show progress indicator
						var canvas = formWindow.find(".plot-container").find("canvas")[0];
						var image;
						var format = $(this).find("input[name=file-type]:checked").val();
						var dst = $(this).find("input[name=file-destination]:checked").val();
						if (dst == "midas") {
							$(this).find(".not-implemented").show();
						} else {
							if (format == "png") {
								image = canvas.toDataURL();
								image = image.replace("image/png", "image/octet-stream");
							} else if (format == "jpeg") {
								var image = canvas.toDataURL("image/jpeg");
								image = image.replace("image/jpeg", "image/octet-stream");
							}
							var url = window.componentFormUrls['CHART'];

							// POST to server to obtain a downloadable result
							var imageInput = $("<input name=\"image\" value=\"" + image + "\"/>");
							var formatInput = $("<input name=\"format\" value=\"" + format + "\"/>");
							var myForm = $("<form method=\"post\" action=\"" + url + "\"></form>");
							myForm.append(imageInput);
							myForm.append(formatInput);
							$("body").append(myForm);
							myForm.submit();
							myForm.remove();
							$(this).dialog("destroy");
						}
					}
				},
				{
					"text": gettext("Cancel"),
					"class": "btn",
					"click": function(ev) {
						$(this).dialog("destroy");
					},
				},
				],
			});
		},

		// renders the chart and the form with inputs for colors and symbols
		// for the first time
		renderChartAndForm: function(resp, formWindow, selectedColors, selectedSymbols) {
			var dataContent = resp.content;
			var colorPalette = selectedColors ? selectedColors: window.chart.generateColorPalette(dataContent.data);
			var symbolPalette = window.chart.generateSymbolPalette(dataContent.data);
			var symbolValues = []

			var plotContainer = formWindow.find(".plot-container");
			var renderChoicesBody = plotContainer.find(".render-choices tbody");

			// fill the form with current color and symbol values
			$.each(dataContent.data, function(idx, series) {
				var rowPattern = "<tr><td>{cls}</td>";
				rowPattern += "<td><div class=\"color-selector\" style=\"background-color: {colorCode};\"></div></td>";
				rowPattern += "<td><input type=\"hidden\" value=\"{colorCode}\"/></td>";

				var colorCode = colorPalette[idx].toLowerCase();
				var seriesRow = $(window.utils.formatStr(rowPattern, {
					"cls": idx,
					"colorCode": colorCode
				}));

				var shapeSelect = $("<select></select>");
				$.each(symbolPalette, function(i, shape) {
					var selected;
					if (selectedSymbols) {
						selected = selectedSymbols[idx] == shape[0];
					} else {
						selected = idx == i;
					}
					if (selected) {
						symbolValues.push(shape[0]);
					}
					var optionPattern = "<option value=\"{value}\" {selected}>{label}</option>";
					var args = {
						"value": shape[0],
						"selected": (selected ? "selected=\"selected\"": ""),
						"label": shape[1]
					}
					shapeSelect.append(window.utils.formatStr(optionPattern, args));
				});

				var shapeCell = $("<td></td>");
				shapeCell.append(shapeSelect);
				seriesRow.append(shapeCell);

				// add color picker
				seriesRow.find('.color-selector').colpick({
					layout: 'rgbhex',
					color: colorCode,
					submitText: gettext('OK'),
					onSubmit: function(hsb, hex, rgb, el) {
						var colorCode = '#' + hex;
						$(el).css('background-color', colorCode);
						$(el).closest("td").next().find("input").val(colorCode);
						$(el).colpickHide();
					}
				}).css('background-color', colorCode);

				renderChoicesBody.append(seriesRow);
			});

			plotContainer.css("min-height", 400);
			plotContainer.css("position", "relative");
			// append to body temporarily in order for axes labels to be drawn correctly
			$("body").append(plotContainer);
			window.chart.renderChart(plotContainer, "body > .plot-container .results-container", dataContent, colorPalette, symbolValues);
			//append to form after rendering because otherwise axes are not rendered
			formWindow.append(plotContainer);

			formWindow.dialog("option", "buttons", window.chart.allButtons());
			formWindow.dialog("option", "minWidth", 650);
			formWindow.dialog("option", "close", function() {
				$(this).find("#point-tooltip").remove();
			});
		},

		mergeAttributeChoices: function(data, formWindow) {
			var x = formWindow.find(".attribute-choices select.x-attr").val();
			if (x != "-") {
				data['x'] = x;
			}
			var y = formWindow.find(".attribute-choices select.y-attr").val();
			if (y != "-") {
				data['y'] = y;
			}
			var cls = formWindow.find(".attribute-choices select.cls-attr").val();
			if (cls != "-") {
				data['cls'] = cls;
			}
		},

		update: function(formWindow, callback, params) {
			var data = window.chart.getOutputParamDetails(formWindow);
			if (!data["dataset_url"]) {
				this.toUnconnectedState(formWindow);
				return;
			}
			this.mergeAttributeChoices(data, formWindow);

			var url = window.componentFormUrls['CHART'];
			formWindow.find(".plot-container").remove();
			var container = $("<div class=\"plot-container\"><img style=\"display: block; width: 250px; margin:auto;\" width=\"250px\" src=\"/static/img/loading.gif\"/></div>");
			formWindow.append(container);
			$.ajax({
				url: url,
				data: data,
				context: container,
			}).done(function(resp) {
				$(this).html(resp.html);
				window.utils.showProgress();
				if (resp.status == "SUCCESS") {
					if (params) {
						callback(resp, formWindow, params);
					} else {
						callback(resp, formWindow);
					}
					formWindow.dialog("option", "buttons", window.chart.allButtons());
				} else {
					formWindow.dialog("option", "minHeight", "0");
					formWindow.dialog("option", "height", "auto");
					formWindow.dialog("option", "buttons", window.chart.errorButtons());
				}
				window.utils.hideProgress();
			});
		},

		// get details of a parameter, that is connected to the current component input connection
		getOutputParamDetails: function(dialog) {
			var inParam = dialog.find("input[value=INPUT_CONNECTION]");
			var srcRefField = inParam.closest("div").find("input[id$=source_ref]");
			var oParamField = window.experimentForm.getOutputParam(srcRefField);
			if (oParamField) {
				return {
					dataset_url: oParamField.val()
				}
			}
			return {}
		},

		// called when connection is deleted
		connectionDeleted: function(srcComponentType, targetComponentType, connectionParams) {
			if (srcComponentType == 'CHART' || targetComponentType == 'CHART') {
				var formWindow = $("#" + window.taskBoxes.getFormWindowId(connectionParams.iTaskBoxId));
				this.toUnconnectedState(formWindow);
			}
		},

		doubleClick: function(componentType, formWindow) {
			if (componentType == 'CHART') {
				formWindow.dialog("option", "minWidth", 650);
				formWindow.dialog("open");
				this.update(formWindow, this.renderChartAndForm);
			}
		}
	}
})();

