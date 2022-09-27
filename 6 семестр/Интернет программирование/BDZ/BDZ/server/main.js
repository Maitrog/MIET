const ws = require('ws');

var clients = {};
var clientsLogin = [];
var history = [];

var webSocketServer = new ws.Server({
    port: 3000
});

// Добавляем в сервер слушателя на событие подключения
webSocketServer.on('connection', function (ws) {

    var id = Math.random();
    clients[id] = ws;
    console.log("новое соединение " + id);

    //Отправляем клиенту id соединения, чтобы потом индивидуально отправлять сообщения
    clients[id].send(JSON.stringify({ 'id_first': id }));

    //Обработка входящих сообщений
    ws.on('message', function (message) {

        console.log('получено сообщение ' + message);
        let p_ms = JSON.parse(message);

        let answer = {
            from_id: "",
            from_name: "",
            message: ""
        };

        if (p_ms) {
            if (p_ms.disconnect === true) {
                for (var i = 0; i < clientsLogin.length; i++) {
                    if (clientsLogin[i] === p_ms.first_name) {
                        clientsLogin.splice(i, 1);
                        delete clients[findClintKey(i)];
                        i--;
                    }
                }
            } else if (p_ms.history === true) {
                if (p_ms.min !== '0') {
                    for (var item in history) {
                        if (history[item].time > new Date().getTime() - p_ms.min * 60000) {
                            clients[p_ms.id].send(JSON.stringify(history[item]));
                        }
                    }
                } else {
                    for (var item in history) {
                        clients[p_ms.id].send(JSON.stringify(history[item]));
                    }
                }
            } else {
                if (p_ms.first_name !== undefined) {
                    if (p_ms.first_name === "") {
                        p_ms.first_name = makeId();
                    }
                    if (clientsLogin.includes(p_ms.first_name)) {
                        p_ms.first_name += "_" + makeId();
                    }

                    //Полученное имя передаем обратно конкретному клиенту
                    clientsLogin.push(p_ms.first_name);
                    answer.name_first = p_ms.first_name;
                    clients[p_ms.id].send(JSON.stringify(answer));

                    let response = {
                        type: "users",
                        users: clientsLogin
                    };
                    for (var key in clients) {
                        clients[key].send(JSON.stringify(response));
                    }
                } else {
                    answer.message = p_ms.message;
                    answer.from_id = p_ms.connect.id;
                    answer.from_name = p_ms.connect.name;

                    if (p_ms.to === "all") {
                        let messageToHistory = {
                            from_id: p_ms.connect.id,
                            from_name: p_ms.connect.name,
                            message: p_ms.message,
                            time: new Date().getTime(),
                            ip: ws._socket.remoteAddress
                        };
                        history.push(messageToHistory);

                        //Рассылка сообщений всем клиентам
                        for (var key in clients) {
                            //Отправляем сообщение каждому клиенту
                            clients[key].send(JSON.stringify(answer));
                        }
                    } else {
                        for (var i = 0; i < clientsLogin.length; i++) {
                            if (p_ms.to === clientsLogin[i]) {
                                clients[findClintKey(i)].send(JSON.stringify(answer));
                                clients[p_ms.connect.id].send(JSON.stringify(answer));
                            }
                        }
                    }
                }
            }
        }
    });

});
function makeId() {
    var text = "";
    var possible = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (var i = 0; i < 5; i++)
        text += possible.charAt(Math.floor(Math.random() * possible.length));

    return text;
}

function findClintKey(i) {
    let j = 1;
    for (var key in clients) {
        if (j - 1 === i) {
            return key;
        }
        j++;
    }
}