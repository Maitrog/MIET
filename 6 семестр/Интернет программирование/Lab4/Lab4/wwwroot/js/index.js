document.getElementById("submitLogin").addEventListener("click", async e => {
    e.preventDefault();

    const response = await fetch("/login", {
        method: "POST",
        headers: { "Accept": "application/json", "Content-Type": "application/json" },
        body: JSON.stringify({
            login: document.getElementById("login").value,
            password: document.getElementById("password").value
        })
    });

    if (response.ok === true) {
        const data = await response.json();
        sessionStorage.setItem("userName", data.username);
        sessionStorage.setItem("isAuthorize", true);
        window.location.assign("/photo/photo");
    }
    else
        console.log("Status: ", response.status);
});

document.getElementById("logOut").addEventListener("click", async e => {

    e.preventDefault();
    const response = await fetch("/logout", {
        method: "POST"
    });
    if (response.ok !== true) {
        console.log("Status: ", response.status);
    }
    sessionStorage.setItem("isAuthorize", false);
    window.location.assign("/");
});

if (sessionStorage.getItem("isAuthorize") === 'true') {
    document.getElementById("userName").innerText = sessionStorage.getItem("userName");
    document.getElementById("userInfo").style.display = "block";
    document.getElementById("loginForm").style.display = "none";
} else {
    document.getElementById("userName").innerText = "";
    document.getElementById("userInfo").style.display = "none";
    document.getElementById("loginForm").style.display = "block";
}