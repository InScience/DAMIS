(function() {
	window.utils = {
		showProgress: function() {
			var spinner = $("#spinner");
			if (spinner.length == 0) {
				var spinner = $('<div id="spinner" style="display: none; background-color: rgba(0, 0, 0, 0.6); width:100%; height:100%; position:fixed; top:0px; left:0px; z-index:9999"/>');
				$("body").append(spinner);
				setTimeout(function() {
					if (spinner.length > 0) {
						spinner.show();
						spinner.spin("modal");
					}
				},
				2000);
			}
		},
		hideProgress: function() {
			var spinner = $("#spinner");
			spinner.spin(false);
			spinner.remove();
		},
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
			window.utils.initToggleSectionBtn(container, true);
		},

		// initializes a button (.toggle-btn) that toggles a section (.toggle-section) 
		// visibility inside a container
		initToggleSectionBtn: function(container, useHideBtn) {
			// toggle file form visibility on click of a button
			var newFileBtn = container.find(".toggle-btn");
			newFileBtn.on("click", function(ev) {
				var newFileForm = container.find(".toggle-section");
				if (newFileBtn.hasClass("show")) {
					newFileForm.show();

					newFileBtn.removeClass("show");
					if (useHideBtn) {
						newFileBtn.html(gettext("Hide form"));
					} else {
						newFileBtn.remove();
					}
				} else {
					newFileForm.hide();

					newFileBtn.addClass("show");
					newFileBtn.html(gettext("New file"));
				}
			})
		}
	}
})();

