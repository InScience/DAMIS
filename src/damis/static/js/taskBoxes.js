;
(function() {
	window.taskBoxes = {
		countBoxes: 0,

		// Maps task boxes to their endpoints
		taskBoxesToEndpoints: {},

		// remove all endpoints of a task box
		removeEndpoints: function(taskBoxId) {
			var epoints = window.taskBoxes.taskBoxesToEndpoints[taskBoxId];
			if (epoints && epoints.ipoints) {
				$.each(epoints.ipoints, function(idx, e) {
					jsPlumb.deleteEndpoint(e);
				});
			}
			if (epoints && epoints.opoints) {
				$.each(epoints.opoints, function(idx, e) {
					jsPlumb.deleteEndpoint(e);
				})
			}
		},

		// Double click on task box
		taskBoxRightClick: function(ev) {
			if (ev.button == 2) {
				var taskBox = $(ev.target);
				var taskForm = $(taskBox.attr("id") + "-form");
				jsPlumb.detachAllConnections(taskBox); // remove connections
				// TODO: reset values in the forms corresponding to this
				// connection
				taskForm.find(".delete-row").click(); // remove task form
				taskBox.remove(); // remove task box
				window.taskBoxes.removeEndpoints(taskBox.attr("id"));
			}
		},
        
        // Initialization required after a different algorithm has been
        // selected 
        handleAlgorithmChange: function(taskForm) {
			var taskBoxId = taskForm.attr("id").replace("-form", "");

			window.taskBoxes.removeEndpoints(taskBoxId);

			// Add new endpoints for input/output parameters
			var taskBox = $("#" + taskBoxId);
			taskBox.html(taskForm.find("select[id$='-algorithm']").find("option:selected").text());
			var parameters = taskForm.find('.parameter-values');

			var outAnchors = ["RightMiddle", [1, 0, 1, 1], [1, 1, 1, 1]];
			var oIdx = 0;
			var inAnchors = ["LeftMiddle", [0, 0, - 1, - 1], [0, 1, - 1, - 1]];
			var iIdx = 0;

			var ipoints = []
			var opoints = []

			$.each(parameters.find('div'), function() {
				var valId = $(this).find("input[id$='-value']").attr("id");
				var parameterFormPrefix = valId.replace("-value", "");

				var isIn = $(this).find("input[id$='is_input']").val();
				var isOut = $(this).find("input[id$='is_output']").val();

				if (isIn === "True") {
					//add input endpoint
					var x = jsPlumb.addEndpoint(taskBox, window.experimentCanvas.getTargetEndpoint(), {
						anchor: inAnchors[iIdx],
						parameters: {
							inParam: valId
						}
					});
					ipoints.push(x);
					iIdx++;
				} else if (isOut === "True") {
					//add output endpoint
					var y = jsPlumb.addEndpoint(taskBox, window.experimentCanvas.getSourceEndpoint(), {
						anchor: outAnchors[oIdx],
						parameters: {
							outParam: parameterFormPrefix
						}
					});
					opoints.push(y);
					oIdx++;
				}
			});
			window.taskBoxes.taskBoxesToEndpoints[taskBoxId] = {
				"ipoints": ipoints,
				"opoints": opoints
			}
        },

		// Initialize a new task box to accept double click events
		initTaskBox: function(ev, ui, taskContainer) {
			// drop the task where it was dragged
			var taskBox = $("<div>New task</div>");
			taskBox.appendTo(taskContainer);
			taskBox.css("left", ui.position.left + "px");
			taskBox.css("top", ui.position.top + "px");

			//assign id and class
			count = window.taskBoxes.countBoxes;
			window.taskBoxes.countBoxes++;
			taskBox.attr("id", "task-box-" + count);
			taskBox.addClass("task-box");
			taskBox.on("mousedown", this.taskBoxRightClick);

			//create modal window with form fields
			// click add form btn 
			var addTaskBtn = $("a[class=\"add-row\"]")
			addTaskBtn.click();

			// get generated form
			var taskForm = addTaskBtn.prev();
			taskForm.attr("id", taskBox.attr("id") + "-form");
			taskForm.dialog({
				autoOpen: false,
				appendTo: "#task-forms",
				modal: true,
				// Canel button should return the box to a previous state, but
				// that is too complicated for now, so no Cancel button
				buttons: [{
					text: "Close",
					click: function(ev) {
			            $(this).dialog("close");
					}
				}]
			});
			taskBox.on('dblclick', function(ev) {
				var taskFormId = $(ev.currentTarget).attr("id") + "-form";
				$("#" + taskFormId).dialog('open');
			});

			//make it draggable
			jsPlumb.draggable(taskBox, {
				grid: [20, 20],
				containment: "parent"
			});
		},
	}

})();

