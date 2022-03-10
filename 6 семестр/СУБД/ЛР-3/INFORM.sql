
CREATE TABLE Children
(
	ChiName nvarchar(50)  NOT NULL ,
	Birthday datetime  NOT NULL 
	CONSTRAINT Check_Children_Birthday_1315037444
		CHECK  (Birthday <= GETDATE() ),
	EmpId numeric(6,0)  NOT NULL 
)
go


ALTER TABLE Children
	ADD CONSTRAINT XPK–≈¡≈ÕŒ  PRIMARY KEY  CLUSTERED (ChiName ASC,EmpId ASC)
go


CREATE TABLE Department
(
	DepId numeric(6, 0) IDENTITY (1,1) 
	CONSTRAINT Check_Department_DepId_2019008052
		CHECK  (DepId > 0 ),
	DepName nvarchar(20)  NOT NULL 
)
go


ALTER TABLE Department
	ADD CONSTRAINT XPKŒ“ƒ≈À PRIMARY KEY  CLUSTERED (DepId ASC)
go


CREATE TABLE Employee
(
	EmpId numeric(6,0) IDENTITY (1,1) 
	CONSTRAINT Check_Employee_EmpId_1179639378
		CHECK  (EmpId > 0 ),
	EmpName nvarchar(50)  NOT NULL ,
	Birthday datetime  NOT NULL 
	CONSTRAINT Check_Department_DepId_1713269525
		CHECK  (DepId > 0 ),
	Salary money  NULL 
	CONSTRAINT Default_Employee_Salary_1066290683
		 DEFAULT  30000,
	Post nvarchar(20)  NULL ,
	DepId numeric(6, 0)  NOT NULL 
)
go


ALTER TABLE Employee
	ADD CONSTRAINT XPK—À”∆¿Ÿ»… PRIMARY KEY  CLUSTERED (EmpId ASC)
go



ALTER TABLE Children
	ADD CONSTRAINT  FK_Employee_Children FOREIGN KEY (EmpId) REFERENCES Employee(EmpId)
		ON DELETE CASCADE
		ON UPDATE CASCADE
go



ALTER TABLE Employee
	ADD CONSTRAINT  FK_Department_Employee FOREIGN KEY (DepId) REFERENCES Department(DepId)
		ON DELETE CASCADE
		ON UPDATE CASCADE
go

