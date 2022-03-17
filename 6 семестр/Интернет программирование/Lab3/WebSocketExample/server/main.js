/* Загружаем модули */
const ws = require('ws');

// Обьект для хранения подключённых клиентов
var clients = {};

// Запускаем WebSocket-сервер на порту 3000
var webSocketServer = new ws.Server({
    port: 3000
});

// Добавляем в сервер слушателя на событие подключения
webSocketServer.on('connection', function (ws) {

    var id = Math.random();
    clients[id] = ws; //Каждому клиенту присваиваем ссылку на объект сервера
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

            if (p_ms.first_name !== undefined) {
                /*
                 *Если это первое подключение и клиент прислал свое имя для чата
                 *Проверяем имена других клиентов и изменяем исходное так, чтобы не повторялось 
                 *(пока не сделано) 
                 */

                //Полученное имя передаем обратно конкретному клиенту
                answer.name_first = p_ms.first_name;
                clients[p_ms.id].send(JSON.stringify(answer));
            } else {
                answer.message = p_ms.message;
                answer.from_id = p_ms.connect.id;
                answer.from_name = p_ms.connect.name;

                //Рассылка сообщений всем клиентам
                for (var key in clients) {
                    //Отправляем сообщение каждому клиенту
                    clients[key].send(JSON.stringify(answer));
                }
            }
        }
    });

});
