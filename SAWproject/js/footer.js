$(document).ready(function() {
    let shift = $("#footer").height();
    $('<style>body:after{height:' + shift + 'px}</style>').appendTo('body');
});
