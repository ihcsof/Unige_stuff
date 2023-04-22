let file;
// useless function just for the dummy "scripts/show_profile.php" for tests
function takeLocalFile(input) {
    file = input.files[0];
}

$(document).ready(() => {

    $("#fileToSend").on("change", (e) => {
        file = e.target.files[0]; //takeLocalFile
    });

    $("#sendImg").on("submit", (e) => {
        e.preventDefault();
        let form_data = new FormData($("#sendImg")[0]);
        if($("#fileToSend").val() == "") return;
        if($("#errorBar").length)
            $("#errorBar").remove();
        $.ajax({
            url : "scripts/add_photo.php",
            type : 'POST',
            data : form_data,
            processData: false,
            contentType: false,
            dataType : "json",
            success : (response) => {
                if(response.msg == "OK") {
                    let reader = new FileReader();

                    reader.addEventListener("load", () => {
                        $("#pic").attr("src", reader.result);
                    }, false);

                    if (file)
                        reader.readAsDataURL(file);
                    else {
                        $.get("error_bar.php?error=file_err", (data) => {
                            $("nav").after(data);
                        });
                    }
                }
                else {
                    $.get("error_bar.php?error=" + response.msg, (data) => {
                        $("nav").after(data);
                    });
                }
            },
            error : (response) => {
                    $.get("error_bar.php?error=call_err", (data) => {
                        $("nav").after(data);
                    });
            }
        });
    });
    $("#delImg").on("click", (e) => {
        e.preventDefault();
        $.post(
            "scripts/delete_img.php",
            {del : "GO"},
            (data) => {
                if (data != "OK") {
        			if($("#errorBar").length)
			            $("#errorBar").remove();
                    $.get("error_bar.php?error=" + data, (pingu) => {
                        $("nav").after(pingu);
                    });
                    return;
                }
                $("#pic").attr("src", "images/default.jpg");
            }
        );
    });

});
