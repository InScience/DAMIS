;(function() {
	window.taskBoxes = {

            handleDbClick : function (task) {
                console.log('Double click on ', task);
            },

            setupTaskBox : function(el) {
                // TODO: setup endpoints according to selected algorithm
                // can be accessed as: window.experimentCanvas.setupTaskBox
            },

            initToolBox : function(spec) {
                $(spec.draggable).draggable({
                    appendTo: spec.droppable,
                    helper: "clone"
                }); 
                $(spec.droppable).droppable({
                    activeClass: "active-canvas",
                    accept: spec.draggable,
                    drop: function( event, ui ) {
                        var el = $("<div>New task</div>");
                        el.addClass("task-box");
                        el.appendTo(spec.droppable);
                        el.css("left", ui.position.left + "px");
                        el.css("top", ui.position.top + "px");
                        jsPlumb.draggable(el, { grid: [20, 20], containment: "parent"});		
                        //var endpoint = jsPlumb.addEndpoint(el, window.experimentCanvas.getSourceEndpoint(), {anchor: "LeftMiddle"});
                        //jsPlumb.addEndpoint(el, window.experimentCanvas.getTargetEndpoint(), {anchor: "RightMiddle"});
                        
                        //endpoint.bind("dblclick", window.experimentCanvas.handleTaskBoxDoubleClick);
                        
                    }
                });
            },
        }

})();
