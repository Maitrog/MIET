using Lab_6.Observer;

Teacher teacher1 = new ("1");
Teacher teacher2 = new ("2");
Teacher teacher3 = new ("3");
Teacher teacher4 = new ("4");
Teacher teacher5 = new ("5");

Deanery deanery = new();
teacher1.Attach(deanery);
teacher2.Attach(deanery);
teacher3.Attach(deanery);
teacher4.Attach(deanery);
teacher5.Attach(deanery);

Department department = new();
deanery.Attach(department);

teacher1.CreateReport();
teacher2.CreateReport();
teacher5.CreateReport();

deanery.CheckTeachersReports();

teacher1.CreateReport();
teacher2.CreateReport();
teacher3.CreateReport();
teacher4.CreateReport();
teacher5.CreateReport();