/* 
 * The MIT License
 *
 * Copyright 2020 The OpenNARS authors.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

bool NAR_Alien_Left_executed = false;
void NAR_Alien_Left()
{
    puts("NAR invoked left");
    NAR_Alien_Left_executed = true;
}
bool NAR_Alien_Right_executed = false;
void NAR_Alien_Right()
{
    puts("NAR invoked right");
    NAR_Alien_Right_executed = true;
}
bool NAR_Alien_Shoot_executed = false;
void NAR_Alien_Shoot()
{
    puts("NAR invoked shoot");
    NAR_Alien_Shoot_executed = true;
}
void NAR_Alien(long iterations)
{
    NAR_INIT();
    puts(">>NAR Alien1 start");
    NAR_AddOperation(Narsese_Term("^left"), NAR_Alien_Left); 
    NAR_AddOperation(Narsese_Term("^right"), NAR_Alien_Right); 
    NAR_AddOperation(Narsese_Term("^shoot"), NAR_Alien_Shoot); 
    double alien0X = 0.5;
    double defenderX = 0.5;
    double alienWidth = 0.18;
    int hits = 0;
    int shots = 0;
    int t=0;
    while(1)
    {
        if(t++ > iterations && iterations != -1)
        {
            break;
        }
        if(iterations == -1 && t%10000 == 0)
        {
            getchar();
        }
        fputs("\033[1;1H\033[2J", stdout); //POSIX clear screen
        bool cond1 = (defenderX <= alien0X - alienWidth);
        bool cond2 = (defenderX >  alien0X + alienWidth);
        if(cond1)
        {
            NAR_AddInputBelief(Narsese_Term("r0"));
        }
        else if(cond2)
        {
            NAR_AddInputBelief(Narsese_Term("l0"));
        }
        else
        {
            NAR_AddInputBelief(Narsese_Term("c0"));
        }
        NAR_AddInputGoal(Narsese_Term("s0"));
        if(NAR_Alien_Shoot_executed)
        {
            NAR_Alien_Shoot_executed = false;
            shots++;
            if(!cond1 && !cond2)
            {
                hits++;
                NAR_AddInputBelief(Narsese_Term("s0"));
                alien0X = ((double)(myrand() % 1000)) / 1000.0;
            }
        }
        if(NAR_Alien_Left_executed)
        {
            NAR_Alien_Left_executed = false;
            defenderX = MAX(0.0, defenderX-0.1);
        }
        if(NAR_Alien_Right_executed)
        {
            NAR_Alien_Right_executed = false;
            defenderX = MIN(1.0, defenderX+0.1);
        }
        printf("shots=%d hits=%d ratio=%f time=%d\n", shots, hits, (float) (((float) hits) / ((float) shots)), t);
        //nanosleep((struct timespec[]){{0, 10000000L}}, NULL); //POSIX sleep
        //NAR_Cycles(10);
    }
}
