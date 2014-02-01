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
					var formWindow = $(this);
					var downloadOptions = $(this).find(".download-options").clone(true);
					downloadOptions.dialog({
						"title": gettext("Select file type and destination"),
						"modal": true,
						"minWidth": 400,
						"open": function() {
							var dialog = $(this).closest(".ui-dialog");
							dialog.find(".ui-dialog-titlebar > button").remove();
						},
						"buttons": [{
							"text": gettext("OK"),
							"class": "btn btn-primary",
							"click": function(ev) {
								var format = $(this).find("input[name=file-type]:checked").val();
								var dst = $(this).find("input[name=file-destination]:checked").val();
								if (dst == 'midas') {
									$(".not-implemented").show();
								} else {
									$(this).dialog("destroy");
									var url = window.componentFormUrls['MATRIX VIEW'];
									var data = window.matrixView.getOutputParamDetails(formWindow);
									document.location.href = url + "?download=True&format=" + format + "&pv_name=" + data.pv_name + "&dataset_url=" + data.dataset_url;
								}
							}
						},
						{
							"text": gettext("Cancel"),
							"class": "btn",
							"click": function(ev) {
								$(".not-implemented").hide();
								$(this).dialog("destroy");
							}
						}]
					});
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
			window.utils.showProgress();
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
					formWindow.dialog("option", "maxHeight", 500);
					formWindow.dialog("option", "width", "auto");
				}
				window.utils.hideProgress();
			});
		},

		initTable: function(table) {
			return table.dataTable({
				"sScrollY": 200,
				"sScrollX": "100%",
				"bInfo": false,
				"bPaginate": false,
				"bFilter": false,
				"bDestroy": true,
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
		},

		doubleClick: function(componentType, formWindow) {
			if (componentType == 'MATRIX VIEW') {
				formWindow.dialog("open");
				var dataTable = $(formWindow).find("table[id^=DataTables]");
				if (dataTable.length == 0) {
					var table = $(formWindow).find(".file-content-table");
					var dataTable = window.matrixView.initTable(table);
				}
			}
		}
	}
})();

