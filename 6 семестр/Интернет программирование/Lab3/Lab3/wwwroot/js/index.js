var socket; //Переменная, хранящая сокет подключения
var client = { //Переменная, хранящая свойства клиента
    connect: {
        id: "",
        name: ""
    },
    message: "",
    disconnect: false
};

//Устанавливаем коннект с сервером и определяем реакцию на события
function SetConnect() {

    //Подключаемся к серверу
    socket = new WebSocket("ws://localhost:3000");

    //Метод onopen открывает соединение с сервером
    socket.onopen = function (e) {
        if (socket.OPEN == 1) {
            toLog("[open] Соединение установлено");
            //Блокируем кнопку установки соединения и закрываем блок с интерфейсом коннекта к серверу
            $("#ConnectOpen").attr("disabled", true);
            $("#ConnectBlock").css("display", "none");
            //Разблокируем кнопку отправки сообщения и открываем блок с интерфейсом отправки сообщения
            $("#BSubmit").attr("disabled", false);
            $("#MessageBlock").css("display", "");
            //Отправляем имя для отображения в списке чата
            client.connect.name = $("#name").val();
            //socket.send(JSON.stringify(client));

        } else {
            toLog("Соединение не установлено");
        }

    };

    /*
     * Метод onmessage определяет обработчик входящих сообщений, который
     * срабатывает каждый раз когда сервер присылает сообщение
    */
    socket.onmessage = function (event) {
        toLog(`[message] Данные получены с сервера: ${event.data}`);
        var dataJSON = JSON.parse(event.data);
        if (dataJSON) {

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
        if (event.wasClean) {
            toLog(`[close] Соединение закрыто чисто, код=${event.code} причина=${event.reason}`);
        } else {
            toLog('[close] Соединение прервано по причине ' + event.code, true);
        }
        //Блокируем кнопку отправки сообщения и открываем блок с интерфейсом отправки сообщения
        $("#BSubmit").attr("disabled", true);
        $("#MessageBlock").css("display", "none");
        //Разблокируем кнопку установки соединения и открываем блок с интерфейсом коннекта к серверу
        $("#ConnectOpen").attr("disabled", false);
        $("#ConnectBlock").css("display", "");
    };

    socket.onerror = function (error) {
        alert(`[error] ${error.message}`);
        toLog(`[error] ${error.message}`);
    };
}

//Отправляем сообщение на сервер
function SendMsg(f) {
    client.message = f.message.value;
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

    var logMsgs = document.getElementById('log').childNodes;
    var logMsgsLegth = logMsgs.length;
    for (var i = 0; i < logMsgsLegth; i++) {
        document.getElementById('log').removeChild(logMsgs[0]);
    }

    $("#BSubmit").attr("disabled", true);
    $("#MessageBlock").css("display", true);
    client.message = "";
    socket.send(JSON.stringify({ "id": client.connect.id, "first_name": client.connect.name, "disconnect": true }));
    socket.close();
}
//Определяем код, срабатывающий после загрузки всех элементов страницы и построения DOM
window.onload = function () {

    //Привязываем вызов функции SetConnect к событию клика по кнопке ConnectOpen
    ConnectOpen.onclick = SetConnect;
    ConnectClose.onclick = CloseConnect;
    document.forms.publish.onsubmit = function () { return SendMsg(this); };

};