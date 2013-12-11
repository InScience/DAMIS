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
						modal: true,
						autoopen: false,
						appendTo: "body",
						buttons: [{
							text: gettext("Cancel"),
							click: function(ev) {
								$(this).dialog("close");
							}
						},
						{
							text: gettext("OK"),
							click: function(ev) {
								$(this).dialog("close");
								$(formSelector).submit();
							}
						}],
						open: function() {
							var dialog = $(this).closest(".ui-dialog");
							dialog.find("button").addClass('btn');
							dialog.find(".ui-dialog-titlebar > button").remove();
						}
					});
				} else {
					dialog.dialog("open");
				}
			}
		}
	}
})();

