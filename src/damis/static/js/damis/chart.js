(function() {
	window.chart = {
		// initialization upon dialog creation
		init: function(componentType, formWindow) {
			if (componentType == 'CHART') {
				this.toUnconnectedState(formWindow);
			}
		},

		// prepare dialog, when component is unconnected 
		toUnconnectedState: function(formWindow) {
			formWindow.find(".plot-container").remove();
			var container = $("<div class=\"plot-container\">" + gettext("This component should be connected to an executed task in order to view results.") + "</div>");
			formWindow.append(container);
			formWindow.dialog("option", "buttons", window.taskBoxes.defaultDialogButtons());
			formWindow.dialog("option", "minWidth", 0);
			formWindow.dialog("option", "width", 300);
		},

		// all buttons for this component
		allButtons: function() {
			var buttons = [{
				"text": gettext('Update'),
				"class": "btn btn-primary",
				"click": function(ev) {
					var dialog = $(ev.currentTarget).closest(".ui-dialog");
					var formWindow = dialog.find("div[id$=-form]");
					window.chart.updateData(formWindow, window.chart.updateChartColorsSymbols, {
						renderChoices: dialog.find(".plot-container .render-choices tbody tr")
					});
				}
			},
			{
				"text": gettext('Download'),
				"class": "btn",
				"click": function(ev) {
					var plotContainer = $(ev.currentTarget).closest(".ui-dialog").find(".plot-container");
					window.chart.downloadChart($(plotContainer[0]));
				}
			}];
			var defaultButtons = window.taskBoxes.defaultDialogButtons();
			return buttons.concat(defaultButtons);
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
		updateChartColorsSymbols: function(dataContent, formWindow, params) {
			var data = dataContent.data;
			var colors = window.chart.generateColorPalette(data);
			var symbols = window.chart.generateSymbolPalette(data);
			$.each(params['renderChoices'], function(idx, choice) {
				// TODO: add color validation or color picker
				var color = $(choice).find("input").val();
				colors[idx] = color ? color: colors[idx];

				var symbol = $(choice).find("option:selected").val();
				symbols[idx] = symbol ? symbol: symbols[idx][0];
			});
			window.chart.renderChartAndForm(dataContent, formWindow, colors, symbols);
		},

		// displays a pop-up asking to download file
		downloadChart: function(plotContainer) {
			var canvas = plotContainer.find("canvas")[0];
			//var image = canvas.toDataURL("image/jpeg");
			//image = image.replace("image/jpeg", "image/octet-stream");
			var image = canvas.toDataURL();
			image = image.replace("image/png", "image/octet-stream");
			// TODO: use server side to obtain download prompt with file extension
			document.location.href = image;
		},

		// renders the chart and the form with inputs for colors and symbols
		// for the first time
		renderChartAndForm: function(dataContent, formWindow, selectedColors, selectedSymbols) {
			var plotContainer = formWindow.find(".plot-container");
			plotContainer.css("min-height", 400);
			plotContainer.css("position", "relative");
			var plotPlaceholder = "<div class=\"results-container\" style=\"width: 600px; height: 300px; margin: auto;\"></div>";
			plotContainer.html(plotPlaceholder);

			var renderChoicesBody = $("<tbody></tbody>");
			var renderChoicesHead = $("<thead><th>" + gettext('Class') + "</th><th>" + gettext('Color') + "</th><th>" + gettext('Shape') + "</th></thead>");
			var renderChoices = $("<table class=\"render-choices\" style=\"margin: auto; margin-top: 20px;\"></table>");
			renderChoices.append(renderChoicesHead);
			renderChoices.append(renderChoicesBody);
			plotContainer.append(renderChoices);

			// append to body temporarily in order for axes labels to be drawn correctly
			$("body").append(plotContainer);

			var colorPalette = selectedColors ? selectedColors: window.chart.generateColorPalette(dataContent.data);
			var symbolPalette = window.chart.generateSymbolPalette(dataContent.data);
			var symbolValues = []

			// fill the form with current color and symbol values
			$.each(dataContent.data, function(idx, series) {
				var seriesRow = $("<tr></tr>");
				seriesRow.append("<td>" + idx + "</td>");
				seriesRow.append("<td><input type=\"text\" value=\"" + colorPalette[idx].toLowerCase() + "\"/></td>");

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
					shapeSelect.append("<option value=\"" + shape[0] + "\"" + (selected ? "selected=\"selected\"": "") + ">" + shape[1] + "</option>");
				});

				var shapeCell = $("<td></td>");
				shapeCell.append(shapeSelect);
				seriesRow.append(shapeCell);

				renderChoicesBody.append(seriesRow);
			});

			window.chart.renderChart(plotContainer, "body > .plot-container .results-container", dataContent, colorPalette, symbolValues);
			//append to form after rendering because otherwise axes are not rendered
			formWindow.append(plotContainer);

			formWindow.dialog("option", "buttons", window.chart.allButtons());
			formWindow.dialog("option", "minWidth", 650);
			formWindow.dialog("option", "close", function() {
				$(this).find("#point-tooltip").remove();
			});
		},

		updateData: function(formWindow, callback, params) {
			var url = window.componentFormUrls['CHART'];
			var data = window.chart.getOutputParamDetails(formWindow);
			formWindow.find(".plot-container").remove();
			var container = $("<div class=\"plot-container\"><img width=\"250px\" src=\"/static/img/loading.gif\"/></div>");
			formWindow.append(container);
			$.ajax({
				url: url,
				data: data,
				context: container,
			}).done(function(resp) {
				if (resp.status == "SUCCESS") {
					if (params) {
						callback(resp.content, formWindow, params);
					} else {
						callback(resp.content, formWindow);
					}
				} else {
					var container = formWindow.find(".plot-container");
					container.html(resp.message);
				}
			});
		},

		// get details of a parameter, that is connected to the current component input connection
		getOutputParamDetails: function(dialog) {
			var inParam = dialog.find("input[value=INPUT_CONNECTION]");
			var srcRefField = inParam.closest("div").find("input[id$=source_ref]");
			var oParamField = window.experimentForm.getOutputParam(srcRefField);
			if (oParamField) {
				return {
					pv_name: oParamField.attr("name"),
					dataset_url: oParamField.val()
				}
			}
			return {}
		},

		// called when connection is established
		connectionEstablished: function(srcComponentType, targetComponentType, connectionParams) {
			if (targetComponentType == 'CHART') {
				var formWindow = $("#" + window.taskBoxes.getFormWindowId(connectionParams.iTaskBoxId));
				this.updateData(formWindow, this.renderChartAndForm);
			}
		},

		// called when connection is deleted
		connectionDeleted: function(srcComponentType, targetComponentType, connectionParams) {
			if (srcComponentType == 'CHART' || targetComponentType == 'CHART') {
				var formWindow = $("#" + window.taskBoxes.getFormWindowId(connectionParams.iTaskBoxId));
				this.toUnconnectedState(formWindow);
			}
		},
	}
})();

