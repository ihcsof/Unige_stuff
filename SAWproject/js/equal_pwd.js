function equal_pwd() {
    let pwd1 = document.getElementById("pass");
	let pwd2 = document.getElementById("confirm");
    pwd2.style = "background-color:" + ((pwd1.value != pwd2.value) ? "red;" : "white;");
}

$(document).ready(() => {
    $(".pwd_in").on("keyup", equal_pwd);
});
