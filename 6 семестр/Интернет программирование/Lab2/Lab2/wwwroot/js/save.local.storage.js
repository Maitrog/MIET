window.onload = () => {
    document.getElementById('userText').value = localStorage.getItem('text');
}

window.onunload = () => {
    localStorage.TextBox = document.getElementById('userText').value;
    //alert("Данные сохранены");
    return "Данные сохранены";
}