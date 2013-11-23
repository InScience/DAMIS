;
(function() {
	window.experimentForm = {
        // parameters for window.experimentForm initialization
		initParams: {},

		// translate parameter binding from client to server
		// representation
		bindingToServer: function() {
			$.each($(".task-window input[id$=is_input]"), function() {
				if ($(this).val() === "True") {
					var iParamField = $(this).closest("div").find("input[id$=value]");
					var oParamAddr = $(iParamField).val();
					if (oParamAddr) {
						var parts = oParamAddr.split(",");
                        // TODO: remove this check when different fields are used
                        // to pass value and reference
                        if (parts.length > 1) {
						    var oParam = window.taskBoxes.getParameter(parts[0], parts[1]);
						    iParamField.val(oParam.attr("id"));
                        }
					}
				}
			});
		},

		// translate parameter binding from server to client
		// representation
		bindingToClient: function(taskForm, taskBox) {
			$.each(taskForm.find("input[id$=is_input]"), function() {
				if ($(this).val() === "True") {
					var iParamField = $(this).closest("div").find("input[id$=value]");
					var oParamId = $(iParamField).val();
					if (oParamId) {
                        // TODO: remove this check when different fields are used
                        // to pass value and reference
                        if (oParamId.match(/PV_\d+/)) {
						    var oParam = $("#" + oParamId);
						    var oParent = oParam.closest("div");
						    iParamField.val(oParent.index() + "," + taskBox.attr("id"));
                        }
					}
				}
			});
		},

		// handles submission of experiment form
		// refresh form data before submition
		// recreate modal windows in case of validation errors
		handleSubmit: function(parameterPrefixesUrl, experimentsListUrl) {
			// pass current task forms prefixes to get parameter
			// formsets prefixes
			var taskFormPrefixes = []
			$.each($(".task-window .task-form"), function(taskBoxIdx, taskForm) {
				var name = $(taskForm).find("input,select,textarea,label").attr("name");
				var taskFormPrefix = /tasks-\d+/g;
				taskFormPrefixes.push(taskFormPrefix.exec(name)[0]);
			});
			$.ajax({
				url: parameterPrefixesUrl,
				data: {
					prefixes: taskFormPrefixes
				},
				context: $(this)
			}).done(function(parameterFormsetPrefixes) {
				// when a box is deleted, other boxes have their ids
				// updated,  however, parameter formsets prefixes are not updated
				// we need to do it manually 
				var paramPrefixes = parameterFormsetPrefixes.split(",");
				$.each($(".task-window .parameter-values"), function(taskBoxIdx, paramsFormset) {
					$.each($(paramsFormset).find("input,select,textarea,label"), function(inputIdx, input) {
						var origPrefix = paramPrefixes[taskBoxIdx];
						var name = $(input).attr("name");
						var id = $(input).attr("id");
						if (name) {
							$(input).attr("name", name.replace(/PV_\d+/, origPrefix));
						}
						if (id) {
							$(input).attr("id", id.replace(/PV_\d+/, origPrefix));
						}
					});
				});

				// translate parameter bindings from client to server
				// representation
				window.experimentForm.bindingToServer();

				var form = $("#experiment-form");
				var data = form.serialize();
				$.post(form.attr("action"), data, function(resp) {
					if (resp === "OK") {
						window.location = experimentsListUrl;
						return;
					}

					//reinitialize the form 
					$("#experiment-form").remove();
					$("#workflow-editor-container").before(resp);

					// recreate modal windows
					// iterate through existing task boxes
					// in the order of creation (asume, it is reflected
					// in DOM order)
					var updatedForms = $("#experiment-form .inline");
					$.each($(".task-box"), function(taskBoxId, taskBox) {
						taskForm = $(updatedForms[taskBoxId + 1]);
						parameterFormset = $(taskForm.next(".parameter-values"));
						// mark the task box as conataining errors
						if (parameterFormset.find(".errorlist").length > 0) {
							$(taskBox).addClass("error");
						}
						window.taskBoxes.createTaskFormDialog(taskForm, parameterFormset, window.taskBoxes.getFormWindowId($(taskBox)));
						taskForm.find(".algorithm-selection select").change(window.taskBoxes.loadAlgorithmParameters);

						//restore parameter bindings from server to client representation
						window.experimentForm.bindingToClient(taskForm, taskBox);
					});

					window.experimentForm.init(window.experimentForm.initParams);
				});
			});
		},
		init: function(params) {
			//store parameter for reinitializing after failed form submission 
			window.experimentForm.initParams = params
			parametersUrl = params['parametersUrl'];
			parameterPrefixesUrl = params['parameterPrefixesUrl'];
			experimentsListUrl = params['experimentsListUrl'];
			taskFormPrefix = params['taskFormPrefix'];

			//initialize the jQuery formset plugin
			$('.inline').formset({
				prefix: taskFormPrefix,
				extraClasses: ['task-form'],
			});

			//assign form submit handler
			$('#execute-btn').click(function(ev) {
				window.experimentForm.handleSubmit(parameterPrefixesUrl, experimentsListUrl)
			});
		}
	}
})();

