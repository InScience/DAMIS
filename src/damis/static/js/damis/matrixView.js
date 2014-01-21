(function() {
	window.matrixView = {
		init: function(componentType, formWindow) {
			if (componentType == 'MATRIX VIEW') {
				this.toUnconnectedState(formWindow);
			}
		},

		// prepare dialog, when component is unconnected 
		toUnconnectedState: function(formWindow) {
			formWindow.find(".matrix-container").remove();
			var container = $("<div class=\"matrix-container\">" + gettext("This component should be connected to an executed task in order to view results.") + "</div>");
			formWindow.append(container);
			formWindow.dialog("option", "buttons", window.matrixView.reducedButtons());
			formWindow.dialog("option", "minWidth", 0);
			formWindow.dialog("option", "width", 300);
		},

        reducedButtons: function() {
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
		allButtons: function() {
			var buttons = [{
				"text": gettext('Download'),
				"class": "btn btn-primary",
				"click": function(ev) {
					var url = window.componentFormUrls['MATRIX VIEW'];
                    var dialog = $(ev.currentTarget).closest(".ui-dialog");
					var formWindow = dialog.find(".task-window");
					var data = window.matrixView.getOutputParamDetails(formWindow);
					var format = dialog.find(".file-type-select").val();
					document.location.href = url + "?download=True&format=" + format + "&pv_name=" + data.pv_name + "&dataset_url=" + data.dataset_url;
				}
			}];
			var reducedButtons = window.matrixView.reducedButtons();
			return buttons.concat(reducedButtons);
		},

		// update dialog content with new data
		update: function(formWindow) {
			var url = window.componentFormUrls['MATRIX VIEW'];
			formWindow.find(".matrix-container").remove();
			var container = $("<div class=\"matrix-container\"><img width=\"250px\" src=\"/static/img/loading.gif\"/></div>");
			formWindow.append(container);
			var data = window.matrixView.getOutputParamDetails(formWindow);
			$.ajax({
				url: url,
				data: data,
				context: container
			}).done(function(resp) {
				$(this).html(resp);
				if (!/<[a-z][\s\S]*>/i.test(resp)) {
					// non-html (failure) response
				} else {
					formWindow.dialog("option", "buttons", window.matrixView.allButtons());
					formWindow.dialog("option", "minWidth", 0);
					formWindow.dialog("option", "maxHeight", 500);
					formWindow.dialog("option", "width", "auto");
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
			if (targetComponentType == 'MATRIX VIEW') {
				this.update($("#" + window.taskBoxes.getFormWindowId(connectionParams.iTaskBoxId)));
			}
		},

		// called when connection is deleted
		connectionDeleted: function(srcComponentType, targetComponentType, connectionParams) {
			if (srcComponentType == 'MATRIX VIEW' || targetComponentType == 'MATRIX VIEW') {
				var formWindow = $("#" + window.taskBoxes.getFormWindowId(connectionParams.iTaskBoxId));
				this.toUnconnectedState(formWindow);
			}
		}
	}
})();

