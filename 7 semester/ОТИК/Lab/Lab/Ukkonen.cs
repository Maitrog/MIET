using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab
{
    internal class Ukkonen
    {
        const int MAXN = 100000;
        string s;
        int n;

        Node[] t = new Node[MAXN];
        int sz;

        State ptr = new State(0, 0);

        public Ukkonen(string inputStr)
        {
            s = inputStr;
            n = inputStr.Length;
            for (int i = 0; i < MAXN; i++)
            {
                t[i] = new Node();
            }
        }

        State Go(State st, int l, int r)
        {
            while (l < r)
                if (st.Pos == t[st.V].Len)
                {
                    st = new State(t[st.V].Get(s[l]), 0);
                    if (st.V == -1) return st;
                }
                else
                {
                    if (s[t[st.V].L + st.Pos] != s[l])
                        return new State(-1, -1);
                    if (r - l < t[st.V].Len - st.Pos)
                        return new State(st.V, st.Pos + r - l);
                    l += t[st.V].Len - st.Pos;
                    st.Pos = t[st.V].Len;
                }
            return st;
        }

        int Split(State st)
        {
            if (st.Pos == t[st.V].Len)
                return st.V;
            if (st.Pos == 0)
                return t[st.V].Par;
            Node v = t[st.V];
            int id = sz++;
            t[id] = new Node(v.L, v.L + st.Pos, v.Par);
            //t[v.Par].Get(s[v.L]) = id;
            t[v.Par].Set(s[v.L], id);
            //t[id].Get(s[v.L + st.Pos]) = st.V;
            t[id].Set(s[v.L + st.Pos], st.V);
            t[st.V].Par = id;
            t[st.V].L += st.Pos;
            return id;
        }

        int GetLink(int V)
        {
            if (t[V].Link != -1) return t[V].Link;
            if (t[V].Par == -1) return 0;
            int to = GetLink(t[V].Par);
            return t[V].Link = Split(Go(new State(to, t[to].Len), t[V].L + (t[V].Par == 0 ? 1 : 0), t[V].R));
        }

        void TreeExtend(int Pos)
        {
            for (; ; )
            {
                State nptr = Go(ptr, Pos, Pos + 1);
                if (nptr.V != -1)
                {
                    ptr = nptr;
                    return;
                }

                int mid = Split(ptr);
                int leaf = sz++;
                t[leaf] = new Node(Pos, n, mid);
                //t[mid].Get(s[Pos]) = leaf;
                t[mid].Set(s[Pos], leaf);

                ptr.V = GetLink(mid);
                ptr.Pos = t[ptr.V].Len;
                if (mid == 0) break;
            }
        }

        public void BuildTree()
        {
            sz = 1;
            for (int i = 0; i < n; ++i)
                TreeExtend(i);
        }
    }

    internal class Node
    {
        public int L, R, Par, Link;
        public Dictionary<char, int> Next;

        public Node(int l = 0, int r = 0, int par = -1)
        {
            L = l;
            R = r;
            Par = par;
            Link = -1;
            Next = new Dictionary<char, int>();
        }
        public int Len
        {
            get
            {
                return R - L;
            }
        }
        public int Get(char c)
        {
            if (!Next.TryGetValue(c, out var _))
            {
                Next[c] = -1;
            }
            return Next[c];
        }
        public void Set(char c, int value)
        {
            if (!Next.TryGetValue(c, out var _))
            {
                Next[c] = -1;
            }
            Next[c] = value;
        }
    }

    public class State
    {
        public int V { get; set; }
        public int Pos { get; set; }
        public State(int v, int pos)
        {
            V = v;
            Pos = pos;
        }
    }
}
