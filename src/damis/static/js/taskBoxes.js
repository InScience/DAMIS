;(function() {
	window.taskBoxes = {
            countBoxes : 0,

            // Initialize a task box ready to accept click events
            initTask: function(ev, ui, taskContainer) {
                // drop the task where it was dragged
                var taskBox = $("<div>New task</div>");
                taskBox.appendTo(taskContainer);
                taskBox.css("left", ui.position.left + "px");
                taskBox.css("top", ui.position.top + "px");

                //assign id and class
                count = window.taskBoxes.countBoxes;
                window.taskBoxes.countBoxes++;
                taskBox.attr("id",  "task-box-" + count);
                taskBox.addClass("task-box");

                //create modal window with form fields
                var taskForm = $("<div class=\"task-form\">Task form</div>");
                taskForm.attr("id", taskBox.attr("id") + "-form");
                taskForm.dialog({
                    autoOpen: false,
                    appendTo: "#task-forms",
                    modal: true,
                    buttons: [ 
                       {text: "Save", click: function() { 
                           /* TODO: create endpoints for in/out parameters */ 
                           $( this ).dialog( "close" ); }
                       },
                       {text: "Cancel", click: function() { $( this ).dialog( "close" ); }}
                    ]
                });
                taskBox.on('dblclick', function (ev) {
                    var taskFormId = $(ev.currentTarget).attr("id") + "-form";
                    $("#" + taskFormId).dialog('open'); 
                });

                //make it draggable
                jsPlumb.draggable(taskBox, { grid: [20, 20], containment: "parent"});		
                 
                // TODO: remove when endpoints are rendered according to in/out
                // parameters
                jsPlumb.addEndpoint(taskBox, window.experimentCanvas.getSourceEndpoint(), {anchor: "LeftMiddle"});
                jsPlumb.addEndpoint(taskBox, window.experimentCanvas.getTargetEndpoint(), {anchor: "RightMiddle"});
            },

            initToolBox : function(spec) {
                $(spec.draggable).draggable({
                    appendTo: spec.droppable,
                    helper: "clone"
                }); 
                $(spec.droppable).droppable({
                    activeClass: "active-canvas",
                    accept: spec.draggable,
                    drop: function (ev, ui) {
                        window.taskBoxes.initTask(ev, ui, spec.droppable);
                    }
                });
            },
        }

})();
