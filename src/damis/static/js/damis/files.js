(function() {
	window.files = {
		init: function(componentType, formWindow) {
			if (componentType == 'UPLOAD FILE') {
				var outParam = formWindow.find("input[value=OUTPUT_CONNECTION]").parent().find("input[name$=value]");
				if (outParam.val()) {
					// editing workflow: a connection already exists 
					formWindow.append(this.fileSelectedView(outParam.val()));
				}
			}
		},

		fileSelectedView: function(fileUrl) {
			var successText = $("<div class=\"file-form-container\"></div>");
			if (fileUrl) {
				var fileName = fileUrl.substring(fileUrl.lastIndexOf("/") + 1);
				tableContent = gettext("A file is uploaded") + ": <a href=\"" + fileUrl + "\"><b>" + fileName + "</b></a>";
				successText.append(tableContent);
			}
			return successText;
		},

		// send request to the server to obtain file upload form
		update: function(dialog) {
			var url = window.componentFormUrls['UPLOAD FILE'];
			var fileForm = dialog.find(".file-form-container");
			if (fileForm.length == 0) {
				var fileForm = $("<div class=\"file-form-container\"><img width=\"250px\" src=\"/static/img/loading.gif\"/></div>");
				dialog.append(fileForm);
				$.ajax({
					url: url,
					context: fileForm
				}).done(function(resp) {
					$(this).html(resp);
					window.utils.customizeFileForm($(this));
					dialog.dialog("option", "buttons", window.files.allButtons());
					dialog.dialog("option", "min-width", 0);
					dialog.dialog("option", "width", "auto");
				});
			}
		},

		// upload form in the iframe
		doUpload: function(fileForm) {
			// TODO: clone does not preserve textarea and input values 
			// so we need to construct a placeholder differently 
			var fileFormPlaceholder = fileForm.clone(true);
			var fileUploadForm = $("#file-upload-form");
			// move the fields to the hidden form
			// replace them with a placeholder
			fileForm.after(fileFormPlaceholder).appendTo(fileUploadForm);

			$("#file-upload-iframe").off("load");
			$("#file-upload-iframe").on("load", function(resp) {
				window.files.handleUploadResponse(fileFormPlaceholder);
			});
			document.getElementById("file-upload-form").submit();
		},

		// process file upload response
		handleUploadResponse: function(fileFormPlaceholder) {
			var fileUploadIframe = $("#file-upload-iframe");
			var textContent = fileUploadIframe.contents().find("body").text();

			// if we no text in the iframe, it means that this was not a POST
			// response, so we should exit
			if (!textContent || textContent.length == 0) {
				return;
			}
			var responseText = $("<div class=\"file-form-container\">" + fileUploadIframe.contents().find("body").html() + "</div>");

			// clear the iframe response in order to prevent unexpected processing
			fileUploadIframe.contents().find("body").html("");
			$("#file-upload-form").html("");

			var formWindow = fileFormPlaceholder.parent();

			if (this.checkSuccess(responseText)) {
				// TODO: display feature naming form to the user? 
				// show read-only file info from the returned response,
				// this will not disappear during saving
				var fileUrl = responseText.find("input[name=file_path]").val();
				formWindow.append(this.fileSelectedView(fileUrl));

				// set OUTPUT_CONNECTION parameter of this task to the uploaded 
				// file url
				var connectionInput = formWindow.find(".parameter-values input[value=OUTPUT_CONNECTION]");
				var valueInput = connectionInput.parent().find("input[name$=value]");
				valueInput.val(fileUrl);

				// display only reduced buttons
				formWindow.dialog("option", "buttons", window.files.reducedButtons());
			} else {
				formWindow.append(responseText);
			}

			fileFormPlaceholder.remove();
			window.utils.customizeFileForm(formWindow);
		},

		// check if the upload was successful
		checkSuccess: function(resp) {
			return resp.find(".errorlist").length == 0;
		},

		reducedButtons: function() {
			var buttons = [{
				"text": gettext('OK'),
				"class": "btn btn-primary",
				"click": function(ev) {
					$(this).dialog("close");
				}
			}];
			return buttons;
		},

		// all buttons of this component dialog
		allButtons: function() {
			var buttons = [{
				"text": gettext('Upload'),
				"class": "btn btn-primary",
				"click": function(ev) {
					var fileForm = $(ev.currentTarget).closest(".ui-dialog").find(".file-form-container");
					window.files.doUpload($(fileForm[0]));
				}
			},
			{
				"text": gettext('Cancel'),
				"class": "btn",
				"click": function(ev) {
					$(this).dialog("close");
				}
			}];
			return buttons;
		},

		doubleClick: function(componentType, formWindow) {
			if (componentType == 'UPLOAD FILE') {
				this.update(formWindow);
			}
		},
	}
})();

