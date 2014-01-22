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

		// enables the Choose file button to open browse dialog and display
		// selected file name
		customizeFileBtn: function(container) {
			var fileInput = container.find("input[type=file]");
			var fileButton = container.find(".choose-file");
			fileButton.on("click", function(ev) {
				fileInput.click();
			});
			fileInput.on("change", function(ev) {
				fileButton.next("span").html($(this).val());
			});
		},
	}
})();

