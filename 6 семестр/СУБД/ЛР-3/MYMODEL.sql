
CREATE TABLE Запросы
(
	Guid uniqueidentifier  NOT NULL ,
	Artist nvarchar(50)  NOT NULL ,
	Song nvarchar(50)  NOT NULL ,
	CreatedAt datetime  NOT NULL 
	CONSTRAINT DF_Requests_CreatedAt_1633757738
		 DEFAULT  GETDATE(),
	PlayedAt datetime  NULL 
	CONSTRAINT Check_Requests_PlayedAt_905258531
		CHECK  (PlayedAt >= CreatedAt ),
	IsSkiped integer  NOT NULL 
	CONSTRAINT DF_Requests_IsSkiped_1923713696
		 DEFAULT  0
	CONSTRAINT Check_Requests_IsSkiped_1457847595
		CHECK  (IsSkiped >= 0 AND IsSkiped <= 1 ),
	UserGuid uniqueidentifier  NULL 
)
go


ALTER TABLE Запросы
	ADD CONSTRAINT XPKЗапросы PRIMARY KEY  CLUSTERED (Guid ASC)
go


CREATE TABLE Пользователь
(
	Guid uniqueidentifier  NOT NULL ,
	Login nvarchar(50)  NOT NULL ,
	NormalizeLogin nvarchar(50)  NOT NULL ,
	Email nvarchar(50)  NOT NULL 
	CONSTRAINT Check_Users_Email_1060046349
		CHECK  (Email LIKE '%_@__%.__%' ),
	NormalizeEmail nvarchar(50)  NOT NULL 
	CONSTRAINT Check_Users_NormalizeEmail_1630694424
		CHECK  (NormalizeEmail LIKE '%_@__%.__%' ),
	PasswordHash nvarchar(50)  NOT NULL ,
	IsBanned integer  NOT NULL 
	CONSTRAINT DF_Users_IsBanned_101912125
		 DEFAULT  0
	CONSTRAINT Check_Users_IsBanned_750663065
		CHECK  (IsBanned >= 0 ANR IsBanned <= 1 )
)
go


ALTER TABLE Пользователь
	ADD CONSTRAINT XPKПользователь PRIMARY KEY  CLUSTERED (Guid ASC)
go



ALTER TABLE Запросы
	ADD CONSTRAINT  R_1 FOREIGN KEY (UserGuid) REFERENCES Пользователь(Guid)
		ON DELETE CASCADE
		ON UPDATE CASCADE
go

