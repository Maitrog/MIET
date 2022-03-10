using lab_2.Builder;

Station station = new Station();
TaxiBuilder tBuilder = new TaxiBuilder();

station.Builder = tBuilder;
station.CreateBoard();
var tBoard = tBuilder.GetBoard();
Console.WriteLine(tBoard.IsReady());

foreach (var p in tBoard.Passengers)
{
    Console.WriteLine(p.ToString());
}
Console.WriteLine("------------------------------");

BusBuilder busBuilder = new BusBuilder();
station.Builder = busBuilder;
station.CreateBoard();
var busBoard = busBuilder.GetBoard();

Console.WriteLine(busBoard.IsReady());
foreach (var p in busBoard.Passengers)
{
    Console.WriteLine(p.ToString());
}
Console.WriteLine("------------------------------");


//station.Builder = busBuilder;
//station.CreateBoard();
//var busBoard = busBuilder.GetBoard();

//Console.WriteLine(busBoard.IsReady());
//foreach (var p in busBoard.Passengers)
//{
//    Console.WriteLine(p.ToString());
//}
//Console.WriteLine("------------------------------");

IntercityBusBuilder intercityBusBuilder = new IntercityBusBuilder();
station.Builder = intercityBusBuilder;
station.CreateBoard();
var intercityBusBoard = intercityBusBuilder.GetBoard();

Console.WriteLine(busBoard.IsReady());
foreach (var p in intercityBusBoard.Passengers)
{
    Console.WriteLine(p.ToString());
}
