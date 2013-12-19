;
(function() {
	window.persistWorkflow = {

		// persists jsPlumb entities to a string
		persistJsPlumbEntities: function() {

			// persist boxes together with their endpoints
			var boxes = {};
			$.each($(".task-box"), function(idx, box) {
				var $box = $(box);
				var boxId = $box.attr("id");

				var endpoints = [];
				$.each(jsPlumb.getEndpoints(boxId), function(eIdx, e) {
					endpoints.push({
						parameters: e.getParameters(),
						anchor: e.anchor.type,
						isTarget: e.isTarget,
					});
				});

				boxes[boxId] = {
					boxId: boxId,
					x: parseInt($box.css("left"), 10),
					y: parseInt($box.css("top"), 10),
					icoUrl: $box.find("img").attr("src"),
					endpoints: endpoints
				};
			});

			// persist connections
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
			var persistedStr = boxesStr + "***" + connectionsStr + "***" + window.taskBoxes.countBoxes;
			return persistedStr;
		},

		// restores jsPlumb entities from a string 
		restoreJsPlumbEntities: function(persistedStr) {
			var parts = persistedStr.split("***");
			var boxes = JSON.parse(parts[0]);
			var connections = JSON.parse(parts[1]);
			window.taskBoxes.countBoxes = parseInt(parts[2]);

			// restore boxes 
			$.each(boxes, function(idx, box) {
				var taskBox = $(window.taskBoxes.assembleBoxHTML("", box['icoUrl']));
				taskBox.attr("id", box['boxId']);
				taskBox.appendTo($("#flowchart-container"));
				taskBox.css("left", box['x'] + "px");
				taskBox.css("top", box['y'] + "px");
			});

			// recreate connections 
			$.each(connections, function(idx, conn) {
				var sourceBox = $("#" + conn.sourceBoxId);
				var targetBox = $("#" + conn.targetBoxId);

				// add endpoints that participate in a connection
				var targetEndpoint = window.experimentCanvas.addEndpoint(true, targetBox, conn.targetAnchor.type, {
					iParamNo: conn.params['iParamNo'],
					iTaskBoxId: conn.params['iTaskBoxId']
				});
				var sourceEndpoint = window.experimentCanvas.addEndpoint(false, sourceBox, conn.sourceAnchor.type, {
					oParamNo: conn.params['oParamNo'],
					oTaskBoxId: conn.params['oTaskBoxId']
				});

				// remove endpoints that participate in a connection from the
				// list of endpoints to be recreated 
				window.persistWorkflow.removeConnectedEndpoints(boxes[conn.targetBoxId]['endpoints'], conn, true);
				window.persistWorkflow.removeConnectedEndpoints(boxes[conn.sourceBoxId]['endpoints'], conn, false);

				var conn = jsPlumb.connect({
					source: sourceEndpoint,
					target: targetEndpoint
				});
			});

			// add remaining unconnected endpoints
			$.each(boxes, function(idx, box) {
				$.each(box.endpoints, function(eIdx, e) {
					window.experimentCanvas.addEndpoint(e.isTarget, box['boxId'], e.anchor, e.parameters);
				});
			});
		},

		// remove endpoint from the array if it matches the connection endpoint
		// by the parameters
		removeConnectedEndpoints: function(epoints, conn, isTarget) {
			var len = epoints.length;
			while (len--) {
				var e = epoints[len];
				var match = isTarget ? e.parameters["iParamNo"] == conn.params["iParamNo"] : e.parameters["oParamNo"] == conn.params["oParamNo"];
				if (match) {
					epoints.splice(len, 1);
				}
			}
		},

		restore: function(persistedStr) {
			jsPlumb.setSuspendDrawing(true);
			this.restoreJsPlumbEntities(persistedStr);
			window.experimentForm.init();
			window.experimentForm.reinitExperimentForm();
			jsPlumb.setSuspendDrawing(false, true);
		},
	}
})();

