;(function() {
	
	window.experimentCanvas = {
                
            // this is the paint style for the connecting lines..
            getConnectorPaintStyle : function() {
                return {
                    lineWidth:4,
                    strokeStyle:"#deea18",
                    joinstyle:"round",
                    outlineColor:"#eaedef",
                    outlineWidth:2
                }
            },
                
	    // .. and this is the hover style. 
            getConnectorHoverStyle : function() {
                return {
                    lineWidth:4,
                    strokeStyle:"#5C96BC",
                    outlineWidth:2,
                    outlineColor:"white"
                }
            },

            getEndpointHoverStyle : function() {return{fillStyle:"#5C96BC"}},

            // the definition of source endpoints (the small blue ones)
            getSourceEndpoint : function() {
                return {
                    endpoint:"Dot",
                    paintStyle:{ 
                        strokeStyle:"#1e8151",
                        fillStyle:"transparent",
                        radius:7,
                        lineWidth:2 
                    },				
                    isSource:true,
                    connector:[ "Flowchart", { stub:[40, 60], gap:10, cornerRadius:5, alwaysRespectStubs:true } ],								                
                    connectorStyle: this.getConnectorPaintStyle(),
                    hoverPaintStyle: this.getEndpointHoverStyle(),
                    connectorHoverStyle:this.getConnectorHoverStyle(),
                    dragOptions:{},
                    overlays:[
                        [ "Label", { location:[0.5, 1.5], label:"Drag", cssClass:"endpointSourceLabel" } ]
                    ]
                }
            },

            // a source endpoint that sits at BottomCenter
            // bottomSource : jsPlumb.extend( { anchor:"BottomCenter" }, sourceEndpoint),
                        
            // the definition of target endpoints (will appear when the user drags a connection) 
            getTargetEndpoint : function() {
                return {
                    endpoint:"Dot",					
                    paintStyle:{ fillStyle:"#1e8151",radius:11 },
                    hoverPaintStyle:this.getEndpointHoverStyle(),
                    maxConnections:-1,
                    dropOptions:{ hoverClass:"hover", activeClass:"active-target" },
                    isTarget:true,			
                    overlays:[
                        [ "Label", { location:[0.5, -0.5], label:"Drop", cssClass:"endpointTargetLabel" } ]
                    ]
                }
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
                        jsPlumb.addEndpoint(el, window.experimentCanvas.getSourceEndpoint(), {anchor: "LeftMiddle"});
                        jsPlumb.addEndpoint(el, window.experimentCanvas.getTargetEndpoint(), {anchor: "RightMiddle"});
                    }
                });
            },

            init : function(spec) {
				
                jsPlumb.importDefaults({
                    Container: spec.id,
                    // default drag options
                    DragOptions : { cursor: 'pointer', zIndex:2000 },
                    // default to blue at one end and green at the other
                    EndpointStyles : [{ fillStyle:'#225588' }, { fillStyle:'#558822' }],
                    // blue endpoints 7 px; green endpoints 11.
                    Endpoints : [ [ "Dot", {radius:7} ], [ "Dot", { radius:11 } ]],
                    // the overlays to decorate each connection with.  note that the label overlay uses a function to generate the label text; in this
                    // case it returns the 'labelText' member that we set on each connection in the 'init' method below.
                    ConnectionOverlays : [
                        [ "Arrow", { location:1 } ],
                    ]
                });		

	        init = function(connection) {
                    connection.getOverlay("label").setLabel(connection.sourceId.substring(6) + "-" + connection.targetId.substring(6));
                    connection.bind("editCompleted", function(o) {
                    if (typeof console != "undefined")
                        console.log("connection edited. path is now ", o.path);
                    });
                };			

                // listen for new connections; initialise them the same way we initialise the connections at startup.
                jsPlumb.bind("connection", function(connInfo, originalEvent) { 
                    init(connInfo.connection);
                });			
						
	        // make draggable						
		jsPlumb.draggable(document.querySelectorAll(".task-box"), { grid: [20, 20], containment: "parent"});		
            
		// listen for clicks on connections, and offer to delete connections on click.
		//
		jsPlumb.bind("click", function(conn, originalEvent) {
		    if (confirm("Delete connection from " + conn.sourceId + " to " + conn.targetId + "?"))
		    jsPlumb.detach(conn); 
		});	
			
		jsPlumb.bind("connectionDrag", function(connection) {
		    console.log("connection " + connection.id + " is being dragged. suspendedElement is ", connection.suspendedElement, " of type ", connection.suspendedElementType);
		});		
			
		jsPlumb.bind("connectionDragStop", function(connection) {
		    console.log("connection " + connection.id + " was dragged");
		});
		},

	};
})();
