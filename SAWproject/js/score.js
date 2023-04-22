$(document).ready(() => {
    $("#rat").html("( " + $("#score").val() + " )");
    $("#score").on("change", (e) => {
        $("#rat").html("( " + $("#score").val() + " )");
    });

    $("#score_ready").on("click", (e) => {
        e.preventDefault();
        $.post(
            "scripts/update_score.php",
            {
                score: $("#score").val(),
                proj_id: $("#proj_id").val(),
                score_already : $("#score_already").val(),
            },
            (data) => {
                $.get("error_bar.php?error=" + data, (pingu) => {
                    $("nav").after(pingu);
                });
            }
        ).fail(() => {
            $.get("error_bar.php?error=call_err", (pingu) => {
                $("nav").after(pingu);
            });
        });
    });
});
