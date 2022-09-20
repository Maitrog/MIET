using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Text;

namespace lab2
{
    internal class State: IComparable<State>
    {
        public string Name { get; }
        public State(string name)
        {
            Name = name;
        }

        public static bool operator ==(State a, State b)
        {
            return a.Name == b.Name;
        }

        public static bool operator !=(State a, State b)
        {
            return !(a == b);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Name);
        }

        public override bool Equals(object obj)
        {
            if (!(obj is State))
            {
                return false;
            }
            return object.Equals(Name, (obj as State).Name);
        }

        public int CompareTo([AllowNull] State other)
        {
            return string.Compare(Name, other.Name, StringComparison.OrdinalIgnoreCase);
        }
    }
}
