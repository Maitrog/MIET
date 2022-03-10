--Тюльников Михаил ПИН-32 Вариант 25--
CREATE TABLE [dbo].[Users]
(
 [Guid]           uniqueidentifier NOT NULL ,
 [Login]          nvarchar(50) NOT NULL ,
 [NormalizeLogin] nvarchar(50) NOT NULL ,
 [Email]          nvarchar(50) NOT NULL ,
 [NormalizeEmail] nvarchar(50) NOT NULL ,
 [PasswordHash]   nvarchar(50) NOT NULL ,
 [IsBanned]       int NOT NULL CONSTRAINT [DF_Users_IsBanned] DEFAULT 0 ,


 CONSTRAINT [PK_Users] PRIMARY KEY CLUSTERED ([Guid] ASC),
 CONSTRAINT [Check_Users_IsBanned] CHECK ( IsBanned >= 0 AND IsBanned <=1 ),
 CONSTRAINT [Check_Users_Email] CHECK ( Email LIKE '%_@__%.__%' ),
 CONSTRAINT [Check_Users_NormalizeEmail] CHECK ( NormalizeEmail LIKE '%_@__%.__%' )
);
GO


CREATE NONCLUSTERED INDEX [Index_Users_Guid] ON [dbo].[Users] 
 (
  [Guid] ASC
 )

GO


CREATE TABLE [dbo].[Requests]
(
 [Guid]      uniqueidentifier NOT NULL ,
 [UserGuid]  uniqueidentifier NOT NULL ,
 [Artists]   nvarchar(50) NOT NULL ,
 [Song]      nvarchar(50) NOT NULL ,
 [CreatedAt] datetime NOT NULL CONSTRAINT [DF_Requests_CreatedAt] DEFAULT GETDATE() ,
 [PlayedAt]  datetime NULL ,
 [IsSkiped]  int NOT NULL CONSTRAINT [DF_Requests_IsSkiped] DEFAULT 0 ,


 CONSTRAINT [PK_Requests] PRIMARY KEY CLUSTERED ([Guid] ASC),
 CONSTRAINT [FK_Users_Requests] FOREIGN KEY ([UserGuid])  REFERENCES [dbo].[Users]([Guid]) ON DELETE CASCADE ON UPDATE CASCADE,
 CONSTRAINT [Check_Requests_IsSkiped] CHECK ( IsSkiped >=0 AND IsSkiped<=1 ),
 CONSTRAINT [Check_Requests_PlayedAt] CHECK (PlayedAt >= CreatedAt)
);
GO


CREATE NONCLUSTERED INDEX [FK_Users_Requests] ON [dbo].[Requests] 
 (
  [UserGuid] ASC
 )

GO

CREATE NONCLUSTERED INDEX [Index_Requests_CreatedAt] ON [dbo].[Requests] 
 (
  [CreatedAt] ASC
 )

GO

CREATE NONCLUSTERED INDEX [Index_Requests_Guid] ON [dbo].[Requests] 
 (
  [Guid] ASC
 )

GO