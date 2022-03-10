﻿using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace lab2
{
    class StudentEnumerator: IEnumerator
    {
        private ArrayList subject = new ArrayList();
        private int position = -1;
        public StudentEnumerator(ArrayList _exam, ArrayList _test)
        {
            foreach (Exam i in _exam)
                foreach (Test j in _test)
                    if (i.Name == j.Name)
                        subject.Add(i);
        }

        public object Current
        {
            get
            {
                if (position == -1 || position >= subject.Count)
                    throw new InvalidOperationException();
                return subject[position];
            }
        }

        public bool MoveNext()
        {
            if(position < subject.Count -1)
            {
                position++;
                return true;
            }
            return false;
        }

        public void Reset()
        {
            position = -1;
        }
    }
}
