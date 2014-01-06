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
			var componentOption = $(formWindow).find(".algorithm-selection option[selected=selected]");
			return this.details[componentOption.val()];
		}
	}
})();

