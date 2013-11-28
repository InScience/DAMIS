;
(function() {
	window.persistWorkflow = {

		persistJsPlumbEntities: function() {
			var boxes = [];
			$.each($(".task-box"), function(taskBoxId, box) {
				var $box = $(box);
				boxes.push({
					boxId: $box.attr("id"),
					x: parseInt($box.css("left"), 10),
					y: parseInt($box.css("top"), 10),
				});
			});
			var connections = [];
			$.each(jsPlumb.getConnections(), function(idx, connection) {
				var sourceId = connection.sourceId;
				var targetId = connection.targetId;
				var sourceAnchor, targetAnchor;
				if (connection.endpoints[0].elementId == sourceId) {
					sourceAnchor = connection.endpoints[0].anchor;
					targetAnchor = connection.endpoints[1].anchor;
				} else {
					targetAnchor = connection.endpoints[0].anchor;
					sourceAnchor = connection.endpoints[1].anchor;
				}
				connections.push({
					connectionId: connection.id,
					sourceBoxId: sourceId,
					targetBoxId: targetId,
					params: connection.getParameters(),
					sourceAnchor: sourceAnchor,
					targetAnchor: targetAnchor,
				});
			});
			var boxesStr = JSON.stringify(boxes);
			var connectionsStr = JSON.stringify(connections);
			var persistedStr = boxesStr + "***" + connectionsStr;
			console.log(persistedStr);
			return persistedStr;
		},

		// params is an empty JSON, as this function is a callback
		persist: function(params) {
			window.persistWorkflow.persistJsPlumbEntities();
			// TODO: submit form without validation
		},

		restoreJsPlumbEntities: function(persistedStr) {
			var parts = persistedStr.split("***");
			var boxes = JSON.parse(parts[0]);
			var connections = JSON.parse(parts[1]);

			// restore boxes 
			$.each(boxes, function(idx, box) {
				var taskBox = $("<div><div>New task</div></div>");
				taskBox.attr("id", box['boxId']);
				taskBox.addClass("task-box");
				taskBox.appendTo($("#flowchart-container"));
				taskBox.css("left", box['x'] + "px");
				taskBox.css("top", box['y'] + "px");
			});

			window.taskBoxes.taskBoxesToEndpoints = {};

			// recreate connections 
			$.each(connections, function(idx, conn) {
				var sourceBox = $("#" + conn.sourceBoxId);
				var targetBox = $("#" + conn.targetBoxId);

				var x = jsPlumb.addEndpoint(targetBox, window.experimentCanvas.getTargetEndpoint(), {
					anchor: conn.targetAnchor.type,
					parameters: {
						iParamNo: conn.params['iParamNo'],
						// parameter form idx
						iTaskBoxId: conn.params['iTaskBoxId']
					},
				});
				var y = jsPlumb.addEndpoint(sourceBox, window.experimentCanvas.getSourceEndpoint(), {
					anchor: conn.sourceAnchor.type,
					parameters: {
						oParamNo: conn.params['oParamNo'],
						// parameter form idx
						oTaskBoxId: conn.params['oTaskBoxId'],
					}
				});
				// reconstruct window.taskBoxes.taskBoxesToEndpoints
				window.taskBoxes.storeEndpoint(conn.targetBoxId, true, x);
				window.taskBoxes.storeEndpoint(conn.sourceBoxId, false, y);

				var conn = jsPlumb.connect({
					source: y,
					target: x
				});
			});

            console.log(window.taskBoxes.taskBoxesToEndpoints);
		},

		restore: function(persistedStr) {
			this.restoreJsPlumbEntities(persistedStr);
			window.experimentForm.init();
			window.experimentForm.reinitExperimentForm();
		},
	}
})();

