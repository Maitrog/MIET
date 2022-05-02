-- �������� �������� ��������� --
CREATE PROCEDURE getNORR(
@id uniqueidentifier,
@norr INT OUTPUT
)
AS
-- ���������� ���������� ����������� ����� �� ��������������
-- ������� �������� @id ����� ��� ������ ������������
-- �������� �������� @norr ����� ��������� ���������� ����������� �����
-- ��������� ���������� ��� �100, ���� �������� �������������� 
-- � ������� Users ����������� 

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

-- ������������ ��������� getNORR --
Declare @Qty int,
        @RetCode int; 
-- RetCode = 0 --
EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

-- RetCode = -100 --
EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a754', @Qty OUTPUT;
SELECT @RetCode, @Qty;


-- �������� ��������� �� ���������� ����� ����������� ����� --
CREATE PROCEDURE addNORR(
@Id  uniqueidentifier
) 
AS
-- ���������� 1 � ����� ����������� ����� � ������� Users
-- ������� �������� @Id ������ �������������� ������������
-- ��������� ���������� ��� �100, ���� ������������ � 
-- ��������������� @Id ����������� 
SET NOCOUNT ON;
UPDATE Users SET NORR = NORR + 1
  WHERE Guid = @Id;
IF @@RowCount=0
   RETURN -100;
RETURN;


-- �������� ��������� �� ���������� ������ � ������� Requests --
CREATE PROCEDURE addRequest(
@Id  uniqueidentifier,
@Artist nvarchar(50),
@Song nvarchar(50)
) 
AS
-- ��������� ������  � ������� Requests � ������������ ����� ���������� ����������� �����
-- ������� �������� @Id ������ �������������� ������������
-- ������� �������� @Artist ������ ��� �����������
-- ������� �������� @Song ������ �������� �����
-- ��������� ���������� ��� �100, ���� ������������ � 
-- ��������������� @Id ����������� 
SET NOCOUNT ON;
INSERT INTO Requests(UserGuid, Artists, Song)
		VALUES(@Id, @Artist, @Song)
RETURN;

-- ������������ ��������� addRequest --
Declare @Qty int,
        @RetCode int; 

EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

EXEC @RetCode = addRequest '9a6327da-1980-4527-abfc-179de065a755', 'ALPHA', 'Layto';
SELECT @RetCode;

EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

-- �������� ��������� �� ���������� ����� ����������� ����� --
CREATE PROCEDURE subNORR( 
@Id  uniqueidentifier
) 
AS
-- �������� 1 �� ����� ����������� ����� � ������� Users
-- ������� �������� @Id ������ �������������� ������������
-- ��������� ���������� ��� �100, ���� ������������ � 
-- ��������������� @Id ����������� 
SET NOCOUNT ON;
UPDATE Users SET NORR = NORR - 1
  WHERE Guid = @Id;
IF @@RowCount=0
   RETURN -100;
RETURN;

-- �������� ��������� �� �������� ������ �� ������� Requests --
CREATE PROCEDURE removeRequest(
@Id  uniqueidentifier,
@UserId  uniqueidentifier
) 
AS
-- ������� ������ �� ������� Requests � ������������ ����� ���������� ����������� �����
-- ������� �������� @Id ������ �������������� �������
-- ������� �������� @UserId ������ �������������� ������������
-- ��������� ���������� ��� �100, ���� ������������ � 
-- ��������������� @UserId ����������� 
-- ��������� ���������� ��� �101, ���� ������ � 
-- ��������������� @Id ����������� 
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

-- ������������ ��������� removeRequest --
Declare @Qty int,
        @RetCode int; 

EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

EXEC @RetCode = removeRequest '851B8266-798D-471A-9731-A73AED9EE4DE','9a6327da-1980-4527-abfc-179de065a755';
SELECT @RetCode;

EXEC @RetCode = getNORR '9a6327da-1980-4527-abfc-179de065a755', @Qty OUTPUT;
SELECT @RetCode, @Qty;

-- �������� �������� afterInsert --
CREATE TRIGGER ai_Requests_trig ON Requests
AFTER Insert
AS
SET NOCOUNT ON
Declare @RetCode int,
@Inserted uniqueidentifier;
SELECT TOP 1 @Inserted = [UserGuid] FROM inserted;
EXEC @RetCode = addNORR @Inserted;

-- �������� �������� afterDelete --
CREATE TRIGGER ad_Requests_trig ON Requests
AFTER Delete
AS
SET NOCOUNT ON
Declare @RetCode int,
@Inserted uniqueidentifier;
SELECT TOP 1 @Inserted = [UserGuid] FROM deleted;
EXEC @RetCode = subNORR @Inserted;