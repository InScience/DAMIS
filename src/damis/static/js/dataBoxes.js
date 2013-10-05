;
(function() {
	window.dataBoxes = {

		// output endpoint of a databox
		endpoint: undefined,

		// Initialization required after a different dataset has been
		// selected 
		handleDataChange: function(dataBox) {
			// change box name
			var option = $("#data-input-container select[id$='dataset']").find("option:selected");
			dataBox.html(option.text().substr(0, 6));
			var e = window.dataBoxes.endpoint;
			if (e) {
				jsPlumb.deleteEndpoint(e);
			}
			e = jsPlumb.addEndpoint(dataBox, window.experimentCanvas.getSourceEndpoint(), {
				anchor: "RightMiddle",
				parameters: {
					outParam: option.val()
				}
			});
			window.dataBoxes.endpoint = e;
		},

		// Initialize a new task box to accept double click events
		initDataBox: function(ev, ui, canvas) {
			// create new data box and constrain its dragging
			var dataBox = $("<div>Dataset</div>");
			dataBox.appendTo(canvas);
			dataBox.css("left", ui.position.left + "px");
			dataBox.css("top", ui.position.top + "px");
			jsPlumb.draggable(dataBox, {
				grid: [20, 20],
				containment: "parent"
			});
			dataBox.addClass("data-box");

			//remove the original draggable data-box
			ui.draggable.remove();

			// get generated form
			var dataInputContainer = $("#data-input-container");
			dataInputContainer.dialog({
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
			dataBox.on('dblclick', function(ev) {
				$("#data-input-container").dialog('open');
			});

			$("#data-input-container").find("select").change(function() {
				window.dataBoxes.handleDataChange(dataBox);
			});
		},
	}
})();

