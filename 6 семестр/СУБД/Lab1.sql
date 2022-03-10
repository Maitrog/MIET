--Тюльников Михаил ПИН-32--

--Task 12--
SELECT [CustNo]
      ,[Company]
      ,[Addr1]
      ,[Addr2]
      ,[City]
      ,[State]
      ,[Zip]
      ,[Country]
      ,[Phone]
      ,[FAX]
      ,[TaxRate]
      ,[Contact]
      ,[LastInvoiceDate]
  FROM [customer];
  
--Task 13--
SELECT [Company]
      ,[City]
  FROM [customer]
  ORDER BY [Company]; --Сортировка по алфавиту--

  --Task 14--
SELECT [Company]
      ,[City]
  FROM [customer]
  ORDER BY  [Company] DESC; --Сортировка по алфавиту в обратном порядке--

  --Task 15--
SELECT *
  FROM [customer]
  WHERE [State] = 'HI'; --Проверка названия штата--

  --Task 16--
SELECT *
  FROM [customer]
  WHERE [State] = 'HI' OR [State] = 'CA'; --Проверка названия штата; OR(ИЛИ) - объединение двух условий--

  --Task 17--
SELECT *
  FROM [customer]
  WHERE [LastInvoiceDate] BETWEEN '1.01.1995' AND '31.01.1995'; --Проверка диапазона дат с помощью BETWEEN--

  --Task 18--
SELECT *
  FROM [customer]
  WHERE [Company] LIKE 'B%s'; --Проверка названия с помощью LIKE--

  --Task 19--
SELECT *
  FROM [customer]
  WHERE [Zip] LIKE '9___0'; --Проверка почтового индекса с помощью LIKE--

  --Task 20--
SELECT [Company], [TaxRate] * 1.02 as NewTaxRate
  FROM [customer];

  --Task 21--
SELECT *
  FROM [customer];

  --Task 22--
SELECT [State], COUNT([State]) as CompanyNumbers --Подсчёт количества компаний с помощью COUNT--
  FROM [customer]
  GROUP BY [State]; --Группировка по штатам--

  --Task 23--
UPDATE customer
  SET [TaxRate] = [TaxRate] * 1.01;

  --Task 24--
SELECT *
  FROM [customer];
  --Task 25--
INSERT INTO [customer] (CustNo, LastInvoiceDate) VALUES (8191098, GETDATE()); --Добавляет строку в таблицу customers; GETDATE() - возвращает текущую дату--
  --Task 26--
DELETE [customer]
  WHERE [LastInvoiceDate] > '1.01.2011';

  --Task 27--
SELECT [customer].[CustNo]
      ,[customer].[Company]
	  ,[orders].[AmountPaid]
  FROM [customer] 
  LEFT JOIN [orders] --Соединяет таблицы с помощью LEFT JOIN--
  ON [customer].[CustNo] = [orders].[CustNo]
  WHERE [AmountPaid] < 1000;

  --Task 28--
SELECT [customer].[Company]
	  ,[employee].[FirstName]
	  ,[employee].[LastName]
	  ,[vendors].[VendorName]
  FROM [orders]
  LEFT JOIN [customer] ON [orders].[CustNo] = [customer].[CustNo]
  LEFT JOIN [employee] ON [orders].[EmpNo] = [employee].[EmpNo]
  LEFT JOIN [items] ON [orders].[OrderNo] = [items].[OrderNo]
  LEFT JOIN [parts] ON [items].[PartNo] = [parts].[PartNo]
  LEFT JOIN [vendors] ON [vendors].[VendorNo] = [parts].[VendorNo];

  --Task 29--
SELECT [customer].[Company]
	  ,[parts].[Description]
	  ,[items].[Qty]
  FROM [orders]
  LEFT JOIN [customer] ON [orders].[CustNo] = [customer].[CustNo]
  LEFT JOIN [employee] ON [orders].[EmpNo] = [employee].[EmpNo]
  LEFT JOIN [items] ON [orders].[OrderNo] = [items].[OrderNo]
  LEFT JOIN [parts] ON [items].[PartNo] = [parts].[PartNo]
  WHERE [items].[Qty] < 10;

  --Task 30--
SELECT [customer].[Company]
	  ,[parts].[Description]
	  ,[parts].[Cost]
  FROM [orders]
  LEFT JOIN [customer] ON [orders].[CustNo] = [customer].[CustNo]
  LEFT JOIN [employee] ON [orders].[EmpNo] = [employee].[EmpNo]
  LEFT JOIN [items] ON [orders].[OrderNo] = [items].[OrderNo]
  LEFT JOIN [parts] ON [items].[PartNo] = [parts].[PartNo]
  WHERE [parts].[OnHand] < [parts].[OnOrder]
  ORDER BY [OnHand] DESC, [OnOrder] ASC;