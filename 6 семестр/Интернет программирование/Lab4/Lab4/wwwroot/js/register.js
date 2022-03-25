document.getElementById("register").addEventListener("click", async e => {
    e.preventDefault();

    const response = await fetch("/register", {
        method: "POST",
        headers: { "Accept": "application/json", "Content-Type": "application/json" },
        body: JSON.stringify({
            login: document.getElementById("login").value,
            password: document.getElementById("password").value
        })
    });

    if (response.ok === true) {
        window.location.assign("/");
    }
    else {
        alert("Такой логин уже существует");
    }
});