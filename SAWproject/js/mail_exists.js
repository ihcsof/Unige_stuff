$(document).ready(() => {
    $("#email").on("keyup", () => {
        $.post("scripts/mail_checker.php",
            {email: $("#email").val()},
            (data) => { $("#mail_warn").html((data) ? "mail already exists" : ""); }
        );
    })
});
