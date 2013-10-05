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
			$(spec.data).draggable({
				appendTo: spec.canvas,
                helper: "clone",
			});
			$(spec.canvas).droppable({
				activeClass: "active-canvas",
				accept: spec.task + ","+ spec.data,
				drop: function(ev, ui) {
                    if ($(ui.draggable).hasClass(spec.task.replace(".", ""))) {
				        window.taskBoxes.initTaskBox(ev, ui, spec.canvas);
                        return;
                    } 
                    if ($(ui.draggable).hasClass(spec.data.replace(".", ""))) {
                        window.dataBoxes.initDataBox(ev, ui, spec.canvas);
                    }
				}
			});
		},
	}
})();
