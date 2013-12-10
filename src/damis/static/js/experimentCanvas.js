;
(function() {

	window.experimentCanvas = {

		// this is the paint style for the connecting lines..
		getConnectorPaintStyle: function() {
			return {
				lineWidth: 4,
				strokeStyle: "#cccccc",
				joinstyle: "round",
				outlineColor: "#eaedef",
				outlineWidth: 2
			}
		},

		// .. and this is the hover style. 
		getConnectorHoverStyle: function() {
			return {
				lineWidth: 4,
				strokeStyle: "#5C96BC",
				outlineWidth: 2,
				outlineColor: "white"
			}
		},

		getEndpointHoverStyle: function() {
			return {
				fillStyle: "#5C96BC"
			}
		},

		// the definition of source endpoints (the small blue ones)
		getSourceEndpoint: function() {
			return {
				endpoint: "Dot",
				paintStyle: {
					fillStyle: "#346789", 
					radius: 7 
				},
				isSource: true,
				connector: ["StateMachine", {
					stub: [40, 60],
					gap: 10,
					cornerRadius: 5,
					alwaysRespectStubs: true
				}],
				connectorStyle: this.getConnectorPaintStyle(),
				hoverPaintStyle: this.getEndpointHoverStyle(),
				connectorHoverStyle: this.getConnectorHoverStyle(),
				dragOptions: {},
			}
		},

		// a source endpoint that sits at BottomCenter
		// bottomSource : jsPlumb.extend( { anchor:"BottomCenter" }, sourceEndpoint),
		// the definition of target endpoints (will appear when the user drags a connection) 
		getTargetEndpoint: function() {
			return {
				endpoint: "Dot",
				paintStyle: {
					strokeStyle: "#346789",
					fillStyle: "transparent",
					radius: 5,
					lineWidth: 2
				},
				hoverPaintStyle: this.getEndpointHoverStyle(),
				maxConnections: - 1,
				dropOptions: {
					hoverClass: "hover",
					activeClass: "active-target"
				},
				isTarget: true,
			}
		},

		// initialize 
		init: function(spec) {

			jsPlumb.importDefaults({
				Container: spec.id,
				// default drag options
				DragOptions: {
					cursor: 'pointer',
					zIndex: 2000
				},
				// default to blue at one end and green at the other
				EndpointStyles: [{
					fillStyle: '#225588'
				},
				{
					fillStyle: '#558822'
				}],
				// blue endpoints 7 px; green endpoints 11.
				Endpoints: [["Dot", {
					radius: 7
				}], ["Dot", {
					radius: 11
				}]],
				// the overlays to decorate each connection with.  note that the label overlay uses a function to generate the label text; in this
				// case it returns the 'labelText' member that we set on each connection in the 'init' method below.
				ConnectionOverlays: [["Arrow", {
					location: 1
				}]]
			});

            jsPlumb.bind("connectionDetached", function(info, originalEvent) {
                // Clear the input parameter value and display it as input field
                var params = info.targetEndpoint.getParameters();
                var param = window.experimentForm.getParameter(params.iParamNo, params.iTaskBoxId);
                var srcRefField = window.experimentForm.getParameterSourceRef(param);
                srcRefField.val("");
                
                // show literal value field
                var valField = window.experimentForm.getParameterValue(param);
                valField.attr("type", "text");
            });

            // maps task box to its output endpoint connection
            // stores output parameter address into input parameter
			jsPlumb.bind("connection", function(info, originalEvent) {
				var conn = info.connection;
				var params = conn.getParameters();

                if ($(conn.source).hasClass("task-box")) {
				    //display disabled field to the user
                    var param = window.experimentForm.getParameter(params.iParamNo, params.iTaskBoxId);
                    var srcRefField= window.experimentForm.getParameterSourceRef(param);
				    srcRefField.val(params.oParamNo + "," + params.oTaskBoxId);

                    //clear literal value field and hide it
                    var valField = window.experimentForm.getParameterValue(param);
                    valField.val("");
                    valField.attr("type", "hidden");
                } else if ($(conn.source).hasClass("data-box")) {
				    var input = $("#" + params.inParam).closest("div").find("input[id$='value']");
                    input.val(params.outParam);
				    input.attr("type", "hidden");
                }
			});

			// listen for clicks on connections, and offer to delete connections on click.
			jsPlumb.bind("click", function(conn, originalEvent) {
				jsPlumb.detach(conn);
			});
		},
	};
})();

