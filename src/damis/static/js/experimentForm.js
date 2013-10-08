;
(function() {
	window.experimentForm = {
		init: function(parametersUrl, parameterPrefixesUrl, experimentsListUrl) {
            // update parameter formset each time a different algorithm is selected
			$('.algorithm-selection select').change(function() {
				$.ajax({
					url: parametersUrl,
					data: {
						algorithm_id: $(this).val(),
						prefix: $(this).attr('name')
					},
					context: $(this)
				}).done(function(resp) {

					var formWindow = $(this).closest('.task').parent();
					formWindow.find(".parameter-values").html(resp);
					window.taskBoxes.handleAlgorithmChange(formWindow);
				});
			});

            // refresh form data before submition
            // recreate modal windows in case of validation errors
			$('#execute-btn').click(function(ev) {
                // pass current task forms prefixes to obtain parameter
                // formsets prefixes
				var names = []
				$.each($(".task-window .task-form"), function(idx, taskForm) {
					var name = $(taskForm).find("input,select,textarea,label").attr("name");
					names.push(name);
				});
				$.ajax({
					url: parameterPrefixesUrl,
					data: {
						prefixes: names
					},
					context: $(this)
				}).done(function(formsetPrefixes) {
					// update parameter formsets prefixes
					var prefixes = formsetPrefixes.split(",");
					$.each($(".task-window .parameter-values"), function(formIdx, params) {
						console.log(formIdx, prefixes[formIdx]);
						$.each($(params).find("input, select, textarea, label"), function(inputIdx, input) {
							var newName = $(input).attr("name");
							newName = newName.replace(/PV_\d+/, prefixes[formIdx]);
							$(input).attr("name", newName);
						});
					});

					var form = $("#experiment-form");
					var data = form.serialize();
					console.log(data);
					$.post("/x/experiment-formset/", data, function(resp) {
						if (resp === "OK") {
							window.location = experimentsListUrl;
							return;
						}
						$("#experiment-form").remove();
						$("#workflow-editor-container").before(resp);
						// TODO: re-creation of modal windows
					});
				});
			});
		},
	}
})();

