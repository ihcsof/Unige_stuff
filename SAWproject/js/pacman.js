$(document).ready(() => {
    let area = $('#area'),
    pacman = $('#pacman'),
    w = area.width() - pacman.width(), // CONFINI MASSIMI
    d = {}, // TASTO PREMUTO IN UN ISTANTE
    x = 3; // MOVIMENTO IN PIXEL

    // REALIZZA IL MOVIMENTO
    function newv(v,a,b) {
        // Calcola n sottraendo o sommando alla old position (v)
        // v = valori in pixel della posizione
        // Per left: a = 37 = sx, b = 39 = dx
        // Per top: a = 38 = top, b = 40 = down
        let n = parseInt(v, 10) - (d[a] ? x : 0) + (d[b] ? x : 0);
        return n < 0 ? 0 : n > w ? w : n;
    }

    // Se premo un tasto metto true alla posizione "#tasto" di d
    $(window).keydown(function(e) {
        d[e.which] = true;
        if(e.which == 37)
            $("#pacman").css("transform", "rotate(180deg)");
        if(e.which == 39)
            $("#pacman").css("transform", "rotate(0deg)");
        if(e.which == 38)
            $("#pacman").css("transform", "rotate(-90deg)");
        if(e.which == 40)
            $("#pacman").css("transform", "rotate(90deg)");
    });
    $(window).keyup(function(e) { d[e.which] = false;});

    // ogni 20msec aggiorno le css_prop del personaggio (chiamndo newv)
    setInterval(function() {
        //let rotatePac = rotatePacman();
        pacman.css({
            left: function(i,v) { return newv(v, 37, 39); },
            top: function(i,v) { return newv(v, 38, 40); }
        });
    }, 20);
});
