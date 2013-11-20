;
(function() {
	window.experimentForm = {
        initParams: {},
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
                        if(id){
						    $(input).attr("id", id.replace(/PV_\d+/, origPrefix));
                        }
					});
				});

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
					});

                    window.experimentForm.init(window.experimentForm.initParams);
                    
					// TODO: check parameter connections
					// TODO: check if connections work properly
				});
			});
		},
		init: function(params) {
            //store parameter for reinitializing after failed form submission 
            window.experimentForm.initParams = params  
            parametersUrl = params['parametersUrl']
            parameterPrefixesUrl = params['parameterPrefixesUrl']
            experimentsListUrl = params['experimentsListUrl']
            taskFormPrefix = params['taskFormPrefix']

            //initialize the jQuery formset plugin
            $('.inline').formset({
                prefix: taskFormPrefix,
                extraClasses: ['task-form'],
            });

			//assign form submit handler
			$('#execute-btn').click(function(ev) {
                window.experimentForm.handleSubmit(parameterPrefixesUrl, experimentsListUrl)
            });
		},
	}
})();

