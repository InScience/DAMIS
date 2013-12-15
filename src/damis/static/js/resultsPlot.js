(function() {
	window.resultsPlot = {
		// TODO: sends Ajax request to obtain results for the connected component
		getDataToRender: function() {
			initData = [{
				group: "1",
				data: window.resultsPlot.generate(2, 1.8)
			},
			{
				group: "2",
				data: window.resultsPlot.generate(4, 0.9)
			},
			{
				group: "3",
				data: window.resultsPlot.generate(7, 1.1)
			},
			{
				group: "4",
				data: window.resultsPlot.generate(10, 0.2)
			}];
			return initData;
		},

		generate: function(offset, amplitude) {
			var res = [];
			var start = 0,
			end = 10;

			for (var i = 0; i <= 50; ++i) {
				var x = start + i / 50 * (end - start);
				res.push([x, amplitude * Math.sin(x + offset)]);
			}

			return res;
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

		generateSymbolPalette: function(data) {
			var baseOptions = [["circle", gettext("Circle")], ["square", gettext("Square")], ["diamond", gettext("Diamond")], ["triangle", gettext("Triangle")], ["cross", gettext("Cross")]];
			var allOptions = [];
			for (var i = 0; i < data.length; i++) {
				allOptions.push(baseOptions[i % baseOptions.length]);
			}
			return allOptions;
		},

		renderChart: function(plotContainer, plotPlaceholder, data, colors, symbols) {
			var data = [];
			$.each(initData, function(idx, rec) {
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

					var containerOffset = $(plotPlaceholder).offset();
					$("#point-tooltip").html(x + ", " + y + " (" + gettext("index") + ": " + item.dataIndex + ", " + gettext("class") + ": " + item.series.label + ")").css({
						top: item.pageY - containerOffset['top'],
						left: item.pageX - containerOffset['left'] + 10
					}).fadeIn(200);
				} else {
					$("#point-tooltip").hide();
				}
			});
		},

		updateChart: function(dialog) {
			var plotContainer = $(dialog.find(".plot-container")[0]);
			var formWindow = dialog.find(".task-window");

			var data = window.resultsPlot.getDataToRender();
			var colors = window.resultsPlot.generateColorPalette(data);
			var symbols = window.resultsPlot.generateSymbolPalette(data);
			var renderChoices = plotContainer.find(".render-choices tbody tr");
			$.each(renderChoices, function(idx, choice) {
				// TODO: add color validation or color picker
				var color = $(choice).find("input").val();
				colors[idx] = color ? color: colors[idx];

				var symbol = $(choice).find("option:selected").val();
				symbols[idx] = symbol ? symbol: symbols[idx][0];
			});
			window.resultsPlot.renderChart(plotContainer, "#" + formWindow.attr("id") + " .results-container", data, colors, symbols);
		},

		downloadChart: function(plotContainer) {
			var canvas = plotContainer.find("canvas")[0];
			var image = canvas.toDataURL("image/jpeg");
			image = image.replace("image/jpeg", "image/octet-stream");

			//var image = canvas.toDataURL();
			//image = image.replace("image/png", "image/octet-stream");
			document.location.href = image;
		},

		chart: function(formWindow) {
			var plotContainer = formWindow.find(".plot-container");
			if (plotContainer.length == 0) {
				var plotContainer = $("<div class=\"plot-container\" style=\"min-height: 400px; position: relative;\"></div>");
				var plotPlaceholder = "<div class=\"results-container\" style=\"width: 600px; height: 300px; margin: auto;\"></div>";
				plotContainer.append(plotPlaceholder);

				var renderChoicesBody = $("<tbody></tbody>");
				var renderChoicesHead = $("<thead><th>" + gettext('Class') + "</th><th>" + gettext('Color') + "</th><th>" + gettext('Shape') + "</th></thead>");
				var renderChoices = $("<table class=\"render-choices\" style=\"margin: auto; margin-top: 20px;\"></table>");
				renderChoices.append(renderChoicesHead);
				renderChoices.append(renderChoicesBody);
				plotContainer.append(renderChoices);

				// append to body temporarily in order for axes labels to be drawn correctly
				$("body").append(plotContainer);

				var initData = window.resultsPlot.getDataToRender();
				var colorPalette = window.resultsPlot.generateColorPalette(initData);
				var symbolPalette = window.resultsPlot.generateSymbolPalette(initData);
				var symbolValues = []

				$.each(initData, function(idx, series) {
					var seriesRow = $("<tr></tr>");
					seriesRow.append("<td>" + idx + "</td>");
					seriesRow.append("<td><input type=\"text\" value=\"" + colorPalette[idx].toLowerCase() + "\"/></td>");

					var shapeSelect = $("<select></select>");
					$.each(symbolPalette, function(i, shape) {
						shapeSelect.append("<option value=\"" + shape[0] + "\"" + (idx == i ? "selected=\"selected\"": "") + ">" + shape[1] + "</option>");
						symbolValues.push(shape[0]);
					});
					var shapeCell = $("<td></td>");
					shapeCell.append(shapeSelect);
					seriesRow.append(shapeCell);

					renderChoicesBody.append(seriesRow);
				});

				window.resultsPlot.renderChart(plotContainer, "body > .plot-container .results-container", initData, colorPalette, symbolValues);
				//append to form after rendering because otherwise axes are not rendered
				formWindow.append(plotContainer);

                window.resultsPlot.customizeDialog(formWindow);
			}
		},

        // customize dialog for specific component: set width, add buttons and close handler
		customizeDialog: function(formWindow) {
			// customize dialog
			formWindow.dialog("option", "close", function() {
				$(this).find("#point-tooltip").remove();
			});
			var buttons = formWindow.dialog("option", "buttons");
			buttons.splice(0, 0, {
				text: gettext('Download'),
				click: function(ev) {
					var plotContainer = $(ev.currentTarget).closest(".ui-dialog").find(".plot-container");
					window.resultsPlot.downloadChart($(plotContainer[0]));
				}
			});
			buttons.splice(0, 0, {
				text: gettext('Update'),
				click: function(ev) {
					var dialog = $(ev.currentTarget).closest(".ui-dialog");
					window.resultsPlot.updateChart(dialog);
				}
			});
			formWindow.dialog("option", "buttons", buttons);
			formWindow.dialog("option", "minWidth", 650);
		}
	}
})();

