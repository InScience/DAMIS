;
(function() {
	window.toolBox = {
		// Make boxes in the toolbox draggable
		init: function(spec) {
			// drag task
			$(spec.task).draggable({
				appendTo: spec.canvas,
				helper: "clone"
			});
			$(spec.canvas).droppable({
				activeClass: "active-canvas",
				accept: spec.task,
				drop: function(ev, ui) {
					if ($(ui.draggable).hasClass(spec.task.replace(".", ""))) {
						window.taskBoxes.createTaskBox(ev, ui, spec.canvas);
						return;
					}
				}
			});
		},
	}
})();

