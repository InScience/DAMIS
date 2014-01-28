$(function() {
	window.datasetUpdate = {
		init: function() {
			$(".damis-list a.update-btn").on("click", function(ev) {
				ev.preventDefault();
				var url = $(this).attr("href");
				$.ajax({
					url: url,
				}).done(function(resp) {
					var dialog = $("#dataset-update-dialog");
					if (dialog.length == 0) {
						dialog = $("<div id=\"dataset-update-dialog\"><div>");
						dialog.html(resp);
						window.utils.customizeFileForm(dialog);
						dialog.dialog({
							"modal": true,
							"appendTo": "body",
							"title": gettext("Update dataset"),
							"buttons": window.datasetUpdate.allButtons(),
							"open": function() {
								var dialog = $(this).closest(".ui-dialog");
								dialog.find(".ui-dialog-titlebar > button").remove();
							},
							"minWidth": 0,
							"width": "auto",
						});
					} else {
						dialog.html(resp);
						window.utils.customizeFileForm(dialog);
						dialog.dialog("open");
					}
				});
			});
		},

		allButtons: function() {
			return [{
				"text": gettext("OK"),
				"class": "btn btn-primary",
				"click": function(ev) {
					window.datasetUpdate.doUpload($(this));
				}
			},
			{
				"text": gettext("Cancel"),
				"class": "btn",
				"click": function(ev) {
					$(this).dialog("close");
				}
			}]
		},

		doUpload: function(dialog) {
			window.utils.showProgress();
			dialog.closest(".ui-dialog").find("button").attr("disabled", "disabled");

			var fileForm = dialog.find(".dynamic-container");
			// TODO: clone does not preserve textarea and input values 
			// so we need to construct a placeholder differently 
			var fileFormPlaceholder = fileForm.clone(true);

			// move the fields to the hidden form
			// replace them with a placeholder
			var fileUploadForm = $("#file-upload-form");
			fileForm.after(fileFormPlaceholder).appendTo(fileUploadForm);

			$("#file-upload-iframe").off("load");
			$("#file-upload-iframe").on("load", function(resp) {
				window.datasetUpdate.handleUploadResponse(dialog);
			});

			var form = dialog.find("form");
			$("#file-upload-form").attr("action", form.attr("action"));
			$("#file-upload-form").submit();
		},

		handleUploadResponse: function(dialog) {
			var fileUploadIframe = $("#file-upload-iframe");
			var textContent = fileUploadIframe.contents().find("body").text();

			// if we no text in the iframe, it means that this was not a POST
			// response, so we should exit
			if (!textContent || textContent.length == 0) {
				return;
			}
			var responseText = $(fileUploadIframe.contents().find("body").html());
			// clear the iframe response in order to prevent unexpected processing
			fileUploadIframe.contents().find("body").html("");
			$("#file-upload-form").html("");

			dialog.dialog("option", "buttons", window.datasetUpdate.allButtons());
			dialog.html(responseText);

			window.utils.customizeFileForm(dialog);
			window.utils.hideProgress();
			if (this.checkSuccess(responseText)) {
				dialog.dialog("close");
				document.location.reload(true);
			}
		},

		checkSuccess: function(resp) {
			return resp.find(".errorlist").length == 0;
		},
	}
});

