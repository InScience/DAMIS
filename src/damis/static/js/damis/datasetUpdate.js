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
					var form = $(this).find("form");
                    window.utils.showProgress();
					$.ajax({
                        url: form.attr("action"),
						"method": "POST",
						"data": form.serialize(),
						"context": $(this)
					}).done(function(resp) {
                        $(this).html(resp);
                        if (window.datasetUpdate.checkSuccess($(this))) {
                            window.location.reload();
                        }
                        window.utils.hideProgress();
					});
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

		checkSuccess: function(resp) {
			return resp.find(".errorlist").length == 0;
		},
	}
});

