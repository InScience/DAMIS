;
(function() {

	window.experimentCanvas = {

		// this is the paint style for the connecting lines..
		getConnectorPaintStyle: function() {
			return {
				lineWidth: 4,
				strokeStyle: "#deea18",
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
					strokeStyle: "#1e8151",
					fillStyle: "transparent",
					radius: 7,
					lineWidth: 2
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
					fillStyle: "#1e8151",
					radius: 11
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

			// listen for new connections; initialise them the same way we initialise the connections at startup.
			jsPlumb.bind("connection", function(connection, originalEvent) {
				var conn = connection.connection;
				var params = conn.getParameters();

				//display disabled field to the user
				var input = $("#" + params.inParam).closest("div").find("input[id$='value']");
				input.val(params.outParam);
				input.attr("disabled", "disabled");

				// save input parameter form prefix and id for server side processing
				input = $("#" + params.inParam).closest("div").find("input[id$='source']");
				input.val(params.outParam);
			});

			// make draggable						
			jsPlumb.draggable(document.querySelectorAll(".task-box"), {
				grid: [20, 20],
				containment: "parent"
			});

			// listen for clicks on connections, and offer to delete connections on click.
			jsPlumb.bind("click", function(conn, originalEvent) {
				jsPlumb.detach(conn);
			});

			// delete connections on right click
			jsPlumb.bind("contextmenu", function(conn, originalEvent) {
				if (conn.connector) {
					jsPlumb.detach(conn);
				}
			});
			$(document).on("contextmenu", function() {
				return false
			});
		},

	};
})();

