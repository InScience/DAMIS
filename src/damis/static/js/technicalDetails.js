(function() {
	window.technicalDetails = {
		init: function(dialog) {
			var url = window.componentFormUrls['TECHNICAL DETAILS'];
			var container = dialog.find(".technical-details-container");
			if (container.length == 0) {
				var container = $("<div class=\"technical-details-container\"></div>");
				dialog.append(container);
				$.ajax({
					url: url,
					data: window.technicalDetails.getOutputParamDetails(dialog),
					context: container
				}).done(function(resp) {
					$(this).html(resp);
				});
				window.files.customizeDialog(dialog);
			}
		},

		getOutputParamDetails: function(dialog) {
			var inParam = dialog.find("input[value=INPUT_CONNECTION]");
			var srcRefField = inParam.closest("div").find("input[id$=source_ref]");
			var oParamField = window.experimentForm.getOutputParam(srcRefField);
			if (oParamField) {
				return {
					pv_name: oParamField.attr("name"),
				}
			}
			return {}
		},
	}
})();

