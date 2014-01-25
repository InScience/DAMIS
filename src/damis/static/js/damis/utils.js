(function() {
	window.utils = {
		initDeleteConfirm: function(formSelector) {
			$(".delete-btn").click(function() {
				window.utils.openDeleteConfirm(formSelector);
			});
		},
		openDeleteConfirm: function(formSelector) {
			if ($(formSelector + " input[type=checkbox]").is(":checked")) {
				var dialog = $(".delete-confirm");
				if (!dialog.hasClass("ui-dialog-content")) {
					dialog.dialog({
						"modal": true,
						"autoopen": false,
						"appendTo": "body",
						"buttons": [{
							"text": gettext("Cancel"),
							"class": "btn btn-primary",
							"click": function(ev) {
								$(this).dialog("close");
							}
						},
						{
							"text": gettext("OK"),
							"class": "btn",
							"click": function(ev) {
								$(this).dialog("close");
								$(formSelector).submit();
							}
						}],
						"open": function() {
							var dialog = $(this).closest(".ui-dialog");
							dialog.find(".ui-dialog-titlebar > button").remove();
						}
					});
				} else {
					dialog.dialog("open");
				}
			}
		},

		// initilializes elements of file input form
		customizeFileForm: function(container) {
			var fileInput = container.find("input[type=file]");
			var fileButton = container.find(".choose-file");
			fileButton.on("click", function(ev) {
				fileInput.click();
			});
			fileInput.on("change", function(ev) {
				var fileName = $(this).val();
				// put the uploaded file name next to the upload button
				fileButton.next("span").html(fileName);

				// prefill title input field with the uploaded file name
				var titleInput = container.find("input[name=title]");
				var baseName = fileName.substring(0, fileName.lastIndexOf("."));
				titleInput.val(baseName);
			});

			// toggle file form visibility on click of a button
			var newFileBtn = container.find(".new-file-btn");
			newFileBtn.on("click", function(ev) {
				var newFileForm = container.find(".new-file-form");
				if (newFileBtn.hasClass("show")) {
					newFileForm.show();

					newFileBtn.removeClass("show");
					newFileBtn.html(gettext("Hide form"));
				} else {
					newFileForm.hide();

					newFileBtn.addClass("show");
					newFileBtn.html(gettext("New file"));
				}
			})

		},
	}
})();

