var socket;
var minimized = false;
var pinned = false;
var client = {
    connect: {
        id: "",
        name: ""
    },
    message: "",
    to: ""
};

//Устанавливаем коннект с сервером и определяем реакцию на события
function SetConnect() {

    //Подключаемся к серверу
    socket = new WebSocket("ws://localhost:3000");

    //Метод onopen открывает соединение с сервером
    socket.onopen = function (e) {
        if (socket.OPEN == 1) {
            //Блокируем кнопку установки соединения и закрываем блок с интерфейсом коннекта к серверу
            $("#ConnectOpen").attr("disabled", true);
            $("#ConnectBlock").addClass('d-none');
            $("#ConnectBlock").removeClass('d-flex');
            //Разблокируем кнопку отправки сообщения и открываем блок с интерфейсом отправки сообщения
            $("#BSubmit").attr("disabled", false);
            $("#MessageBlock").addClass("d-inline");
            $("#MessageBlock").removeClass("d-none");
            //Отправляем имя для отображения в списке чата
            client.connect.name = $("#name").val();
            //socket.send(JSON.stringify(client));

        } else {
            alert("Соединение не установлено");
        }

    };

    /*
     * Метод onmessage определяет обработчик входящих сообщений, который
     * срабатывает каждый раз когда сервер присылает сообщение
    */
    socket.onmessage = function (event) {
        var dataJSON = JSON.parse(event.data);
        if (dataJSON) {
            if (dataJSON.type === "users") {
                let selectUser = document.getElementById('sendTo');
                for (var i = selectUser.childElementCount; i > 1; i--) {
                    selectUser.removeChild(selectUser.childNodes[i]);
                }
                dataJSON.users.forEach(x => {
                    if (x !== client.connect.name) {
                        var userNameElement = document.createElement('option');
                        userNameElement.setAttribute("value", x);
                        userNameElement.appendChild(document.createTextNode(x));
                        selectUser.appendChild(userNameElement);
                    }
                });
            }

            if (dataJSON.id_first !== undefined) {
                //Если получено сообщение с идентификатором сервера
                client.connect.id = dataJSON.id_first;
                socket.send(JSON.stringify({ "id": client.connect.id, "first_name": client.connect.name }));
            }
            if (dataJSON.name_first !== undefined) {
                //Если получено сообщение с подтвержденным именем
                client.connect.name = dataJSON.name_first;
                $("#MyName").html(client.connect.name);
                showMessage(client.connect.name + ": Вошел в чат");
            }
            if (dataJSON.message !== undefined && dataJSON.message !== "") {
                showMessage(dataJSON.from_name + ": " + dataJSON.message);
            }
        }
    };

    /*
     * Метод onclose срабатывает при потере коннекта с сервером
    */
    socket.onclose = function (event) {
        //Блокируем кнопку отправки сообщения и открываем блок с интерфейсом отправки сообщения
        $("#BSubmit").attr("disabled", true);
        $("#MessageBlock").css("display", "none");
        //Разблокируем кнопку установки соединения и открываем блок с интерфейсом коннекта к серверу
        $("#ConnectOpen").attr("disabled", false);
        $("#ConnectBlock").css("display", "");
    };

    socket.onerror = function (error) {
        alert(`[error] ${error.message}`);
    };
}

//Отправляем сообщение на сервер
function SendMsg(f) {
    client.message = f.message.value;
    client.to = f.sendTo.value;
    socket.send(JSON.stringify(client));
    return false;
}

// показать сообщение в div#message
function showMessage(message) {
    var messageElem = document.createElement('div');
    messageElem.appendChild(document.createTextNode(message));
    document.getElementById('messages').appendChild(messageElem);
}

// запись сообщения в лог#log
function toLog(msg, show) {

    var messageElem = document.createElement('div');
    let d = new Date();
    //Форматируем дату и время
    dt = ('0' + d.getDate()).slice(-2) + '.' + ('0' + (d.getMonth() + 1)).slice(-2) + '.' + d.getFullYear();
    dt += " " + d.getHours() + ":" + d.getMinutes() + ":" + d.getSeconds() + ":" + d.getMilliseconds();

    if (show) { alert(msg); }

    messageElem.appendChild(document.createTextNode(dt));
    messageElem.appendChild(document.createElement('br'));
    messageElem.appendChild(document.createTextNode(msg));
    document.getElementById('log').appendChild(messageElem);
}

