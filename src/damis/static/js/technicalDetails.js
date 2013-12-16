(function() {
	window.technicalDetails = {
		init: function(componentType, formWindow) {
			if (componentType == 'TECHNICAL DETAILS') {
				var container = $("<div class=\"technical-details-container\">" + gettext("This component should be connected to an executed task in order to view results.") + "</div>");
			    formWindow.append(container);
				this.customizeDialog(formWindow);
			}
		},

		customizeDialog: function(formWindow) {
			var buttons = formWindow.dialog("option", "buttons");
			buttons.splice(0, 0, {
				text: gettext('Download'),
				click: function(ev) {
					// TODO: add file download functionality
				}
			});
			formWindow.dialog("option", "buttons", buttons);
		},

		// update dialog content with new data
		update: function(formWindow) {
			var url = window.componentFormUrls['TECHNICAL DETAILS'];
			formWindow.find(".technical-details-container").remove();
			var container = $("<div class=\"technical-details-container\"><img src=\"static/img/loading.gif\"/></div>");
			formWindow.append(container);
			$.ajax({
				url: url,
				data: window.technicalDetails.getOutputParamDetails(formWindow),
				context: container
			}).done(function(resp) {
				$(this).html(resp);
			});
		},

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

		connectionEstablished: function(srcComponentType, targetComponentType, connectionParams) {
			if (targetComponentType == 'TECHNICAL DETAILS') {
				this.update($("#" + window.taskBoxes.getFormWindowId(connectionParams.iTaskBoxId)));
			}
		},

		connectionDeleted: function(srcComponentType, targetComponentType, connectionParams) {
			if (srcComponentType == 'TECHNICAL DETAILS' || targetComponentType == 'TECHNICAL DETAILS') {
            }
		}
	}
})();

