from django.core.urlresolvers import reverse_lazy

COMPONENT_TITLE__TO__FORM_URL = {
    "UPLOAD FILE":       reverse_lazy('component-upload-file-form'),
    "EXISTING FILE":     reverse_lazy('component-existing-file-form'),
    "MIDAS FILE":        reverse_lazy('component-midas-file-form'),
    "SELECT FEATURES":   reverse_lazy('component-select-features-form'),
    "TECHNICAL DETAILS": reverse_lazy('component-technical-details-form'),
    "CHART":             reverse_lazy('component-chart-form'),
    "MATRIX VIEW":       reverse_lazy('component-matrix-form'),
}
