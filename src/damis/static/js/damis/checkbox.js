$(function(){
    $('.select-all').change(function() {
        var checked = $(this).is(':checked');
        var index = $(this).closest('th,td').index();
        var tbody = $(this).closest('table').find('tbody').first();
        var sel = 'tr > td:nth-child(' + index+1 +') input[type=checkbox]';
        tbody.find(sel).attr('checked', checked);
        tbody.find(sel).prop('checked', checked);
    });
});
