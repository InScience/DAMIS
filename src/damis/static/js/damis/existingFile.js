(function() {
	window.existingFile = {
		init: function(componentType, formWindow) {
			if (componentType == 'EXISTING FILE') {
				window.existingFile.update(formWindow);
				var outParam = formWindow.find("input[value=OUTPUT_CONNECTION]").parent().find("input[name$=value]");
				if (outParam.val()) {
					// editing workflow: a connection already exists 
					// TODO: put the message into the message container
					formWindow.find(".message").html(this.fileSelectedView(outParam.val()));
				}
			}
		},

		fileSelectedView: function(fileUrl) {
			var successText = "";
			if (fileUrl) {
				var fileName = fileUrl.substring(fileUrl.lastIndexOf("/") + 1);
				successText = gettext("File used in the experiment") + ": <a href=\"" + fileUrl + "\"><b>" + fileName + "</b></a>";
			}
			return successText;
		},

		// send request to the server to obtain file upload form
		update: function(dialog, url) {
			if (!url) {
				url = window.componentFormUrls['EXISTING FILE'];
			}
			var container = dialog.find(".file-form-container");
			var fileList;
			if (container.length == 0) {
				container = $("<div class=\"file-form-container\"><img width=\"250px\" src=\"/static/img/loading.gif\"/></div>");
				dialog.append(container);
			} else {
				fileList = container.find(".file-list");
			}
			$.ajax({
				url: url,
				context: container
			}).done(function(resp) {
                var container = $(this);
				container.html(resp);

				// bind paging handler
				container.find(".pagination a").on("click", function(ev) {
					ev.preventDefault();
					var page_url = $(this).attr("href");
					window.existingFile.update(dialog, page_url);
				});
				// bind selection handler
				container.find("input[name=dataset_pk]").on("click", function(ev) {
                    var fileUrl = $(this).val();

                    // set OUTPUT_CONNECTION value for this component
				    var connectionInput = dialog.find(".parameter-values input[value=OUTPUT_CONNECTION]");
				    var valueInput = connectionInput.parent().find("input[name$=value]");
				    valueInput.val(fileUrl);

					// show message
					container.find(".message").html(window.existingFile.fileSelectedView(fileUrl));
				});

				dialog.dialog("option", "buttons", window.existingFile.allButtons());
				dialog.dialog("option", "minWidth", 0);
				dialog.dialog("option", "width", "auto");
			});
		},

		// all buttons of this component dialog
		allButtons: function() {
			return window.taskBoxes.defaultDialogButtons();
		},
	}
})();

