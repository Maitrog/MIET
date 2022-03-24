using lab3.Composite;

Airplane airplane = new();
FirstClass firstClass = new();
BuisnesClass buisnesClass = new();
EconomyСlass economyСlass = new();

airplane.Add(new Pilot());
airplane.Add(new Pilot());
for (int i = 0; i < 6; i++)
{
    airplane.Add(new Stewardess());
}
airplane.Add(firstClass);
while (!firstClass.IsReady())
{
    airplane.AddPassenger(firstClass, new Passenger());
}
airplane.Add(buisnesClass);
while (!buisnesClass.IsReady())
{
    airplane.AddPassenger(buisnesClass, new Passenger());
}
airplane.Add(economyСlass);
while (!economyСlass.IsReady())
{
    airplane.AddPassenger(economyСlass, new Passenger());
}

Console.WriteLine(airplane.Info());
Console.WriteLine(airplane.GetWeight());
airplane.RemoveBaggage();
Console.WriteLine(airplane.GetWeight());