;
(function() {
	window.componentSettings = {
		getComponentDetails: function(params) {
			var formWindow;
			if (params['boxId']) {
				formWindow = $("#" + window.taskBoxes.getFormWindowId(params['boxId']));
			} else if (params['formWindowId']) {
				formWindow = $("#" + params['formWindowId']);
			} else if (params['formWindow']) {
				formWindow = params['formWindow'];
			}
			var componentInput = $(formWindow).find(".algorithm-selection select");
			return this.details[componentInput.val()];
		}
	}
})();

