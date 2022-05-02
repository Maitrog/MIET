-- Создание хранимой процедуры --
CREATE PROCEDURE getNORR(
@id uniqueidentifier,
@norr INT OUTPUT
)
AS
-- Определяет количество подчиненных строк по идентификатору
-- Входной параметр @id нужен для поиска пользователя
-- Выходной параметр @norr будет содержать количество подчиненных строк
-- Процедура возвращает код –100, если значение идентификатора 
-- в таблице Users отсутствует 

SET NOCOUNT ON;
SELECT @norr=COUNT(Guid)
FROM Requests
WHERE UserGuid=@id;
SELECT Guid 
FROM Users
WHERE Guid=@id;
IF @@ROWCOUNT=0
	RETURN -100;
ELSE
	RETURN 0;

-- Тестирование процедуры getNORR --
Declare @Qty int,
        @RetCode int; 
-- RetCode = 0 --
EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

-- RetCode = -100 --
EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a754', @Qty OUTPUT;
SELECT @RetCode, @Qty;


-- Создание процедуры на увеличение числа подчиненных строк --
CREATE PROCEDURE addNORR(
@Id  uniqueidentifier
) 
AS
-- Прибавляет 1 к числу подчиненных строк в таблице Users
-- Входной параметр @Id задает индентификатор пользователя
-- Процедура возвращает код –100, если пользователь с 
-- идентификатором @Id отсутствует 
SET NOCOUNT ON;
UPDATE Users SET NORR = NORR + 1
  WHERE Guid = @Id;
IF @@RowCount=0
   RETURN -100;
RETURN;


-- Создание процедуры на добавление строки в таблицу Requests --
CREATE PROCEDURE addRequest(
@Id  uniqueidentifier,
@Artist nvarchar(50),
@Song nvarchar(50)
) 
AS
-- Добавляет строку  в таблицу Requests и корректирует общий количество подчиненных строк
-- Входной параметр @Id задает индентификатор пользователя
-- Входной параметр @Artist задает имя исполнителя
-- Входной параметр @Song задает название песни
-- Процедура возвращает код –100, если пользователь с 
-- идентификатором @Id отсутствует 
SET NOCOUNT ON;
INSERT INTO Requests(UserGuid, Artists, Song)
		VALUES(@Id, @Artist, @Song)
RETURN;

-- Тестирование процедуры addRequest --
Declare @Qty int,
        @RetCode int; 

EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

EXEC @RetCode = addRequest '9a6327da-1980-4527-abfc-179de065a755', 'ALPHA', 'Layto';
SELECT @RetCode;

EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

-- Создание процедуры на уменьшение числа подчиненных строк --
CREATE PROCEDURE subNORR( 
@Id  uniqueidentifier
) 
AS
-- Вычитает 1 из числа подчиненных строк в таблице Users
-- Входной параметр @Id задает индентификатор пользователя
-- Процедура возвращает код –100, если пользователь с 
-- идентификатором @Id отсутствует 
SET NOCOUNT ON;
UPDATE Users SET NORR = NORR - 1
  WHERE Guid = @Id;
IF @@RowCount=0
   RETURN -100;
RETURN;

-- Создание процедуры на удаление строки из таблицы Requests --
CREATE PROCEDURE removeRequest(
@Id  uniqueidentifier,
@UserId  uniqueidentifier
) 
AS
-- Удаляет строку из таблицы Requests и корректирует общий количество подчиненных строк
-- Входной параметр @Id задает индентификатор запроса
-- Входной параметр @UserId задает индентификатор пользователя
-- Процедура возвращает код –100, если пользователь с 
-- идентификатором @UserId отсутствует 
-- Процедура возвращает код –101, если запрос с 
-- идентификатором @Id отсутствует 
SET NOCOUNT ON;
Declare @RetCode int; 

DELETE FROM Requests
   WHERE (Guid = @Id)
IF @@RowCount=0
   RETURN -101;
EXEC @RetCode = subNORR @UserId;
IF @RetCode<>0
   RETURN @RetCode;
RETURN;

-- Тестирование процедуры removeRequest --
Declare @Qty int,
        @RetCode int; 

EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

EXEC @RetCode = removeRequest '851B8266-798D-471A-9731-A73AED9EE4DE','9a6327da-1980-4527-abfc-179de065a755';
SELECT @RetCode;

EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

-- Создание триггера afterInsert --
CREATE TRIGGER ai_Requests_trig ON Requests
AFTER Insert
AS
SET NOCOUNT ON
Declare @RetCode int,
@Inserted uniqueidentifier;
SELECT TOP 1 @Inserted = [UserGuid] FROM inserted;
EXEC @RetCode = addNORR @Inserted;

-- Создание триггера afterDelete --
CREATE TRIGGER ad_Requests_trig ON Requests
AFTER Delete
AS
SET NOCOUNT ON
Declare @RetCode int,
@Inserted uniqueidentifier;
SELECT TOP 1 @Inserted = [UserGuid] FROM deleted;
EXEC @RetCode = subNORR @Inserted;