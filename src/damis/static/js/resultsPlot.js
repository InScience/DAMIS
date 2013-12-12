(function() {
	window.resultsPlot = {
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

		init: function() {
            // TODO: initData is parameter, obtained via Ajax
            // TODO: each data group should have a color, find a way to define default
            // colors
			initData = [{
				group: "1",
				symbol: "circle",
				data: window.resultsPlot.generate(2, 1.8)
			},
			{
				group: "2",
				symbol: "square",
				data: window.resultsPlot.generate(4, 0.9)
			},
			{
				group: "3",
				symbol: "diamond",
				data: window.resultsPlot.generate(7, 1.1)
			}]

			var plotSelector = "#results-plot";

			var data = []
			$.each(initData, function(idx, rec) {
				data.push({
					label: rec['group'],
					points: {
						symbol: rec['symbol']
					},
					data: rec['data'],
				});
			});

			var plot = $.plot($(plotSelector), data, {
				series: {
					points: {
						show: true,
						radius: 3
					},
				},
				grid: {
					clickable: true,
					hoverable: true
				}
			});

			$("<div id='point-tooltip'></div>").css({
				position: "absolute",
				display: "none",
				border: "1px solid #fdd",
				padding: "2px",
				"background-color": "#fee",
				opacity: 0.80
			}).appendTo("body");

			$(plotSelector).bind("plotclick", function(event, pos, item) {
				if (item) {
					var x = item.datapoint[0].toFixed(2),
					y = item.datapoint[1].toFixed(2);

					$("#point-tooltip").html(x + ", " + y + " (" + gettext("index") + ": " + item.dataIndex + ", " + gettext("class") + ": " + item.series.label + ")").css({
						top: item.pageY + 5,
						left: item.pageX + 5
					}).fadeIn(200);
				} else {
					$("#tooltip").hide();
				}
			});
		},
	}
})();