function CloseConnect() {
    var userMsgs = document.getElementById('messages').childNodes;
    var userMsgsLegth = userMsgs.length;
    for (var i = 0; i < userMsgsLegth; i++) {
        document.getElementById('messages').removeChild(userMsgs[0]);
    }

    $("#ConnectOpen").attr("disabled", false);
    $("#ConnectBlock").removeClass('d-none');
    $("#ConnectBlock").addClass('d-flex');
    $("#BSubmit").attr("disabled", true);
    $("#MessageBlock").addClass("d-none");
    $("#MessageBlock").removeClass("d-inline");
    client.message = "";
    socket.send(JSON.stringify({ "id": client.connect.id, "first_name": client.connect.name, "disconnect": true }));
    socket.close();
}

document.getElementById("GetHistory").addEventListener("click", e => {
    e.preventDefault();
    let min = document.getElementById("min").value;
    socket.send(JSON.stringify({ "id": client.connect.id, "first_name": client.connect.name, "min": min, "history": true }));
});

//Определяем код, срабатывающий после загрузки всех элементов страницы и построения DOM
window.onload = function () {

    //Привязываем вызов функции SetConnect к событию клика по кнопке ConnectOpen
    ConnectOpen.onclick = SetConnect;
    ConnectClose.onclick = CloseConnect;
    document.forms.publish.onsubmit = function () { return SendMsg(this); };

};

dragElement(document.getElementById("draggableChat"));

function dragElement(elmnt) {
    var pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0;
    if (document.getElementById(elmnt.id + "header")) {
        // if present, the header is where you move the DIV from:
        document.getElementById(elmnt.id + "header").onmousedown = dragMouseDown;
    } else {
        // otherwise, move the DIV from anywhere inside the DIV:
        elmnt.onmousedown = dragMouseDown;
    }

    function dragMouseDown(e) {
        e = e || window.event;
        e.preventDefault();
        // get the mouse cursor position at startup:
        pos3 = e.clientX;
        pos4 = e.clientY;
        document.onmouseup = closeDragElement;
        // call a function whenever the cursor moves:
        document.onmousemove = elementDrag;
    }

    function elementDrag(e) {
        e = e || window.event;
        e.preventDefault();
        // calculate the new cursor position:
        pos1 = pos3 - e.clientX;
        pos2 = pos4 - e.clientY;
        pos3 = e.clientX;
        pos4 = e.clientY;
        // set the element's new position:
        elmnt.style.top = (elmnt.offsetTop - pos2) + "px";
        elmnt.style.left = (elmnt.offsetLeft - pos1) + "px";
    }

    function closeDragElement() {
        // stop moving when mouse button is released:
        document.onmouseup = null;
        document.onmousemove = null;
    }
}

document.getElementById("minimize").addEventListener("click", e => {
    e.preventDefault();

    if (minimized === false) {
        $("#content").addClass('d-none');
        $("#content").removeClass('d-inline');
        $("#draggableChat").css("height", "60px");

        var top = Number($("#draggableChat").css("top").split("px")[0]) + 540;
        $("#draggableChat").css("top", top + "px");
        minimized = true;
    } else {
        $("#content").addClass('d-inline');
        $("#content").removeClass('d-none');
        $("#draggableChat").css("height", "600px");

        var top = Number($("#draggableChat").css("top").split("px")[0]) - 540;
        $("#draggableChat").css("top", top + "px");
        minimized = false;
    }
});

document.getElementById("pin").addEventListener("click", e => {
    e.preventDefault();

    if (pinned === false) {
        $("#draggableChat").addClass("position-fixed");
        pinned = true;
    } else {
        $("#draggableChat").removeClass("position-fixed");
        pinned = false;
    }
})